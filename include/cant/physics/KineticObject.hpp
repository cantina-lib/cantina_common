
#ifndef CANTINA_PHYSICS_KINETICOBJECT_HPP
#define CANTINA_PHYSICS_KINETICOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Movable.hpp>
#include <cant/physics/PhysicalObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T> class KineticUpdater;
/**
 * Interface for DynamicObject and RigidObject
 */
template <size_u dim, typename T>
class KineticObject : public PhysicalObject<dim, T>, public Movable<dim, T>
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<T>);
    // static_assert(std::is_floating_point_v<T>); ?

   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position    Position;
    typedef typename Positionable<dim, T>::Vector      Vector;

    /** -- methods -- **/
    KineticObject();

    // todo: BIG
    // add an event callback in order to automatically move the object to different lists
    // in the simulation depending on their flags??
    CANT_NODISCARD ObjectBehaviourFlags getFlags() const override;
    CANT_NODISCARD bool hasFlag(FObjectBehaviour flag) const override;
    void raiseFlags(ObjectBehaviourFlags flag, bool add) override;
    void resetFlags(ObjectBehaviourFlags flags) override;


    // these should only be called by the KineticUpdater.
    virtual void updateVelocity(T dt) = 0;
    virtual void updatePosition(T dt) = 0;
    virtual void clearForceBuffer() = 0;

   private:
    /** -- fields -- **/
    ObjectBehaviourFlags m_flags;

    /** -- friend classes -- **/
    // in order to call the update functions from KineticUpdaters.
    friend class KineticUpdater<dim, T>;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticObject.inl>

#endif  // CANTINA_PHYSICS_KINETICOBJECT_HPP
