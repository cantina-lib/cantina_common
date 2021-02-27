
#ifndef CANTINA_PHYSICS_KINETICUPDATER_HPP
#define CANTINA_PHYSICS_KINETICUPDATER_HPP

#pragma once

#include <cant/common/types.hpp>


#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class KineticObject;

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class KineticUpdater
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position Position;
    typedef Position                                    Velocity;
    typedef Position                                    Acceleration;

    typedef KineticObject<Len_T, Mass_T, Time_T, dim> Object;

    /** -- methods -- **/
    virtual ~KineticUpdater() = default;

    /**
     *
     * Updates velocity, position and clears the force buffer for given object.
     * @param object
     * @param dt
     */
    void stepDelta(ShPtr<Object> & object, Time_T dt) const;
private:
    /** -- methods -- **/
    /**
     * Should update velocity from acceleration and position from velocity.
     * @param object
     * @param dt
     */
    virtual void stepDeltaInternal(ShPtr<Object> & object, Time_T dt) const = 0;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticUpdater.inl>

#endif  // CANTINA_PHYSICS_KINETIC_HPP