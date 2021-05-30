cmake_minimum_required(VERSION 3.12)

project(cantina_common CXX)

set(CANTINA_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CANTINA_COMMON_INLINE_DIR ${PROJECT_SOURCE_DIR}/inline)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/cmake")

include(SetProjectFlags)

set(CANTINA_VERSION 0.0.94
        CACHE INTERNAL
        "Cantina version"
        )
set(CANTINA_BREW STILL_PERSONAL_BUT_EVEN_BETTER
        CACHE INTERNAL
        "Cantina brew"
        )

set(CANTINA_CXX_FLAGS ${${PROJECT_NAME}_CXX_FLAGS}
        CACHE INTERNAL
        "Cantina project-wide c++ flags"
        )
set(CANTINA_CXX_STANDARD cxx_std_17
        CACHE INTERNAL
        "Cantina project-wide c++ standard"
        )

set(CANTINA_COMMON_FILES
        # Cantina
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/undef_macro.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/config.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/info.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/traits.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/option.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/functor.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/memory.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/common/CantinaException.hpp

        # Pantoufle
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pan/common/PantoufleException.hpp

        # Eurêka
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/reka/common/types.hpp

        # Maths
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/maths.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/approx.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/maths/algo.hpp
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

        # Physics
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/Positionable.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/Movable.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/Flags.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalCollider.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalCollision.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalForce.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/WeakRefPhysicalForce.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/StaticPhysicalLink.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalForceField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/UniformForceField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CustomForceField.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/HookeSpringLink.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalShape.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicalObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/KineticObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/DynamicObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/RigidObject.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/KineticUpdater.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/LeapfrogUpdater.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionDetector.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/CollisionSolver.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/physics/PhysicsSimulation.hpp

        # Patterns
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pattern/Event.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pattern/Property.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/pattern/Slider.hpp

        # Time
        ## headers
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/common/types.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/time.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/Clock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/CustomExternalClock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/SystemExternalClock.hpp
        ${CANTINA_COMMON_INCLUDE_DIR}/cant/time/InternalClock.hpp
        )

# header-only library
add_library(${PROJECT_NAME} INTERFACE)

# apply Project flags and c++ standard defined in included cmake files.
# target_compile_options(${PROJECT_NAME} INTERFACE ${CANTINA_CXX_FLAGS})
target_compile_features(${PROJECT_NAME} INTERFACE ${CANTINA_CXX_STANDARD})

target_compile_definitions(${PROJECT_NAME} INTERFACE CANTINA_VERSION ${CANTINA_VERSION})
target_compile_definitions(${PROJECT_NAME} INTERFACE CANTINA_BREW ${CANTINA_BREW})

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CANTINA_COMMON_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CANTINA_COMMON_INLINE_DIR}>
        )

set(CANTINA_COMMON_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)

