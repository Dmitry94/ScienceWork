project(graph-paint-demo)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(SRC_FILES
    graph.cpp
    gen_new_paint.cpp
    main.cpp)

set(HDR_FILES
    gpp_amputation.h
    gpp_generator.h
    gpp_solver.h
    gpp_structs.h
    graph.h)

set(FILES ${SRC_FILES} ${HDR_FILES})
add_executable(${PROJECT_NAME} ${FILES})
target_link_libraries(${PROJECT_NAME} pbab)
