/*
 * Hassan Assaf
 * INFO-6025 Project 2 Loading and Saving in XML with Localization
 * Due 2022-11-04
 */
#include <pugixml/pugixml.hpp>
#include <iostream>
#include <map>
#include <vector>
#include "XML_helper.h"
#include <random>

// Vector of words to be randomized
std::vector<std::string> words = { "wind", "unused", "paste", "value", "wholesale", "undesirable", "juice", "loaf", "circle", "jog", "coal", "story", "protest", "cagey", "gullible", "yellow", "industrious", "receive", "malicious", "coop", "hurt", "fluffy", "pin", "soap", "handy", "thoughtless", "stove", "crowded", "thought", "interest", "tag", "rest", "vivacious", "anger", "eatable", "fix", "volcano", "lethal", "peace", "teaching", "puffy", "sable", "abnormal", "expand", "disgusted", "warn", "laugh", "cheat", "worried", "magnificent", "unite", "wanting", "fry", "class", "bitter", "flight", "celery", "greedy", "giraffe", "rich", "elderly", "mountainous", "zinc", "unwieldy", "argue", "dynamic", "rob", "evanescent", "pull", "corn", "wilderness", "quack", "station", "threatening", "harbor", "seed", "irritate", "decide", "mice", "miss", "calm", "halting", "motionless", "sprout", "demonic", "imperfect", "tick", "sheep", "far", "acidic", "foamy", "wistful", "plastic", "pies", "faulty", "slippery", "terrify", "love", "regular", "tell" };
// Localization mapped
std::map<std::string, std::map<std::string, std::string>> language_map;

// Method : random
// Summary: generate random number between values, taken from https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
// Params : int, int
// Returns: int
int random(int min, int max)
{
	static bool first = true;
	if (first)
	{
		// Seed for the first time
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}
// Declaration of gamestate struct
gameState gameState_;
int main(int argc, char** argv) {
	// Create XML helper 
	XML_helper xml_helper;
	// Read localization file
	xml_helper.readLocal("local.xml");
	// Setting language to en as the backup incase something goes wrong
	std::string language = "en";
	int input = 0;
	// Take user input for language
	do
	{
		std::cout << "Enter # of Language:\n1. English\n2. Francais\n3. Espanol\n4. Italiano\n5. Dutch" << std::endl;
		std::cin >> input;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}
	} while (input < 1 || input > 5);
	switch (input)
	{
	case 1: // ENGLISH
		language = "en";
		break;
	case 2: // FRENCH
		language = "fr";
		break;
	case 3: // SPANISH
		language = "es";
		break;
	case 4: // ITALIAN
		language = "it";
		break;
	case 5: // DUTCH
		language = "nl";
		break;
	default: // DEFAULT TO ENGLISH
		language = "en";
		break;
	}

	std::cout << xml_helper.language_map.at(language).at("WELCOME") << std::endl;
	std::cout << xml_helper.language_map.at(language).at("STARTGAME") << std::endl;
	// Take input for new game or load previous game
	std::string guess = "";
	std::cin >> guess;
	do
	{
		// Load game
		if (guess == "l")
		{
			xml_helper.loadGamestate("gamestate.xml", &gameState_);
		}
		else gameState_.currentWord = words[random(0, 49)];
		std::string markedWord = gameState_.currentWord;
		markedWord.at(random(0, markedWord.size() - 1)) = '_';

		std::cout << xml_helper.language_map.at(language).at("RULES") << std::endl;
		std::cout << "\n" << markedWord << std::endl;
		std::cout << xml_helper.language_map.at(language).at("OPTIONS") << std::endl;

		while (guess != gameState_.currentWord)
		{
			std::cin >> guess;
			gameState_.totalGuesses++;
			if (guess == "s")
			{
				xml_helper.saveGamestate("gamestate.xml", gameState_);
				break;
			}
			if (guess != gameState_.currentWord)
				std::cout << xml_helper.language_map.at(language).at("INCORRECT") << std::endl;
		}

		if (guess == gameState_.currentWord)
		{
			std::cout << std::endl << xml_helper.language_map.at(language).at("CORRECT") << std::endl;
			gameState_.correctGuesses++;
			std::cout << xml_helper.language_map.at(language).at("CGUESSES") << " " << gameState_.correctGuesses << std::endl;
		}

		std::cout << xml_helper.language_map.at(language).at("TGUESSES") << " " << gameState_.totalGuesses << std::endl << std::endl;
	} while (guess != "s");
	return 0;
}