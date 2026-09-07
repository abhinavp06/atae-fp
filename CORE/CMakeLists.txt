cmake_minimum_required(VERSION 3.20)

project(
    atae_fp
    VERSION 0.1.0
    DESCRIPTION "Hobby DSP Library"
    LANGUAGES CXX
)

# -----------------------------------------------------------------------------
# Global Settings
# -----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(ATAE_FP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/output/")

# -----------------------------------------------------------------------------
# Build Options
# -----------------------------------------------------------------------------

option(BUILD_PLAYGROUND "Build playground executable" ON)
option(BUILD_TESTS "Build unit tests" ON)
option(RUN_TESTS_AFTER_BUILD "Run unit tests after a successful build" ON)

# -----------------------------------------------------------------------------
# Library
# -----------------------------------------------------------------------------

add_library (atae_fp
    # AUDIO FILE
    src/io/audio_file.cpp

    # OSCILLATORS
    src/oscillators/oscillator.cpp
    src/oscillators/sine_oscillator.cpp
    src/oscillators/square_oscillator.cpp
    src/oscillators/saw_oscillator.cpp

    # NOISE
    src/noise/white_noise.cpp
    src/noise/pink_noise.cpp
    
    #MIXER
    src/mixer/mixer.cpp
    
    # FILTERS
    src/filters/naive_filter.cpp
    src/filters/one_pole_lpf.cpp 

    # ENVELOPE
    src/envelope/adsr.cpp
)

target_include_directories(atae_fp 
    PUBLIC 
        include

    PRIVATE
        tools
)
# -----------------------------------------------------------------------------
# Playground
# -----------------------------------------------------------------------------

if(BUILD_PLAYGROUND)
    add_subdirectory(playground)
endif()

# -----------------------------------------------------------------------------
# Unit Tests
# -----------------------------------------------------------------------------

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()