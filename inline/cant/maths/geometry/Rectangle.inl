
#ifndef CANTINA_MATHS_RECTANGLE_INL
#define CANTINA_MATHS_RECTANGLE_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <size_u dim, typename T>
Rectangle<dim, T>::Rectangle(Rectangle::Point centre, Rectangle::Point halfDims)
    : m_centre(std::move(centre)), m_halfDims(std::move(halfDims))
{}

template <size_u dim, typename T>
bool
  Rectangle<dim, T>::intersects(Rectangle const & other) const
{
    for (size_u i = 0; i < dim; ++i)
    {
        if (std::abs(this->m_centre.get(i) - other.m_centre.get(i)) > this->m_halfDims.get(i) + other.m_halfDims.get(i))
        {
            return false;
        }
    }
    return true;
}

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_MATHS_RECTANGLE_INL