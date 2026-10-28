#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream> 


class clsCurrency
{
private:

	enum enMode{enEmpty=1,enUpdate=2};
	enMode _Mode;
	string _Country;
	string _CurrencyName;
	string _CurrecyCode;
	float _Rate;
	static clsCurrency ConvertCurrencyStringToObject(string Line, string Seperator = "#//#")
	{
		vector <string > vCurrencyData;
		vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::enUpdate, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}
	 string _ConvertCurrencyObjectToString(clsCurrency Currency, string Seperator = "#//#")
	{
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());
		return stCurrencyRecord;
	}
	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency  vCurrencyData = ConvertCurrencyStringToObject(Line);
				vCurrencies.push_back(vCurrencyData);
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	static  void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//write Mode
		if (MyFile.is_open())
		{
			for (clsCurrency Currency : vCurrencies)
			{
				string DataLine = Currency._ConvertCurrencyObjectToString(Currency);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void Update()
	{
		vector <clsCurrency> vCurrencies;
		vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrenciesDataToFile(vCurrencies);
	}
	static clsCurrency GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::enEmpty, "", "", "", 0);
	}

public: 
	clsCurrency(enMode Mode , string Country ,string CurrencyName,string CurrencyCode,float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyName = CurrencyName;
		_CurrecyCode = CurrencyCode;
		_Rate = Rate;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::enEmpty);
	}

	 string Country()
	{
		return _Country;
	}
	 string CurrencyName()
	{
		return _CurrencyName;
	}
	 string CurrencyCode()
	{
		return _CurrecyCode;
	}
	float Rate()
	{
		return _Rate;
	}	
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		Update();
	}

 static  clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);

		if (CurrenciesFile.is_open())
		{
			string Line;
			while (getline(CurrenciesFile, Line))
			{
				clsCurrency Currency = ConvertCurrencyStringToObject(Line);
				if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
				{
					CurrenciesFile.close();
					return Currency;

				}
			}
		}
		CurrenciesFile.close();
		return GetEmptyCurrencyObject();
	}
	clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);

		if (CurrenciesFile.is_open())
		{
			string Line;
			while (getline(CurrenciesFile, Line))
			{
				clsCurrency Currency = ConvertCurrencyStringToObject(Line);
				if (clsString::UpperAllString(Currency.Country())== Country)
				{
					CurrenciesFile.close();
					return Currency;

				}
			}
		}
		CurrenciesFile.close();
		return GetEmptyCurrencyObject();
	}
	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}
	static bool IfNeitherCurrencyIsUSD(clsCurrency Currency1, clsCurrency Currency2)
	{
		return (Currency1.CurrencyCode() != "USD" && Currency2.CurrencyCode() != "USD");
	}


	double ConvertToUSD(double Amount)
	{
		return ((double)Amount / Rate());
	}
	double ConvertToOtherCurrencies(double Amount, clsCurrency Currency2)
	{
		Amount = ConvertToUSD(Amount);
		return (double)(Amount *= Currency2.Rate());

	}
	static double CalculateCurrencyExchang(clsCurrency Currency1, clsCurrency Currency2,double Amount)
	{
		if (Currency1.CurrencyCode() == "USD")
		{
			return Currency2.Rate() * Amount;
	   }
		else if (Currency2.CurrencyCode() == "USD")
		{
			return Amount / Currency1.Rate();
		}
		return 0;
	}
	static vector <clsCurrency> GetCurrenciesList()
	{
		vector <clsCurrency> Currencies = _LoadCurrenciesDataFromFile();
		return Currencies;
	}
};

