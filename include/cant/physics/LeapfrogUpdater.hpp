
#ifndef CANTINA_PHYSICS_LEAPFROGUPDATER_HPP
#define CANTINA_PHYSICS_LEAPFROGUPDATER_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/KineticUpdater.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

/**
 * A kinetic updater that first computes velocity before position from acceleration.
 * @tparam Len_T
 * @tparam Mass_T
 * @tparam Time_T
 * @tparam dim
 */
template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class LeapfrogUpdater : public KineticUpdater<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position Position;
    typedef Position                                    Velocity;
    typedef Position                                    Acceleration;

    typedef KineticObject<Len_T, Mass_T, Time_T, dim> Object;

    /** -- methods -- **/
private:
    /** -- methods -- **/
    /**
     * Should update velocity from acceleration and position from velocity.
     * @param object
     * @param dt
     */
    void stepDeltaInternal(ShPtr<Object> & object, Time_T dt) const override;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/LeapfrogUpdater.inl>

#endif  // CANTINA_PHYSICS_KINETIC_HPP