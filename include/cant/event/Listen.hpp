//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_EVENT_LISTEN_HPP
#define CANTINA_EVENT_LISTEN_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/event/event_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_EVENT_NAMESPACE_BEGIN

    /*
     * Interface for the masses, can be used as such.
     * Only used to type-check in ListenerInterface
     */
    class Lecturer
    {
    public:
        /** -- methods -- **/
        virtual ~Lecturer() = default;
    };

    /*
     * Interface for the masses, can be used as such.
     * The classes will provide implementation by delegating to ManagedListener.
     */
    template <class DerivedLecturerInterface>
    class Listener
    {
        /** -- constraints -- **/
        // There should be this constraint,
        // however this requires DerivedLecturerInterface to be complete.
        // but LecturerInterface adds nothing to this,
        // so no. Will have to check manually.
        /*
        static_assert
                (
                        std::is_base_of_v<LecturerInterface, DerivedLecturerInterface>,
                        "DerivedLecturerInterface must inherit from LecturerInterface!"
                );
        */
    public:
        /** -- methods -- **/
        virtual ~Listener() = default;

        virtual void subscribe(Ptr<DerivedLecturerInterface> lecturer) = 0;
        virtual void unsubscribe(Ptr<DerivedLecturerInterface> lecturer) = 0;

        // no getNotified routine
    };

    /*
     * These two will provide a limited *Trait* of Lecturer / Listener
     * To be used internally by the ListenManager.
     * This is done to be able to type-check at compile-time.
     * (ListenManager won't prompt a subscription, hence the decoupling)
     * Classes which use this pattern
     * should inherit from LecturerTrait / ListenerTrait instead.
     */
    class ManagedListener;
    class ManagedLecturer
    {
    public:
        /** -- methods -- **/
        virtual ~ManagedLecturer() = default;
        /*
         * No subscription routine here
         */
    protected:
        /** -- methods -- **/
        void updateAllSubscribers() const;

    private:
        /** -- methods -- **/
        virtual void addListener(Ptr<ManagedListener> listener) = 0;
        virtual void removeListener(Ptr<ManagedListener> Listener) = 0;

        CANT_NODISCARD virtual Stream<Ptr<ManagedListener>>& getListeners() = 0;
        CANT_NODISCARD virtual Stream<Ptr<ManagedListener>> const& getListeners() const = 0;

        /** -- friends -- **/
        friend class ListenManager;
    };

    class ManagedListener
    {
    public:
        /** -- methods -- **/
        virtual ~ManagedListener() = default;
        /*
         * No subscription routine here
         */
    private:
        /** -- methods -- **/
        /*
         * We indirect public methods in order to type-check at compile-time.
         */
        virtual void getNotifiedInternal(CPtr<ManagedLecturer> lecturer) = 0;

        virtual void addLecturer(Ptr<ManagedLecturer> baseLecturer) = 0;
        virtual void removeLecturer(Ptr<ManagedLecturer> baseLecturer) = 0;

        virtual Stream<Ptr<ManagedLecturer>>& getLecturers() = 0;

        /** -- friends -- **/
        friend class ListenManager;
    };

    template <class DerivedLecturer>
    class ExtraManagedListener : public ManagedListener
    {
    private:
        /** -- methods -- **/
        /*
         * We indirect public methods in order to type-check at compile-time.
         */
        virtual void getNotified(CPtr<DerivedLecturer> lecturer) = 0;

    };

    // static
    class ListenManager
    {
    public:
        /** -- methods -- **/
        static void beginSubscription(Ptr<ManagedLecturer> lecturer, Ptr<ManagedListener> listener);
        static void updateSubscription(CPtr<ManagedLecturer> lecturer, Ptr<ManagedListener> listener);
        static void endSubscription(Ptr<ManagedLecturer> lecturer, Ptr<ManagedListener> listener);

        static void endAllSubscriptionsLecturer(Ptr<ManagedLecturer> lecturer);
        static void endAllSubscriptionsListener(Ptr<ManagedListener> listener);
    };

    /*
     * IMPORTANT:
     * SHOULD BE INHERITED PUBLICLY,
     * IN ORDER TO HAVE ACCESS TO m_listeners FROM DERIVED
     */
    template <class DerivedListener>
    class LecturerTrait : public ManagedLecturer, public Lecturer
    {
        /** -- constraints -- **/
    public:
        /** -- methods -- **/
        /*
         * IMPORTANT
         * actual unsubscription routine at destruction time has to be done here,
         * rather than in ManagedLecturer, because unsubscription involves this member data
         * m_listeners etc. that are destructed by the time ~ManagedLecturer is called.
         * For the same reason, the purely virtual functions in ManagedLecturer would be called.
         * which is not good.
         */
        ~LecturerTrait() override;

        LecturerTrait();
        LecturerTrait(LecturerTrait const&) = delete;
        LecturerTrait& operator=(LecturerTrait const&) = delete;



    private:
        /** -- methods -- **/
        // private inheritance
        void addListener(Ptr<ManagedListener> listener) final;
        void removeListener(Ptr<ManagedListener> listener) final;

        CANT_NODISCARD Stream<Ptr<ManagedListener>>& getListeners() final;
        CANT_NODISCARD Stream<Ptr<ManagedListener>> const& getListeners() const final;


        /** -- fields -- **/
        Stream<Ptr<DerivedListener>> m_listeners;
        Stream<Ptr<ManagedListener>> m_managedlisteners;

    };


    /*
     * IMPORTANT:
     * SHOULD BE INHERITED PUBLICLY,
     * IN ORDER TO HAVE ACCESS TO m_listeners FROM DERIVED
     * and also suscribe
     */
    template <class DerivedLecturer>
    class ListenerTrait : public ManagedListener, public Listener<DerivedLecturer>
    {
        /** -- constraints -- **/
    public:
        /** -- methods -- **/
        ~ListenerTrait() override;

        ListenerTrait();
        ListenerTrait(ListenerTrait const&) = delete;
        ListenerTrait& operator=(ListenerTrait const&) = delete;

        void subscribe(Ptr<DerivedLecturer> lecturer) override;
        void unsubscribe(Ptr<DerivedLecturer> lecturer) override;

    private:
        /** -- methods -- **/
        // private inheritance
        void addLecturer(Ptr<ManagedLecturer> lecturer) final;
        void removeLecturer(Ptr<ManagedLecturer> lecturer) final;
        void getNotifiedInternal(CPtr<ManagedLecturer> lecturer) final;

        virtual void getNotified(CPtr<DerivedLecturer> lecturer) = 0;

        CANT_NODISCARD Stream<Ptr<ManagedLecturer>>& getLecturers() final;

        /** -- fields -- **/
        Stream<Ptr<DerivedLecturer>> m_lecturers;
        Stream<Ptr<ManagedLecturer>> m_managedLecturers;
    };

CANTINA_EVENT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/event/Listen.inl>

#endif //CANTINA_EVENT_LISTEN_HPP
