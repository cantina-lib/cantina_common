
#ifndef CANTINA_PHYSICS_PHYSICALSTATE_HPP
#define CANTINA_PHYSICS_PHYSICALSTATE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Positionable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, size_u dim>
class PhysicalState : public Positionable<Len_T, dim>
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<Len_T>);

   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position Position;
    typedef typename Positionable<Len_T, dim>::Vector   Vector;

    /** -- methods -- **/
    CANT_EXPLICIT
    PhysicalState(Position position);
    PhysicalState();

    void
      translate(Vector const & vec);
    // manually sets the mass and position respectively.
    // does not compute again velocity or acceleration.
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

#include <cant/physics/PhysicalState.inl>

#endif  // CANTINA_PHYSICS_PHYSICALSTATE_HPP
