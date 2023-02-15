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

#include "distributed_kv_data_manager.h"

#include "mock_single_kv_store.h"

namespace {
    bool g_mockStartWatchDeviceChangeRet = true;
    bool g_mockGetSingleKvStoreRet = true;
    bool g_mockGetLocalDeviceRet = true;
    bool g_mockGetDeviceListRet = true;
}

void mockStartWatchDeviceChange(bool mockRet)
{
    g_mockStartWatchDeviceChangeRet = mockRet;
}

void mockGetSingleKvStore(bool mockRet)
{
    g_mockGetSingleKvStoreRet = mockRet;
}

void mockGetLocalDevice(bool mockRet)
{
    g_mockGetLocalDeviceRet = mockRet;
}

void mockGetDeviceList(bool mockRet)
{
    g_mockGetDeviceListRet = mockRet;
}

namespace OHOS {
namespace DistributedKv {
DistributedKvDataManager::DistributedKvDataManager()
{}

DistributedKvDataManager::~DistributedKvDataManager()
{}

Status DistributedKvDataManager::GetDeviceList(std::vector<DeviceInfo> &deviceInfoList, DeviceFilterStrategy strategy)
{
    if (false == g_mockGetDeviceListRet) {
        return Status::INVALID_ARGUMENT;
    }
    return Status::SUCCESS;
}

Status DistributedKvDataManager::GetSingleKvStore(const Options &options, const AppId &appId, const StoreId &storeId,
    std::shared_ptr<SingleKvStore> &singleKvStore)
{
    if (false == g_mockGetSingleKvStoreRet) {
        return Status::INVALID_ARGUMENT;
    }
    return Status::SUCCESS;
}

Status DistributedKvDataManager::GetLocalDevice(DeviceInfo &localDevice)
{
    if (false == g_mockGetLocalDeviceRet) {
        return Status::INVALID_ARGUMENT;
    }
    return Status::SUCCESS;
}
}  // namespace DistributedKv
}  // namespace OHOS