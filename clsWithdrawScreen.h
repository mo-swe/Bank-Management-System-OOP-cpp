#pragma once
#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class  clsWithdrawScreen
    :protected clsScreen
{
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


    static void ShowWithdrawScreen()
    {
        clsScreen::_DrawScreenHeader("\t  Withdraw Screen");

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
        double Amount;
        cout << "\nEnter Withdraw Amount :";
        Amount = clsInputValidate::ReadNumber<double>();

        char DeleteOrNot;
        cout << "\n\n are you sure you want Perform this Transaction :\n";
        cin >> DeleteOrNot;

        if (toupper(DeleteOrNot) == 'Y')
        {
            if (Client.Withdraw(Amount))
            {

                cout << "\nAmount Withrdaw Successfully \n";
                cout << "\nNew Balance Is :" << Client.AccountBalance;
            }
            else
            {
                cout << "\ncannot Withdraw , Insuffecinet Balance!\n. \n";
                cout << "\nAmount to Withdraw is :" << Amount;
                cout << "\nyour Balance Is :  " << Client.AccountBalance;
            }

        }
        else
        {
            cout << "\n Operation Was Cacelled. \n";
        }


    };



};
