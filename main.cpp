#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> tokenize(std::string input) {
	std::stringstream ssInput(input);
	std::vector<std::string> tokens;
	std::string token;
	char delimeter = ' ';
	while (std::getline(ssInput, token, delimeter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

int main()
{
	std::string input;
	std::stringstream chartInput;

	while (true)
	{
		std::cin >> input;
		std::vector<std::string> tokens = tokenize(input);

		if (tokens.size() > 0 && tokens[0] == "quit")
			break;



	}

	std::cout << "Thanks for playing!" << std::endl;
}