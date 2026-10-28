#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsScreen.h"

class clsUpdateCurrencyRateScreen :protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "___________________________\n";
		cout << "\nCountry      : " << Currency.Country();
		cout << "\nCode         : " << Currency.CurrencyCode();
		cout << "\nName         : " << Currency.CurrencyName();
		cout << "\nRate         : " << Currency.Rate();
		cout << "\n___________________________\n";
	}

public :
	static void ShowUpdateCurrencyRate()
	{
		clsScreen::_DrawScreenHeader("\t Update Currency Rate Screen");

		
		string CurrencyCode;

		cout << "\n\nPlease Enter Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		while (Currency.IsEmpty())
		{
			cout << "\nCurrency Code is not found, choose another one : ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		}

		_PrintCurrency(Currency);

		char Answer;

		cout << "\n\nAre you sure you want to update this currency rate? [y/n] : ";
		cin >> Answer;

		if(Answer == 'y' || Answer == 'Y')
		{

			float NewRate;

			cout << "\n\nUpdate Currency Rate : ";
			cout << "\n____________________________\n";
			cout << "\nPlease Enter New Rate : ";
			NewRate = clsInputValidate::ReadNumber<float>();
			Currency.UpdateRate(NewRate);
			cout << "\n\nCurrency Rate Updated Successfully.\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\n\nUpdate Cancelled.\n";
		}

	}
};

