cmake_minimum_required(VERSION 3.5.0)

project(PONG)


set(ThirdParty_Dir "${CMAKE_SOURCE_DIR}/Thirdparty")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
#Getting all the c and cpp files needed in the project
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c")
list(APPEND SRC_FILES "main.cpp")
list(APPEND SRC_FILES "${ThirdParty_Dir}/glad/glad.c")
list(APPEND SRC_FILES "${ThirdParty_Dir}/stb_image/stb_image.cpp")
file(GLOB_RECURSE ImGUI_SRC "${ThirdParty_Dir}/ImGui/*.cpp" "${ThirdParty_Dir}/ImGui/*.c")
list(APPEND SRC_FILES ${ImGUI_SRC})

#adding the include directories
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${ThirdParty_Dir}"
	
)

#Setting the texture files
file(GLOB TEXTURE_FILES "${SRC_DIR}/Textures/*.png")

foreach(TEXTURE_FILE ${TEXTURE_FILES})
    get_filename_component(FILE_NAME ${TEXTURE_FILE} NAME)
    configure_file(${TEXTURE_FILE} "${CMAKE_BINARY_DIR}/src/Textures/${FILE_NAME}" COPYONLY)
endforeach()

#setting the shader files
file(GLOB SHADER_FILES "${SRC_DIR}/Shaders/*.glsl")
foreach(SHADER_FILE ${SHADER_FILES})
	get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
	configure_file(${SHADER_FILE} "${CMAKE_BINARY_DIR}/src/Shaders/${FILE_NAME}" COPYONLY)
endforeach()

#setting the font files
file(GLOB FONT_FILES "${SRC_DIR}/Fonts/*.ttf")
foreach(FONT_FILE ${FONT_FILES})
	get_filename_component(FILE_NAME ${FONT_FILE} NAME)
	configure_file(${FONT_FILE} "${CMAKE_BINARY_DIR}/src/Fonts/${FILE_NAME}" COPYONLY)
endforeach()

#setting the audio files
file(GLOB AUDIO_FILES "${SRC_DIR}/Audio/*.mp3" "${SRC_DIR}/Audio/*.wav")
foreach(AUDIO_FILE ${AUDIO_FILES})
	get_filename_component(FILE_NAME ${AUDIO_FILE} NAME)
	configure_file(${AUDIO_FILE} "${CMAKE_BINARY_DIR}/src/Audio/${FILE_NAME}" COPYONLY)
endforeach()

add_executable(PONG ${SRC_FILES} "src/Collision.h"  )


target_link_libraries(PONG "${ThirdParty_Dir}/GLFW/glfw3.lib" "${ThirdParty_Dir}/irrKlang/irrKlang.lib")


add_custom_command(TARGET PONG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${ThirdParty_Dir}/irrKlang/irrKlang.dll"
    "${ThirdParty_Dir}/irrKlang/ikpMP3.dll"
    "${ThirdParty_Dir}/irrKlang/ikpFlac.dll"
    $<TARGET_FILE_DIR:PONG>)