
#ifndef CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_HPP
#define CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_HPP

#pragma once

#include <type_traits>

#include <cant/common/types.hpp>
#include <cant/maths/algebra/Vector.hpp>

#include <cant/physics/PhysicalForce.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class PhysicalAppliedForce : public PhysicalForce<Len_T, Mass_T, Time_T, dim>
    {
        /** -- contraints -- **/
        static_assert(std::is_arithmetic_v<Len_T>);
        static_assert(std::is_floating_point_v<Mass_T>);
        static_assert(std::is_floating_point_v<Time_T>);

    public:
        /** -- typedefs -- **/
        typedef PhysicalForce<Len_T, Mass_T, Time_T, dim> Force;

        /** -- methods -- **/
        PhysicalAppliedForce();

        CANT_NODISCARD
        typename Force::DeltaForce
        getDeltaForce(UPtr<typename Force::State> const& state) const override = 0;

    };


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalAppliedForce.inl>

#endif //CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_HPP
