CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
project(opengl)

add_executable(main 
./Source/main.cpp
./Source/init.cpp)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(main ${SDL2_LIBRARIES} GLEW::GLEW)
file(COPY Res DESTINATION ${CMAKE_BINARY_DIR})
