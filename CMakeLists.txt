cmake_minimum_required(VERSION 3.6)

project(cantina_common)

set(CMAKE_CXX_STANDARD 20)

set(CANTINA_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CANTINA_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)

# fmr EXTENTION FOR FUTURE SUPPORT OF format
set(FMT_LIB_DIR ${THIRDPARTY_DIR}/fmt)
add_subdirectory(${FMT_LIB_DIR})

set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC")

set(CANTINA_COMMON_INCLUDE_DIRS
        ${CANTINA_COMMON_INCLUDE_DIR}
        ${FMT_LIB_DIR}/include
        CACHE INTERNAL
        "List of include directories for cantina_common"
        )

include_directories(
        ${CANTINA_COMMON_INCLUDE_DIRS}
)

set(CANTINA_COMMON_FILES
        # Cantina
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/CantinaException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/config.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/impl.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/info.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/memory.hpp

        ### common
        ## source
        ${CANTINA_COMMON_SOURCE_DIR}/cant/pan/common/Time.cpp
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/PantoufleException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/Cloneable.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/Time.hpp
        )

add_library(cantina_common ${CANTINA_COMMON_FILES})

set(CANTINA_COMMON_LIBRARIES cantina_common fmt PARENT_SCOPE)

