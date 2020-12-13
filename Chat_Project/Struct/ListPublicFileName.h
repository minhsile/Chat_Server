#pragma once
#include "ChatStruct.h"
ref class ListPublicFileNameStruct :public ChatStruct
{
public:
	array<String^>^ listFileName;
	ListPublicFileNameStruct() {
		listFileName = nullptr;
	}

	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::ListPublicFileName)));


		String^ message = "";
		if (listFileName != nullptr) {
			for (int i = 0; i < listFileName->Length - 1; ++i)
				message += listFileName[i] + ",";
			if (listFileName->Length > 0)
				message += listFileName[listFileName->Length - 1];
		}

		if (message != "") {
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(message))); 
			byteData->AddRange(Encoding::UTF8->GetBytes(message));
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}

	virtual ChatStruct^ unpack(array<Byte>^ buffer) override {
		int offset = 4;
		int length = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		String^ message = "";

		if (length > 0) {
			message = Encoding::UTF8->GetString(buffer, offset, length);
			array<wchar_t>^ delimiter = gcnew array<wchar_t>(1);
			delimiter[0] = ',';
			listFileName = message->Split(delimiter);

		}
		return this;
	}
};

