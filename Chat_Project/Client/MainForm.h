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

	private: System::Windows::Forms::Button^ butSetInfor;
	private: System::Windows::Forms::Label^ labOnline;
	private: System::Windows::Forms::ListBox^ lbOnlineUser;
	private: System::Windows::Forms::Button^ butChangePass;
	private: System::Windows::Forms::Button^ butDisconnect;
	private: System::Windows::Forms::Button^ butShowInfor;
	private: System::Windows::Forms::Button^ butUpDownloadFile;


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
			this->butDisconnect = (gcnew System::Windows::Forms::Button());
			this->labOnline = (gcnew System::Windows::Forms::Label());
			this->lbOnlineUser = (gcnew System::Windows::Forms::ListBox());
			this->butChangePass = (gcnew System::Windows::Forms::Button());
			this->butSetInfor = (gcnew System::Windows::Forms::Button());
			this->butShowInfor = (gcnew System::Windows::Forms::Button());
			this->butUpDownloadFile = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
		
			this->butDisconnect->Location = System::Drawing::Point(33, 322);
			this->butDisconnect->Name = L"butDisconnect";
			this->butDisconnect->Size = System::Drawing::Size(120, 23);
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
		
			this->butChangePass->Location = System::Drawing::Point(33, 293);
			this->butChangePass->Name = L"butChangePass";
			this->butChangePass->Size = System::Drawing::Size(120, 23);
			this->butChangePass->TabIndex = 22;
			this->butChangePass->Text = L"Change Password";
			this->butChangePass->UseVisualStyleBackColor = true;
			this->butChangePass->Click += gcnew System::EventHandler(this, &MainScreen::butChangePass_Click);
			
			this->butSetInfor->Location = System::Drawing::Point(33, 264);
			this->butSetInfor->Name = L"butSetInfor";
			this->butSetInfor->Size = System::Drawing::Size(120, 23);
			this->butSetInfor->TabIndex = 23;
			this->butSetInfor->Text = L"Set Information";
			this->butSetInfor->UseVisualStyleBackColor = true;
			this->butSetInfor->Click += gcnew System::EventHandler(this, &MainScreen::butSetInfor_Click);
		
			this->butShowInfor->Location = System::Drawing::Point(33, 235);
			this->butShowInfor->Name = L"butShowInfor";
			this->butShowInfor->Size = System::Drawing::Size(120, 23);
			this->butShowInfor->TabIndex = 24;
			this->butShowInfor->Text = L"Show My Information";
			this->butShowInfor->UseVisualStyleBackColor = true;
			this->butShowInfor->Click += gcnew System::EventHandler(this, &MainScreen::butShowInfor_Click);
			
			this->butUpDownloadFile->Location = System::Drawing::Point(33, 206);
			this->butUpDownloadFile->Name = L"butUpDownloadFile";
			this->butUpDownloadFile->Size = System::Drawing::Size(120, 23);
			this->butUpDownloadFile->TabIndex = 24;
			this->butUpDownloadFile->Text = L"Up/Download File";
			this->butUpDownloadFile->UseVisualStyleBackColor = true;
			this->butUpDownloadFile->Click += gcnew System::EventHandler(this, &MainScreen::butPublicFile_Click);
			
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(187, 359);
			this->Controls->Add(this->butUpDownloadFile);
			this->Controls->Add(this->butShowInfor);
			this->Controls->Add(this->butSetInfor);
			this->Controls->Add(this->butChangePass);
			this->Controls->Add(this->lbOnlineUser);
			this->Controls->Add(this->labOnline);
			this->Controls->Add(this->butDisconnect);
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
	private: System::Void butShowInfor_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butPublicFile_Click(System::Object^ sender, System::EventArgs^ e);
};
}
