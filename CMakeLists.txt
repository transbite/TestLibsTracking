project(AIGSApp)

cmake_minimum_required(VERSION 2.8)

message("Config with cmake " ${CMAKE_VERSION})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)
#find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

if(Qt5Widgets_FOUND)
    message(STATUS "VTKTests - Qt5Widgets found...")
endif()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
if(VTK_FOUND)
    message("VTK_VERSION:" ${VTK_VERSION})
endif()

find_package(AIGS REQUIRED)
include(${AIGS_USE_FILE})
if(AIGS_FOUND)
    message("AIGS_VERSION:" ${AIGS_VERSION})
endif()
if(UNIX)
##if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x)
##endif()
endif()

set(SRCS main.cpp TestApp.cpp TestApp.h 
   )
set(FRMS
    TestApp.ui   
    )

qt5_wrap_ui(FRMS_HDRS ${FRMS})

add_executable(AIGSApp MACOSX_BUNDLE ${SRCS} ${FRMS_HDRS})

target_link_libraries(AIGSApp ${VTK_LIBRARIES})
target_link_libraries(AIGSApp ${AIGS_LIBRARIES})


#qt5_use_modules(AIGSApp Widgets OpenGL Sql WebKitWidgets Concurrent)
qt5_use_modules(AIGSApp Widgets OpenGL Sql Concurrent)

