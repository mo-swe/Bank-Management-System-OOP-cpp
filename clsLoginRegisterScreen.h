#pragma once
#pragma once
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsLoginRegisterScreen : protected clsScreen
{
    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord Record)
    {
        cout << "\t|  " << left << setw(26) << Record.DateTime;
        cout << "| " << left << setw(20) << Record.UserName;
        cout << "| " << left << setw(20) << Record.Password;
        cout << "| " << left << setw(12) << Record.Permissions;
    }
public:
    static  void ShowLoginRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pRegister))
        {
            return;
        }
        vector <clsUser::stLoginRegisterRecord>RegistersList = clsUser::LoadRegistersFromFile();

        clsScreen::_DrawScreenHeader("Login Register List Screen", "\t    (" + to_string(RegistersList.size()) + ") Record(s).");

        // طباعة القائمة العلوية للجدول (Table Header)
        cout << "\n\t____________________________________________________________________________________________________\n" << endl;
        cout << "\t| " << left << setw(27) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(12) << "Permissions" << endl;
        cout << "\t____________________________________________________________________________________________________\n" << endl;

        // طباعة عناصر الـ vector
        if (RegistersList.empty())
        {
            cout << "\t\t\t\tNo Logins Available In the System!\n";
        }
        else
        {
            for (const clsUser::stLoginRegisterRecord& Record : RegistersList)
            {
                _PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }
        }

        cout << "\t____________________________________________________________________________________________________\n" << endl;
    }
};

