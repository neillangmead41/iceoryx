// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_binding_c/internal/c2cpp_enum_translation.hpp"
#include "iceoryx_binding_c/internal/c2cpp_binding.h"
#include "iceoryx_hoofs/error_handling/error_handling.hpp"

namespace c2cpp
{
iox::popo::ConsumerTooSlowPolicy consumerTooSlowPolicy(const ENUM iox_ConsumerTooSlowPolicy policy) noexcept
{
    switch (policy)
    {
    case ConsumerTooSlowPolicy_WAIT_FOR_CONSUMER:
        return iox::popo::ConsumerTooSlowPolicy::WAIT_FOR_CONSUMER;
    case ConsumerTooSlowPolicy_DISCARD_OLDEST_DATA:
        return iox::popo::ConsumerTooSlowPolicy::DISCARD_OLDEST_DATA;
    }

    errorHandler(
        iox::Error::kBINDING_C__UNDEFINED_STATE_IN_IOX_CONSUMER_TOO_SLOW_POLICY, nullptr, iox::ErrorLevel::MODERATE);
    return iox::popo::ConsumerTooSlowPolicy::DISCARD_OLDEST_DATA;
}
iox::popo::ConsumerTooSlowPolicy subscriberTooSlowPolicy(const ENUM iox_SubscriberTooSlowPolicy policy) noexcept
{
    return consumerTooSlowPolicy(policy);
}

iox::popo::QueueFullPolicy queueFullPolicy(const ENUM iox_QueueFullPolicy policy) noexcept
{
    switch (policy)
    {
    case QueueFullPolicy_BLOCK_PRODUCER:
        return iox::popo::QueueFullPolicy::BLOCK_PRODUCER;
    case QueueFullPolicy_DISCARD_OLDEST_DATA:
        return iox::popo::QueueFullPolicy::DISCARD_OLDEST_DATA;
    }

    errorHandler(iox::Error::kBINDING_C__UNDEFINED_STATE_IN_IOX_QUEUE_FULL_POLICY, nullptr, iox::ErrorLevel::MODERATE);
    return iox::popo::QueueFullPolicy::DISCARD_OLDEST_DATA;
}

iox::popo::SubscriberEvent subscriberEvent(const iox_SubscriberEvent value) noexcept
{
    switch (value)
    {
    case SubscriberEvent_DATA_RECEIVED:
        return iox::popo::SubscriberEvent::DATA_RECEIVED;
    }

    iox::LogFatal() << "invalid iox_SubscriberEvent value";
    errorHandler(iox::Error::kBINDING_C__C2CPP_ENUM_TRANSLATION_INVALID_SUBSCRIBER_EVENT_VALUE);
    return iox::popo::SubscriberEvent::DATA_RECEIVED;
}

iox::popo::SubscriberState subscriberState(const iox_SubscriberState value) noexcept
{
    switch (value)
    {
    case SubscriberState_HAS_DATA:
        return iox::popo::SubscriberState::HAS_DATA;
    }

    iox::LogFatal() << "invalid iox_SubscriberState value";
    errorHandler(iox::Error::kBINDING_C__C2CPP_ENUM_TRANSLATION_INVALID_SUBSCRIBER_STATE_VALUE);
    return iox::popo::SubscriberState::HAS_DATA;
}
} // namespace c2cpp
