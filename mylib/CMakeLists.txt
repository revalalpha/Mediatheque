project(mylib)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
    ${HEADER_DIR}/LibrarySystem.h
    ${HEADER_DIR}/Client.h
    ${HEADER_DIR}/Console.h
    ${HEADER_DIR}/Media.h
    ${HEADER_DIR}/Film.h
    ${HEADER_DIR}/Book.h
    ${HEADER_DIR}/Game.h
    ${HEADER_DIR}/RunningConsole.h
    ${HEADER_DIR}/MediaFactory.h
)

set(SOURCES
    ${SOURCE_DIR}/LibrarySystem.cpp
    ${SOURCE_DIR}/Client.cpp
    ${SOURCE_DIR}/Console.cpp
    ${SOURCE_DIR}/Media.cpp
    ${SOURCE_DIR}/Film.cpp
    ${SOURCE_DIR}/Book.cpp
    ${SOURCE_DIR}/Game.cpp
    ${SOURCE_DIR}/RunningConsole.cpp
    ${SOURCE_DIR}/MediaFactory.cpp
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

