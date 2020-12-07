#pragma once

//#include "PrivateChat.h"
namespace Client {
	ref class MainScreen;
}

#include "Controller.h"

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//User


	/// <summary>
	/// Summary for MainScreen
	/// </summary>
	public ref class MainScreen : public System::Windows::Forms::Form
	{
	public:
		MainScreen(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainScreen()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Label^ labInfo;
	private: System::Windows::Forms::Button^ butSetInfor;
	private: System::Windows::Forms::Label^ labOnline;
	private: System::Windows::Forms::ListBox^ lbOnlineUser;
	private: System::Windows::Forms::Button^ butChangePass;
	private: System::Windows::Forms::Button^ butDisconnect;
	private: System::Windows::Forms::TextBox^ txtUsername;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labInfo = (gcnew System::Windows::Forms::Label());
			this->butDisconnect = (gcnew System::Windows::Forms::Button());
			this->labOnline = (gcnew System::Windows::Forms::Label());
			this->lbOnlineUser = (gcnew System::Windows::Forms::ListBox());
			this->butChangePass = (gcnew System::Windows::Forms::Button());
			this->butSetInfor = (gcnew System::Windows::Forms::Button());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			this->labInfo->AutoSize = true;
			this->labInfo->Location = System::Drawing::Point(20, 188);
			this->labInfo->Name = L"labInfo";
			this->labInfo->Size = System::Drawing::Size(141, 13);
			this->labInfo->TabIndex = 11;
			this->labInfo->Text = L"----------------- MY INFO -----------";
			this->butDisconnect->Location = System::Drawing::Point(46, 307);
			this->butDisconnect->Name = L"butDisconnect";
			this->butDisconnect->Size = System::Drawing::Size(99, 23);
			this->butDisconnect->TabIndex = 19;
			this->butDisconnect->Text = L"Logout";
			this->butDisconnect->UseVisualStyleBackColor = true;
			this->butDisconnect->Click += gcnew System::EventHandler(this, &MainScreen::butDisconnect_Click);
			this->labOnline->AutoSize = true;
			this->labOnline->Location = System::Drawing::Point(43, 9);
			this->labOnline->Name = L"labOnline";
			this->labOnline->Size = System::Drawing::Size(97, 13);
			this->labOnline->TabIndex = 20;
			this->labOnline->Text = L"ONLINE FRIENDS";
			this->lbOnlineUser->FormattingEnabled = true;
			this->lbOnlineUser->Location = System::Drawing::Point(23, 25);
			this->lbOnlineUser->Name = L"lbOnlineUser";
			this->lbOnlineUser->Size = System::Drawing::Size(137, 160);
			this->lbOnlineUser->TabIndex = 21;
			this->lbOnlineUser->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainScreen::lbOnlineUser_MouseDoubleClick);
			this->butChangePass->Location = System::Drawing::Point(33, 274);
			this->butChangePass->Name = L"butChangePass";
			this->butChangePass->Size = System::Drawing::Size(120, 23);
			this->butChangePass->TabIndex = 22;
			this->butChangePass->Text = L"Change Password";
			this->butChangePass->UseVisualStyleBackColor = true;
			this->butChangePass->Click += gcnew System::EventHandler(this, &MainScreen::butChangePass_Click);
			this->butSetInfor->Location = System::Drawing::Point(33, 241);
			this->butSetInfor->Name = L"butSetInfor";
			this->butSetInfor->Size = System::Drawing::Size(120, 23);
			this->butSetInfor->TabIndex = 23;
			this->butSetInfor->Text = L"Set Information";
			this->butSetInfor->UseVisualStyleBackColor = true;
			this->butSetInfor->Click += gcnew System::EventHandler(this, &MainScreen::butSetInfor_Click);
			this->txtUsername->Location = System::Drawing::Point(41, 206);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(100, 20);
			this->txtUsername->TabIndex = 17;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(187, 346);
			this->Controls->Add(this->butSetInfor);
			this->Controls->Add(this->butChangePass);
			this->Controls->Add(this->lbOnlineUser);
			this->Controls->Add(this->labOnline);
			this->Controls->Add(this->butDisconnect);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->labInfo);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MainScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Chat Client";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainScreen::MainScreen_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainScreen::MainScreen_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainScreen::MainScreen_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainScreen_Load(System::Object^ sender, System::EventArgs^ e);
	//private: System::Void butSend_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainScreen_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	//public: void AddTextToContent(String^ text);
	public: void UpdateOnlineUsers();
	public: void AddAnOnlineUser(String^ username);
	public: void DeleteAnOnlineUser(String^ username);
	public: void SetOnlineUsers(array<String^>^ arrOnlineUsers);
	private: System::Void lbOnlineUser_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void butDisconnect_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainScreen_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	private: System::Void butChangePass_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butSetInfor_Click(System::Object^ sender, System::EventArgs^ e);
};
}
