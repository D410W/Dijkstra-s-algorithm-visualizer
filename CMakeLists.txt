# CMakeLists.txt
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Dijkstras_Algorithm LANGUAGES CXX)

# (Optional but recommended) Set the C++ standard
# This ensures consistency across different compilers.
set(CMAKE_CXX_STANDARD 17) # For C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # CMake will error if C++17 is not available
 
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")

list(APPEND CMAKE_PREFIX_PATH "/home/thales/.local/share/vcpkg/installed/x64-linux")

find_package(jsoncpp CONFIG REQUIRED)

cmake_policy(SET CMP0072 NEW)

add_executable(executable src/main.cpp src/simulation.cpp)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/")

target_compile_options(executable PRIVATE -Wall -pedantic)

# (Optional) Link libraries if your executable needs them
# For example, if you were using an external library like Boost, you'd link it here.
# target_link_directories(executable PUBLIC /usr/local/lib)

# Link SFML static libraries and dependencies
target_link_libraries(executable PRIVATE
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    X11
    Xrandr
    Xcursor
    Xi
    udev
    freetype
    GL
    JsonCpp::JsonCpp
)

# (Optional) If you have headers in a separate 'include' directory, tell CMake where to find them.
# This assumes your headers are in a directory named 'include' at the project root.
# target_include_directories(my_executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
