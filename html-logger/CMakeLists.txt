project(html-logger)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(SRC_FILES
    html_body.cpp
    html_doc.cpp
    html_head.cpp
    html_logger.cpp
    html_table.cpp
    html_tag.cpp)

set(HDR_FILES
    html_body.h
    html_doc.h
    html_head.h
    html_logger.h
    html_table.h
    html_tag.h)

set(FILES ${SRC_FILES} ${HDR_FILES})
add_executable(${PROJECT_NAME} ${FILES})
