/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ans_log_wrapper.h"
#include "appmgr/app_mgr_constants.h"
#include "bundle_constants.h"
#include "bundle_mgr_interface.h"
#include "common_event_manager.h"
#include "common_event_support.h"
#include "ipc_skeleton.h"

#include "reminder_event_manager.h"

using namespace OHOS::EventFwk;
namespace OHOS {
namespace Notification {
ReminderEventManager::ReminderEventManager(std::shared_ptr<ReminderDataManager> &reminderDataManager)
{
    init(reminderDataManager);
}

void ReminderEventManager::init(std::shared_ptr<ReminderDataManager> &reminderDataManager) const
{
    MatchingSkills matchingSkills;
    matchingSkills.AddEvent(ReminderRequest::REMINDER_EVENT_ALARM_ALERT);
    matchingSkills.AddEvent(ReminderRequest::REMINDER_EVENT_ALERT_TIMEOUT);
    matchingSkills.AddEvent(ReminderRequest::REMINDER_EVENT_CLOSE_ALERT);
    matchingSkills.AddEvent(ReminderRequest::REMINDER_EVENT_SNOOZE_ALERT);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_PACKAGE_REMOVED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_PACKAGE_DATA_CLEARED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_PACKAGE_RESTARTED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_TIMEZONE_CHANGED);
    matchingSkills.AddEvent(CommonEventSupport::COMMON_EVENT_TIME_CHANGED);
    CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    auto subscriber = std::make_shared<ReminderEventSubscriber>(subscriberInfo, reminderDataManager);

    std::string identity = IPCSkeleton::ResetCallingIdentity();
    if (CommonEventManager::SubscribeCommonEvent(subscriber)) {
        ANSR_LOGD("SubscribeCommonEvent ok");
    } else {
        ANSR_LOGD("SubscribeCommonEvent fail");
    }
    IPCSkeleton::SetCallingIdentity(identity);
}

ReminderEventManager::ReminderEventSubscriber::ReminderEventSubscriber(
    const CommonEventSubscribeInfo &subscriberInfo,
    std::shared_ptr<ReminderDataManager> &reminderDataManager) : CommonEventSubscriber(subscriberInfo)
{
    reminderDataManager_ = reminderDataManager;
}

void ReminderEventManager::ReminderEventSubscriber::OnReceiveEvent(const EventFwk::CommonEventData &data)
{
    Want want = data.GetWant();
    std::string action = want.GetAction();
    ANSR_LOGI("Recieved common event:%{public}s", action.c_str());
    if (action == ReminderRequest::REMINDER_EVENT_ALARM_ALERT) {
        reminderDataManager_->ShowActiveReminder();
        return;
    }
    if (action == ReminderRequest::REMINDER_EVENT_ALERT_TIMEOUT) {
        reminderDataManager_->TerminateAlerting(want);
        return;
    }
    if (action == ReminderRequest::REMINDER_EVENT_CLOSE_ALERT) {
        reminderDataManager_->CloseReminder(want, true);
        return;
    }
    if (action == ReminderRequest::REMINDER_EVENT_SNOOZE_ALERT) {
        reminderDataManager_->SnoozeReminder(want);
        return;
    }
    if (action == ReminderRequest::REMINDER_EVENT_REMOVE_NOTIFICATION) {
        reminderDataManager_->CloseReminder(want, false);
        return;
    }
    if (action == CommonEventSupport::COMMON_EVENT_PACKAGE_REMOVED) {
        HandlePackageRemove(want);
        return;
    }
    if (action == CommonEventSupport::COMMON_EVENT_PACKAGE_DATA_CLEARED) {
        HandlePackageRemove(want);
        return;
    }
    if (action == CommonEventSupport::COMMON_EVENT_PACKAGE_RESTARTED) {
        HandleProcessDied(want);
        return;
    }
    if (action == CommonEventSupport::COMMON_EVENT_TIMEZONE_CHANGED) {
        reminderDataManager_->RefreshRemindersDueToSysTimeChange(ReminderDataManager::TIME_ZONE_CHANGE);
        return;
    }
    if (action == CommonEventSupport::COMMON_EVENT_TIME_CHANGED) {
        reminderDataManager_->RefreshRemindersDueToSysTimeChange(ReminderDataManager::DATE_TIME_CHANGE);
        return;
    }
}

void ReminderEventManager::ReminderEventSubscriber::HandlePackageRemove(OHOS::EventFwk::Want &want) const
{
    OHOS::AppExecFwk::ElementName ele = want.GetElement();
    std::string bundleName = ele.GetBundleName();
    int userId = want.GetIntParam(OHOS::AppExecFwk::Constants::USER_ID, -1);
    sptr<NotificationBundleOption> bundleOption = new NotificationBundleOption(bundleName, -1);
    reminderDataManager_->CancelAllReminders(bundleOption, userId);
}

void ReminderEventManager::ReminderEventSubscriber::HandleProcessDied(OHOS::EventFwk::Want &want) const
{
    sptr<NotificationBundleOption> bundleOption = GetBundleOption(want);
    reminderDataManager_->OnProcessDiedLocked(bundleOption);
}

sptr<NotificationBundleOption> ReminderEventManager::ReminderEventSubscriber::GetBundleOption(
    const OHOS::EventFwk::Want &want) const
{
    OHOS::AppExecFwk::ElementName ele = want.GetElement();
    std::string bundleName = ele.GetBundleName();
    int userId = want.GetIntParam(OHOS::AppExecFwk::Constants::USER_ID, -1);
    int32_t uid = ReminderRequest::GetUid(userId, bundleName);
    ANSR_LOGD("bundleName=%{public}s, userId=%{public}d, uid=%{public}d", bundleName.c_str(), userId, uid);
    sptr<NotificationBundleOption> bundleOption = new NotificationBundleOption(bundleName, uid);
    return bundleOption;
}
}  // namespace OHOS
}  // namespace Notification
