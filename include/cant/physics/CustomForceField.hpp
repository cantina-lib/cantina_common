
#ifndef CANTINA_PHYSICS_CUSTOMFORCEFIELD_HPP
#define CANTINA_PHYSICS_CUSTOMFORCEFIELD_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/functor.hpp>
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
class CustomForceField : public PhysicalForceField<dim, T>
{
   public:
    /** -- typedefs -- **/
    typedef PhysicalForceField<dim, T> ForceField;
    typedef typename ForceField::Vector Vector;
    typedef typename ForceField::Object     Object;
    typedef typename ForceField::ObjectStream ObjectStream;
    typedef Functor<Vector(ShPtr<Object> const &)> DeltaForceFunctor;

    /** -- methods -- **/
    CANT_EXPLICIT CustomForceField(DeltaForceFunctor func);

    void setDeltaForceFunctor(DeltaForceFunctor func);

   private:
    /** -- methods -- **/
    // implemented from PhysicalForceField.
    CANT_NODISCARD Vector getDeltaForce(ShPtr<Object> const & object) const final;

    /** -- fields -- **/
    DeltaForceFunctor m_func;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CustomForceField.inl>

#endif  // CANTINA_PHYSICS_CUSTOMFORCE_HPP
