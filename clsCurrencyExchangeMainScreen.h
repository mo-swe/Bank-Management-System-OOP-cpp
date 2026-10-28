#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen :protected clsScreen
{
private:
	static enum CurrencyMainMenuOptions
	{eListCurrencies=1,eFindCurrencies=2,eUpdateRate=3,eCurrencyCalculator=4,MainMenu=5 };

	static int ReadCurrencyMainMenuOption()
	{
		cout << "\n\t\t\t\t\tChoose what do you want to do? [1 to 5]? ";
		int Choice  = clsInputValidate::ReadNumberBetween<int>(1, 5);
		return Choice;
	}
	static void _ShowListCurrenciesScreen()
	{
		//cout << "\nList Currencies Screen Will be here...\n";
		clsCurrenciesListScreen::ShowCurrenciesList();
	}
	static void _ShowFindCurrenciesScreen()
	{
		//cout << "\nFind Currencies Screen Will be here...\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		//cout << "\nUpdate Rate Screen Will be here...\n";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRate();
	}
	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will be here...\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
	
	static void _GoBackToCurrencyMainMenue()
	{
		cout << "\nPress any key to go back to Currency Main Menue...\n";
		system("pause>0");
		ShowCurrencyExchangeMainScreen();
	}
	static void _PerformCurrencyMainMenueOption(CurrencyMainMenuOptions MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case CurrencyMainMenuOptions::eListCurrencies:
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case CurrencyMainMenuOptions::eFindCurrencies:
			system("cls");
			_ShowFindCurrenciesScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case CurrencyMainMenuOptions::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case CurrencyMainMenuOptions::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case CurrencyMainMenuOptions::MainMenu:
			break;
		default:
			break;
		}
	}
public:

	
	
	static void ShowCurrencyExchangeMainScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pCurrency))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("Currency Exchange Main Screen");

		
		cout << "\n\t\t\t\t\t===========================================";
		cout << "\n\t\t\t\t\tCurrency Exchange Menu";
		cout << "\n\t\t\t\t\t===========================================";
		cout << "\n\t\t\t\t\t[1] List Currencies.";
		cout << "\n\t\t\t\t\t[2] Find Currencies.";
		cout << "\n\t\t\t\t\t[3] Update Rate.";
		cout << "\n\t\t\t\t\t[4] Currency Calculator.";
		cout << "\n\t\t\t\t\t[5] Main Menue.";
		cout << "\n\t\t\t\t\t===========================================";
		_PerformCurrencyMainMenueOption((CurrencyMainMenuOptions)ReadCurrencyMainMenuOption());
	}
};

