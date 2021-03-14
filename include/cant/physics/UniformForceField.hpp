
#ifndef CANTINA_PHYSICS_UNIFORMFORCEFIELD_HPP
#define CANTINA_PHYSICS_UNIFORMFORCEFIELD_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForceField.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

/**
 * Applies a force individually to all objects in the simulation.
 * Should hold a reference to the stream of objects used by the simulation.
 * @tparam dim
 * @tparam T
 */
template <size_u dim, typename T>
class UniformForceField : public PhysicalForceField<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalForceField<dim, T> ForceField;
    typedef typename ForceField::Vector Vector;
    typedef typename ForceField::Object     Object;
    typedef typename ForceField::ObjectStream ObjectStream;

    /** -- methods -- **/
    UniformForceField(ObjectStream & objects, Vector vec);
    CANT_EXPLICIT UniformForceField(Vector vec);

    CANT_INLINE void setVector(Vector vec);
    CANT_INLINE Vector const & getVector() const;

   private:
    /** -- methods -- **/
    // implemented from PhysicalForceField.
    CANT_NODISCARD Vector getDeltaForce(ShPtr<Object> const & object) const final;

    /** -- fields -- **/
    Vector m_vec;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/UniformForceField.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
