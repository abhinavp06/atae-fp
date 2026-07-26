set(ATAE_FP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/output/")

# OSCILLATORS
add_executable(sine_wave_playground "oscillators/sine_oscillator_playground.cpp")
target_link_libraries(sine_wave_playground PRIVATE atae_fp)
target_compile_definitions(sine_wave_playground PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

add_executable(square_wave_playground "oscillators/square_oscillator_playground.cpp")
target_link_libraries(square_wave_playground PRIVATE atae_fp)
target_compile_definitions(square_wave_playground PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

add_executable(saw_wave_playground "oscillators/saw_oscillator_playground.cpp")
target_link_libraries(saw_wave_playground PRIVATE atae_fp)
target_compile_definitions(saw_wave_playground PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

# NOISE
add_executable(white_noise_playground "noise/white_noise_playground.cpp")
target_link_libraries(white_noise_playground PRIVATE atae_fp)
target_compile_definitions(white_noise_playground PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")