#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>



class clsUser : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };


	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	string _RegisterDateTime;
	bool _MarkedForDelete = false;
	 static const short _EncryptionKey = 2232;

	

	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
	{

		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User.UserName + Seperator;
		stUserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		stUserRecord += to_string(User.Permissions);

		return stUserRecord;

	}
	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

	}
	
	static  vector <clsUser> _LoadUsersDataFromFile()
	{

		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsUser User = _ConvertLinetoUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();

		}

		return vUsers;

	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser U : vUsers)
			{
				if (U.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConverUserObjectToLine(U);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	string _RegstierLoginInString(string Seprator = "#//#")
	{

		string RegisterDetailesInLine;
		RegisterDetailesInLine += clsDate::GetSystemDateTimeString() + Seprator;
		RegisterDetailesInLine += UserName + Seprator;
		RegisterDetailesInLine += clsUtil::EncryptText(Password) + Seprator;
		RegisterDetailesInLine += to_string(Permissions);

		return RegisterDetailesInLine;
	}
	void _SaveRegstierDetailesInFile()
	{
		fstream RegisterDetailesFile;

		RegisterDetailesFile.open("LoginRegister.txt", ios::out | ios::app);

		if (RegisterDetailesFile.is_open())
		{
			string DataLine = _RegstierLoginInString();
			RegisterDetailesFile << DataLine << endl;
		}
		RegisterDetailesFile.close();

	}
	
	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.GetUserName() == UserName)
			{
				U = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}


public:

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string UserName, string Password,
		int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)

	{
		_Mode = Mode;
		_Password = Password;
		_UserName = UserName;
		_Permissions = Permissions;
	}
	
	enum enPermissions
	{
		pAll = -1, pListClients = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16,
		pTransactions = 32, pManageUsers = 64, pRegister = 128
		, pCurrency = 256
	};
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}


	 string GetUserName()
	{
		return _UserName;
	}
	 void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	string GetRegisterDateTime()
	{
		return _RegisterDateTime;
	}
	

	 string GetPassword() { return _Password; }
	 void SetPassword(string Password) { _Password = Password; }
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	// Permissions Property
	 int GetPermissions() { return _Permissions; }
	 void SetPermissions(int Permissions) { _Permissions = Permissions; }
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;




	static clsUser Find(string UserName)
	{


		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{



		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName && User.GetPassword() == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };


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
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserNameExists;
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
	static bool IsUserExist(string UserName)
	{

		clsUser User1 = clsUser::Find(UserName);
		return (!User1.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				U._MarkedForDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	

	 bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::pAll) // أو -1
		{
			return true;
		}
		
		if (this->Permissions & Permission)
			true;
		
			return false;

	}

	 static stLoginRegisterRecord ConvertLinetoRegisterObject(string Line, string Seperator = "#//#")
	 {
		 vector<string> vData;
		 vData = clsString::Split(Line, Seperator);
		 stLoginRegisterRecord Record;
		 Record.DateTime = vData[0];
		 Record.UserName = vData[1];
		 Record.Password = clsUtil::DecryptText(vData[2]);
		 Record.Permissions = stoi(vData[3]);
		 return Record;

	 }
	 static  vector <stLoginRegisterRecord> LoadRegistersFromFile()
	 {

		 vector <stLoginRegisterRecord> vData;

		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::in);//read Mode

		 if (MyFile.is_open())
		 {

			 string Line;


			 while (getline(MyFile, Line))
			 {

				 stLoginRegisterRecord Record = ConvertLinetoRegisterObject(Line);

				 vData.push_back(Record);
			 }

			 MyFile.close();

		 }

		 return vData;

	 }
	 void RigsterLogIn()
	 {
		 _SaveRegstierDetailesInFile();
	 }


};

