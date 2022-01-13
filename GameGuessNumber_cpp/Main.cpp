#include<iostream>
#include<ctime>
#include<string>
#include<cmath>

//#define DEBUG

// Difficulty levels
enum Difficult { PADAWAN = 1, JEDI };

// Struct of number and boolean who show is digit position guess
struct Number
{
	int num;
	bool isGuess;
};

int checkInput(const char* messege, const int min, const int max);

int main()
{
	srand(static_cast<size_t>(time(NULL)));

	// Choose level of difficulty and digit count
	int difficulty = checkInput("Chose difficylty level\nEnter \"1\" to chose EASY (you will see digits on right plases)\nEnter \"2\" to chose HARD (you will not see digits on right plases)\nEnter level: ", 1, 2);
	system("cls");
	int digitsCount = checkInput("Chose quantity of digits from 3 to 9\nEnter number: ", 3, 9);
	system("cls");

	// Max and min values of the hidden digits
	const int min = 0, max = 9;

	// Init and generate random number
	Number* pcNumber = new Number[digitsCount];
	for (int i = 0; i < digitsCount; ++i)
	{
		pcNumber[i].num = rand() % (max + 1 - min) + min;
		pcNumber[i].isGuess = false;
	}

	// Simple int from array generate num and calculate min and max possible numbers
	int number = 0;
	int minPossible = std::pow(10, digitsCount - 1), maxPossible = 0;
	for (int i = 0, degree = digitsCount - 1; i < digitsCount; ++i, --degree)
	{
		number += pcNumber[i].num * static_cast<int>(std::pow(10, degree));
		maxPossible += 9 * static_cast<int>(std::pow(10, degree));
	}

	// Max count of attempts, player answer and is player guess
	int uTry = 7, uAnswer = 0; 
	bool uGuess = false;

	// Plaing cucle
	while(true)
	{
		// Print instruction
		std::cout << "I have thought a " << digitsCount << " digit number"
			<< "\nyou have to guess it"
			<< "\nyou have " << uTry << " attempts" << std::endl;

		// Print digits if chose EASY
#ifndef DEBUG
		std::cout << std::endl;
#endif // !DEBUG
		if (difficulty == PADAWAN)
		{
			for (int i = 0; i < digitsCount; ++i)
			{
				if (pcNumber[i].isGuess)
					std::cout << pcNumber[i].num;
				else
					std::cout << "_ ";
			}
#ifdef DEBUG
			std::cout << std::endl;
#endif // DEBUG
		}

		// Print number, for debug
#ifdef DEBUG
		for (int i = 0; i < digitsCount; ++i)
			std::cout << pcNumber[i].num;
		std::cout << std::endl;
#endif // DEBUG
#ifndef DEBUG
		std::cout << std::endl;
#endif // !DEBUG

		// Ask players answer, with input check and incrase attempts
		uAnswer = checkInput("\nEnter number: ", minPossible, maxPossible);
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
			// Increment if digit on right position, show if choose EASY
			if (str_Number[i] == str_uAnswer[i])
			{
				++rightPosition;
				if (!pcNumber[i].isGuess)
					pcNumber[i].isGuess = true;
			}
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
			<< rightPosition << " from it on their plases\n"
			<< "Your previous answer is " << uAnswer << "\n\n";
	}

	if (uGuess)
		std::cout << "\nCongratulations, it is right number!" << std::endl;
	else
		std::cout << "\nSorry, you is lose.... Loser)" << std::endl;

	delete[]pcNumber;

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
			system("cls");
			std::cout << "Some troubles, try again!\n\n";
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
			system("cls");
			std::cout << "It\'s not a number, try again!\n\n";
			continue;
		}

		num = atoi(input.c_str());
		if (num < min || num > max)
		{
			system("cls");
			std::cout << "Unvaliable diapason, try again!\n\n";
			continue;
		}

		break;
	}
	return num;
}
