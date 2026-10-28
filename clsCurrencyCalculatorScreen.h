#pragma once
#include <iostream>
#include <cctype>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>

class clsCurrencyCalculatorScreen :protected clsScreen 
{
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n----------------------------------------------------\n";
		cout << "\nCountry     : " << Currency.Country();
		cout << "\nCurrency    : " << Currency.CurrencyName();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nRate        : " << Currency.Rate() << endl;
		cout << "----------------------------------------------------\n";
	}
	static double _ReadAmount()
	{
		double Amount = 0;
		cout << "\n\nEnter Amount : \n";
		Amount = clsInputValidate::ReadNumber<double>();
		return Amount;
	}
	static clsCurrency _GetCurrency(string Messege)
	{
		string Code = "";
	
			cout << "\n\nEnter Currency " << Messege << " Code : " << endl;
			Code = clsInputValidate::ReadString();
			clsCurrency Currecny = clsCurrency::FindByCode(Code);
			while (Currecny.IsEmpty())
			{
				cout << "\nPlease enter a valid Currency Code :" << endl;
				Code = clsInputValidate::ReadString();
			 Currecny = clsCurrency::FindByCode(Code);
		      }
			return Currecny;
	}

	static void _PrintCalculationsResults()
	{
		clsCurrency Currency1 = _GetCurrency("From");
		clsCurrency Currency2 = _GetCurrency("To");
		while (Currency1.CurrencyCode() == Currency2.CurrencyCode())
		{
			cout << "\n\nError : Both Currencies are the same, Please try again.\n";
			Currency2 = _GetCurrency("To");
		}
		
		double Amount = _ReadAmount();
		double AmountInUSD = Currency1.ConvertToUSD(Amount);
		
			cout << "\n\nConvert From : \n";
			_PrintCurrency(Currency1);
			cout << endl << Amount << " " << Currency1.CurrencyCode() << " = " <<
				AmountInUSD << " " << "USD " << endl;
			

		if(!(Currency2.CurrencyCode() == "USD"))
		{
			cout << "\n\nTo : \n";
			_PrintCurrency(Currency2);
			cout << endl << Amount << " " <<Currency1.CurrencyCode() << " = " <<
				Currency1.ConvertToOtherCurrencies(Amount,Currency2) << " " << Currency2.CurrencyCode() << endl;

		}

	}
public :
	/*static void ShowCurrencyCalculatorScreen()
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\tCurrency Calculator Screen");
		string Code = "";
		do
		{

			cout << "\n\nEnter Currency from Code : \n";
			Code = clsInputValidate::ReadString();
		} while (!clsCurrency::IsCurrencyExist(Code));

		clsCurrency FromCurrency = clsCurrency::FindByCode(Code);

		do
		{
			cout << "\n\nEnter Currency to Code : \n";
			Code = clsInputValidate::ReadString();
		} while (!clsCurrency::IsCurrencyExist(Code));

		clsCurrency ToCurrency = clsCurrency::FindByCode(Code);

		if (FromCurrency.CurrencyCode() == ToCurrency.CurrencyCode())
		{
			cout << "\n\nError : Both Currencies are the same, Please try again.\n";
			return;
		}


		double Amount = 0;
		cout << "\n\nEnter Amount : \n";
		Amount = clsInputValidate::ReadDblNumber();



		if (!clsCurrency::IfNeitherCurrencyIsUSD(FromCurrency, ToCurrency))
		{
			cout << "\n\nConvert From : \n";
			_PrintCurrency(FromCurrency);
			cout << endl << Amount << " " << FromCurrency.CurrencyCode() << " = " <<
				clsCurrency::CalculateCurrencyExchang(FromCurrency, ToCurrency, Amount) << " " << ToCurrency.CurrencyCode() << endl;
		}
		else
		{
			Code = "USD";
			clsCurrency clsUSD = clsCurrency::FindByCode(Code);
			cout << "\n\nConvert From : \n";
			_PrintCurrency(FromCurrency);
			cout << endl << Amount << " " << FromCurrency.CurrencyCode() << " = " <<
				clsCurrency::CalculateCurrencyExchang(FromCurrency, clsUSD, Amount) << " " << clsUSD.CurrencyCode() << endl;

			cout << "\n\nConverting From USD to : \n";
			cout << "\nTo\n";
			_PrintCurrency(ToCurrency);

			cout << endl << clsCurrency::CalculateCurrencyExchang(FromCurrency, clsUSD, Amount) << " " << clsUSD.CurrencyCode() << " = " <<
				clsCurrency::CalculateCurrencyExchang(clsUSD, ToCurrency, clsCurrency::CalculateCurrencyExchang(FromCurrency, clsUSD, Amount)) << " " << ToCurrency.CurrencyCode() << endl;




		}

       char Answer = 'N';
		cout << "\n\nDo you want to perform another currency exchange? (Y/N) : ";
		cin >> Answer;
		
		if (toupper(Answer) == 'Y')
		{
			ShowCurrencyCalculatorScreen();
		}
		else
		{
			return;
		}

	}*/

	static void ShowCurrencyCalculatorScreen()
	{
		char Answer = 'Y';
		while (toupper(Answer) == 'Y')
		{
			system("cls");
			clsScreen::_DrawScreenHeader("\tCurrency Calculator Screen");
			_PrintCalculationsResults();
			cout << "\n\nDo you want to perform another currency exchange? (Y/N) : ";
			cin >> Answer;

		}

	}
};

