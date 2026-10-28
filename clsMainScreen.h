#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsLoginScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersMenu.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegisters=8,eCurrencyExchange=9,eExit = 10
    };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 10);
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        //  cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();


    }

    static void _ShowAddNewClientsScreen()
    {
        // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteUserScreen();

    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();


    }

    static void _ShowFindClientScreen()
    {
        // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();


    }

    static void _ShowTransactionsMenue()
    {
        // cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenu();

    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersMenu::ShowManageUsersMenu();



    }
    static void _ShowLoginRegistersScreen()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
	}
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
    {

        switch (MainMenuOption)
        {
        case enMainMenuOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenuOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenuOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenuOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenuOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenuOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenuOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case enMainMenuOptions::eLoginRegisters:
            system("cls");
            _ShowLoginRegistersScreen();
            _GoBackToMainMenue();
            break;
		case enMainMenuOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenue();
			break;  
        case enMainMenuOptions::eExit:
            system("cls");
            _Logout();

            break;
        }

    }



public:


    static void ShowMainMenu()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
    }

};


