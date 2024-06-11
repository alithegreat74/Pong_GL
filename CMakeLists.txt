cmake_minimum_required(VERSION 3.5)

project(Pong)

# Set the directories for your third-party libraries
set(thirdpartyDir ${CMAKE_SOURCE_DIR}/Thirdparty)

# Include directories for header files
include_directories(
    "${thirdpartyDir}/GLAD"
    "${thirdpartyDir}/ImGUI"
    "${thirdpartyDir}/glm"
    "${thirdpartyDir}/stb_image"
    "${thirdpartyDir}/GLFW"

)

# Add subdirectory for stb_image (assuming it has its own CMakeLists.txt)
add_subdirectory("${thirdpartyDir}/stb_image")

# Collect ImGui source files
set(ImGUI_Dir "${thirdpartyDir}/ImGUI")
file(GLOB_RECURSE ImGUI_SRC_FILES ${ImGUI_Dir}/*.cpp)

# Collect all source files in the src folder
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# Add glad source file
list(APPEND SRC_FILES "${thirdpartyDir}/GLAD/glad.c")

# Add main source file (make sure it's in the src directory)
list(APPEND SRC_FILES "${CMAKE_SOURCE_DIR}/main.cpp")

# Create the executable
add_executable(pong ${SRC_FILES} ${ImGUI_SRC_FILES})

# Link the static libraries
set(glfw_lib "${thirdpartyDir}/src/glfw3.lib")
target_link_libraries(pong ${glfw_lib} stb_image)
