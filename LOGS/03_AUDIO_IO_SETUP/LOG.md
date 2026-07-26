# Introduction
<b>--- 26-07-2026 09:32 SUNDAY ---</b>
# Ideas
## <b>--- 26-07-2026 09:32 SUNDAY ---</b>
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
1. 10.23 -> Shifted a few files around and started implementing some CMake files
    1. Split CMake into independent targets (library, playground, tests) with the library being the only shared dependency.
    1. Build and run unit tests by default, but allow both behaviors to be toggled through CMake options.
1. 10.44 -> Now start with implementing header files and cpp files
1. 11.29 -> Implemented sine wave
1. 11.45 -> Done with Saw and Square
1. 12.02 -> Done with white noise.
1. 14.07  -> Now back to CMake setup.
    1. 14.47 -> Went through so many challenges
        1. Finding out that OUTPUT_DIR is a pointer
        1. Then figuring out how to add OUTPUT_DIR and "sine_wave" as a string together in fstream.. ewnded up creating a variable for it
        1. Manually seeing my file explorer to hunt for the output
        1. First it was in the build directory's output directory. Changed it to the root output direcotry by the output paths in CMake (playground and test)
        1. Also forgot how to write a simple cout statement
        1. Figured out how to actually build with CMake and where and how my directories, sub directories, outputs and tests are located and created.
1. 15.09 -> Initial idea: 
    1. To implement an Audio Buffer i first need to know how audio is processed digitally. 
    1. Why is it processed in buffers. 
    1. Are there buffers in C++? 
    1. How are buffers implemented in C++? 
    1. Then finally merge everything to create an audio buffer class and integrate it with the current playground/ tests and the core classes.
1. 15.12 -> How is Audio processed digitally? (Radikal Doodz - Definitely On)
    1. Very basic concepts. Sampling, Quantization, etc. Move to next.
1. 15.13 -> Why is it processed in buffers?
    1. okay - basically time given to process data
1. 15.14 -> C++ buffers
    1. 15.16 -> Trying to find how to implement buffers made up of double values
        1. it's just a vector of doubles
1. 15.17 -> Audio Buffer Class
    1. 15.21 -> I have the basdic properties down. Now I'm debating if I should expose the buffer via any methods? I mean I know I have to but I'm debating ways.
        1. If I expose the buffer simply as a public variable anyone can manipulate it. 
        1. But that's okay since the job of the buffer is to simply provide.
        1. But the buffer needs to know it's length. So, for memory safety I should ask for the duration. That same function should initialize a buffer.
            1. While this is nice, how do I stop the usage of the buffer before the setDuration function is called? Need to explore.
                1. 15.26 -> I could have a default buffer value like I did for sample_rate_.
                1. 15.27 -> Think of more ways before weighing pros and cons. OR weigh them now. Go now.
                    1. PROS:
                        1. don't need to worry about any garbage user.. no need to worry about point memory safety above
                        1. anyone who owns a buffer should have access to the variable. But it has to be protected. Not public. I dont want any owner to update it directly. They have to go through the instance.
                            1. 15.30 -> let me understand public vs protected vs private once
                                1. yeah.. protected
                    1. CONS:
                        1. I don't see any cons now except that it feels a little bare metal
                            1. Let me think of this.. bare metal vs abstraction?
                                1. 15.33 -> 
                                    1. If I have an exposed variable.. I have more freedom.
                                    1. If I abstract, I, as a mantainer have to do more work. No freedom. Can cause frustration in implementing
                                    1. Maybe for critical code, bare metal is better?
                    1. 15.35 -> Verdict: Bare metal is nice.
    1. 15.42 -> There are so many patterns I can see with the class I am creating and how everything is declared. However, I will do this in my free time. TODO: Microoptimizing a class that I have implemented.
        1. Going back and forth with [ChatGPT Chat](https://chatgpt.com/share/6a65de78-66cc-83e8-9256-48eaee60e434) and it has a good argument for abstraction. TODO: Use this ChatGPT conversation as part of the microoptimization
1.15.52 -> Integrating AudioBuffer with one of the implemented classes. Pick white noise for now.
    1. 15.57 -> After some thinking, I looked into the atae repository's audio_buffer.h and realised that a struct makes more sense.
        1. I could feel the resistance while trying to fit my AudioBuffer class into the White noise generator. A struct makes so much mroe sense.
        1. It fits my "bare metal" and "freedom" approach too. 
        1. Now I can either take a direction here of making this a well guarded libraryt or go bare metal right now with structs, later phase challenges and then refactor.
        1. I choose the latter.
        1. 16.02 -> In fact, I'll create a struct and only store a vector in it for now. No need for a sample rate either. Will tackle when required.
        1. 16.07 -> TODO: integrate AudioBuffer in the playground/ files
1. 16.12 -> Now, actual audio output for white_noise
    1. For this, I'll first need to find out how to convert my buffer to an audio file.
    1. Then update the playground/noise/white_noise.cpp file.
    1. But to test the audio I'll need the updated playground file. playground/ first.
    1. 
### C++ Findings
1. `virtual` is used to define functions in a base class which are expected to be redefined in derived classes
1. A base class with virtual functions should have a virtual destructor so derived objects are destroyed correctly through a base pointer.
    1. Example: If `Oscillator* osc = new SineOscillator();`, then `delete osc;` should call both the `SineOscillator` destructor and the `Oscillator` destructor.
1. A virtual function with `= 0` is a pure virtual function, making the class abstract and forcing derived classes to implement it.
    1. Analogy: An `Animal` can't "speak" on its own, but a `Dog` or `Cat` can. Similarly, an `Oscillator` can't generate a waveform on its own, but a `SineOscillator`, `SquareOscillator`, etc. can.
1. If header includes a library, no need to include it again in the cpp implementation.
1. Constructor initializer lists initialize class members before the constructor body runs. Writing `member_(value)` inside the constructor body attempts to call the object like a function instead of initializing it.
    1. Analogy: A constructor initializer list is like setting a person's name while creating their ID card; the constructor body is like changing their name after the ID card already exists.
1. 14.14 -> `CMAKE_SOURCE_DIR` always refers to the top-level directory where the first `CMakeLists.txt` was called, not the directory of the current CMake file.
    1. Example: If `CORE/CMakeLists.txt` is the root file, then `${CMAKE_SOURCE_DIR}` points to `CORE/` even when used inside `playground/CMakeLists.txt` or `tests/CMakeLists.txt`.
1. 16.10 -> Use clear() + reserve() when you want to build the buffer by push_back()
    1. clear() removes any old samples before generating new ones.
    1. reserve(sample_count) allocates space up front, so repeated push_back() is efficient.
    1. resize() is not needed here because it creates actual elements, which you would then overwrite or accidentally append to.
    1. This pattern keeps the buffer size correct and avoids the double-sizing bug.