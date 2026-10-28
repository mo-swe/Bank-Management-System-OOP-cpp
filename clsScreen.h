#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;


class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title,string Subtitle="")
	{
		cout << setw(40) << left << "" << "______________________________________";
		cout << "\n\n\t\t\t\t\t" << setw(50) << left << Title << endl;
		if (Subtitle != "")
		{
			cout << "\n\t\t\t\t\t" << setw(50) << left << Subtitle << endl;
		}
		cout << setw(40) << left << "" << "______________________________________\n";
		cout << "\n\n\t\t\t\t\tUser :" << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tDate :" << clsDate::DateToString(clsDate()) << endl;
	}
	static bool CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			cout << "\n\nUser :" << CurrentUser.UserName;
			cout << "\nDate :" << clsDate::DateToString(clsDate::GetSystemDate());
			return false;
		}
		else
		{
			true;
		}
	}
};

