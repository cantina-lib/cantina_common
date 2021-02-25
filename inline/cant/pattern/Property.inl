
#ifndef CANTINA_PATTERNS_PROPERTY_INL
#define CANTINA_PATTERNS_PROPERTY_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PATTERN_NAMESPACE_BEGIN

    template <typename T>
    Property<T>::Property(Getter getter, Setter setter, T val)
    : m_getter(std::move(getter)),
      m_setter(std::move(setter)),
      m_value(val)
    {

    }

    template <typename T> Property<T>& Property<T>::operator=(T const& other)
    {
        m_value = m_setter(other);
        return *this;
    }
    template <typename T> Property<T>& Property<T>::operator+=(T const& other)
    {
       return operator=(m_value + other);
    }
    template <typename T> Property<T>& Property<T>::operator-=(T const& other)
    {
        return operator=(m_value - other);
    }
    template <typename T> Property<T>& Property<T>::operator*=(T const& other)
    {
        return operator=(m_value * other);
    }

    // conversion to T
    template <typename T>
    CANT_INLINE
    Property<T>::
      operator T() const
    {
        return m_getter();
    }

CANTINA_PATTERN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PATTERNS_PROPERTY_INL