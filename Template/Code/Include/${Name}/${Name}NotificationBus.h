/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once
#include <AzFramework/Input/User/LocalUserId.h>
#include <AzCore/EBus/EBus.h>
#include <AzCore/std/string/string.h>

namespace ${Name}
{
    ////////////////////////////////////////////////////////////////////////////////////////
    // EBUS interface used to listen for achievement unlocked events
    class ${Name}Notifications
        : public AZ::EBusTraits
    {
    public:
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        virtual void On${Name}Unlocked(const AZStd::string& achievementId, const AzFramework::LocalUserId& localUserId) = 0;
        virtual void On${Name}UnlockRequested(const AZStd::string& achievementId, const AzFramework::LocalUserId& localUserId) = 0;
        virtual void On${Name}DetailsQueried(const AzFramework::LocalUserId& localUserId, const ${Name}Details& achievementDetails) = 0;
    };
    using ${Name}NotificationBus = AZ::EBus<${Name}Notifications>;
} // namespace ${Name}
