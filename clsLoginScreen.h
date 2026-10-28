#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
class clsLoginScreen :protected clsScreen
{
	static	bool _Login(int &LoginFaildCount)
	{
		bool FailedLogin = false;
		
		string UserName, Password;
		do
		{
			if (FailedLogin)
			{
				LoginFaildCount--;
				cout << "\nInvalid UserName/Password !\n";
				cout << "You Have " << LoginFaildCount << " Trials to login.\n\n";
			}
			if (LoginFaildCount == 0)
			{
				cout << "\n\n\nYour Loocked after 3 trials\n";
				return false;
			}
			

			cout << "\n Enter UserName: ";
			UserName = clsInputValidate::ReadString();
			cout << "\n Enter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);
			FailedLogin = CurrentUser.IsEmpty();
		} while (FailedLogin);
		CurrentUser.RigsterLogIn();
			clsMainScreen::ShowMainMenu();
			return true;
	}

public:
	static bool ShowLoginScreen(int& LoginFaildCount)
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\t   Login Screen");
		return _Login(LoginFaildCount);
	}
};

