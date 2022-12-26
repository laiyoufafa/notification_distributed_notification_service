/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"

#define private public
#include "distributed_device_callback.h"

using namespace testing::ext;
namespace OHOS {
namespace Notification {
class DistributedDeviceCallbackTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

public:
    virtual void OnConnected(const std::string &deviceId);
    virtual void OnDisconnected(const std::string &deviceId);
};

void DistributedDeviceCallbackTest::SetUp()
{}

void DistributedDeviceCallbackTest::TearDown()
{}

void DistributedDeviceCallbackTest::OnConnected(const std::string &deviceId)
{}

void DistributedDeviceCallbackTest::OnDisconnected(const std::string &deviceId)
{}

/**
 * @tc.name      : DistributedDeviceCallback_00100
 * @tc.number    : DistributedDeviceCallback_00100
 * @tc.desc      : test OnDeviceChanged function and callback_.OnConnected is nullptr .
 */
HWTEST_F(DistributedDeviceCallbackTest, DistributedDeviceCallback_00100, Function | SmallTest | Level1)
{
    DistributedDeviceCallback::IDeviceChange deviceCallback = {
        .OnConnected = std::bind(&DistributedDeviceCallbackTest::OnConnected, this, std::placeholders::_1),
        .OnDisconnected = std::bind(&DistributedDeviceCallbackTest::OnDisconnected, this, std::placeholders::_1),
    };
    std::shared_ptr<DistributedDeviceCallback> deviceCallback_ =
        std::make_shared<DistributedDeviceCallback>(deviceCallback);
    deviceCallback_->callback_.OnConnected = nullptr;
    DistributedKv::DeviceInfo info;
    deviceCallback_->OnDeviceChanged(info, DistributedKv::DeviceChangeType::DEVICE_ONLINE);
}

/**
 * @tc.name      : DistributedDeviceCallback_00200
 * @tc.number    : DistributedDeviceCallback_00200
 * @tc.desc      : test OnDeviceChanged function and callback_.OnDisconnected is nullptr .
 */
HWTEST_F(DistributedDeviceCallbackTest, DistributedDeviceCallback_00200, Function | SmallTest | Level1)
{
    DistributedDeviceCallback::IDeviceChange deviceCallback = {
        .OnConnected = std::bind(&DistributedDeviceCallbackTest::OnConnected, this, std::placeholders::_1),
        .OnDisconnected = std::bind(&DistributedDeviceCallbackTest::OnDisconnected, this, std::placeholders::_1),
    };
    std::shared_ptr<DistributedDeviceCallback> deviceCallback_ =
        std::make_shared<DistributedDeviceCallback>(deviceCallback);
    deviceCallback_->callback_.OnDisconnected = nullptr;
    DistributedKv::DeviceInfo info;
    deviceCallback_->OnDeviceChanged(info, DistributedKv::DeviceChangeType::DEVICE_OFFLINE);
}
}  // namespace Notification
}  // namespace OHOS