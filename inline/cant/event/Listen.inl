//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_EVENT_LISTEN_INL
#define CANTINA_EVENT_LISTEN_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_EVENT_NAMESPACE_BEGIN

    template<class DerivedListener>
    LecturerTrait<DerivedListener>::
    ~LecturerTrait()
    {
        ListenManager::endAllSubscriptionsLecturer(this);
    }

    template<class DerivedLecturer>
    ListenerTrait<DerivedLecturer>::
    ~ListenerTrait()
    {
        ListenManager::endAllSubscriptionsListener(this);
    }

    template<class DerivedListener>
    CANT_INLINE
    LecturerTrait<DerivedListener>::
    LecturerTrait()
        : m_listeners(),
          m_managedlisteners()
    {

        static_assert
                (
                        std::is_convertible_v<Ptr<DerivedListener>, Ptr<ManagedListener>>,
                        "DerivedListener must inherit from ManagedListener publicly!"
                );
    }

    template<class DerivedLecturer>
    CANT_INLINE
    ListenerTrait<DerivedLecturer>::
    ListenerTrait()
        : m_lecturers(),
          m_managedLecturers()
    {
        static_assert
                (
                        std::is_convertible_v<Ptr<DerivedLecturer>, Ptr<ManagedLecturer>>,
                        "DerivedLecturer must inherit from ManagedLecturer publicly!"
                );
    }

    CANT_INLINE
    void
    ListenManager::
    beginSubscription(Ptr<ManagedLecturer> lecturer, Ptr<ManagedListener> listener)
    {
        CANTINA_ASSERT(lecturer && listener, "Noooo");
        lecturer->addListener(listener);
        listener->addLecturer(lecturer);
    }

    CANT_INLINE
    void
    ListenManager::
    endSubscription(Ptr<ManagedLecturer> lecturer, Ptr<ManagedListener> listener)
    {
        CANTINA_ASSERT(lecturer && listener, "Noooo");
        lecturer->removeListener(listener);
        listener->removeLecturer(lecturer);
    }

    CANT_INLINE
    void
    ListenManager::
    endAllSubscriptionsLecturer(Ptr <ManagedLecturer> lecturer)
    {
        for (auto& listener : lecturer->getListeners())
        {
            endSubscription(lecturer, listener);
        }
    }

    CANT_INLINE
    void
    ListenManager::
    endAllSubscriptionsListener(Ptr <ManagedListener> listener)
    {
        for (auto& lecturer : listener->getLecturers())
        {
            endSubscription(lecturer, listener);
        }

    }

    CANT_INLINE
    void
    ListenManager::
    updateSubscription(CPtr <ManagedLecturer> lecturer, Ptr <ManagedListener> listener)
    {
        listener->getNotifiedInternal(lecturer);
    }

    CANT_INLINE
    void
    ManagedLecturer::
    updateAllSubscribers() const
    {
        for (auto& listener : getListeners())
        {
            ListenManager::updateSubscription(this, listener);
        }
    }

    template<class DerivedListener>
    void
    LecturerTrait<DerivedListener>::
    addListener(Ptr <ManagedListener> listener)
    {

        const auto derived = dynamic_cast<Ptr<DerivedListener>>(listener);
        CANTINA_ASSERT(derived, "Wrong one!");

        m_listeners.push_back(derived);
        m_managedlisteners.push_back((derived));
    }

    template<class DerivedListener>
    void
    LecturerTrait<DerivedListener>::
    removeListener(Ptr<ManagedListener> baseListener)
    {
        const auto it = std::find(m_managedlisteners.begin(), m_managedlisteners.end(), baseListener);
        CANTINA_ASSERT(it != m_managedlisteners.end(), "NNNOOO");

        const size_u dist = std::distance(m_managedlisteners.begin(), it);
        m_managedlisteners.erase(it);
        m_listeners.erase(m_listeners.begin() + dist);
    }


    template<class DerivedListener>
    CANT_INLINE
    Stream <Ptr<ManagedListener>>&
    LecturerTrait<DerivedListener>::
    getListeners()
    {
        return m_managedlisteners;
    }

    template<class DerivedListener>
    CANT_INLINE
    const Stream <Ptr<ManagedListener>>&
    LecturerTrait<DerivedListener>::
    getListeners() const
    {
        return m_managedlisteners;
    }



    template<class DerivedLecturer>
    CANT_INLINE
    void
    ListenerTrait<DerivedLecturer>::
    subscribe(Ptr<DerivedLecturer> lecturer)
    {
        ListenManager::beginSubscription(lecturer, this);
    }

    template<class DerivedLecturer>
    CANT_INLINE
    void
    ListenerTrait<DerivedLecturer>::
    unsubscribe(Ptr<DerivedLecturer> lecturer)
    {
        ListenManager::endSubscription(lecturer, this);
    }

    template<class DerivedLecturer>
    void ListenerTrait<DerivedLecturer>::
    addLecturer(Ptr <ManagedLecturer> lecturer)
    {
        auto derived = dynamic_cast<Ptr<DerivedLecturer>>(lecturer);
        CANTINA_ASSERT(derived, "Wrong one!");

        m_lecturers.push_back(derived);
        m_managedLecturers.push_back((lecturer));
    }

    template<class DerivedLecturer>
    void
    ListenerTrait<DerivedLecturer>::
    removeLecturer(Ptr<ManagedLecturer> baseLecturer)
    {
        const auto it = std::find(m_managedLecturers.begin(), m_managedLecturers.end(), baseLecturer);
        CANTINA_ASSERT(it != m_managedLecturers.end(), "NOOOOO");

        const size_u dist = std::distance(m_managedLecturers.begin(), it);
        m_managedLecturers.erase(it);
        m_lecturers.erase(m_lecturers.begin() + dist);

    }

    template<class DerivedLecturer>
    CANT_INLINE
    Stream <Ptr<ManagedLecturer>>&
    ListenerTrait<DerivedLecturer>::
    getLecturers()
    {
        return m_managedLecturers;
    }


    template<class DerivedLecturer>
    CANT_INLINE
    void ListenerTrait<DerivedLecturer>::
    getNotifiedInternal(CPtr <ManagedLecturer> lecturer)
    {
        const auto derived = dynamic_cast<CPtr<DerivedLecturer>>(lecturer);
        CANTINA_ASSERT(derived, "Wrong one, damn it.");
        this->getNotified(derived);
    }



CANTINA_EVENT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_EVENT_LISTEN_INL
