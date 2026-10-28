#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;



    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _RegisterTransferInString(clsBankClient DestinationClient, double Amount, string Seperator = "#//#")
    {
        string stTransferRecord = "";
		stTransferRecord += clsDate::GetSystemDateTimeString() + Seperator;
        stTransferRecord += AccountNumber() + Seperator;
        stTransferRecord += DestinationClient.AccountNumber() + Seperator;
        stTransferRecord += to_string(Amount) + Seperator;
        stTransferRecord += to_string(AccountBalance) + Seperator;
        stTransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        stTransferRecord += CurrentUser.UserName;

        return stTransferRecord;
	}
    void _SaveTransferRecord(clsBankClient SourceClient, clsBankClient DestinationClient, double Amount)
    {
        fstream TransferDetailesFile;
        TransferDetailesFile.open("TransferLog.txt", ios::out | ios::app);
        if (TransferDetailesFile.is_open())
        {
            string DataLine = _RegisterTransferInString(DestinationClient, Amount);
            TransferDetailesFile << DataLine << endl;
        }
        TransferDetailesFile.close();
	}


public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

   

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    void Deposit(float Amount)
    {
        AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        else
        {
            AccountBalance -= Amount;
            Save();
            return true;
        }
    }
    bool Transfer(double AmountToTransfer, clsBankClient &DestinationClient)
    {
        if (AmountToTransfer > AccountBalance)
        {
            return false; 
        }
        Withdraw(AmountToTransfer);
        DestinationClient.Deposit(AmountToTransfer);
		_SaveTransferRecord(*this, DestinationClient, AmountToTransfer);
        return true;
    }
    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;

    }


    struct stTransferRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SourceBalanceAfterTransfer;
        double DestinationBalanceAfterTransfer;
        string UserName;
	};

    static stTransferRecord ConvertTransferLineToRecord(string Line, string Seperator = "#//#")
    {
        vector<string> vTransferData;
        vTransferData = clsString::Split(Line, Seperator);
        stTransferRecord TransferRecord;
        TransferRecord.DateTime = vTransferData[0];
        TransferRecord.SourceAccountNumber = vTransferData[1];
        TransferRecord.DestinationAccountNumber = vTransferData[2];
        TransferRecord.Amount = stod(vTransferData[3]);
        TransferRecord.SourceBalanceAfterTransfer = stod(vTransferData[4]);
        TransferRecord.DestinationBalanceAfterTransfer = stod(vTransferData[5]);
        TransferRecord.UserName = vTransferData[6];
        return TransferRecord;
	}

   static  vector < stTransferRecord> GetTransfersList()
    {
        vector <stTransferRecord> vTransfers;
        fstream TransferDetailesFile;

        TransferDetailesFile.open("TransferLog.txt", ios::in);
        if (TransferDetailesFile.is_open())
        {
            string Line;
            while (getline(TransferDetailesFile, Line))
            {
                stTransferRecord TransferRecord = ConvertTransferLineToRecord(Line);
                vTransfers.push_back(TransferRecord);
            }
        }
        TransferDetailesFile.close();
        return vTransfers;
    }
};

