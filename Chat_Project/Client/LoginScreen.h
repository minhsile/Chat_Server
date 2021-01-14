#pragma once


namespace Client {
	ref class LoginScreen;
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
	/// Summary for LoginScreen
	/// </summary>
	public ref class LoginScreen : public System::Windows::Forms::Form
	{
	public:
		LoginScreen(void)
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
		~LoginScreen()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::Button^ butLogin;
	private: System::Windows::Forms::Label^ labPassword;
	private: System::Windows::Forms::Button^ butSignup;
	private: System::Windows::Forms::Label^ labUsername;

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
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->butLogin = (gcnew System::Windows::Forms::Button());
			this->labPassword = (gcnew System::Windows::Forms::Label());
			this->butSignup = (gcnew System::Windows::Forms::Button());
			this->labUsername = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			this->txtPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtPassword->Location = System::Drawing::Point(113, 73);
			this->txtPassword->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->PasswordChar = 42;
			this->txtPassword->Size = System::Drawing::Size(235, 26);
			this->txtPassword->TabIndex = 14;
			this->butLogin->Location = System::Drawing::Point(226, 117);
			this->butLogin->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->butLogin->Name = L"butLogin";
			this->butLogin->Size = System::Drawing::Size(109, 28);
			this->butLogin->TabIndex = 16;
			this->butLogin->Text = L"Log in";
			this->butLogin->UseVisualStyleBackColor = true;
			this->butLogin->Click += gcnew System::EventHandler(this, &LoginScreen::butLogin_Click);
			this->labPassword->AutoSize = true;
			this->labPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labPassword->Location = System::Drawing::Point(27, 76);
			this->labPassword->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labPassword->Name = L"labPassword";
			this->labPassword->Size = System::Drawing::Size(78, 20);
			this->labPassword->TabIndex = 13;
			this->labPassword->Text = L"Password";
			this->butSignup->Location = System::Drawing::Point(65, 117);
			this->butSignup->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->butSignup->Name = L"butSignup";
			this->butSignup->Size = System::Drawing::Size(109, 28);
			this->butSignup->TabIndex = 17;
			this->butSignup->Text = L"Sign up";
			this->butSignup->UseVisualStyleBackColor = true;
			this->butSignup->Click += gcnew System::EventHandler(this, &LoginScreen::butSignup_Click);
			this->labUsername->AutoSize = true;
			this->labUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labUsername->Location = System::Drawing::Point(27, 27);
			this->labUsername->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labUsername->Name = L"labUsername";
			this->labUsername->Size = System::Drawing::Size(83, 20);
			this->labUsername->TabIndex = 11;
			this->labUsername->Text = L"Username";
			this->txtUsername->BackColor = System::Drawing::SystemColors::Window;
			this->txtUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtUsername->Location = System::Drawing::Point(113, 27);
			this->txtUsername->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(235, 26);
			this->txtUsername->TabIndex = 12;
			this->AcceptButton = this->butLogin;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(383, 171);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->labPassword);
			this->Controls->Add(this->labUsername);
			this->Controls->Add(this->butSignup);
			this->Controls->Add(this->butLogin);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->Name = L"LoginScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CLIENT";
			this->Load += gcnew System::EventHandler(this, &LoginScreen::LoginScreen_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//public: MainScreen^ Mf = gcnew MainScreen;
	private: System::Void butSignup_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void LoginScreen_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butLogin_Click(System::Object^ sender, System::EventArgs^ e);
};
}
