//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_PATTERNS_EVENT_INL
#define CANTINA_PATTERNS_EVENT_INL

#pragma once

#include <algorithm>

#include <cant/common/functor.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERNS_NAMESPACE_BEGIN

template <typename Arg_T, typename... Args>
CANT_INLINE void
  Event<Arg_T, Args...>::notify(Arg_T arg, Args ... args)
{
    for (auto& listener : m_listeners)
    {
        listener->invoke(arg, args...);
    }
}

template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::addListener(ShPtr<Event::Listener>& listener)
{
    auto const it      = std::find(m_listeners.cbegin(), m_listeners.cend(), listener);
    if (it != m_listeners.cend())
    {
        // listener is already in the list.
        return false;
    }
    m_listeners.push_back(listener);
    m_listeners.back()->addEvent(this);
    return true;
}
template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::removeListener(ShPtr<Event::Listener> const& listener)
{
    return removeListener(listener.get());
}

template <typename Arg_T, typename... Args>
bool Event<Arg_T, Args...>::removeListener(Listener const* listener)
{
    auto const it      = std::find_if(
      m_listeners.cbegin(),
      m_listeners.cend(),
      [listener](auto const& el) { return el.get() == listener; }
      );
    if (it == m_listeners.cend())
    {
        // listener is not in the list.
        return false;
    }
    (*it)->removeEvent(this);
    m_listeners.erase(it);
    return true;
}


template <typename Arg_T, typename... Args>
Event<Arg_T, Args...>::Event() = default;


    template <typename Arg_T, typename... Args>
    EventListener<Arg_T, Args...>::
    ~EventListener()
    {
        unsubscribeFromAllEvents();
    }

    template <typename Arg_T, typename... Args>
    void
    EventListener<Arg_T, Args...>::addEvent(E * event)
    {
        auto const it      = std::find(m_events.cbegin(), m_events.cend(), event);
        bool const found   = it != m_events.cend();
        CANTINA_ASSERT(!found, "EventListener is managed by Event, this should not happen.");
        if (!found)
        {
            m_events.push_back(event);
        }
    }

    template <typename Arg_T, typename... Args>
    void
      EventListener<Arg_T, Args...>::removeEvent(E const * event)
    {
        auto const it      = std::find(m_events.cbegin(), m_events.cend(), event);
        bool const found   = it != m_events.cend();
        CANTINA_ASSERT(found, "EventListener is managed by Event, this should not happen.");
        if (found)
        {
            m_events.erase(it);
        }
    }
    template <typename Arg_T, typename... Args>
    void
      EventListener<Arg_T, Args...>::unsubscribeFromAllEvents()
    {
        // Important:
        // Sadly, there's no way to check whether the events point to valid memory.
        // This whole thing made me realise the value of forcing object allocation of the heap.
        // Interesting to realise how little I know about this stuff.
        std::for_each(
          m_events.begin(),
          m_events.end(),
          [this](E * event)
          {
              event->removeListener(this);
          });
    }
    template <typename Arg_T, typename... Args>
    EventListener<Arg_T, Args...>::EventListener()
    :   m_events()
    { }

    template <class C, typename Arg_T, typename... Args>
    void
      SelfEventListener<C, Arg_T, Args...>::invoke(Arg_T arg, Args ... args)
    {
        (m_this->*m_method)(arg, args...);
    }
    template <class C, typename Arg_T, typename... Args>
    SelfEventListener<C, Arg_T, Args...>::SelfEventListener(C * const a_this, SelfEventListener::Method method)
        : m_this(a_this),
          m_method(std::move(method))
    {

    }

    template <typename Arg_T, typename... Args>
    void
      StaticEventListener<Arg_T, Args...>::invoke(Arg_T arg, Args... args)
    {
        m_action(arg, args...);
    }

CANTINA_PATTERNS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PATTERNS_EVENT_INL
