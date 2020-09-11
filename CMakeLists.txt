cmake_minimum_required(VERSION 3.6)

project(cantina_common)

set(CMAKE_CXX_STANDARD 20)


set(IS_GNU   OFF)
set(IS_MSVC  OFF)
set(IS_CLANG OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL     "GNU")
        set(IS_GNU   ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(IS_MSVC  ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(IS_CLANG ON)
endif()

if (CMAKE_BUILD_TYPE STREQUAL 'Release')
        set(CANTINA_OPTIMISATION ON)
else()
        set(CANTINA_OPTIMISATION OFF)
endif()


if (${IS_GNU} OR ${IS_CLANG})
        if (${CANTINA_OPTIMISATION})
                set(CANTINA_OPTIMISATION_LEVEL "-O3")
        else()
                set(CANTINA_OPTIMISATION_LEVEL "")
        endif()
        set(CANTINA_MAIN_CXX_FLAGS
                "-fPIC \
                -Werror \
                -Wall -pedantic \
                -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for Cantina"
                )
        set(CANTINA_THIRDPARTY_CXX_FLAGS
                " \
                -fPIC \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for third-party libraries in Cantina"
                )
        set(CANTINA_TILDE_CXX_FLAGS
                "-fPIC \
                -Werror \
                -Wall -pedantic \
                -Wshadow -Wnon-virtual-dtor \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for cantina~"
                )
elseif (${IS_MSVC})
        if (${CANTINA_OPTIMISATION})
                set(CANTINA_OPTIMISATION_LEVEL "/O2")
        else()
                set(CANTINA_OPTIMISATION_LEVEL "")
        endif()
        set(CANTINA_MAIN_CXX_FLAGS
                " \
                /EHsc \
                /WX \
                /W4 /w14640 /permissive \
                /w14242 /w14254 /w14263 /w14265 /w14287 \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for Cantina"
                )
        set(CANTINA_THIRDPARTY_CXX_FLAGS
                " \
                /EHsc \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for third-party libraries in Cantina"
                )
        set(CANTINA_TILDE_CXX_FLAGS
                " \
                /EHsc \
                /WX \
                /W4 /w14640 /permissive \
                /w14242 /w14254 /w14263 /w14265 /w14287 \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for cantina~"
                )
else()
        message(ERROR "Nope!")
endif()

set(CMAKE_CXX_FLAGS ${CANTINA_MAIN_CXX_FLAGS})

set(CANTINA_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CANTINA_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)


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

