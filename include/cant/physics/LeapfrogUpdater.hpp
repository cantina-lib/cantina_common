
#ifndef CANTINA_PHYSICS_LEAPFROGUPDATER_HPP
#define CANTINA_PHYSICS_LEAPFROGUPDATER_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/KineticUpdater.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

/**
 * A kinetic updater that first computes velocity before position from acceleration.
 * @tparam dim
 * @tparam T
 */
template <size_u dim, typename T>
class LeapfrogUpdater : public KineticUpdater<dim, T>
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef typename Positionable<dim, T>::Vector Vector;

    typedef KineticObject<dim, T> Object;

    /** -- methods -- **/
private:
    /** -- methods -- **/
    /**
     * Should update velocity from acceleration and position from velocity.
     * @param object
     * @param dt
     */
    void stepDeltaInternal(ShPtr<Object> & object, T dt) const override;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/LeapfrogUpdater.inl>

#endif  // CANTINA_PHYSICS_KINETIC_HPP