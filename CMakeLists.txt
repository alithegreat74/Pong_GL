cmake_minimum_required(VERSION 3.5)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Pong)

add_executable(pong "main.cpp")

include(FetchContent)

# GLFW Dependency declare
FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
)

FetchContent_Declare(
	GLEW
	GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
	GIT_TAG glew-cmake-2.1.0
)
# Download and make GLFW available
FetchContent_MakeAvailable(GLFW)
FetchContent_MakeAvailable(GLEW)

target_link_libraries(pong PRIVATE glfw)
# Include directories for GLEW
target_include_directories(pong PRIVATE ${glew_SOURCE_DIR}/include)

# Link GLFW and GLEW to pong
target_link_libraries(pong PRIVATE glew )