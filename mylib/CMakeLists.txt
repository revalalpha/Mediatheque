project(mylib)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
    ${HEADER_DIR}/LibrarySystem.h
    ${HEADER_DIR}/Client.h
    ${HEADER_DIR}/Console.h
)

set(SOURCES
    ${SOURCE_DIR}/LibrarySystem.cpp
    ${SOURCE_DIR}/Client.cpp
    ${SOURCE_DIR}/Console.cpp
)

add_library(${PROJECT_NAME}
STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME}
PUBLIC 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")

