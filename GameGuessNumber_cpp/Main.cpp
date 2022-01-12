#include<iostream>
#include<ctime>
#include<string>

#define DEBUG

int checkInput(const char* messege, const int min, const int max);

int main()
{
	srand(static_cast<size_t>(time(NULL)));

	const int min = 100000, max = 999999;
	int number;
	for (int i = 0; i < 5; ++i)
		number = min + rand() % (max - min);
	int uTry = 7, uAnswer = 0; bool uGuess = false;

	do
	{
		std::cout << "I have thought of a number from " << min << " to " << max
			<< "\nyou have to guess it"
			<< "\nyou have " << uTry << " attempts" << std::endl;
#ifdef DEBUG
		std::cout << number << std::endl;
#endif // DEBUG

		uAnswer = checkInput("\nEnter number: ", min, max);

		system("cls");
	} while (uTry && !uGuess);







	return 0;
}

int checkInput(const char* messege, const int min, const int max)
{
	std::string input;
	int num;
	while (true)
	{
		std::cout << messege;
		std::getline(std::cin, input);

		if (std::cin.fail() || std::cin.bad())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Some troubles, try again!\n";
			continue;
		}

		bool isDigit = true;
		for (const auto el : input)
			if (!std::isdigit(el))
			{
				isDigit = false;
				break;
			}
		if (!isDigit)
		{
			std::cout << "It\'s not a number, try again!\n";
			continue;
		}

		num = atoi(input.c_str());
		if (num < min || num > max)
		{
			std::cout << "Unvaliable diapason, try again!\n";
			continue;
		}

		break;
	}
	return num;
}
