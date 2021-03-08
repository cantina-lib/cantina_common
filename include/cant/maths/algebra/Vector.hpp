
#ifndef CANTINA_MATHS_VECTOR_HPP
#define CANTINA_MATHS_VECTOR_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <typename Dim_T, size_u dim>
class Vector
{
    /** -- constraints -- **/
    static_assert(std::is_arithmetic_v<Dim_T>);

   public:
    /** -- methods -- **/
    CANT_CONSTEXPR
    Vector();
    template <typename T, typename... Ts>
    // NO EXPLICIT TO CONVERT SCALAR TO VEC IF dim = 1
    CANT_CONSTEXPR
      Vector(T t, Ts... ts);

    CANT_NODISCARD
    CANT_CONSTEXPR static Vector
      fill(Dim_T t);

    CANT_NODISCARD
    CANT_CONSTEXPR Dim_T
      getDistance(Vector const & other) const;
    CANT_NODISCARD
    CANT_CONSTEXPR Dim_T
      getNorm() const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      getNormalised() const;
    CANT_NODISCARD
    CANT_CONSTEXPR Dim_T
      dot(Vector const & other) const;

    CANT_NODISCARD
    CANT_CONSTEXPR Array<Dim_T, dim> const &
      getArray() const;

    CANT_NODISCARD
    CANT_CONSTEXPR Dim_T
      get(size_u i) const;
    CANT_CONSTEXPR void
      set(size_u i, Dim_T val);
    template <size_u i>
    CANT_NODISCARD CANT_CONSTEXPR Dim_T
      get() const;
    template <size_u i>
    CANT_CONSTEXPR void
      set(Dim_T val);

    CANT_CONSTEXPR Vector
      operator-() const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      operator+(Vector const & other) const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
                   operator-(Vector const & other) const;
    CANT_CONSTEXPR Vector &
                   operator+=(Vector const & other);
    CANT_CONSTEXPR Vector &
                   operator-=(Vector const & other);

    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      operator*(Dim_T scalar) const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      operator/(Dim_T scalar) const;

    CANT_CONSTEXPR Vector &
                   operator*=(Dim_T scalar);
    CANT_CONSTEXPR Vector &
                   operator/=(Dim_T scalar);

    // you shall not perform internal product in a vector space!
    /*
    CANT_NODISCARD Vector& operator*(Vector const& other) = delete;
    CANT_NODISCARD Vector& operator/(Vector const& other) = delete;
     */

   private:
    /** -- fields -- **/
    Array<Dim_T, dim> m_fields;

    /** -- friends -- **/
    friend CANT_CONSTEXPR Vector<Dim_T, dim>
                          operator*(Dim_T scalar, Vector<Dim_T, dim> const & vec)
    {
        return vec.operator*(scalar);
    }
    friend CANT_CONSTEXPR Vector<Dim_T, dim>
                          operator/(Dim_T scalar, Vector<Dim_T, dim> const & vec)
    {
        return vec.operator/(scalar);
    }
};

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/maths/algebra/Vector.inl>

#endif  // CANTINA_MATHS_VECTOR_HPP
