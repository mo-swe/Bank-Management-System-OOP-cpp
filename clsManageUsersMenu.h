#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include <iomanip>


class clsManageUsersMenu :protected clsScreen
{

private:
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2,
        eDeleteUser = 3, eUpdateUser = 4,
        eFindUser=5,eMainMenu=6
    };

    static short _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6);
        return Choice;
    }


    static void _ShowListUsersScreen()
    {
        //cout << "\nList Users Will Be Here soon :-)\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        //cout << "\nAdd New Users Will Be Here soon :-)\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
       // cout << "\nAdd New User Will Be Here soon :-)\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Will Be Here soon :-)\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void _ShowFindUserScreen()
    {
        //cout << "\Find User Will Be Here soon :-)\n";
        clsFindUserScreen::ShowFindUserScreen();
    }
    static void _GoBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();

    }
    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
    {
        switch (ManageUsersMenuOption)
        {
        case enManageUsersMenuOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case enManageUsersMenuOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case enManageUsersMenuOptions::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }


        case enManageUsersMenuOptions::eMainMenu:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }

public:


    static void ShowManageUsersMenu()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\tManage Users Screen");
        
        cout << endl;
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    }
};

