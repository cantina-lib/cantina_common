cmake_minimum_required(VERSION 3.6)

project(cantina_common)

set(CMAKE_CXX_STANDARD 20)

set(CANTINA_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CANTINA_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)

set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC")

set(CANTINA_COMMON_INCLUDE_DIRS
        ${CANTINA_COMMON_INCLUDE_DIR}
        CACHE INTERNAL
        "List of include directories for cantina_common"
        )

include_directories(
        ${CANTINA_COMMON_INCLUDE_DIRS}
)

set(CANTINA_COMMON_FILES
        # Cantina
        ## source
        ${CANTINA_COMMON_SOURCE_DIR}/cant/common/CantinaException.cpp
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/CantinaException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/CantinaException.inl
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/config.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/impl.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/info.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/undef_macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/memory.hpp

        # Maths
        ## source
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/maths.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/interpolation/interpolation.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/interpolation/interpolation.inl

        # Pantoufle
        ## source
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/PantoufleException.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/PantoufleException.inl

        # Eurêka
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/reka/common/types.hpp

        )


add_library(cantina_common STATIC ${CANTINA_COMMON_FILES})

set(CANTINA_COMMON_LIBRARIES cantina_common PARENT_SCOPE)

