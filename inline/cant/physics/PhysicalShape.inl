
#ifndef CANTINA_PHYSICS_PHYSICALSHAPE_INL
#define CANTINA_PHYSICS_PHYSICALSHAPE_INL

#pragma once

#include <c3ga/Mvec.hpp>
#include <c3ga/c3gaTools.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalShape<dim, T>::PhysicalShape(DistanceFunctor func, T radius)
    : m_func(std::move(func)), m_radius(radius)
{

}

template <size_u dim, typename T>
PhysicalShape<dim, T>::~PhysicalShape() = default;

template <size_u dim, typename T>
CANT_INLINE T
  PhysicalShape<dim, T>::getRadius() const
{
    return m_radius;
}
template <size_u dim, typename T>
Optional<typename PhysicalShape<dim, T>::Intersection>
  PhysicalShape<dim, T>::getIntersection(ShPtr<PhysicalShape> const &     other,
                                         Position const & thisCentre,
                                         Position const & otherCentre) const
{
    static_assert(dim == 3, "Not so generic now, are we?");
    typedef c3ga::Mvec<T> MultiVector; // In 3D.

    static auto const conformMultiVectorToVector = [](MultiVector const & mv) -> Vector
    {
      return { mv[c3ga::E1], mv[c3ga::E2], mv[c3ga::E3] };
    };

    // make conform spheres from the centres and the radius of the shape.
    // we can easily do that by first making dual spheres:
    // S* = u_c - (r ** 2)/2 * e_infinity
    // Actually, we need to intersect after that,
    // so we'll keep the dual spheres.
    MultiVector const thisDualSphere = c3ga::dualSphere<T>(
      thisCentre.template get<0>(), thisCentre.template get<1>(), thisCentre.template get<2>(),
        this->m_radius);
    MultiVector const otherDualSphere = c3ga::dualSphere<T>(
      otherCentre.template get<0>(), otherCentre.template get<1>(), otherCentre.template get<2>(),
      other->m_radius);
    // compute the intersection multi-vector.
    // could be a sphere
    MultiVector const contact = thisDualSphere ^ otherDualSphere;

    // check whether the two spheres are intersecting,
    // That is, whether the contact point is 'real'.
    // It should be a circle, tangent bivector or an imaginary circle.
    // In any case, it can be checked by computing:
    // (contact / R . e_infinity) ** 2.
    // if it's strictly positive, the two spheres are strictly in each other,
    // if it's null, the spheres are touching,
    // if it's negative, they are not intersecting.

    T contactRadius;
    MultiVector contactCentre;
    MultiVector contactDirection;
    c3ga::extractDualCircle(contact, contactRadius, contactCentre, contactDirection);
    if (contactRadius < static_cast<T>(0.0))
    {
        // no intersection!
        return Optional<Intersection>();
    }

    Intersection intersection;
    intersection.direction = conformMultiVectorToVector(contactDirection);
    intersection.centre = conformMultiVectorToVector(contactCentre);
    intersection.radius = contactRadius;

    return intersection;
}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALSHAPE_INL