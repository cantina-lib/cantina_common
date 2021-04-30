
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_HPP
#define CANTINA_PHYSICS_PHYSICALOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Flags.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class PhysicalObject
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<T>);

   public:
    /** -- typedefs -- **/

    /** -- methods -- **/
    virtual ~PhysicalObject() = default;

    // todo: BId
    // add an event callback in order to automatically move the object to different lists
    // in the simulation depending on their flags??
    CANT_NODISCARD virtual ObjectBehaviourFlags getFlags() const = 0;
    CANT_NODISCARD virtual bool hasFlag(FObjectBehaviour flag) const = 0;
    virtual void raiseFlags(ObjectBehaviourFlags flag, bool add) = 0;
    virtual void resetFlags(ObjectBehaviourFlags flags) = 0;

   protected:
    /** -- fields -- **/
    // todo
    CANT_CONSTEXPR static ObjectBehaviourFlags c_defaultObjectFlags = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>


#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_HPP
