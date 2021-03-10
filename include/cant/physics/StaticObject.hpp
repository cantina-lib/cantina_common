
#ifndef CANTINA_PHYSICS_STATICOBJECT_HPP
#define CANTINA_PHYSICS_STATICOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Positionable.hpp>
#include <cant/physics/PhysicalObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class StaticObject : public PhysicalObject<dim, T>, public Positionable<dim, T>
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<T>);

   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef typename Positionable<dim, T>::Vector   Vector;

    /** -- methods -- **/
    CANT_EXPLICIT StaticObject(Position position = Position());

    void
      translate(Vector const & vec);
    // manually sets position respectively.
    void
      setPosition(Position pos) override;
    Position const &
      getPosition() const override;

   private:
    /** -- fields -- **/
    Position m_position;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/StaticObject.inl>

#endif  // CANTINA_PHYSICS_STATICOBJECT_HPP
