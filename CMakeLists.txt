cmake_minimum_required(VERSION 3.6)

project(cantina_common)

set(CMAKE_CXX_STANDARD 20)

set(CANTINA_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CANTINA_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)

set(GIT_SUBMODULE_DIR ${PROJECT_SOURCE_DIR}/submodules)

# fmr EXTENTION FOR FUTURE SUPPORT OF format
set(FMT_LIB_DIR ${GIT_SUBMODULE_DIR}/fmt)
add_subdirectory(${FMT_LIB_DIR})

set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC")


include_directories(
        ${CANTINA_COMMON_INCLUDE_DIR}
        ${FMT_LIB_DIR}/include
)

set(CANTINA_COMMON_FILES
        # Cantina
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/CantinaException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/config.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/impl.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/info.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/memory.hpp

        ### common
        ## source
        ${CANTINA_COMMON_SOURCE_DIR}/cant/pan/Time.cpp
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/PantoufleException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/Cloneable.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/Time.hpp
        )

add_library(cantina_common ${CANTINA_COMMON_FILES})

target_link_libraries(cantina_common fmt)
