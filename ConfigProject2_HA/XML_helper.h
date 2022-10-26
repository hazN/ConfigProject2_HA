/*
 * Hassan Assaf
 * INFO-6025 Project 2 Loading and Saving in XML with Localization
 * Due 2022-11-04
 */
#pragma once

#include <pugixml/pugixml.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>

struct gameState
{
	int correctGuesses = 0;
	int totalGuesses = 0;
	std::string currentWord = "";
};

class XML_helper
{
public:
	std::map<std::string, std::map<std::string, std::string>> language_map;
	std::map<std::string, std::vector<std::string>> words_map;
	int readLocal(std::string path);
	int saveGamestate(std::string path, gameState gameState_);
	int loadGamestate(std::string path, gameState* gameState_);
};