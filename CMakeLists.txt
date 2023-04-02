cmake_minimum_required(VERSION 3.0)

#set c++ standard 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set project name
project(OpenglLearn)

#set source files
set(SOURCE_FILES main.cpp core/gpu.cpp core/core_structure.cpp core/img.cpp core/shader.cpp core/os.cpp core/mesh.cpp driver/iron_gl.cpp driver/glad.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#add imgui
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

#set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/driver ${CMAKE_CURRENT_SOURCE_DIR}/base )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)


#link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw imgui)
