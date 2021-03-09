
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_HPP
#define CANTINA_PHYSICS_PHYSICALOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Flags.hpp>
#include <cant/physics/Positionable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class PhysicalObject : public Positionable<dim, T>
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<T>);

   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef typename Positionable<dim, T>::Vector   Vector;

    /** -- methods -- **/
    CANT_EXPLICIT PhysicalObject(Position position = Position());

    void
      translate(Vector const & vec);
    // manually sets position respectively.
    // does not compute again velocity or acceleration.
    void
      setPosition(Position pos) override;
    Position const &
      getPosition() const override;


    // todo: BIG
    // add an event callback in order to automatically move the object to different lists
    // in the simulation depending on their flags??
    CANT_NODISCARD ObjectBehaviourFlags getFlags() const;
    CANT_NODISCARD bool hasFlags(ObjectBehaviourFlags flag) const;
    void raiseFlags(ObjectBehaviourFlags flag, bool add);

   protected:
    /** -- methods -- **/
    CANT_NODISCARD ObjectBehaviourFlags
                   resetFlags(ObjectBehaviourFlags flags);

   private:
    /** -- fields -- **/
    Position m_position;

    ObjectBehaviourFlags m_flags;

    // todo
    CANT_CONSTEXPR static ObjectBehaviourFlags c_defaultObjectFlags = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalObject.inl>

#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_HPP
