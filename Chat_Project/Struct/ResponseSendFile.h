#pragma once
#include "ChatStruct.h"

ref class ResponseSendFileStruct : public ChatStruct
{
public:
	String^ strUsername;
	bool IsAccept;

	ResponseSendFileStruct()
	{
		strUsername = nullptr;
		IsAccept = false;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::ResponseSendFile)));

		//add Username info
		if (strUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add IsAccept Info
		byteData->AddRange(BitConverter::GetBytes(IsAccept));

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

		offset += usernameLength; //Update offset
		IsAccept = BitConverter::ToBoolean(buff, offset);

		return this;
	}
};


