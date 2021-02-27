
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_HPP
#define CANTINA_PHYSICS_RIGIDOBJECT_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class RigidObject : public KineticObject<Len_T, Mass_T, Time_T, dim>, public Collidable<Len_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalShape<Len_T, dim>            Shape;
    typedef PhysicalCollider<Len_T, dim> Collider;

    /** -- methods -- **/
    CANT_EXPLICIT RigidObject(UPtr<Shape> shape);
    RigidObject(Mass_T mass, UPtr<Shape> shape);

    // and now I have to redefine all this stuff to satisfy the Collidable interface, nyeh!

    // Collidable
    WPtr<Collider>
      getCollider() const override;
    CANT_NODISCARD bool
      isStatic() const override
    {
        return false;
    }

   private:
    /** -- fields -- **/
    ShPtr<Collider> m_collider;

    Stream<WPtr<Collider>> m_inContactColliders;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/RigidObject.inl>

#endif  // CANTINA_PHYSICS_RIGIDOBJECT_HPP
