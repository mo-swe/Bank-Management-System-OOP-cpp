#pragma once

#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen: protected clsScreen
{
private:
    static  void _Print(clsBankClient& Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
public:
    static void ShowDeleteUserScreen()
{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\tDelete Client Screen");

    string AccountNumber = "";

    cout << "\nPlease Enter client Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);


    _Print(Client);
    char DeleteOrNot;
    cout << "\n\n are you sure you want delete this client :\n";
    cin >> DeleteOrNot;

    if (toupper(DeleteOrNot) == 'Y')
    {
    if (Client.Delete())
    {
        cout << "\nClient Deleted successfuly :-)\n";
        _Print(Client);
    }
    else
    {
        cout << "\nError Client Was Not Deleted\n";
    }
    }

}

};

