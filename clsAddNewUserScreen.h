#pragma once
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsAddNewUserScreen :protected clsScreen 
{

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permissions : ";
        User.Permissions = _ReadPermissions();
    }
    static int _ReadPermissions()
    {
        int Permissions = 0;
        char Answer = ' ';

        cout << "\n Do you want give full access y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            return -1;
        }
        cout << "\n Do you want give access to ? ";
        cout << "\n Show Clients List y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pListClients;
        }
        cout << "\n Add New Client ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pAddNewClient;
        }
        cout << "\n Delete Client ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pDeleteClient;
        }
        cout << "\n Update Client  y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pUpdateClient;
        }
        cout << "\n Find Client y/n ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pFindClient;
        }
        cout << "\n Transactions  y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pTransactions;
        }
        cout << "\n Manage Users  y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pManageUsers;
        }
        cout << "\n Log Registers Screen y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions |= clsUser::enPermissions::pRegister;
        }

		cout << "\n Currency Exchange Screen y/n? ";
		cin >> Answer;
        if (toupper(Answer) == 'Y')

        {
            Permissions |= clsUser::enPermissions::pCurrency;
        }

        return Permissions;
    }
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
    static void ShowAddNewUserScreen()
    {
        clsScreen::_DrawScreenHeader("\tAdd New User Screen");
        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is exiset , enter another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::GetAddNewUserObject(UserName);

        cout << "\nAdd New User : \n";

        _ReadUserInfo(User1);


        clsUser::enSaveResults Save;
        Save = User1.Save();

        switch (Save)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\n User Added Successfuly :-)\n";
            _PrintUser(User1);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\n Erorr was not save Because it is Empty. \n";
            break;
        }
        case clsUser::enSaveResults::svFaildUserNameExists:
        {
            cout << "\n Erorr was not save Because User Aleardy Exist . \n";
            break;
        }
        }
    }
};


