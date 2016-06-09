# CMakeLists for src directory
PROJECT(evl_logger)

aux_source_directory(. SRCS_FILES)

# shared library
ADD_LIBRARY(evl_logger SHARED ${SRCS_FILES})

# static library
ADD_LIBRARY(evl_logger_static STATIC ${SRCS_FILES})
SET_TARGET_PROPERTIES(evl_logger_static PROPERTIES OUTPUT_NAME "evl_logger")
SET_TARGET_PROPERTIES(evl_logger PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(evl_logger_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

