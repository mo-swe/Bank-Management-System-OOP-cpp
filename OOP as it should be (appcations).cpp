#include <iostream>
#include "clsLoginScreen.h"

int main()

{
	int LoginTries = 3;

	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen(LoginTries))
		{
			break;
		}
	}

    return 0;
}

