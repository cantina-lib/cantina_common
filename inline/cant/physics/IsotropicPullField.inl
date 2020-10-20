
#ifndef CANTINA_PHYSICS_TARGETTEDFORCEFIELD_INL
#define CANTINA_PHYSICS_TARGETTEDFORCEFIELD_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    typename IsotropicPullField<Len_T, Mass_T, Time_T, dim>::ForceField::DeltaForce
    IsotropicPullField<Len_T, Mass_T, Time_T, dim>::
    getDeltaForce(UPtr<typename DynamicObject::State> const& state) const
    {
        // first update the target.
        ShPtr<const SourceObject> target = m_source.lock();
        if (!target)
        {
            // throw CANTINA_EXCEPTION("Not supposed to happen.");
            this->signalEnded();
            return typename ForceField::DeltaForce();
        }
        Vector vec = target->getPosition() - state->getPosition();
        Len_T dist = vec.getNorm();
        const ScalarForce_T scalarForce = m_func(dist);
        if (maths::approx<type_d>::equal(static_cast<Len_T>(0.), dist))
        {
            // singularity.
            return typename ForceField::DeltaForce();
        }
        else
        {
            vec = vec.getNormalised();
            vec *= scalarForce;
            return vec;
        }
    }

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    IsotropicPullField<Len_T, Mass_T, Time_T, dim>::
    setSource(ShPtr<const SourceObject>& source)
    {
        m_source = source;
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    IsotropicPullField<Len_T, Mass_T, Time_T, dim>::
    IsotropicPullField(ForceDistanceFunctor func, ShPtr<const SourceObject> source)
        : m_func(std::move(func)),
          m_source(source)
    { }


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_TARGETTEDFORCEFIELD_INL
