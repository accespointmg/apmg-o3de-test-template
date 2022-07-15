/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/Component/Component.h>
#include <${Name}/${Name}RequestBus.h>
#include <AzCore/std/parallel/atomic.h>
#include <AzCore/std/string/string.h>
#include <AzCore/Component/TickBus.h>

namespace ${Name}
{
    ////////////////////////////////////////////////////////////////////////////////////////
    // A system component providing an interface to query and unlock achievements
    class ${Name}SystemComponent
        : public AZ::Component
        , protected ${Name}RequestBus::Handler
    {
    public:
        ////////////////////////////////////////////////////////////////////////////////////////
        // Component setup
        AZ_COMPONENT(${Name}SystemComponent, "{07CFF8FE-668E-476A-95D9-A3B0CCCE2414}");

        ////////////////////////////////////////////////////////////////////////////////////////
        // Component overrides
        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);

    protected:
        ////////////////////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        ////////////////////////////////////////////////////////////////////////////////////////
        // ${Name}RequestBus interface implementation
        void Unlock${Name}(const Unlock${Name}Params& params) override;
        void Query${Name}Details(const Query${Name}Params& params) override;
    
    public:
        ////////////////////////////////////////////////////////////////////////////////////////
        // Base class for platform specific implementations
        class Implementation
        {
        public:
            AZ_CLASS_ALLOCATOR(Implementation, AZ::SystemAllocator, 0);

            static Implementation* Create(${Name}SystemComponent& achievementsSystemComponent);
            Implementation(${Name}SystemComponent& achievementsSystemComponent);

            AZ_DISABLE_COPY_MOVE(Implementation);

            virtual ~Implementation();

            virtual void Unlock${Name}(const Unlock${Name}Params& params) = 0;
            virtual void Query${Name}Details(const Query${Name}Params& params) = 0;

            static void OnUnlock${Name}Complete(const Unlock${Name}Params& params);
            static void OnQuery${Name}DetailsComplete(const Query${Name}Params& params, const ${Name}Details& details);

            ${Name}SystemComponent& m_achievementsSystemComponent;
        };

        private:
            ////////////////////////////////////////////////////////////////////////////////////////
            // Private pointer to the platform specific implementation
            AZStd::unique_ptr<Implementation> m_pimpl;
    };
}
