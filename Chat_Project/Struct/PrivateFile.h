#pragma once
#include "ChatStruct.h"

ref class PrivateFileStruct :public ChatStruct
{
public:

	String^ strUsername;
	String^ strFilename;
	int iPackageNumber;
	int iTotalPackage;
	array<Byte>^ bData;

	PrivateFileStruct() {
		strUsername = nullptr;
		strFilename = nullptr;
		iPackageNumber = 0;
		iTotalPackage = 0;
		bData = nullptr;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::PrivateFile)));

		//add strUsername info
		if (strUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of strUsername
			byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //strUsername string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add strFilename Info
		if (strFilename != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strFilename))); //Length of strstrFilename
			byteData->AddRange(Encoding::UTF8->GetBytes(strFilename)); //strstrFilename string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//file package number and total package info
		byteData->AddRange(BitConverter::GetBytes(iPackageNumber));
		byteData->AddRange(BitConverter::GetBytes(iTotalPackage));

		//Add data info
		byteData->AddRange(BitConverter::GetBytes(bData->Length));
		byteData->AddRange(bData);
		//Return
		return byteData->ToArray();

	}
	virtual ChatStruct^ unpack(array<Byte>^ buff) override {
		int offset = 4; //Skip messageType
		int strUsernameLength, strFilenameLength;

		strUsernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (strUsernameLength > 0)
			strUsername = Encoding::UTF8->GetString(buff, offset, strUsernameLength);

		offset += strUsernameLength; //Update offset

		strFilenameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (strFilenameLength > 0)
			strFilename = Encoding::UTF8->GetString(buff, offset, strFilenameLength);

		offset += strFilenameLength;
		iPackageNumber = BitConverter::ToInt32(buff, offset);
		offset += 4;
		iTotalPackage = BitConverter::ToInt32(buff, offset);
		offset += 4;

		int dataSize = BitConverter::ToInt32(buff, offset);
		offset += 4;
		bData = gcnew array<Byte>(dataSize);
		if (dataSize > 0)
			System::Array::Copy(buff, offset, bData, 0, dataSize);

		return this;

	}
};


