
#ifndef CANTINA_MATHS_RECTANGLE_HPP
#define CANTINA_MATHS_RECTANGLE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/maths/algebra/Vector.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

// see:
// https://studiofreya.com/3d-math-and-physics/simple-aabb-vs-aabb-collision-detection/

template <typename Dim_T, size_u dim>
class Rectangle
{
   public:
    /** -- typedefs  -- **/
    typedef Vector<Dim_T, dim> Point;

    /** -- methods -- **/
    Rectangle(Point centre, Point halfDims);

    CANT_NODISCARD bool
      intersects(Rectangle const & other) const;

   private:
    Point m_centre;
    Point m_halfDims;
};

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/maths/geometry/Rectangle.inl>

#endif  // CANTINA_MATHS_RECTANGLE_HPP