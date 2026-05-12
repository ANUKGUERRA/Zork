#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


#include "World.h"

std::vector<std::string> tokenize(const std::string& input) {
	std::stringstream ssInput(input);
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(ssInput, token, ' '))
	{
		if (!token.empty())
		{
			std::transform(token.begin(), token.end(), token.begin(), ::tolower);
			tokens.emplace_back(token);
		}
	}
	return tokens;
}


int main()
{
	std::string input;

	World world;

	while (true)
	{
		std::getline(std::cin, input);
		std::vector<std::string> tokens = tokenize(input);

		if (tokens.empty()) continue;
		if (tokens[0] == "quit" || tokens[0] == "exit") break;

		if (!world.HandleInput(tokens)) 
		{
			std::cout << "Try a diferent sentence" << std::endl;
		}
	}

	std::cout << "Thanks for playing!" << std::endl;
}