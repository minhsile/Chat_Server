#pragma once

namespace Server {
	ref class MainForm;
}

#include "Server.h"

namespace Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Label^ labIPServer;
	private: System::Windows::Forms::TextBox^ txtIPServer;
	private: System::Windows::Forms::Label^ labPortServer;
	private: System::Windows::Forms::TextBox^ txtPortServer;
	private: System::Windows::Forms::TextBox^ txtClientChatBox;
	private: System::Windows::Forms::Label^ labConference;
	private: System::Windows::Forms::Button^ btListen;

	private: System::Windows::Forms::Label^ labConnect;
	private: System::Windows::Forms::TextBox^ txtConnected;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	

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
			this->labIPServer = (gcnew System::Windows::Forms::Label());
			this->txtIPServer = (gcnew System::Windows::Forms::TextBox());
			this->labPortServer = (gcnew System::Windows::Forms::Label());
			this->txtPortServer = (gcnew System::Windows::Forms::TextBox());
			this->btListen = (gcnew System::Windows::Forms::Button());
			this->txtClientChatBox = (gcnew System::Windows::Forms::TextBox());
			this->labConference = (gcnew System::Windows::Forms::Label());
			this->labConnect = (gcnew System::Windows::Forms::Label());
			this->txtConnected = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			this->labIPServer->AutoSize = true;
			this->labIPServer->Location = System::Drawing::Point(23, 13);
			this->labIPServer->Name = L"labIPServer";
			this->labIPServer->Size = System::Drawing::Size(20, 13);
			this->labIPServer->TabIndex = 1;
			this->labIPServer->Text = L"IP:";
			this->txtIPServer->Location = System::Drawing::Point(49, 10);
			this->txtIPServer->Name = L"txtIPServer";
			this->txtIPServer->Size = System::Drawing::Size(109, 20);
			this->txtIPServer->TabIndex = 2;
			this->txtIPServer->TextChanged += gcnew System::EventHandler(this, &MainForm::txtIPServer_TextChanged);
			this->labPortServer->AutoSize = true;
			this->labPortServer->Location = System::Drawing::Point(14, 37);
			this->labPortServer->Name = L"labPortServer";
			this->labPortServer->Size = System::Drawing::Size(29, 13);
			this->labPortServer->TabIndex = 3;
			this->labPortServer->Text = L"Port:";
			this->txtPortServer->Location = System::Drawing::Point(49, 36);
			this->txtPortServer->Name = L"txtPortServer";
			this->txtPortServer->Size = System::Drawing::Size(67, 20);
			this->txtPortServer->TabIndex = 4;
			this->btListen->Location = System::Drawing::Point(67, 71);
			this->btListen->Name = L"btListen";
			this->btListen->Size = System::Drawing::Size(75, 23);
			this->btListen->TabIndex = 5;
			this->btListen->Text = L"Run Server";
			this->btListen->UseVisualStyleBackColor = true;
			this->btListen->Click += gcnew System::EventHandler(this, &MainForm::btListen_Click);
			this->txtClientChatBox->Location = System::Drawing::Point(162, 37);
			this->txtClientChatBox->Multiline = true;
			this->txtClientChatBox->Name = L"txtClientChatBox";
			this->txtClientChatBox->ReadOnly = true;
			this->txtClientChatBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtClientChatBox->Size = System::Drawing::Size(267, 187);
			this->txtClientChatBox->TabIndex = 10;
			this->labConference->AutoSize = true;
			this->labConference->Location = System::Drawing::Point(268, 17);
			this->labConference->Name = L"labConference";
			this->labConference->Size = System::Drawing::Size(61, 13);
			this->labConference->TabIndex = 6;
			this->labConference->Text = L"CHAT BOX";
			this->labConnect->AutoSize = true;
			this->labConnect->Location = System::Drawing::Point(23, 120);
			this->labConnect->Name = L"labConnect";
			this->labConnect->Size = System::Drawing::Size(95, 13);
			this->labConnect->TabIndex = 9;
			this->labConnect->Text = L"ONLINE CLIENTS";
			this->txtConnected->Location = System::Drawing::Point(12, 136);
			this->txtConnected->Multiline = true;
			this->txtConnected->Name = L"txtConnected";
			this->txtConnected->ReadOnly = true;
			this->txtConnected->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtConnected->Size = System::Drawing::Size(130, 88);
			this->txtConnected->TabIndex = 10;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(441, 240);
			this->Controls->Add(this->btListen);
			this->Controls->Add(this->txtConnected);
			this->Controls->Add(this->labConnect);
			this->Controls->Add(this->labConference);
			this->Controls->Add(this->txtClientChatBox);
			this->Controls->Add(this->txtPortServer);
			this->Controls->Add(this->labPortServer);
			this->Controls->Add(this->txtIPServer);
			this->Controls->Add(this->labIPServer);
			this->Name = L"MainForm";
			this->Text = L"Server";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: Thread^ threadListenClient;
	public: static void ListenClientMessage(Object^ obj);
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	public: void AddTextToContent(String^ text);
	public: void UpdateConnectedClient(List<String^>^ lstClient);
	//public: void UpdateClientList(List<String^>^ lstClient);
	private: System::Void btListen_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void labInfo_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void labClientList_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void txtIPServer_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void txtPortServer_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
