set(ATAE_FP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/output")

# OSCILLATORS
add_executable(sine_wave_test oscillators/sine_osc.cpp)
target_link_libraries(sine_wave_test PRIVATE atae_fp)
target_compile_definitions(sine_wave_test PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

add_executable(square_wave_test oscillators/square_osc.cpp)
target_link_libraries(square_wave_test PRIVATE atae_fp)
target_compile_definitions(square_wave_test PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

add_executable(saw_wave_test oscillators/saw_osc.cpp)
target_link_libraries(saw_wave_test PRIVATE atae_fp)
target_compile_definitions(saw_wave_test PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")

# NOISE
add_executable(white_noise_test noise/white_noise.cpp)
target_link_libraries(white_noise_test PRIVATE atae_fp)
target_compile_definitions(white_noise_test PRIVATE 
    OUTPUT_DIR="${ATAE_FP_OUTPUT_DIR}")