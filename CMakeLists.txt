cmake_minimum_required(VERSION 3.10)

project(FzF VERSION 1.0 LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(PROJECT_SOURCES
    src/main.cpp
    src/gui/gui.cpp
    src/ripgrep/ripgrep.cpp
)

set(PROJECT_HEADERS
    
    src/main.h
    src/gui/gui.h
    src/ripgrep/ripgrep.h
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    
)

add_executable(FzF ${PROJECT_SOURCES}) 

target_link_libraries(FzF ${wxWidgets_LIBRARIES})

message(STATUS "Configured FzF project")
message(STATUS "Using wxWidgets: ${wxWidgets_LIBRARIES}")