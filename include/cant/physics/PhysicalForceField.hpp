
#ifndef CANTINA_PHYSICS_PHYSICALFORCEFIELD_HPP
#define CANTINA_PHYSICS_PHYSICALFORCEFIELD_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForce.hpp>
#include <cant/physics/PhysicalState.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    // Class for Force Fields, whose force depends on the position of the object
    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class PhysicalForceField : public PhysicalForce<Len_T, Mass_T, Time_T, dim>
    {
        /** -- contraints -- **/
        static_assert(std::is_arithmetic_v<Len_T>);
        static_assert(std::is_floating_point_v<Mass_T>);
        static_assert(std::is_floating_point_v<Time_T>);

    public:
        /** -- typedefs -- **/
        typedef PhysicalForce<Len_T, Mass_T, Time_T, dim> Force;

        /** -- methods -- **/
        PhysicalForceField();
        // were the acceleration is a function of distance,
        // we would need to know the position of the object it is applied to.
        // should only be called by PhysicalState.
        CANT_NODISCARD
        typename Force::DeltaForce
        getDeltaForce(UPtr<typename Force::State> const& state) const override = 0;

    };


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalForceField.inl>

#endif //CANTINA_PHYSICS_PHYSICALFORCEFIELD_HPP
