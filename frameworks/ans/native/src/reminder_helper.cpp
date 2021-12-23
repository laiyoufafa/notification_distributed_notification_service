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
#include "ans_notification.h"
#include "application_env_impl.h"
#include "iservice_registry.h"
#include "notification_helper.h"
#include "reminder_helper.h"
#include "system_ability_definition.h"
#include "singleton.h"

namespace OHOS {
namespace Notification {
ErrCode ReminderHelper::PublishReminder(ReminderRequest &reminder)
{
    REMINDER_LOGI("PublishReminder start");

    // wait bundle manager to implement permission check.
    // if (!CheckPermission()) {
    //     return ERR_PERMISSION_DENIED;
    // }
    
    NotificationSlot slot(reminder.GetSlotType());
    NotificationHelper::AddNotificationSlot(slot);
    return DelayedSingleton<AnsNotification>::GetInstance()->PublishReminder(reminder);
}

ErrCode ReminderHelper::CancelReminder(const int32_t reminderId)
{
    REMINDER_LOGI("CancelReminder start");
    return DelayedSingleton<AnsNotification>::GetInstance()->CancelReminder(reminderId);
}

ErrCode ReminderHelper::CancelAllReminders()
{
    REMINDER_LOGI("CancelAllReminders start");
    return DelayedSingleton<AnsNotification>::GetInstance()->CancelAllReminders();
}

bool ReminderHelper::CheckPermission()
{
    REMINDER_LOGI("CheckPermission");
    AppExecFwk::ApplicationEnvImpl* application = AppExecFwk::ApplicationEnvImpl::GetInstance();
    std::string pkgName = application->GetBundleName();
    sptr<ISystemAbilityManager> systemManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemManager == nullptr) {
        REMINDER_LOGE("Permission denied");
        return false;
    }
    auto bundleManager =
        iface_cast<AppExecFwk::IBundleMgr>(systemManager->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID));
    if (bundleManager->CheckPermission(pkgName, "ohos.permission.PUBLISH_AGENT_REMINDER") != 0) {
        REMINDER_LOGE("Permission denied");
        return false;
    }
    return true;
}

ErrCode ReminderHelper::GetValidReminders(std::vector<sptr<ReminderRequest>> &validReminders)
{
    REMINDER_LOGI("GetValidReminders start");
    return DelayedSingleton<AnsNotification>::GetInstance()->GetValidReminders(validReminders);
}

ErrCode AddNotificationSlot(const NotificationSlot &slot)
{
    REMINDER_LOGI("AddNotificationSlot start");
    return DelayedSingleton<AnsNotification>::GetInstance()->AddNotificationSlot(slot);
}

ErrCode RemoveNotificationSlot(const NotificationConstant::SlotType &slotType)
{
    REMINDER_LOGI("RemoveNotificationSlot start");
    return DelayedSingleton<AnsNotification>::GetInstance()->RemoveNotificationSlot(slotType);
}
}
}