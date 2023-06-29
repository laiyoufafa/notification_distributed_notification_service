/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef BASE_NOTIFICATION_DISTRIBUTED_NOTIFICATION_SERVICE_INTERFACES_INNER_API_PUSH_CALLBACK_H
#define BASE_NOTIFICATION_DISTRIBUTED_NOTIFICATION_SERVICE_INTERFACES_INNER_API_PUSH_CALLBACK_H

#include <chrono>
#include <iremote_object.h>

#include "native_engine/native_engine.h"
#include "native_engine/native_value.h"
#include "parcel.h"
#include "push_callback_stub.h"

class NativeReference;
class NativeValue;

namespace OHOS {
namespace Notification {
/**
 * @class JSPushCallBack
 */
class JSPushCallBack : public PushCallBackStub {
public:
    JSPushCallBack(NativeEngine &engine);
    virtual ~JSPushCallBack();
    bool OnCheckNotification(const std::string &notificationData);
    void SetJsPushCallBackObject(NativeValue *pushCallBackObject);
    bool IsEqualPushCallBackObject(NativeValue *pushCallBackObject);

private:
    bool HandleCheckNotificationTask(const std::string &notificationData);
    bool ConvertFunctionResult(NativeValue *funcResult);
    void ConvertJsonStringToValue(
        const std::string &notificationData, std::string &pkgName, int32_t &notifyId, int32_t &contentType);
    NativeEngine &engine_;
    std::unique_ptr<NativeReference> pushCallBackObject_;
    std::mutex mutexlock;
    std::condition_variable condition;
};
} // namespace Notification
} // namespace OHOS
#endif // BASE_NOTIFICATION_DISTRIBUTED_NOTIFICATION_SERVICE_INTERFACES_INNER_API_PUSH_CALLBACK_H