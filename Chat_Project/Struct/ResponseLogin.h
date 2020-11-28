#pragma once
#include "ChatStruct.h"

ref class ResponseLoginStruct : public ChatStruct
{
public:
	bool IsSucc;
	String^ errorMsg;
	ResponseLoginStruct() //Default constructor
	{
		IsSucc = false; //Not success
		errorMsg = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::ResponseLogin)));
		byteData->AddRange(BitConverter::GetBytes(IsSucc));

		if (errorMsg != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(errorMsg))); //errorMsg length
			byteData->AddRange(Encoding::UTF8->GetBytes(errorMsg)); //errorMsg string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}
	virtual ChatStruct^ unpack(array<Byte>^ buff) override
	{
		int offset = 4;
		IsSucc = BitConverter::ToBoolean(buff, offset);
		offset += 1;
		int errorMsgLength = BitConverter::ToInt32(buff, offset);
		offset += 4;
		if (errorMsgLength > 0)
			errorMsg = Encoding::UTF8->GetString(buff, offset, errorMsgLength);

		return this;
	}
};