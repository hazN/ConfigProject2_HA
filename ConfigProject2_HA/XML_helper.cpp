/*
 * Hassan Assaf
 * INFO-6025 Project 2 Loading and Saving in XML with Localization
 * Due 2022-11-04
 */
#include "XML_helper.h"

// Method : readLocal
// Summary: Read localization file
// Params : string
// Returns: int
int XML_helper::readLocal(std::string path)
{
	// Create a document object
	pugi::xml_document localizedFile;

	// Load the XML file based off path
	const char* cPath = path.c_str();
	pugi::xml_parse_result result = localizedFile.load_file(cPath);
	if (!result) {
		std::cout << "Failed to load " << path << std::endl;
		return -1;
	}
	//std::cout << "Successfully loaded " << path << std::endl;

	// Check if messages are empty
	pugi::xml_object_range<pugi::xml_node_iterator> messages = localizedFile.child("localization").children();
	if (messages.empty()) {
		std::cout << "localization file empty..." << std::endl;
		return 0;
	}
	// Parse through messages in the XML
	pugi::xml_node_iterator msgIt;
	for (msgIt = messages.begin();
		msgIt != messages.end();
		msgIt++)
	{
		pugi::xml_node msgNode = *msgIt;
		pugi::xml_attribute category = msgNode.attribute("category");

		// Parse message
		pugi::xml_node_iterator msgInfoIt;
		for (msgInfoIt = msgNode.children().begin();
			msgInfoIt != msgNode.children().end();
			msgInfoIt++)
		{
			pugi::xml_node msgInfoNode = *msgInfoIt;

			// Attributes
			for (pugi::xml_attribute_iterator attIt = msgInfoNode.attributes_begin();
				attIt != msgInfoNode.attributes_end();
				attIt++)
			{
				pugi::xml_attribute attribute = *attIt;
				std::map<std::string, std::string>& map_ = language_map[attribute.value()];
				map_.try_emplace(category.value(), msgInfoNode.child_value());
				language_map.try_emplace(attribute.value(), map_);
			}
		}
	}
	return 0;
}
// Method : saveGamestate
// Summary: Save the gamestate into an xml file
// Params : string, gameState
// Returns: int
int XML_helper::saveGamestate(std::string path, gameState gameState_)
{
	// Create a document object
	pugi::xml_document gamestate;

	// Create root
	pugi::xml_node root = gamestate.append_child("GameState");

	// Add data
	pugi::xml_node nodeChild = root.append_child("TotalGuesses");
	nodeChild.append_attribute("intVal") = gameState_.totalGuesses;
	nodeChild = root.append_child("CorrectGuesses");
	nodeChild.append_attribute("intVal") = gameState_.correctGuesses;
	nodeChild = root.append_child("CurrentWord");
	nodeChild.append_child(pugi::node_pcdata).set_value(gameState_.currentWord.c_str());

	// Save file
	if (!gamestate.save_file(path.c_str(), PUGIXML_TEXT("  ")))
		return -1;
	return 0;
}

// Method : loadGamestate
// Summary: Load the gamestate from an xml file
// Params : string, *gameState
// Returns: int
int XML_helper::loadGamestate(std::string path, gameState *gameState_)
{
	// Create a document object
	pugi::xml_document gamestate;

	// Load the XML file based off path
	const char* cPath = path.c_str();
	pugi::xml_parse_result result = gamestate.load_file(cPath);
	if (!result) {
		std::cout << "Failed to load " << path << std::endl;
		return -1;
	}

	// Check if nodes are empty
	pugi::xml_object_range<pugi::xml_node_iterator> nodes = gamestate.child("GameState").children();
	if (nodes.empty()) {
		std::cout << "gamestate is empty..." << std::endl;
		return 0;
	}
	// Parse through messages in the XML
	gameState_->totalGuesses = gamestate.document_element().child("TotalGuesses").attribute("intVal").as_int();
	gameState_->correctGuesses = gamestate.document_element().child("CorrectGuesses").attribute("intVal").as_int();
	gameState_->currentWord = gamestate.document_element().child("CurrentWord").text().as_string();
	return 0;
}