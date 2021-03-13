
#ifndef CANTINA_PHYSICS_PHYSICALSHAPE_HPP
#define CANTINA_PHYSICS_PHYSICALSHAPE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/common/functor.hpp>
#include <cant/common/option.hpp>

#include <cant/physics/Positionable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

// CONVEX!!
// For now rotation
// So only ball-shape, basically.
template <size_u dim, typename T>
class PhysicalShape
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef typename Positionable<dim, T>::Vector Vector;
    typedef maths::Rectangle<dim, T>                AABB;
    typedef Functor<T(Position const &, Position const &)> DistanceFunctor;

    /** -- structs -- **/
    // see:
    // https://www.myphysicslab.com/engine2D/collision-en.html
    struct Intersection
    {
        Vector centre;
        T radius;

        Vector direction;
    };


    /** -- methods -- **/
    virtual ~PhysicalShape();
    PhysicalShape(DistanceFunctor func, T radius);

    CANT_NODISCARD T
      getRadius() const;

    // centres in world coordinates
    CANT_NODISCARD Optional<Intersection> getIntersection(ShPtr<PhysicalShape> const & other,
                       Position const &            thisCentre,
                       Position const &            otherCentre) const;

    // pos should be in object coordinates here!!
    /*
    CANT_NODISCARD Position const &
                   getCentreObject() const;
    CANT_NODISCARD bool
      isInObject(Position const & pos) const;
    CANT_NODISCARD Vector
      getVectorToCentreObject(Position const & pos) const;
      */

   private:
    /** -- fields -- **/
    DistanceFunctor m_func;
    T m_radius;
    Position m_centre; // in object coordinates.
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalShape.inl>

#endif  // CANTINA_PHYSICS_PHYSICALSHAPE_HPP