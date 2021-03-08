
#ifndef CANTINA_MATHS_VECTOR_HPP
#define CANTINA_MATHS_VECTOR_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class Vector
{
    /** -- constraints -- **/
    static_assert(std::is_arithmetic_v<T>);

   public:
    /** -- methods -- **/
    CANT_CONSTEXPR
    Vector();
    template <typename U, typename... Us>
    // NO 'EXPLICIT' IN ORDER TO ALLOW CONVERTION FROM SCALAR TO VEC IF dim = 1
    CANT_CONSTEXPR
      Vector(U t, Us... ts);

    CANT_NODISCARD
    CANT_CONSTEXPR static Vector
      fill(T t);

    CANT_NODISCARD
    CANT_CONSTEXPR T
      getDistance(Vector const & other) const;
    CANT_NODISCARD
    CANT_CONSTEXPR T
      getNorm() const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      getNormalised() const;
    CANT_NODISCARD
    CANT_CONSTEXPR T
      dot(Vector const & other) const;

    CANT_NODISCARD
    CANT_CONSTEXPR Array<T, dim> const &
      getArray() const;

    CANT_NODISCARD
    CANT_CONSTEXPR T
      get(size_u i) const;
    CANT_CONSTEXPR void
      set(size_u i, T val);
    template <size_u i>
    CANT_NODISCARD CANT_CONSTEXPR T
      get() const;
    template <size_u i>
    CANT_CONSTEXPR void
      set(T val);

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
      operator*(T scalar) const;
    CANT_NODISCARD
    CANT_CONSTEXPR Vector
      operator/(T scalar) const;

    CANT_CONSTEXPR Vector &
                   operator*=(T scalar);
    CANT_CONSTEXPR Vector &
                   operator/=(T scalar);

    // you shall not perform internal product in a vector space!
    /*
    CANT_NODISCARD Vector& operator*(Vector const& other) = delete;
    CANT_NODISCARD Vector& operator/(Vector const& other) = delete;
     */

   private:
    /** -- fields -- **/
    Array<T, dim> m_fields;

    /** -- friends -- **/
    friend CANT_CONSTEXPR Vector<dim, T>
                          operator*(T scalar, Vector<dim, T> const & vec)
    {
        return vec.operator*(scalar);
    }
    friend CANT_CONSTEXPR Vector<dim, T>
                          operator/(T scalar, Vector<dim, T> const & vec)
    {
        return vec.operator/(scalar);
    }
};

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/maths/algebra/Vector.inl>

#endif  // CANTINA_MATHS_VECTOR_HPP
