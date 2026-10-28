#pragma once
#include "clsDate.h"
#include <iostream>
using namespace std;


class clsInputValidate
{

public:
	static string ReadString()
	{
		string S1 = " ";
		getline(cin>>ws, S1);
		return S1;
	}
	template  <typename T> static  T IsNumberBetween(T Number, short NumberFrom, T NumberEnd)
	{
		return (Number >= NumberFrom) && (Number <= NumberEnd);
	}
	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}
	static bool IsDateBetween(clsDate Date,clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;

	}
	template <typename T> static T ReadNumber()
	{
		T number;
		string ErrorMessage = "Invalid Number, Enter again:\n";
		// cin >> number evaluates to false if non-numeric characters are entered
		while (!(std::cin >> number)) {
			cout << ErrorMessage << endl;
			cin.clear(); // Reset error state flags
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear invalid input from buffer
		}

		return number;
	}
	template  <typename T> static  T ReadNumberBetween(T NumberFrom, T NumberEnd)
	{
		T Number;
		string Message = "Invalid Number, Enter again:\n";
			Number =ReadNumber<T>();
			while (!IsNumberBetween(Number, NumberFrom, NumberEnd))
			{
				cout << Message << endl;
				Number = ReadNumber<T>();

		     }
		return Number;
	}


	


};

