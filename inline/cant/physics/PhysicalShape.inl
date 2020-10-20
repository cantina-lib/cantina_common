
#ifndef CANTINA_PHYSICS_PHYSICALSHAPE_INL
#define CANTINA_PHYSICS_PHYSICALSHAPE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, size_u dim>
    CANT_INLINE
    bool
    PhysicalShape<Len_T, dim>::
    isInObject(Position const& pos) const
    {
        return getRadius() <= pos.getDistance(m_centreObject);
    }

    template<typename Len_T, size_u dim>
    CANT_INLINE
    typename PhysicalShape<Len_T, dim>::Vector
    PhysicalShape<Len_T, dim>::
    getVectorToCentreObject(PhysicalShape::Position const& pos) const
    {
        return m_centreObject - pos;
    }

    template<typename Len_T, size_u dim>
    CANT_INLINE
    Len_T
    PhysicalShape<Len_T, dim>::
    getRadius() const
    {
        return m_radius;
    }

    template<typename Len_T, size_u dim>
    CANT_INLINE
    typename PhysicalShape<Len_T, dim>::Position const&
    PhysicalShape<Len_T, dim>::
    getCentreObject() const
    {
        return m_centreObject;
    }


    template<typename Len_T, size_u dim>
    bool
    PhysicalShape<Len_T, dim>::
    intersectsObject(UPtr <PhysicalShape> const& other, Position const& centreThis, Position const& centreOther) const
    {
        // get vec of centre to centre
        return centreThis.getDistance(centreOther) <= this->getRadius() + other->getRadius();
    }

    template<typename Len_T, size_u dim>
    PhysicalShape<Len_T, dim>::
    PhysicalShape(Position centreObject, Len_T radius)
            : m_centreObject(std::move(centreObject)),
              m_radius(radius)
    { }

    template<typename Len_T, size_u dim>
    PhysicalShape<Len_T, dim>::
    ~PhysicalShape() = default;

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_PHYSICALSHAPE_INL