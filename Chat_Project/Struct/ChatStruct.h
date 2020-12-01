#pragma once
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Runtime::Serialization;
using namespace System::Collections::Generic; //List
using namespace System::Text; //Encoding

ref class ChatStruct abstract
{
public:
	enum class MessageType {
		Login, ResponseLogin, Signup, ResponseSignup, UserStatus, PrivateMessage, PrivateFile, RequestSendFile,
		ChangePassword, ResponseChangePassword, LoginNotification, LogoutNotification, ResponseSendFile
	};
	MessageType messageType;

	virtual array<Byte>^ pack() = 0;
	virtual ChatStruct^ unpack(array<Byte>^ buff) = 0;
};
