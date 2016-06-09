# the whole CMakeLists.txt for project ttiger
PROJECT(evl_logger)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

MESSAGE(STSTUS "###################################")  
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")  
  
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
    MESSAGE(STATUS "current platform: Linux ")  
    ADD_DEFINITIONS(-D_PF_LINUX_)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")  
    MESSAGE(STATUS "current platform: Windows")  
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")  
    MESSAGE(STATUS "current platform: FreeBSD")  
ELSE ()  
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
  
MESSAGE(STSTUS "###################################")  

# include directories
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/../../   # for third_party
    ${PROJECT_SOURCE_DIR}/include

    /usr/local/include
    /usr/local/boost_1_61_0
    /usr/include
)

# lib directories
LINK_DIRECTORIES(
    ${PROJECT_BINARY_DIR}/lib

    /usr/local/lib
    /usr/lib
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
INSTALL(FILES ${PROJECT_BINARY_DIR}/lib/libevl_logger.so ${PROJECT_BINARY_DIR}/lib/libevl_logger.a DESTINATION lib/evllogger)
INSTALL(DIRECTORY include/ DESTINATION include)

ADD_SUBDIRECTORY(src)
