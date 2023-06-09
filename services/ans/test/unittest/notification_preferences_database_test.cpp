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

#define private public
#include <gtest/gtest.h>

#include "notification_preferences_database.h"

using namespace testing::ext;
namespace OHOS {
namespace Notification {
class NotificationPreferencesDatabaseTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() {};
    void TearDown() {};

    const std::string bundleName_ = "bundleName";
    const int bundleUid_ = 2001;
    int32_t userId = 100;
    std::unique_ptr<NotificationPreferencesDatabase> preferncesDB_ =
        std::make_unique<NotificationPreferencesDatabase>();
};

/**
 * @tc.name      : PutSlotsToDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Put slots into Disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutSlotsToDisturbeDB_00100, Function | SmallTest | Level1)
{
    std::vector<sptr<NotificationSlot>> slots;
    sptr<NotificationSlot> slot1 = new NotificationSlot(NotificationConstant::SlotType::SOCIAL_COMMUNICATION);
    sptr<NotificationSlot> slot2 = new NotificationSlot(NotificationConstant::SlotType::SERVICE_REMINDER);
    slots.push_back(slot1);
    slots.push_back(slot2);
    EXPECT_TRUE(preferncesDB_->PutSlotsToDisturbeDB(bundleName_, bundleUid_, slots));
}

/**
 * @tc.name      : PutSlotsToDisturbeDB_00200
 * @tc.number    :
 * @tc.desc      : Put slots into Disturbe DB when bundle name is null, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutSlotsToDisturbeDB_00200, Function | SmallTest | Level1)
{
    std::vector<sptr<NotificationSlot>> slots;
    sptr<NotificationSlot> slot1 = new NotificationSlot(NotificationConstant::SlotType::SOCIAL_COMMUNICATION);
    sptr<NotificationSlot> slot2 = new NotificationSlot(NotificationConstant::SlotType::SERVICE_REMINDER);
    slots.push_back(slot1);
    slots.push_back(slot2);
    EXPECT_FALSE(preferncesDB_->PutSlotsToDisturbeDB(std::string(), 0, slots));
}

/**
 * @tc.name      : PutSlotsToDisturbeDB_00300
 * @tc.number    :
 * @tc.desc      : Put slots into Disturbe DB when slots is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutSlotsToDisturbeDB_00300, Function | SmallTest | Level1)
{
    std::vector<sptr<NotificationSlot>> slots;
    EXPECT_FALSE(preferncesDB_->PutSlotsToDisturbeDB(bundleName_, bundleUid_, slots));
}

/**
 * @tc.name      : PutGroupsToDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Put slot group into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutGroupsToDisturbeDB_00100, Function | SmallTest | Level1)
{
    sptr<NotificationSlotGroup> slotGroup = new NotificationSlotGroup("id", "name");
    std::vector<sptr<NotificationSlotGroup>> groups;
    groups.push_back(slotGroup);

    EXPECT_TRUE(preferncesDB_->PutGroupsToDisturbeDB(bundleName_, bundleUid_, groups));
}

/**
 * @tc.name      : PutGroupsToDisturbeDB_00200
 * @tc.number    :
 * @tc.desc      : Put slot group into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutGroupsToDisturbeDB_00200, Function | SmallTest | Level1)
{
    sptr<NotificationSlotGroup> slotGroup = new NotificationSlotGroup("id", "name");
    std::vector<sptr<NotificationSlotGroup>> groups;
    groups.push_back(slotGroup);
    EXPECT_FALSE(preferncesDB_->PutGroupsToDisturbeDB(std::string(), 0, groups));
}

/**
 * @tc.number    : PutGroupsToDisturbeDB_00300
 * @tc.name      :
 * @tc.desc      : Put slot group into disturbe DB when groups is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutGroupsToDisturbeDB_00300, Function | SmallTest | Level1)
{
    std::vector<sptr<NotificationSlotGroup>> groups;
    EXPECT_FALSE(preferncesDB_->PutGroupsToDisturbeDB(bundleName_, bundleUid_, groups));
}

/**
 * @tc.name      : PutShowBadge_00100
 * @tc.number    :
 * @tc.desc      : Put bundle show badge into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutShowBadge_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutShowBadge(bundleInfo, true));
    EXPECT_TRUE(preferncesDB_->PutShowBadge(bundleInfo, false));
}

/**
 * @tc.number    : PutShowBadge_00200
 * @tc.name      :
 * @tc.desc      : Put bundle show badge into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutShowBadge_00200, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(std::string());
    EXPECT_FALSE(preferncesDB_->PutShowBadge(bundleInfo, false));
}

/**
 * @tc.name      : PutImportance_00100
 * @tc.number    :
 * @tc.desc      : Put bundle importance into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutImportance_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);

    EXPECT_TRUE(
        preferncesDB_->PutImportance(bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_NONE));
    EXPECT_TRUE(
        preferncesDB_->PutImportance(bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_MIN));
    EXPECT_TRUE(
        preferncesDB_->PutImportance(bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_LOW));
    EXPECT_TRUE(preferncesDB_->PutImportance(
        bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_DEFAULT));
    EXPECT_TRUE(
        preferncesDB_->PutImportance(bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_HIGH));
    EXPECT_TRUE(preferncesDB_->PutImportance(
        bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_UNDEFINED));
}

/**
 * @tc.name      : PutImportance_00200
 * @tc.number    :
 * @tc.desc      : Put bundle importance into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutImportance_00200, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(std::string());
    bundleInfo.SetBundleUid(0);

    EXPECT_FALSE(
        preferncesDB_->PutImportance(bundleInfo, OHOS::Notification::NotificationSlot::NotificationLevel::LEVEL_NONE));
}

/**
 * @tc.name      : PutTotalBadgeNums_00100
 * @tc.number    :
 * @tc.desc      : Put bundle total badge nums into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutTotalBadgeNums_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutTotalBadgeNums(bundleInfo, 0));
}

/**
 * @tc.number    : PutTotalBadgeNums_00200
 * @tc.name      :
 * @tc.desc      : Put bundle total badge nums into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutTotalBadgeNums_00200, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(std::string());
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_FALSE(preferncesDB_->PutTotalBadgeNums(bundleInfo, 0));
}

/**
 * @tc.name      : PutPrivateNotificationsAllowed_00100
 * @tc.number    :
 * @tc.desc      : Put bundle private notification allowed into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutPrivateNotificationsAllowed_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutPrivateNotificationsAllowed(bundleInfo, true));
    EXPECT_TRUE(preferncesDB_->PutPrivateNotificationsAllowed(bundleInfo, true));
}

/**
 * @tc.name      : PutPrivateNotificationsAllowed_00200
 * @tc.number    :
 * @tc.desc      : Put bundle private notification allowed into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutPrivateNotificationsAllowed_00200, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(std::string());
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_FALSE(preferncesDB_->PutPrivateNotificationsAllowed(bundleInfo, false));
}

/**
 * @tc.name      : PutNotificationsEnabledForBundle_00100
 * @tc.number    :
 * @tc.desc      : Put bundle enable into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutNotificationsEnabledForBundle_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutNotificationsEnabledForBundle(bundleInfo, true));
    EXPECT_TRUE(preferncesDB_->PutNotificationsEnabledForBundle(bundleInfo, false));
}

/**
 * @tc.name      : PutNotificationsEnabledForBundle_00200
 * @tc.number    :
 * @tc.desc      : Put bundle enable into disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutNotificationsEnabledForBundle_00200, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(std::string());
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_FALSE(preferncesDB_->PutNotificationsEnabledForBundle(bundleInfo, false));
}

/**
 * @tc.number    : PutNotificationsEnabled_00100
 * @tc.name      :
 * @tc.desc      : Put notification enable into disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutNotificationsEnabled_00100, Function | SmallTest | Level1)
{
    EXPECT_TRUE(preferncesDB_->PutNotificationsEnabled(userId, true));
    EXPECT_TRUE(preferncesDB_->PutNotificationsEnabled(userId, false));
}

/**
 * @tc.number    : PutDoNotDisturbDate_00100
 * @tc.name      :
 * @tc.desc      : Put disturbe mode into disturbe DB when DoNotDisturbType is NONE, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutDoNotDisturbDate_00100, Function | SmallTest | Level1)
{
    sptr<NotificationDoNotDisturbDate> date =
        new NotificationDoNotDisturbDate(NotificationConstant::DoNotDisturbType::NONE, 0, 0);
    EXPECT_TRUE(preferncesDB_->PutDoNotDisturbDate(userId, date));
}

/**
 * @tc.number    : PutDoNotDisturbDate_00200
 * @tc.name      :
 * @tc.desc      : Put disturbe mode into disturbe DB when DoNotDisturbType is ONCE, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutDoNotDisturbDate_00200, Function | SmallTest | Level1)
{
    std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();
    auto beginDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t beginDate = beginDuration.count();
    timePoint += std::chrono::hours(1);
    auto endDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t endDate = endDuration.count();
    sptr<NotificationDoNotDisturbDate> date =
        new NotificationDoNotDisturbDate(NotificationConstant::DoNotDisturbType::ONCE, beginDate, endDate);
    EXPECT_TRUE(preferncesDB_->PutDoNotDisturbDate(userId, date));
}

/**
 * @tc.number    : PutDoNotDisturbDate_00300
 * @tc.name      :
 * @tc.desc      : Put disturbe mode into disturbe DB when DoNotDisturbType is DAILY, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutDoNotDisturbDate_00300, Function | SmallTest | Level1)
{
    std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();
    auto beginDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t beginDate = beginDuration.count();
    timePoint += std::chrono::hours(1);
    auto endDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t endDate = endDuration.count();
    sptr<NotificationDoNotDisturbDate> date =
        new NotificationDoNotDisturbDate(NotificationConstant::DoNotDisturbType::DAILY, beginDate, endDate);

    EXPECT_TRUE(preferncesDB_->PutDoNotDisturbDate(userId, date));
}

/**
 * @tc.number    : PutDoNotDisturbDate_00400
 * @tc.name      :
 * @tc.desc      : Put disturbe mode into disturbe DB when DoNotDisturbType is CLEARLY, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutDoNotDisturbDate_00400, Function | SmallTest | Level1)
{
    std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();
    auto beginDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t beginDate = beginDuration.count();
    timePoint += std::chrono::hours(1);
    auto endDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
    int64_t endDate = endDuration.count();
    sptr<NotificationDoNotDisturbDate> date =
        new NotificationDoNotDisturbDate(NotificationConstant::DoNotDisturbType::CLEARLY, beginDate, endDate);

    EXPECT_TRUE(preferncesDB_->PutDoNotDisturbDate(userId, date));
}

/**
 * @tc.number    : ParseFromDisturbeDB_00100
 * @tc.name      :
 * @tc.desc      : Parse store date from disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, ParseFromDisturbeDB_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutPrivateNotificationsAllowed(bundleInfo, true));
    NotificationPreferencesInfo info;
    EXPECT_TRUE(preferncesDB_->ParseFromDisturbeDB(info));
}

/**
 * @tc.name      : RemoveAllDataFromDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Remove all bundle info from disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveAllDataFromDisturbeDB_00100, Function | SmallTest | Level1)
{
    EXPECT_TRUE(preferncesDB_->RemoveAllDataFromDisturbeDB());
}

/**
 * @tc.name      : RemoveBundleFromDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Remove a bundle info from disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveBundleFromDisturbeDB_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo bundleInfo;
    bundleInfo.SetBundleName(bundleName_);
    bundleInfo.SetBundleUid(bundleUid_);
    EXPECT_TRUE(preferncesDB_->PutTotalBadgeNums(bundleInfo, 0));
    EXPECT_EQ(true, preferncesDB_->RemoveBundleFromDisturbeDB(bundleName_));
}

/**
 * @tc.name      : RemoveBundleFromDisturbeDB_00200
 * @tc.number    :
 * @tc.desc      : Remove a bundle info from disturbe DB when bundle name is null, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveBundleFromDisturbeDB_00200, Function | SmallTest | Level1)
{
    EXPECT_EQ(true, preferncesDB_->RemoveBundleFromDisturbeDB(std::string()));
}

/**
 * @tc.name      : RemoveSlotFromDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Remove slot from disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveSlotFromDisturbeDB_00100, Function | SmallTest | Level1)
{
    std::vector<sptr<NotificationSlot>> slots;
    sptr<NotificationSlot> slot1 = new NotificationSlot(NotificationConstant::SlotType::SOCIAL_COMMUNICATION);
    slots.push_back(slot1);
    EXPECT_TRUE(preferncesDB_->PutSlotsToDisturbeDB(bundleName_, bundleUid_, slots));

    EXPECT_TRUE(preferncesDB_->RemoveSlotFromDisturbeDB(
        bundleName_, OHOS::Notification::NotificationConstant::SlotType::SOCIAL_COMMUNICATION));
}

/**
 * @tc.name      : RemoveSlotFromDisturbeDB_00200
 * @tc.number    :
 * @tc.desc      : Remove slot from disturbe DB when bundle name is null, return is false
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveSlotFromDisturbeDB_00200, Function | SmallTest | Level1)
{
    EXPECT_FALSE(preferncesDB_->RemoveSlotFromDisturbeDB(
        std::string(), OHOS::Notification::NotificationConstant::SlotType::SOCIAL_COMMUNICATION));
}

/**
 * @tc.name      : RemoveGroupsFromDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Remove slot froup from disturbe DB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveGroupsFromDisturbeDB_00100, Function | SmallTest | Level1)
{
    sptr<NotificationSlotGroup> slotGroup = new NotificationSlotGroup("id", "name");
    std::vector<sptr<NotificationSlotGroup>> groups;
    groups.push_back(slotGroup);
    EXPECT_TRUE(preferncesDB_->PutGroupsToDisturbeDB(bundleName_, bundleUid_, groups));
    std::vector<std::string> groupIds;
    groupIds.push_back("id");
    EXPECT_TRUE(preferncesDB_->RemoveGroupsFromDisturbeDB(bundleName_, groupIds));
}

/**
 * @tc.number    : RemoveGroupsFromDisturbeDB_00200
 * @tc.name      :
 * @tc.desc      :  Remove slot froup from disturbe DB when bundle name is null, return is false.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, RemoveGroupsFromDisturbeDB_00200, Function | SmallTest | Level1)
{
    std::vector<std::string> groupIds;
    groupIds.push_back("group1");
    groupIds.push_back("group2");
    EXPECT_FALSE(preferncesDB_->RemoveGroupsFromDisturbeDB(std::string(), groupIds));
}

/**
 * @tc.number    : GetRemoveGroupKeys_00100
 * @tc.name      :
 * @tc.desc      : Get remove group disturbe key, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, GetRemoveGroupKeys_00100, Function | SmallTest | Level1)
{
    std::string groupId = "id";
    std::vector<OHOS::DistributedKv::Key> keys;
    EXPECT_TRUE(preferncesDB_->GetRemoveGroupKeysFromDisturbeDB(bundleName_, groupId, keys));
}

/**
 * @tc.name      : StoreDeathRecipient_00100
 * @tc.number    :
 * @tc.desc      : Test store when death recipient.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, StoreDeathRecipient_00100, Function | SmallTest | Level1)
{
    EXPECT_TRUE(preferncesDB_->StoreDeathRecipient());
}

/**
 * @tc.name      : GetKvStore_00100
 * @tc.number    :
 * @tc.desc      : Open disturbe DB, return is SUCCESS.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, GetKvStore_00100, Function | SmallTest | Level1)
{
    EXPECT_EQ(OHOS::DistributedKv::Status::SUCCESS, preferncesDB_->GetKvStore());
}

/**
 * @tc.name      : CheckKvStore_00100
 * @tc.number    :
 * @tc.desc      : Check disturbe DB is exsit, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, CheckKvStore_00100, Function | SmallTest | Level1)
{
    EXPECT_TRUE(preferncesDB_->CheckKvStore());
}

/**
 * @tc.name      : PutBundlePropertyValueToDisturbeDB_00100
 * @tc.number    :
 * @tc.desc      : Put bundle property value to disturbeDB, return is true.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, PutBundlePropertyValueToDisturbeDB_00100, Function | SmallTest | Level1)
{
    NotificationPreferencesInfo::BundleInfo info;
    EXPECT_EQ(true, preferncesDB_->PutBundlePropertyValueToDisturbeDB(info));
}

/**
 * @tc.number    : ChangeSlotToEntry_00100
 * @tc.name      :
 * @tc.desc      : Change slot to entry.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, ChangeSlotToEntry_00100, Function | SmallTest | Level1)
{
    sptr<NotificationSlot> slot = new NotificationSlot(NotificationConstant::SlotType::SOCIAL_COMMUNICATION);
    std::vector<OHOS::DistributedKv::Entry> entries;
    EXPECT_TRUE(preferncesDB_->SlotToEntry(bundleName_, bundleUid_, slot, entries));
}

/**
 * @tc.name      : ChangeGroupToEntry_00100
 * @tc.number    :
 * @tc.desc      : Change slot group to entry.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, ChangeGroupToEntry_00100, Function | SmallTest | Level1)
{
    sptr<NotificationSlotGroup> slotGroup = new NotificationSlotGroup("id", "name");
    std::vector<OHOS::DistributedKv::Entry> entries;

    EXPECT_TRUE(preferncesDB_->GroupToEntry(bundleName_, bundleUid_, slotGroup, entries));
}

/**
 * @tc.name      : CheckBundle_00100
 * @tc.number    :
 * @tc.desc      :Check bundle is exsit, return true when exsiting, create a bundle when does not exsit.
 */
HWTEST_F(NotificationPreferencesDatabaseTest, CheckBundle_00100, Function | SmallTest | Level1)
{
    EXPECT_EQ(true, preferncesDB_->CheckBundle(bundleName_, bundleUid_));
}
}  // namespace Notification
}  // namespace OHOS
