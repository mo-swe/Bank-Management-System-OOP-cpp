#pragma once
#pragma once
#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsAddNewClientScreen :protected clsScreen 
{
	
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }
    static  void _PrintClient(clsBankClient & Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client. Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:
   static void ShowAddNewClientScreen()
    {
       if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
       {
           return;
       }
        clsScreen::_DrawScreenHeader("\tAdd New Client Screen");
        string AccountNumber;
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is exiset , enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\nAdd New Client : \n";

        _ReadClientInfo(Client1);


        clsBankClient::enSaveResults Save;
        Save = Client1.Save();

        switch (Save)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\n Client Added Successfuly :-)\n";
            _PrintClient(Client1);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\n Erorr was not save Because it is Empty. \n";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\n Erorr was not save Because Client Aleardy Exist . \n";
            break;
        }
        }
    }
};

