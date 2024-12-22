cmake_minimum_required(VERSION 3.10)
project(MyProject) 
set(CMAKE_CXX_STANDARD 17)          
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_EXE_LINKER_FLAGS " -static")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exes)
aux_source_directory(src/. SRC_LIST_1)
aux_source_directory(imgui/. SRC_LIST_2)
find_package(OpenGL REQUIRED)
add_executable(MyExecutable 
    ${SRC_LIST_1}
    ${SRC_LIST_2}
)
include_directories (${PROJECT_SOURCE_DIR}/libs/glfw/include)
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/imgui)
find_library(glfw glfw3 HINTS ${PROJECT_SOURCE_DIR}/libs/glfw/lib-mingw-w64)
target_link_libraries(MyExecutable PRIVATE ${glfw} OpenGL::GL)