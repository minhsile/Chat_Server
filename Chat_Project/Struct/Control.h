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
#include "ResponseSendFile.h"
#include "ChangePassword.h"
#include "ResponseChangePassword.h"
#include "LoginNotification.h"
#include "LogoutNotification.h"
#include "SetInfor.h"
#include "RequestInfor.h"
#include "ResponseInfor.h"

#include "ListPublicFileName.h"
#include "RequestSendPublicFile.h"
#include "UploadPublicFile.h"
#include "DownloadPublicFile.h"
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
		case ChatStruct::MessageType::ResponseSendFile:
			result = gcnew ResponseSendFileStruct;
			result->messageType = ChatStruct::MessageType::ResponseSendFile;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::ChangePassword:
			result = gcnew ChangePasswordStruct();
			result->messageType = ChatStruct::MessageType::ChangePassword;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::ResponseChangePassword:
			result = gcnew ResponseChangePasswordStruct();
			result->messageType = ChatStruct::MessageType::ResponseChangePassword;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::LoginNotification:
			result = gcnew LoginNotificationStruct();
			result->messageType = ChatStruct::MessageType::LoginNotification;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::LogoutNotification:
			result = gcnew LogoutNotificationStruct();
			result->messageType = ChatStruct::MessageType::LogoutNotification;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::SetInfor:
			result = gcnew SetInformationStruct();
			result->messageType = ChatStruct::MessageType::SetInfor;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::RequestInfor:
			result = gcnew RequestInforStruct();
			result->messageType = ChatStruct::MessageType::RequestInfor;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::ResponseInfor:
			result = gcnew ResponseInforStruct();
			result->messageType = ChatStruct::MessageType::ResponseInfor;
			result->unpack(buff);
			break;
		case ChatStruct::MessageType::ListPublicFileName:
		{
			result = gcnew ListPublicFileNameStruct();
			result->messageType = ChatStruct::MessageType::ListPublicFileName;
			result->unpack(buff);
			break;
		}
		case ChatStruct::MessageType::UploadPublicFile:
		{
			result = gcnew UploadPublicFileStruct();
			result->messageType = ChatStruct::MessageType::UploadPublicFile;
			result->unpack(buff);
			break;
		}
		case ChatStruct::MessageType::RequestSendPublicFile:
		{
			result = gcnew RequestSendPublicFileStruct();
			result->messageType = ChatStruct::MessageType::RequestSendPublicFile;
			result->unpack(buff);
			break;
		}
		case ChatStruct::MessageType::DownloadPublicFile:
		{
			result = gcnew DownloadPublicFileStruct();
			result->messageType = ChatStruct::MessageType::DownloadPublicFile;
			result->unpack(buff);
			break;
		}
		default:
			break;
		}
		return result;
	}
};