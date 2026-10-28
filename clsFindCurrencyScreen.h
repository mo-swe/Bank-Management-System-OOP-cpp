#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsScreen.h"


class clsFindCurrencyScreen :protected clsScreen
{
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCuurency Found :\n";

		cout << "\nCurrency Card:\n";
		cout << "___________________________\n";
		cout << "\nCountry      : " << Currency.Country();
		cout << "\nCode         : " << Currency.CurrencyCode();
		cout << "\nName         : " << Currency.CurrencyName();
		cout << "\nRate         : " << Currency.Rate();
		cout << "\n___________________________\n";
	}
	static void _ShowResult(clsCurrency Currency)
	{
		if (Currency.IsEmpty())
		{
			cout << "\nCurrency Not Found :)\n";
		}
		else
		{
			_PrintCurrency(Currency);
		}
	}
public : 
	static void ShowFindCurrencyScreen()
	{
		clsScreen::_DrawScreenHeader("\t Find Currency Screen");

		short FindByCodeOrByCountry;
		cout << "\n\nFind By :  [1] Code or [2] Country ?";
		FindByCodeOrByCountry = clsInputValidate::ReadNumber<short>();

		if (FindByCodeOrByCountry == 1)
		{
			string Code;
			cout << "\n\nPlease Enter CurrencyCode :";
			Code = clsInputValidate::ReadString();
			clsCurrency Currency = Currency.FindByCode(Code);

			_ShowResult(Currency);
		}
		else 
		{
			string Country;
			cout << "\n\nPlease Enter Country Name :";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = Currency.FindByCountry(Country);
			_ShowResult(Currency);

		}
		

	}

};

