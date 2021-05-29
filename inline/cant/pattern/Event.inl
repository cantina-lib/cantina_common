//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_PATTERNS_EVENT_INL
#define CANTINA_PATTERNS_EVENT_INL

#pragma once

#include <algorithm>

#include <cant/common/functor.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERN_NAMESPACE_BEGIN

template <typename Arg_T, typename... Args>
CANT_INLINE void
  Event<Arg_T, Args...>::invoke(Arg_T arg, Args... args)
{
    for (auto & listenerToken : m_listenerTokens)
    {
        listenerToken->update(arg, args...);
    }
}

template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::addListener(ShPtr<EventListener<Arg_T, Args...>> & listener)
{
    return addListener(listener->m_token);
}

template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::removeListener(const ShPtr<EventListener<Arg_T, Args...>> & listener)
{
    return removeListener(listener->m_token);
}

template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::addListener(ShPtr<ListenerToken<Arg_T, Args...>> & listenerToken)
{
    auto const it = std::find(m_listenerTokens.cbegin(), m_listenerTokens.cend(), listenerToken);
    if (it != m_listenerTokens.cend())
    {
        // listener is already in the list.
        return false;
    }
    m_listenerTokens.push_back(listenerToken);
    m_listenerTokens.back()->addEvent(m_token);
    return true;
}

template <typename Arg_T, typename... Args>
bool
  Event<Arg_T, Args...>::removeListener(const std::shared_ptr<ListenerToken<Arg_T, Args...>> & listenerToken)
{
    auto const it = std::find(m_listenerTokens.cbegin(), m_listenerTokens.cend(), listenerToken);
    if (it == m_listenerTokens.cend())
    {
        // listener is not in the list.
        return false;
    }
    (*it)->removeEvent(m_token);
    m_listenerTokens.erase(it);
    return true;
}

template <typename Arg_T, typename... Args>
Event<Arg_T, Args...>::Event() : m_token(std::make_shared<EventToken<Arg_T, Args...>>(this)), m_listenerTokens()
{}

template <typename Arg_T, typename... Args>
Event<Arg_T, Args...>::~Event() = default;

template <typename Arg_T, typename... Args>
EventListener<Arg_T, Args...>::~EventListener()
{
    unsubscribeFromAllEvents();
}

template <typename Arg_T, typename... Args>
void
  EventListener<Arg_T, Args...>::addEvent(ShPtr<EventToken<Arg_T, Args...>> & eventToken)
{
    auto const it    = std::find(m_eventTokens.cbegin(), m_eventTokens.cend(), eventToken);
    bool const found = it != m_eventTokens.cend();
    CANTINA_ASSERT(!found, "EventListener is managed by Event, this should not happen.");
    if (!found)
    {
        m_eventTokens.push_back(eventToken);
    }
}

template <typename Arg_T, typename... Args>
void
  EventListener<Arg_T, Args...>::removeEvent(ShPtr<EventToken<Arg_T, Args...>> const & event)
{
    auto const it    = std::find(m_eventTokens.cbegin(), m_eventTokens.cend(), event);
    bool const found = it != m_eventTokens.cend();
    CANTINA_ASSERT(found, "EventListener is managed by Event, this should not happen.");
    if (found)
    {
        m_eventTokens.erase(it);
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
    std::for_each(m_eventTokens.begin(), m_eventTokens.end(), [this](ShPtr<EventToken<Arg_T, Args...>> & eventToken) {
        eventToken->removeListener(m_token);
    });
}
template <typename Arg_T, typename... Args>
EventListener<Arg_T, Args...>::EventListener()
    : m_token(std::make_shared<ListenerToken<Arg_T, Args...>>(this)), m_eventTokens()
{}

template <class C, typename Arg_T, typename... Args>
CANT_INLINE void
  SelfEventListener<C, Arg_T, Args...>::update(Arg_T arg, Args... args)
{
    (m_this->*m_method)(arg, args...);
}
template <class C, typename Arg_T, typename... Args>
SelfEventListener<C, Arg_T, Args...>::SelfEventListener(C * const a_this, SelfEventListener::Method method)
    : m_this(a_this), m_method(std::move(method))
{}

template <typename Arg_T, typename... Args>
CANT_INLINE void
  StaticEventListener<Arg_T, Args...>::update(Arg_T arg, Args... args)
{
    m_action(arg, args...);
}

template <typename Arg_T, typename... Args>
EventToken<Arg_T, Args...>::EventToken(Event<Arg_T, Args...> * event) : m_event(event)
{}

template <typename Arg_T, typename... Args>
CANT_INLINE void
  ListenerToken<Arg_T, Args...>::removeEvent(ShPtr<EventToken<Arg_T, Args...>> const & eventToken)
{
    m_listener->removeEvent(eventToken);
}

template <typename Arg_T, typename... Args>
CANT_INLINE void
  ListenerToken<Arg_T, Args...>::addEvent(ShPtr<EventToken<Arg_T, Args...>> & eventToken)
{
    m_listener->addEvent(eventToken);
}

template <typename Arg_T, typename... Args>
CANT_INLINE bool
  EventToken<Arg_T, Args...>::removeListener(ShPtr<ListenerToken<Arg_T, Args...>> & listenerToken)
{
    return m_event->removeListener(listenerToken);
}

template <typename Arg_T, typename... Args>
ListenerToken<Arg_T, Args...>::ListenerToken(EventListener<Arg_T, Args...> * listener) : m_listener(listener)
{}
template <typename Arg_T, typename... Args>
CANT_INLINE
void
  ListenerToken<Arg_T, Args...>::update(Arg_T arg, Args... args)
{
    m_listener->update(arg, args...);
}

CANTINA_PATTERN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PATTERNS_EVENT_INL
