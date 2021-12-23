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

#include <gtest/gtest.h>

#include "ans_log_wrapper.h"
#include "reminder_request_timer.h"
#include "reminder_helper.h"

using namespace testing::ext;
namespace OHOS {
namespace Notification {
class ReminderRequestTimerTest : public testing::Test {
public:
    static void SetUpTestCase(){};
    static void TearDownTestCase(){};
    void SetUp(){};
    void TearDown(){
        ReminderHelper::CancelAllReminders();
    };
};

/**
 * @tc.number    : initCountDownTime_00100
 * @tc.name      :
 * @tc.desc      : set countDownTime = 0 should throw exception.
 */
HWTEST_F(ReminderRequestTimerTest, initCountDownTime_00100, Function | SmallTest | Level1)
{
    try {
        auto rrc = std::make_shared<ReminderRequestTimer>(0);
        EXPECT_TRUE(false) << "countDownTime < 0 should throw exception.";
    } catch (const std::invalid_argument &e) {
        REMINDER_LOGI("countDownTime < 0 throw exception.");
    }
}

/**
 * @tc.number    : initCountDownTime_00200
 * @tc.name      :
 * @tc.desc      : set countDownTime > (UINT64_MAX / 1000) should throw exception.
 */
HWTEST_F(ReminderRequestTimerTest, initCountDownTime_00200, Function | SmallTest | Level1)
{
    try {
        auto rrc = std::make_shared<ReminderRequestTimer>(UINT64_MAX / 1000);
        EXPECT_TRUE(false) << "countDownTime >= (UINT64_MAX / 1000) should throw exception.";
    } catch (const std::invalid_argument &e) {
        REMINDER_LOGI("countDownTime > (UINT64_MAX / 1000) throw exception.");
    }
}


/**
 * @tc.number    : initCountDownTime_00300
 * @tc.name      :
 * @tc.desc      : set countDownTime with normal value.
 */
HWTEST_F(ReminderRequestTimerTest, initCountDownTime_00300, Function | SmallTest | Level1)
{
    auto rrc = std::make_shared<ReminderRequestTimer>(1);
    EXPECT_TRUE(rrc->GetInitInfo() == 1) << "countDownTime is not 1";

    auto rrc2 = std::make_shared<ReminderRequestTimer>(10);
    EXPECT_TRUE(rrc2->GetInitInfo() == 1) << "countDownTime is not 10";

    auto rrc3 = std::make_shared<ReminderRequestTimer>(100);
    EXPECT_TRUE(rrc3->GetInitInfo() == 1) << "countDownTime is not 1";
}
}
}