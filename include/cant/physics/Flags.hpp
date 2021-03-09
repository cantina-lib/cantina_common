
#ifndef CANTINA_PHYSICS_PHYSICALOBJECTTYPES_HPP
#define CANTINA_PHYSICS_PHYSICALOBJECTTYPES_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

// shamefully stolen idea from here:
// https://pybullet.org/Bullet/BulletFull/btCollisionObject_8h_source.html#l00131
// todo
// not defined in a class in order to allow implicit conversions from and to int.
enum FObjectBehaviour : int
{
    fStaticObject = 1,
    fNoFieldObject = 1 << 1,
};

typedef int ObjectBehaviourFlags;

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALOBJECTTYPES_HPP
