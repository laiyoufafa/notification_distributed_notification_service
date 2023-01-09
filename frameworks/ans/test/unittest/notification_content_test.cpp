/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "notification_basic_content.h"
#include "notification_content.h"
#undef private 
#undef protected

using namespace testing::ext;
namespace OHOS {
namespace Notification {
class NotificationContentTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: NotificationContentMarshalling_0100
 * @tc.desc: Marshalling
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationContentMarshalling_0100, Level1)
{
    Parcel parcel;
    std::shared_ptr<NotificationNormalContent> normalContent = std::make_shared<NotificationNormalContent>();
    EXPECT_NE(normalContent, nullptr);
    NotificationContent notificationContent(normalContent);
    auto result = notificationContent.Marshalling(parcel);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0100
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0100, Level1)
{
    Parcel parcel;
    std::shared_ptr<NotificationNormalContent> normalContent = std::make_shared<NotificationNormalContent>();
    EXPECT_NE(normalContent, nullptr);
    NotificationContent notificationContent(normalContent);
    auto result = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: NotificationBasicContentGetAdditionalText_0100
 * @tc.desc: GetAdditionalText
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationBasicContentGetAdditionalText_0100, Level1)
{
    std::string additionalText = "test";
    NotificationBasicContent notificationBasicContent;
    notificationBasicContent.SetAdditionalText(additionalText);
    auto result = notificationBasicContent.GetAdditionalText();
    EXPECT_EQ(result, additionalText);
}

/**
 * @tc.name: NotificationBasicContentGetText_0100
 * @tc.desc: GetText
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationBasicContentGetText_0100, Level1)
{
    std::string Text = "test";
    NotificationBasicContent notificationBasicContent;
    notificationBasicContent.SetText(Text);
    auto result = notificationBasicContent.GetText();
    EXPECT_EQ(result, Text);
}

/**
 * @tc.name: NotificationBasicContentGetTitle_0100
 * @tc.desc: GetTitle
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationBasicContentGetTitle_0100, Level1)
{
    std::string title = "titleTest";
    NotificationBasicContent notificationBasicContent;
    notificationBasicContent.SetTitle(title);
    auto result = notificationBasicContent.GetTitle();
    EXPECT_EQ(result, title);
}

/**
 * @tc.name: NotificationBasicContentMarshalling_0100
 * @tc.desc: Marshalling
 * @tc.type: FUNC
 * @tc.require: issueI5S0ZS
 */
HWTEST_F(NotificationContentTest, NotificationBasicContentMarshalling_0100, Level1)
{
    Parcel parcel;
    NotificationBasicContent notificationBasicContent;
    auto result = notificationBasicContent.Marshalling(parcel);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0200
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0200, Level1)
{
    std::shared_ptr<NotificationNormalContent> normalContent0 = nullptr;
    NotificationContent notificationContent0(normalContent0);

    std::shared_ptr<NotificationLongTextContent> longTextContent = nullptr;
    NotificationContent notificationContent1(longTextContent);

    std::shared_ptr<NotificationPictureContent> pictureContent = nullptr;
    NotificationContent notificationContent2(pictureContent);

    std::shared_ptr<NotificationConversationalContent> conversationContent = nullptr;
    NotificationContent notificationContent3(conversationContent);

    std::shared_ptr<NotificationMultiLineContent> multiLineContent = nullptr;
    NotificationContent notificationContent4(multiLineContent);

    std::shared_ptr<NotificationMediaContent> mediaContent = nullptr;
    NotificationContent notificationContent5(mediaContent);
    
    std::shared_ptr<NotificationNormalContent> normalContent = std::make_shared<NotificationNormalContent>();
    NotificationContent notificationContent(normalContent);
    auto result = notificationContent.GetContentType();
    EXPECT_EQ(result, NotificationContent::Type::BASIC_TEXT);

    Parcel parcel;
    auto result1 = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result1, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0300
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0300, Level1)
{
    std::shared_ptr<NotificationConversationalContent> conversationContent =
        std::make_shared<NotificationConversationalContent>();
    NotificationContent notificationContent(conversationContent);
    auto result = notificationContent.GetContentType();
    EXPECT_EQ(result, NotificationContent::Type::CONVERSATION);

    Parcel parcel;
    auto result1 = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result1, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0400
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0400, Level1)
{
    std::shared_ptr<NotificationPictureContent> pictureContent = std::make_shared<NotificationPictureContent>();
    NotificationContent notificationContent(pictureContent);
    auto result = notificationContent.GetContentType();
    EXPECT_EQ(result, NotificationContent::Type::PICTURE);

    Parcel parcel;
    auto result1 = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result1, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0500
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0500, Level1)
{
    std::shared_ptr<NotificationMultiLineContent> multiLineContent = std::make_shared<NotificationMultiLineContent>();
    NotificationContent notificationContent(multiLineContent);
    auto result = notificationContent.GetContentType();
    EXPECT_EQ(result, NotificationContent::Type::MULTILINE);

    Parcel parcel;
    auto result1 = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result1, true);
}

/**
 * @tc.name: NotificationContentReadFromParcel_0600
 * @tc.desc: ReadFromParcel
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, NotificationContentReadFromParcel_0600, Level1)
{
    std::shared_ptr<NotificationMediaContent> mediaContent = std::make_shared<NotificationMediaContent>();
    NotificationContent notificationContent(mediaContent);
    auto result = notificationContent.GetContentType();
    EXPECT_EQ(result, NotificationContent::Type::MEDIA);

    Parcel parcel;
    auto result1 = notificationContent.ReadFromParcel(parcel);
    EXPECT_EQ(result1, true);
}

/**
 * @tc.name: ConvertJsonToContent_0100
 * @tc.desc: ConvertJsonToContent
 * @tc.type: FUNC
 * @tc.require: issueI665WK
 */
HWTEST_F(NotificationContentTest, ConvertJsonToContent_0100, Level1)
{
    std::shared_ptr<NotificationMediaContent> mediaContent = std::make_shared<NotificationMediaContent>();
    NotificationContent notificationContent(mediaContent);

    nlohmann::json jsonObject;
    auto result1 = notificationContent.ConvertJsonToContent(nullptr, jsonObject);
    EXPECT_EQ(result1, false);
}
}
}