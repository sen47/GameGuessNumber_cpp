#include<iostream>
#include<ctime>
#include<string>

#define DEBUG

int checkInput(const char* messege, const int min, const int max);

int main()
{
	srand(static_cast<size_t>(time(NULL)));

	// Max and min values of the hidden number
	const int min = 100000, max = 999999;

	// Generate random number 
	int number;
	for (int i = 0; i < 5; ++i)
		number = min + rand() % (max - min);
	
	// Max count of attempts, player answer and is player guess
	int uTry = 7, uAnswer = 0; 
	bool uGuess = false;

	// Plaing cucle
	while(true)
	{
		// Print instruction
		std::cout << "I have thought of a number from " << min << " to " << max
			<< "\nyou have to guess it"
			<< "\nyou have " << uTry << " attempts" << std::endl;

		// Print number, for debug
#ifdef DEBUG
		std::cout << number << std::endl;
#endif // DEBUG

		// Ask players answer, with input check and incrase attempts
		uAnswer = checkInput("\nEnter number: ", min, max);
		--uTry;

		// Exit if player guess
		if (uAnswer == number)
		{
			uGuess = true;
			break;
		}
		else if (!uTry)
			break;

		// Transform to string for for compare
		std::string str_uAnswer{ std::to_string(uAnswer) }, str_Number{ std::to_string(number) };
		
		// Compare their positions 
		int rightPosition = 0, rightDigit = 0;
		for (int i = 0; i < str_Number.size(); ++i)
		{
			// Increment if digit on right position
			if (str_Number[i] == str_uAnswer[i])
				++rightPosition;
		}

		// Compare right digits
		for (const auto ansEl : str_uAnswer)
		{
			// Increment if answer contains right digits
			for (const auto numEl : str_Number)
			if (ansEl==numEl)
			{
				++rightDigit;
				break;
			}
		}

		system("cls");

		// If unswer uncorrect,  and print message, else your attempts is over
		
		std::cout << "You not guess, in your answer "
			<< rightDigit << " digits is right, and "
			<< rightPosition << " on their plases\n"
			<< "yor previous number is " << uAnswer << "\n\n";
	}

	if (uGuess)
		std::cout << "\nCongratulations, it is right number!" << std::endl;
	else
		std::cout << "\nSorry, you is lose.... Loser)" << std::endl;

	return 0;
}

// Checking user input for type and diapason
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
