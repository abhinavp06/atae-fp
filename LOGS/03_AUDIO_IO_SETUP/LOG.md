# Introduction
<b>--- 26-07-2026 09:32 SUNDAY ---</b>
# Ideas
## Idea 1 --- 26-07-2026 09:32 ---
Integrate generation of Audio files so that I can hear my output instead of CSVs.
<br/><br/>
### TODO
1. First setup this repository like a proper audio library.
1. Then create classes which will add structure.
1. Look into how I can generate Audio Buffers, etc.
1. Implement audio buffers and test output.
1. Vibecode a UI which let's me see my output in a CSV format and plays the audio output with a waveform visualization as well.
1. Unit tests?
### Implementation Notes
1. After searching for a while, I decided I'll need to implement a static library.
    1. Also, read 
        1. [this](https://medium.com/@gs8763076/the-complete-guide-to-c-libraries-create-compare-and-understand-how-dynamic-linking-works-a403d947dc27)
        1. [this](https://medium.com/@jacob.m.adams/creating-shared-static-libraries-with-cmake-7e5ae160c59d)
        1. [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
1. 10:23 -> Shifted a few files around and started implementing some CMake files
    1. Split CMake into independent targets (library, playground, tests) with the library being the only shared dependency.
    1. Build and run unit tests by default, but allow both behaviors to be toggled through CMake options.
1. 10.44 -> Now start with implementing header files and cpp files
1. 11.29 -> Implemented sine wave
1. 11.45 -> Done with Saw and Square
### C++ Findings
1. `virtual` is used to define functions in a base class which are expected to be redefined in derived classes
1. A base class with virtual functions should have a virtual destructor so derived objects are destroyed correctly through a base pointer.
    1. Example: If `Oscillator* osc = new SineOscillator();`, then `delete osc;` should call both the `SineOscillator` destructor and the `Oscillator` destructor.
1. A virtual function with `= 0` is a pure virtual function, making the class abstract and forcing derived classes to implement it.
    1. Analogy: An `Animal` can't "speak" on its own, but a `Dog` or `Cat` can. Similarly, an `Oscillator` can't generate a waveform on its own, but a `SineOscillator`, `SquareOscillator`, etc. can.
1. If header includes a library, no need to include it again in the cpp implementation.
1. Constructor initializer lists initialize class members before the constructor body runs. Writing `member_(value)` inside the constructor body attempts to call the object like a function instead of initializing it.
    1. Analogy: A constructor initializer list is like setting a person's name while creating their ID card; the constructor body is like changing their name after the ID card already exists.