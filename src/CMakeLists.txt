# CMakeLists for src directory
PROJECT(evl_logger)

aux_source_directory(. SRCS_FILES)

# shared library
ADD_LIBRARY(evl_logger SHARED ${SRCS_FILES})

# static library
ADD_LIBRARY(evl_logger_static STATIC ${SRCS_FILES})

SET(_STATCI_LIB_OUTPUT_NAME "evl_logger_static-rtl")

if (CMAKE_SYSTEM_NAME MATCHES "Windows") 
    TARGET_LINK_LIBRARIES(evl_logger log4cplusD)
	if (MSVC_COMPILER_VERSION MATCHES "v120")
		SET(_STATCI_LIB_OUTPUT_NAME ${_STATCI_LIB_OUTPUT_NAME}_v120)
	endif()
	
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		SET(_STATCI_LIB_OUTPUT_NAME ${_STATCI_LIB_OUTPUT_NAME}_debug)
	endif()
	
else()
    TARGET_LINK_LIBRARIES(evl_logger log4cplus)
	
endif()

SET_TARGET_PROPERTIES(evl_logger_static PROPERTIES OUTPUT_NAME ${_STATCI_LIB_OUTPUT_NAME})
SET_TARGET_PROPERTIES(evl_logger PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(evl_logger_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

