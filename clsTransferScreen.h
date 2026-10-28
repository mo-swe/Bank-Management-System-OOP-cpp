#pragma once

#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsTransferScreen :protected clsScreen
{
private :
    static  void _Print(clsBankClient& Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public :

    static void ShowTransferScreen()
    {
        clsScreen::_DrawScreenHeader("\t  Transfer Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number to Transfer From : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient ClinetToTransferFrom = clsBankClient::Find(AccountNumber);


        _Print(ClinetToTransferFrom);


        cout << "\nPlease Enter Account Number to Transfer To : ";
        AccountNumber = clsInputValidate::ReadString();

        
      
        while (!clsBankClient::IsClientExist(AccountNumber) || AccountNumber == ClinetToTransferFrom.AccountNumber())
        {
            if (AccountNumber == ClinetToTransferFrom.AccountNumber())
            {
                cout << "\nYou cannot transfer to the same account. Choose another Account Number: ";
            }
            else
            {
                cout << "\nAccount number is not found, choose another one: ";
            }

            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient ClinetToTransferTo = clsBankClient::Find(AccountNumber);


        _Print(ClinetToTransferTo);

        double Amount = 0;
        char YeaOrNo;
        cout << "\n Enter Amount To Transfer\n";
        Amount = clsInputValidate::ReadNumber<double>();

        while(Amount>ClinetToTransferFrom.AccountBalance)
        {
            cout << "\nAmount Exceeds The Avaliable Balance , Enter Another Amount ?";
            Amount = clsInputValidate::ReadNumber<double>();
        }

        cout << "\n\n are you sure you want Perform this Transaction :\n";
        cin >> YeaOrNo;

        if (toupper(YeaOrNo) == 'Y')
        {

            if(ClinetToTransferFrom.Transfer(Amount,ClinetToTransferTo))
            { 
            cout << "\nTransfer Done Successfully \n";
            }
           
        }
        else
        {
            cout << "\nOperation Was Cacelled. \n";
        }
        _Print(ClinetToTransferFrom);
        _Print(ClinetToTransferTo);
    }
};

