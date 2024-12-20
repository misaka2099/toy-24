cmake_minimum_required(VERSION 3.10)
project(MyProject) 
set(CMAKE_CXX_STANDARD 17)          
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exes)

find_package(OpenGL REQUIRED)
add_executable(MyExecutable 
    expression.cpp
    fraction.cpp
    main.cpp
    varify.cpp
    data.cpp
    imgui_draw.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
)
include_directories (${PROJECT_SOURCE_DIR}/libs/glfw/include)
find_library(glfw glfw3 HINTS ${PROJECT_SOURCE_DIR}/libs/glfw/lib-mingw-w64)
target_link_libraries(MyExecutable PRIVATE ${glfw} OpenGL::GL)