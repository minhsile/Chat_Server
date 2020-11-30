#pragma once

namespace Client {
	ref class ConnectServer;
}

#include "Controller.h"
namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ConnectServer
	/// </summary>
	public ref class ConnectServer : public System::Windows::Forms::Form
	{
	public:
		ConnectServer(void)
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
		~ConnectServer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labTxtIP;
	protected:

	protected:

	private: System::Windows::Forms::Label^ labTxtPort;
	private: System::Windows::Forms::TextBox^ txtIP;
	private: System::Windows::Forms::TextBox^ txtPort;
	private: System::Windows::Forms::Button^ butConnect;


	protected:


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labTxtIP = (gcnew System::Windows::Forms::Label());
			this->labTxtPort = (gcnew System::Windows::Forms::Label());
			this->txtIP = (gcnew System::Windows::Forms::TextBox());
			this->txtPort = (gcnew System::Windows::Forms::TextBox());
			this->butConnect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labTxtIP
			// 
			this->labTxtIP->AutoSize = true;
			this->labTxtIP->Location = System::Drawing::Point(19, 31);
			this->labTxtIP->Name = L"labTxtIP";
			this->labTxtIP->Size = System::Drawing::Size(20, 13);
			this->labTxtIP->TabIndex = 0;
			this->labTxtIP->Text = L"IP:";
			// 
			// labTxtPort
			// 
			this->labTxtPort->AutoSize = true;
			this->labTxtPort->Location = System::Drawing::Point(19, 58);
			this->labTxtPort->Name = L"labTxtPort";
			this->labTxtPort->Size = System::Drawing::Size(29, 13);
			this->labTxtPort->TabIndex = 1;
			this->labTxtPort->Text = L"Port:";
			// 
			// txtIP
			// 
			this->txtIP->Location = System::Drawing::Point(86, 31);
			this->txtIP->Name = L"txtIP";
			this->txtIP->Size = System::Drawing::Size(100, 20);
			this->txtIP->TabIndex = 2;
			// 
			// txtPort
			// 
			this->txtPort->Location = System::Drawing::Point(86, 58);
			this->txtPort->Name = L"txtPort";
			this->txtPort->Size = System::Drawing::Size(100, 20);
			this->txtPort->TabIndex = 3;
			// 
			// butConnect
			// 
			this->butConnect->Location = System::Drawing::Point(60, 112);
			this->butConnect->Name = L"butConnect";
			this->butConnect->Size = System::Drawing::Size(75, 23);
			this->butConnect->TabIndex = 4;
			this->butConnect->Text = L"Connect";
			this->butConnect->UseVisualStyleBackColor = true;
			this->butConnect->Click += gcnew System::EventHandler(this, &ConnectServer::butConnect_Click);
			// 
			// ConnectServer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(212, 155);
			this->Controls->Add(this->butConnect);
			this->Controls->Add(this->txtPort);
			this->Controls->Add(this->txtIP);
			this->Controls->Add(this->labTxtPort);
			this->Controls->Add(this->labTxtIP);
			this->Name = L"ConnectServer";
			this->Text = L"ConnectServer";
			this->Load += gcnew System::EventHandler(this, &ConnectServer::ConnectServer_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void butConnect_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ConnectServer_Load(System::Object^ sender, System::EventArgs^ e);

};
}
