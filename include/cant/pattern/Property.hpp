
#ifndef CANTINA_PATTERN_PROPERTY_HPP
#define CANTINA_PATTERN_PROPERTY_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERN_NAMESPACE_BEGIN

/**
 * Emulating C#-style property.
 * @tparam T
 */
template <typename T>
class Property
{
   public:
    /** -- typedefs -- **/
    typedef T& (*Getter)();
    typedef T& (*Setter)(T const&);
    /** -- methods -- **/
    Property(Getter, Setter, T val = T());
    Property(Property<T> const& other);
    // Here there should be a certain number of operator overloading.
    // For now, I'll stick to the most useful ones.
    Property<T>& operator=(T const& val);
    Property<T>& operator+=(T const& val);
    Property<T>& operator-=(T const& val);
    Property<T>& operator*=(T const& val);

    // conversion to T
    CANT_INLINE
    CANT_EXPLICIT operator T() const;

    /** -- fields -- **/

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    Getter m_getter;
    Setter m_setter;
    T m_value;
};

CANTINA_PATTERN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pattern/Property.inl>

#endif  // CANTINA_PATTERNS_PROPERTY_HPP