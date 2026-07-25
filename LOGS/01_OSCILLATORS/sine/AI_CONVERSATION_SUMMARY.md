# Building a Digital Sine Wave Oscillator
*My journey of understanding oscillators from first principles.*

---

# The Goal

Generate a sequence of samples representing a sine wave.

- **X-axis** → Time (Samples)
- **Y-axis** → Amplitude (-1.0 to +1.0)

At first, I thought I had to manually construct the wave by changing the amplitude every sample.

I eventually realized that this is **not** how oscillators work.

---

# Initial Thought Process (Incorrect)

I initially thought something like this:

```cpp
sample += constant;
```

or

```cpp
sample = previous_sample + phase_increment;
```

and then manually flip the sign after reaching π.

```cpp
if (phase == π)
    phase *= -1;
```

### Why this is wrong

Adding a constant every sample produces a **linear** relationship.

```
/
/
/
/
/
```

If I repeatedly change the direction, I get something similar to:

```
/\/\/\/\/\
```

which resembles a triangle wave.

A sine wave is **not linear**.

Its slope changes continuously.

---

# Analogy 1 - Driving a Car

Imagine driving.

Driving at a constant speed in a straight line:

```
------------
```

Adding a constant every sample behaves similarly.

Now imagine constantly turning the steering wheel.

```
~~~~~~~~~~~~~
```

That curved path resembles a sine wave.

The conclusion:

> A sine wave cannot be built by repeatedly adding the same amount.

---

# The Biggest Realization

Instead of asking:

> "How do I construct a sine wave?"

The correct question is:

> "Where am I in the current cycle?"

The answer to that question is called **Phase**.

---

# Analogy 2 - Walking Around a Circular Track

Imagine walking around a perfectly circular running track.

```
        π/2

   π             0

      3π/2
```

Your position on this track is called **Phase**.

Phase simply answers:

> "Where am I?"

It does **not** answer:

- Is the signal positive?
- Is the signal negative?
- Is it rising?
- Is it falling?

Those are all consequences of the phase.

---

# Analogy 3 - The Unit Circle

Imagine a point rotating around a unit circle.

```
        y (+1)
         ↑
         ●
      /     \
     /       \
----●---------●----→ x
   π           0
```

The point has coordinates:

```
(x, y)
```

As it rotates:

- x-coordinate follows cosine
- y-coordinate follows sine

Therefore,

```cpp
amplitude = sin(phase);
```

Notice something beautiful.

The oscillator never asks:

> Should the amplitude be positive?

or

> Should it be negative?

The mathematics already knows.

---

# Analogy 4 - The Runner

Imagine a runner on a circular track.

There are two independent concepts.

### Phase

Where is the runner?

Example:

```
45°
180°
300°
```

### Frequency

How fast is the runner moving?

Examples:

```
1 lap/sec
10 laps/sec
441 laps/sec
```

These are different concepts.

Phase answers:

> Where am I?

Frequency answers:

> How quickly am I moving?

---

# Understanding Frequency

Suppose

```cpp
frequency = 441 Hz;
```

This means

```
441 complete circles every second.
```

NOT

```
441 samples
```

The sample rate determines the number of samples.

```
sample_rate = 44100 samples/sec
```

So in one second:

```
441 circles
44100 samples
```

---

# Deriving Phase Increment

One complete circle equals

```
2π radians
```

Each second we need

```
441 circles
```

Each second contains

```
44100 samples
```

Therefore

```cpp
phase_increment =
    (2π radians)
    ×
    (441 circles/sec)
    ÷
    (44100 samples/sec)
```

which becomes

```cpp
phase_increment =
    2 * π * frequency / sample_rate;
```

Code:

```cpp
double phase_increment =
    2 * std::numbers::pi *
    WAVE_FREQUENCY /
    SAMPLE_RATE;
```

---

# The Oscillator

The oscillator only remembers one thing.

```cpp
double phase;
```

Nothing else.

Every sample:

```cpp
sample = sin(phase);
```

Then move around the circle.

```cpp
phase += phase_increment;
```

Entire loop:

```cpp
double phase = 0.0;

for (int i = 0; i < sample_count; i++)
{
    samples[i] = std::sin(phase);

    phase += phase_increment;
}
```

Notice there is

- no sign flipping
- no previous sample
- no manual handling of positive/negative values

---

# Wrapping the Phase

Eventually

```
phase > 2π
```

Initially I wrote

```cpp
if (phase >= 2 * std::numbers::pi)
{
    phase = 0;
}
```

This is almost correct but loses information.

Suppose

```
phase = 6.30

2π = 6.28318
```

The oscillator is actually

```
0.01682 radians
```

into the next revolution.

Resetting to zero discards that information.

Correct implementation:

```cpp
if (phase >= 2 * std::numbers::pi)
{
    phase -= 2 * std::numbers::pi;
}
```

---

# Analogy 5 - Walking Around a Circular Track

Suppose the circular track is

```
100 meters
```

You walk

```
103 meters
```

Where are you?

Not

```
0 meters
```

You're actually

```
3 meters
```

into the next lap.

Exactly the same thing happens with phase.

---

# Final Oscillator

```cpp
#include <iostream>
#include <numbers>
#include <cmath>

const double SAMPLE_RATE = 44100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 441.0;

int main()
{
    int sample_count =
        static_cast<int>(SAMPLE_RATE) *
        WAVE_DURATION_S;

    double samples[sample_count] = {0};

    double phase = 0.0;

    double phase_increment =
        2 * std::numbers::pi *
        WAVE_FREQUENCY /
        SAMPLE_RATE;

    for (int i = 0; i < sample_count; i++)
    {
        samples[i] = std::sin(phase);

        phase += phase_increment;

        if (phase >= 2 * std::numbers::pi)
        {
            phase -= 2 * std::numbers::pi;
        }
    }

    return 0;
}
```

---

# What I Learned

Initially, I thought an oscillator **generated amplitudes**.

I now understand that it **stores a phase**.

```
phase
   │
   ▼
sin()
   │
   ▼
amplitude
```

Every sample follows exactly two steps:

```cpp
sample = std::sin(phase);

phase += phase_increment;
```

Everything else naturally emerges from this.

---

# The Biggest Takeaway

An oscillator is **not drawing a sine wave.**

It is simply

> Moving around a circle at a constant angular speed and reading the vertical coordinate.

The sine wave is just a consequence of circular motion.