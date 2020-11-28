#pragma  once
#include "ChatStruct.h"
#include "Login.h"
#include "Signup.h"
#include "ResponseLogin.h"
#include "ResponseSignup.h"
#include "UserStatus.h"
#include "PrivateChat.h"
#include "PrivateFile.h"
#include "RequestSendFile.h"
ref class ChatControl
{
public:
	static ChatStruct^ unpack(array<Byte>^ buff)
	{
		if (buff->Length == 0)
			return nullptr;

		ChatStruct^ result = nullptr; //The result
		ChatStruct::MessageType messageType = (ChatStruct::MessageType)BitConverter::ToInt32(buff, 0); //Read first 4 byte for messageType

		//
		switch (messageType)
		{
		case ChatStruct::MessageType::Login:
			result = gcnew LoginStruct(); //Login Unpack
			result->messageType = ChatStruct::MessageType::Login;
			result->unpack(buff); //Call Override function
			break;
		case ChatStruct::MessageType::ResponseLogin:
			result = gcnew ResponseLoginStruct();
			result->messageType = ChatStruct::MessageType::ResponseLogin;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::Signup:
			result = gcnew SignupStruct();
			result->messageType = ChatStruct::MessageType::Signup;
			result->unpack(buff);

			break;
		case ChatStruct::MessageType::ResponseSignup:
			result = gcnew ResponseSignupStruct();
			result->messageType = ChatStruct::MessageType::ResponseSignup;
			result->unpack(buff);

			break;
		case ChatStruct::MessageType::UserStatus:
			result = gcnew UserStatusStruct();
			result->messageType = ChatStruct::MessageType::UserStatus;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::PrivateMessage:
			result = gcnew PrivateMessageStruct();
			result->messageType = ChatStruct::MessageType::PrivateMessage;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::PrivateFile:
			result = gcnew PrivateFileStruct();
			result->messageType = ChatStruct::MessageType::PrivateFile;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::RequestSendFile:
			result = gcnew RequestSendFileStruct();
			result->messageType = ChatStruct::MessageType::RequestSendFile;
			result->unpack(buff);
			break;
			//case ChatStruct::MessageType::LoginNotification:
			//	result = gcnew LoginNotificationStruct();
			//	result->messageType = ChatStruct::MessageType::LoginNotification;
			//	result->unpack(buff);

			//	break;
			//case ChatStruct::MessageType::LogoutNotification:
			//	result = gcnew LogoutNotificationStruct();
			//	result->messageType = ChatStruct::MessageType::LogoutNotification;
			//	result->unpack(buff);
			//	break;

		default:
			break;
		}

		return result;
	}
};