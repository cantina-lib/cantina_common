
#ifndef CANTINA_PHYSICS_TARGETTEDFORCEFIELD_HPP
#define CANTINA_PHYSICS_TARGETTEDFORCEFIELD_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>
#include <cant/common/functor.hpp>

#include <cant/physics/PhysicalForceField.hpp>
#include <cant/physics/KineticObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class IsotropicPullField : public PhysicalForceField<Len_T, Mass_T, Time_T, dim>
    {
    public:
        /** -- typedef -- **/
        typedef Mass_T ScalarForce_T;
        typedef Mass_T Distance_T;
        typedef Functor<ScalarForce_T(Len_T)> ForceDistanceFunctor;
        typedef typename Positionable<Len_T, dim>::Vector Vector;

        typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;
        typedef KineticObject<Len_T, Mass_T, Time_T, dim> DynamicObject;
        typedef PhysicalObject<Len_T, dim> SourceObject;

        /** -- methods -- **/
        CANT_EXPLICIT IsotropicPullField(ForceDistanceFunctor func, ShPtr<const SourceObject> source);

        //  implementation of PhysicalForce
        CANT_NODISCARD
        typename ForceField::DeltaForce
        getDeltaForce(UPtr<typename DynamicObject::State> const& state) const final;

        void setSource(ShPtr<const SourceObject>& source);

    private:

        /** -- fields -- **/
        ForceDistanceFunctor m_func;
        WPtr<const SourceObject> m_source;

        Time_T m_dt;

    };

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/IsotropicPullField.inl>

#endif //CANTINA_PHYSICS_TARGETTEDFORCEFIELD_HPP
