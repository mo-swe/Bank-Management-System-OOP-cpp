#pragma once
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static  void _PrintUser(clsUser& User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }
public:
    static void ShowDeleteUserScreen()
    {
        clsScreen::_DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);


        _PrintUser(User);
        char DeleteOrNot;
        cout << "\n\n are you sure you want delete this User :\n";
        cin >> DeleteOrNot;

        if (toupper(DeleteOrNot) == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted successfuly :-)\n";
                
            }
            else
            {
                cout << "\nError User Was Not Deleted\n";
            }
            _PrintUser(User);
        }

    }

};



