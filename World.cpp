#include "World.h"

World::World()
{
	Room* entranceHall = new Room("Entrance Hall", "A grand hall with dusty chandeliers and a cold marble floor.");

	Room* kitchen = new Room("Kitchen", "A greasy kitchen that smells of rotten food.");

	Room* diningRoom = new Room("Dining Room", "A luxurious dining room with a long oak table.");

	Room* library = new Room("Library", "Rows of old books line the walls. Something feels strange here.");

	Room* cellar = new Room("Cellar", "A dark humid cellar beneath the mansion.");

	Room* garden = new Room("Garden",	"An overgrown garden illuminated by moonlight.");

	//Player
	player = new Player("John Graves", "A sharp detective searching for the killer.", entranceHall);

	//Exits
	Exit* hallKitchen = new Exit("east", "west", "A wooden door connects the hall and kitchen.", entranceHall, kitchen);

	Exit* hallDining = new Exit( "north", "south", "Large double doors lead into the dining room.", entranceHall, diningRoom);

	Exit* hallLibrary = new Exit("west", "east", "A silent corridor leads to the library.", entranceHall, library);

	Exit* kitchenCellar = new Exit("down", "up", "A narrow stairway descends into the cellar.", kitchen, cellar);

	Exit* diningGarden = new Exit("north", "south", "Glass doors open toward the garden.", diningRoom, garden);

	//NPCS
	NPC* marcus = new NPC("Marcus", "The nervous old butler of the mansion.", diningRoom);
	marcus->defaultDialogue =
	{
		"I already told the police everything.",
		"Lord Blackwood drank wine before dinner."
	};

	marcus->conditionalDialogue["found_diary"] =
	{
		"That diary means nothing!",
		"You should stop digging into private matters..."
	};

	marcus->conditionalDialogue["found_poison"] =
	{
		"...Where did you find that?"
	};

	Item* detectiveBadge = new Item("detective_badge", "A worn brass badge identifying its owner as a private detective.", player);
	NPC* elisa = new NPC("Elisa", "A frightened maid avoiding eye contact.", library, detectiveBadge, 1, true);
	elisa->defaultDialogue =
	{
		"I found a wierd key, i can only give it to you if you have a detective badge"
	};

	NPC* thomas = new NPC("Thomas", "A tired gardener covered in mud.", garden);

	NPC* henri = new NPC("Henri", "A stressed chef smoking near the kitchen.", kitchen);

	//Items

	Item* bloodyKey = new Item("bloody_key", "A small brass key with dried blood on it.", elisa);

	Item* tornDiary = new Item("diary_page", "A torn diary page mentioning an argument with Marcus.", library);

	Item* wineBottle = new Item("wine_bottle", "A half-empty wine bottle used during dinner.", diningRoom);

	Item* silverKnife = new Item("silver_knife", "A decorative silver knife. Surprisingly clean.", diningRoom);

	Item* oldShovel = new Item("shovel", "A muddy gardening shovel.", garden);

	Item* lockedChest = new Item("chest", "An old wooden chest with a lock.", cellar, bloodyKey, 2, true);

	Item* poisonBottle = new Item("poison_bottle", "A tiny bottle containing deadly poison.", lockedChest);

	Item* victimLetter = new Item("letter", "A letter from Lord Blackwood saying he feared Marcus.", lockedChest);


	entities.reserve(32);

	// Player
	entities.emplace_back(player);

	// Rooms
	entities.emplace_back(entranceHall);
	entities.emplace_back(kitchen);
	entities.emplace_back(diningRoom);
	entities.emplace_back(library);
	entities.emplace_back(cellar);
	entities.emplace_back(garden);

	// Exits
	entities.emplace_back(hallKitchen);
	entities.emplace_back(hallDining);
	entities.emplace_back(hallLibrary);
	entities.emplace_back(kitchenCellar);
	entities.emplace_back(diningGarden);

	// Items
	entities.emplace_back(bloodyKey);
	entities.emplace_back(tornDiary);
	entities.emplace_back(wineBottle);
	entities.emplace_back(silverKnife);
	entities.emplace_back(oldShovel);
	entities.emplace_back(poisonBottle);
	entities.emplace_back(victimLetter);
	entities.emplace_back(lockedChest);

	// NPCs
	entities.emplace_back(marcus);
	entities.emplace_back(elisa);
	entities.emplace_back(thomas);
	entities.emplace_back(henri);

	player->Look("");
}

World::~World()
{
	for (Entity* entity : entities)
	{
		delete entity;
	}

	entities.clear();
	player = nullptr;
}

bool World::HandleInput(const std::vector<std::string>& tokens)
{
	if (tokens.empty()) return false;


	const std::string& instruction = tokens[0];
	std::string parameter;
	if (tokens.size() > 1)
	{
		parameter = tokens[1];
	}
	else 
	{
		parameter = "";
	}


	if (instruction == "look")	return player->Look(parameter);
	if (instruction == "go")	return player->Go(parameter);
	if (instruction == "take")	return player->Take(parameter);
	if (instruction == "drop")	return player->Drop(parameter);
	if (instruction == "talk")	return player->Talk(parameter);
	if (instruction == "open")	return player->Open(parameter);
	if (instruction == "close")	return player->Close(parameter);
	
	return false;
}

void World::AddFlag(const std::string& flag)
{
	flags.insert(flag);
}

bool World::HasFlag(const std::string& flag) const
{
	return flags.find(flag) != flags.end();
}

bool World::CheckWinCondition()
{
	return false;
}

