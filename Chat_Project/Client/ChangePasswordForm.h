#pragma once

namespace Client {
	ref class ChangePasswordScreen;
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
	/// Summary for ChangePasswordScreen
	/// </summary>
	public ref class ChangePasswordScreen : public System::Windows::Forms::Form
	{
	public:
		ChangePasswordScreen(void)
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
		~ChangePasswordScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labUsername;
	private: System::Windows::Forms::Label^ labOldPass;

	private: System::Windows::Forms::Label^ labNewPass;
	private: System::Windows::Forms::Label^ labConfirmPass;
	private: System::Windows::Forms::TextBox^ txtUsername;
	private: System::Windows::Forms::TextBox^ txtOldPass;
	private: System::Windows::Forms::TextBox^ txtNewPass;
	private: System::Windows::Forms::TextBox^ txtConfirmPass;
	private: System::Windows::Forms::Button^ butChange;

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
			this->labUsername = (gcnew System::Windows::Forms::Label());
			this->labOldPass = (gcnew System::Windows::Forms::Label());
			this->labNewPass = (gcnew System::Windows::Forms::Label());
			this->labConfirmPass = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->txtOldPass = (gcnew System::Windows::Forms::TextBox());
			this->txtNewPass = (gcnew System::Windows::Forms::TextBox());
			this->txtConfirmPass = (gcnew System::Windows::Forms::TextBox());
			this->butChange = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labUsername
			// 
			this->labUsername->AutoSize = true;
			this->labUsername->Location = System::Drawing::Point(73, 20);
			this->labUsername->Name = L"labUsername";
			this->labUsername->Size = System::Drawing::Size(58, 13);
			this->labUsername->TabIndex = 0;
			this->labUsername->Text = L"Username:";
			// 
			// labOldPass
			// 
			this->labOldPass->AutoSize = true;
			this->labOldPass->Location = System::Drawing::Point(38, 46);
			this->labOldPass->Name = L"labOldPass";
			this->labOldPass->Size = System::Drawing::Size(93, 13);
			this->labOldPass->TabIndex = 1;
			this->labOldPass->Text = L"Current Password:";
			// 
			// labNewPass
			// 
			this->labNewPass->AutoSize = true;
			this->labNewPass->Location = System::Drawing::Point(50, 70);
			this->labNewPass->Name = L"labNewPass";
			this->labNewPass->Size = System::Drawing::Size(81, 13);
			this->labNewPass->TabIndex = 2;
			this->labNewPass->Text = L"New Password:";
			// 
			// labConfirmPass
			// 
			this->labConfirmPass->AutoSize = true;
			this->labConfirmPass->Location = System::Drawing::Point(12, 96);
			this->labConfirmPass->Name = L"labConfirmPass";
			this->labConfirmPass->Size = System::Drawing::Size(119, 13);
			this->labConfirmPass->TabIndex = 2;
			this->labConfirmPass->Text = L"Confirm New Password:";
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(138, 17);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(100, 20);
			this->txtUsername->TabIndex = 3;
			// 
			// txtOldPass
			// 
			this->txtOldPass->Location = System::Drawing::Point(138, 43);
			this->txtOldPass->Name = L"txtOldPass";
			this->txtOldPass->Size = System::Drawing::Size(100, 20);
			this->txtOldPass->TabIndex = 3;
			// 
			// txtNewPass
			// 
			this->txtNewPass->Location = System::Drawing::Point(138, 67);
			this->txtNewPass->Name = L"txtNewPass";
			this->txtNewPass->Size = System::Drawing::Size(100, 20);
			this->txtNewPass->TabIndex = 3;
			// 
			// txtConfirmPass
			// 
			this->txtConfirmPass->Location = System::Drawing::Point(138, 93);
			this->txtConfirmPass->Name = L"txtConfirmPass";
			this->txtConfirmPass->Size = System::Drawing::Size(100, 20);
			this->txtConfirmPass->TabIndex = 3;
			// 
			// butChange
			// 
			this->butChange->Location = System::Drawing::Point(96, 121);
			this->butChange->Name = L"butChange";
			this->butChange->Size = System::Drawing::Size(105, 23);
			this->butChange->TabIndex = 4;
			this->butChange->Text = L"Change Password";
			this->butChange->UseVisualStyleBackColor = true;
			this->butChange->Click += gcnew System::EventHandler(this, &ChangePasswordScreen::butChange_Click);
			// 
			// ChangePasswordScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(296, 156);
			this->Controls->Add(this->butChange);
			this->Controls->Add(this->txtConfirmPass);
			this->Controls->Add(this->txtNewPass);
			this->Controls->Add(this->txtOldPass);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->labConfirmPass);
			this->Controls->Add(this->labNewPass);
			this->Controls->Add(this->labOldPass);
			this->Controls->Add(this->labUsername);
			this->Name = L"ChangePasswordScreen";
			this->Text = L"Change Password";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ChangePasswordScreen_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butChange_Click(System::Object^ sender, System::EventArgs^ e);
};
}
