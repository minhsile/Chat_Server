#pragma once
#include "ChatStruct.h"

ref class LogoutNotificationStruct : public ChatStruct
{
public:
	String^ strUsername;

	LogoutNotificationStruct()
	{
		strUsername = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::LogoutNotification)));

		//add Username info
		if (strUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//Return
		return byteData->ToArray();
	}
	virtual ChatStruct^ unpack(array<Byte>^ buff) override
	{
		int offset = 4; //Skip messageType
		int usernameLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			strUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

		return this;
	}
};

