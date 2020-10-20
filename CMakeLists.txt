cmake_minimum_required(VERSION 3.6)

project(cantina_common)


set(CANTINA_CXX_STANDARD 20
        CACHE INTERNAL
        "c++ standard for Cantina"
)

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
        ## -Warray-bounds is clang-only I think?
        set(CANTINA_MAIN_CXX_FLAGS
                "-fPIC \
                -Werror \
                -Wall -pedantic \
                -Wextra -Wshadow -Wnon-virtual-dtor  -Warray-bounds \
                -Wold-style-cast \
                -Wimplicit-fallthrough=5 -Wconversion \
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
        ## Removed -Wextra here because of warning in cast to t_newmethod in pd.
        set(CANTINA_TILDE_CXX_FLAGS
                "-fPIC \
                -Werror \
                -Wall -pedantic \
                -Wshadow -Wnon-virtual-dtor -Warray-bounds \
                -Wimplicit-fallthrough=5 -Wconversion \
                ${CANTINA_OPTIMISATION_LEVEL} \
                "
                CACHE INTERNAL
                "Compilation flags for Cantina"
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
set(CANTINA_COMMON_INLINE_DIR ${PROJECT_SOURCE_DIR}/inline)

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)


set(CANTINA_COMMON_INCLUDE_DIRS
        ${CANTINA_COMMON_INCLUDE_DIR}
        ${CANTINA_COMMON_INLINE_DIR}
        CACHE INTERNAL
        "List of include directories for cantina_common"
        )

include_directories(
        ${CANTINA_COMMON_INCLUDE_DIRS}
)


set(CANTINA_COMMON_FILES
        # Cantina
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/undef_macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/config.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/info.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/option.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/functor.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/memory.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/CantinaException.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/common/CantinaException.inl

        # Pantoufle
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/PantoufleException.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/pan/common/PantoufleException.inl

        # Eurêka
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/reka/common/types.hpp

        # Maths
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/maths.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/utils.hpp
        ### Algebra
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/algebra/algebra.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/algebra/Vector.hpp
        ### Geometry
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/geometry/Rectangle.hpp
        ### Polynomial
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/polynomial/polynomial.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/polynomial/PackedPolynomial.hpp
        ### Interpolation
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/interpolation/interpolation.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/interpolation/BrokenLinesInterpolation.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/interpolation/InterpolationOneD.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/polynomial/utils.inl
        ### Algebra
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/algebra/Vector.inl
        ### Geometry
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/geometry/Rectangle.inl
        ### Polynomial
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/polynomial/PackedPolynomial.inl
        ### Interpolation
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/interpolation/InterpolationOneD.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/maths/interpolation/BrokenLinesInterpolation.inl

        # Physics
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/Positionable.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/Kinetic.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalCollider.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalCollision.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalForce.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalAppliedForce.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalForceField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CustomForceField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/IsotropicPullField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalShape.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CustomShape.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalState.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/KineticState.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/KineticObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/RigidObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionDetector.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionSolver.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicsSimulation.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalPosition.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalForce.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalForceField.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalAppliedForce.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/CustomForceField.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/IsotropicPullField.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalShape.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/CustomShape.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalState.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/KineticState.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalObject.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/CollisionObject.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/KineticObject.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/RigidObject.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicalCollision.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/PhysicsSimulation.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/physics/CollisionDetector.inl

        # Event
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/event/event.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/event/event_forward.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/event/Listen.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/event/Listen.inl

        # Time
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/time.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/time_forward.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/Clock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/CustomClock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/SystemClock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/InternalClock.hpp
        ## inline
        ${CANTINA_COMMON_INLINE_DIR}/cant/time/InternalClock.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/time/CustomClock.inl
        ${CANTINA_COMMON_INLINE_DIR}/cant/time/SystemClock.inl
        )

# header-only library

