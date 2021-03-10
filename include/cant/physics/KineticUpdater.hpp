
#ifndef CANTINA_PHYSICS_KINETICUPDATER_HPP
#define CANTINA_PHYSICS_KINETICUPDATER_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class KineticUpdater
{
   public:
    /** -- typedefs -- **/
    typedef KineticObject<dim, T> Object;
    typedef typename Object::Position Position;
    typedef typename Object::Vector Vector;

    /** -- methods -- **/
    virtual ~KineticUpdater() = default;

    /**
     *
     * Updates velocity, position and clears the force buffer for given object.
     * @param object
     * @param dt
     */
    void stepDelta(ShPtr<Object> & object, T dt) const;

   protected:
    /** -- methods -- **/
    // utility functions, defined here in order to call
    // the corresponding private methods of KineticObject from sub-class.
    void updateVelocity(ShPtr<Object> & object, T dt) const;
    void updatePosition(ShPtr<Object> & object, T dt) const;
private:
    /** -- methods -- **/
    /**
     * Should update velocity from acceleration and position from velocity.
     * @param object
     * @param dt
     */
    virtual void stepDeltaInternal(ShPtr<Object> & object, T dt) const = 0;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticUpdater.inl>

#endif  // CANTINA_PHYSICS_KINETIC_HPP