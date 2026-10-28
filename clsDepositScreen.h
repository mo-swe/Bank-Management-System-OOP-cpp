#pragma once

#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDepositScreen :protected clsScreen
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


    static void ShowDepositScreen()
    {
        clsScreen::_DrawScreenHeader("\t  Deposit Screen");

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
        cout << "\nEnter Deposit Amount :";
        Amount = clsInputValidate::ReadNumber<double>();

        char DeleteOrNot;
        cout << "\n\n are you sure you want Perform this Transaction :\n";
        cin >> DeleteOrNot;

        if (toupper(DeleteOrNot) == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully \n";
            cout << "\nNew Balance Is :" << Client.AccountBalance;
        }
        else
        {
            cout << "\n Operation Was Cacelled. \n";
        }

    }


};

