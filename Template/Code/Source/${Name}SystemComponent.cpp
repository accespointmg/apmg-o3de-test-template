/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <${Name}SystemComponent.h>
#include <${Name}/${Name}NotificationBus.h>
#include <AzCore/Component/TickBus.h>

namespace ${Name}
{
    class ${Name}NotificationBusBehaviorHandler
        : public ${Name}NotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        ////////////////////////////////////////////////////////////////////////////////////////////
        AZ_EBUS_BEHAVIOR_BINDER(${Name}NotificationBusBehaviorHandler, "{33DFB6A3-434B-4341-B603-5F387D1CACFE}", AZ::SystemAllocator
            , On${Name}Unlocked
            , On${Name}DetailsQueried
            , On${Name}UnlockRequested
        );

        ////////////////////////////////////////////////////////////////////////////////////////////
        void On${Name}Unlocked(const AZStd::string& achievementId, const AzFramework::LocalUserId& localUserId) override
        {
            Call(FN_On${Name}Unlocked, achievementId, localUserId);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        void On${Name}UnlockRequested(const AZStd::string& achievementId, const AzFramework::LocalUserId& localUserId) override
        {
            Call(FN_On${Name}UnlockRequested, achievementId, localUserId);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        void On${Name}DetailsQueried(const AzFramework::LocalUserId& localUserId, const ${Name}Details& achievementDetails) override
        {
            Call(FN_On${Name}DetailsQueried, localUserId, achievementDetails);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}Details::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<${Name}Details>()
                ->Version(0);

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<${Name}Details>("${Name}Details", "Struct to hold platform agnostic achievement details for query results")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            
            behaviorContext->Class<${Name}Details>()
                ->Constructor<${Name}Details&>()
                ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
                ->Property("id", BehaviorValueProperty(&${Name}Details::id))
                ->Property("name", BehaviorValueProperty(&${Name}Details::name))
                ->Property("desc", BehaviorValueProperty(&${Name}Details::desc))
                ->Property("rewardValue", BehaviorValueProperty(&${Name}Details::rewardValue))
                ->Property("secret", BehaviorValueProperty(&${Name}Details::secret))
                ->Property("currentProgress", BehaviorValueProperty(&${Name}Details::currentProgress))
                ->Property("unlocked", BehaviorValueProperty(&${Name}Details::unlocked));
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    ${Name}Details::${Name}Details() :
        id(0),
        name(""),
        desc(""),
        rewardValue(0),
        currentProgress(0),
        unlocked(false),
        secret(false)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<${Name}SystemComponent, AZ::Component>()
                ->Version(0);

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<${Name}SystemComponent>("${Name}", "Platform agnostic interface for retrieving achievement details and unlocking achievements")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EBus<${Name}NotificationBus>("${Name}NotificationBus")
                ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::All)
                ->Handler<${Name}NotificationBusBehaviorHandler>();

            using Unlock${Name}Params = ${Name}Requests::Unlock${Name}Params;
            behaviorContext->Class<Unlock${Name}Params>()
                ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
                ->Property("achievementId", BehaviorValueProperty(&Unlock${Name}Params::achievementId))
                ->Property("localUserId", BehaviorValueProperty(&Unlock${Name}Params::localUserId))
                ->Property("percentage", BehaviorValueProperty(&Unlock${Name}Params::percentage));

            using Query${Name}Params = ${Name}Requests::Query${Name}Params;
            behaviorContext->Class<Query${Name}Params>()
                ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
                ->Property("achievementId", BehaviorValueProperty(&Query${Name}Params::achievementId))
                ->Property("localUserId", BehaviorValueProperty(&Query${Name}Params::localUserId));

            behaviorContext->EBus<${Name}RequestBus>("${Name}RequestBus")
                ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::All)
                ->Attribute(AZ::Script::Attributes::Category, "${Name}")
                ->Event("Unlock${Name}", &${Name}RequestBus::Events::Unlock${Name})
                ->Event("Query${Name}Details", &${Name}RequestBus::Events::Query${Name}Details);
        }

        ${Name}Details::Reflect(context);
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("${Name}Service"));
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("${Name}Service"));
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Activate()
    {
        m_pimpl.reset(Implementation::Create(*this));
        ${Name}RequestBus::Handler::BusConnect();
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Deactivate()
    {
        ${Name}RequestBus::Handler::BusDisconnect();
        m_pimpl.reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Unlock${Name}(const Unlock${Name}Params& params)
    {
        ${Name}NotificationBus::Broadcast(&${Name}Notifications::On${Name}UnlockRequested, params.achievementId, params.localUserId);
        AZ_Printf("${Name}", "Unlock ${Name} request for localuserId %s, achievement ID %s", AzFramework::LocalUserIdToString(params.localUserId).c_str(), params.achievementId.c_str());
        if (m_pimpl)
        {
            m_pimpl->Unlock${Name}(params);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Query${Name}Details(const Query${Name}Params& params)
    {
        AZ_Printf("${Name}", "Query ${Name} request for localuserId %s, achievement ID %s", AzFramework::LocalUserIdToString(params.localUserId).c_str(), params.achievementId.c_str());
        if (m_pimpl)
        {
            m_pimpl->Query${Name}Details(params);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ${Name}SystemComponent::Implementation::Implementation(${Name}SystemComponent& achievementSystemComponent)
        : m_achievementsSystemComponent(achievementSystemComponent)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ${Name}SystemComponent::Implementation::~Implementation()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Implementation::OnUnlock${Name}Complete(const Unlock${Name}Params& params)
    {
        AZ::TickBus::QueueFunction([params]()
        {
            if (params.On${Name}UnlockCallback)
            {
                params.On${Name}UnlockCallback(params.localUserId, params.achievementId);
            }
            ${Name}NotificationBus::Broadcast(&${Name}Notifications::On${Name}Unlocked, params.achievementId, params.localUserId);
        });
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    void ${Name}SystemComponent::Implementation::OnQuery${Name}DetailsComplete(const Query${Name}Params& params, const ${Name}Details& details)
    {
        AZ::TickBus::QueueFunction([params, details]()
        {
            if (params.On${Name}DetailsQueriedCallback)
            {
                params.On${Name}DetailsQueriedCallback(params.localUserId, details);
            }
            ${Name}NotificationBus::Broadcast(&${Name}Notifications::On${Name}DetailsQueried, params.localUserId, details);
        });
    }
}
