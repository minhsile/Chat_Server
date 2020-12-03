#pragma once
#include "ChatStruct.h"

ref class ChangePasswordStruct : public ChatStruct
{
public:
	String^ strUsername;
	String^ strOldPassword;
	String^ strNewPassword;
	String^ strConfirmNewPassword;

	ChangePasswordStruct()
	{
		strUsername = nullptr;
		strOldPassword = nullptr;
		strNewPassword = nullptr;
		strConfirmNewPassword = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::ChangePassword)));

		//add Username info
		if (strUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//add Old Password Info
		if (strOldPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strOldPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(strOldPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));
		//add New Password Info
		if (strNewPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strNewPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(strNewPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));
		//add Confirm New Password Info
		if (strNewPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strConfirmNewPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(strConfirmNewPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));
		//Return
		return byteData->ToArray();
	}

	virtual ChatStruct^ unpack(array<Byte>^ buff) override
	{
		int offset = 4; //Skip messageType
		int usernameLength, oldpasswordLength, newpasswordLength, confirmnewpasswordLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			strUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

		offset += usernameLength; //Update offset

		oldpasswordLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (oldpasswordLength > 0)
			strOldPassword = Encoding::UTF8->GetString(buff, offset, oldpasswordLength);
		offset += oldpasswordLength;

		newpasswordLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (newpasswordLength > 0)
			strNewPassword = Encoding::UTF8->GetString(buff, offset, newpasswordLength);
		offset += newpasswordLength;

		confirmnewpasswordLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (confirmnewpasswordLength > 0)
			strConfirmNewPassword = Encoding::UTF8->GetString(buff, offset, confirmnewpasswordLength);

		return this;
	}
};

