#include "World.h"

World::World()
{
	Room* entranceHall = new Room("Entrance Hall", "A grand hall with dusty chandeliers and a cold marble floor. The air smells of candle wax and old wood.");
	Room* kitchen = new Room("Kitchen", "A greasy kitchen that reeks of rotten food. Copper pots hang from the ceiling, and a half-eaten meal sits abandoned on the counter.");
	Room* diningRoom = new Room("Dining Room", "A luxurious dining room with a long oak table. An unfinished glass of wine still sits at the head of the table - Lord Blackwood's seat.");
	Room* library = new Room("Library", "Rows of old books line the walls. A reading chair sits by the fireplace, its cushion still warm. Something feels strange here.");
	Room* cellar = new Room("Cellar", "A dark, humid cellar beneath the mansion. Shelves of dusty wine bottles line the stone walls. The smell of mildew is overwhelming.");
	Room* garden = new Room("Garden", "An overgrown garden illuminated by cold moonlight. The hedges are wild and untamed - nobody has cared for this place in years.");


	//Player
	player = new Player("John Graves", "A sharp private detective hired to investigate Lord Blackwood's sudden death.", entranceHall);

	//Exits
	Exit* hallKitchen = new Exit("east", "west", "A wooden door connects the hall and kitchen.", entranceHall, kitchen);
	Exit* hallDining = new Exit("north", "south", "Large double doors lead into the dining room.", entranceHall, diningRoom);
	Exit* hallLibrary = new Exit("west", "east", "A silent corridor leads to the library.", entranceHall, library);
	Exit* kitchenCellar = new Exit("down", "up", "A narrow stairway descends into the cellar.", kitchen, cellar);
	Exit* diningGarden = new Exit("north", "south", "Glass doors open toward the moonlit garden.", diningRoom, garden);



	//Items
	Item* detectiveBadge = new Item("detective_badge", "A worn brass badge identifying its owner as a licensed private detective. The initials J.G. are engraved on the back.", player);
	Item* bloodyKey = new Item("bloody_key", "A small brass key with a dark, rust-coloured stain on its teeth. Someone was in a hurry when they last used it.", nullptr);
	Item* tornDiary = new Item("diary_page", "A torn page from Lord Blackwood's diary. The handwriting is shaky: 'Marcus was furious when I told him. I fear what he might do.'", library);
	Item* wineBottle = new Item("wine_bottle", "A half-empty wine bottle from the dinner table. The label reads 'Chateau Moreau 1887'. A faint bitter smell clings to the rim.", diningRoom);
	Item* silverKnife = new Item("silver_knife", "A decorative silver knife from the dining table. Its blade is suspiciously clean for a dinner utensil.", diningRoom);
	Item* oldShovel = new Item("shovel", "A muddy gardening shovel. Freshly used - the dirt on the blade is still moist.", garden);
	Item* lockedChest = new Item("chest", "An old wooden chest secured with a brass lock. Someone has gone to great lengths to keep this hidden down here.", cellar, bloodyKey, 2, true);
	Item* poisonBottle = new Item("poison_bottle", "A tiny unlabelled glass bottle. A single drop of its dark liquid remains. The smell is unmistakable - arsenic.", lockedChest);
	Item* victimLetter = new Item("letter", "A letter written by Lord Blackwood, dated two days before his death: 'I have changed my will. Marcus shall receive nothing. I fear he already suspects.'", lockedChest);

	//NPCS
	// 
	// MARCUS
	NPC* marcus = new NPC("Marcus", "The nervous old butler of the mansion. His eyes dart away whenever they meet yours.", diningRoom);

	marcus->defaultDialogue =
	{
		"I already told the police everything I know.",
		"Lord Blackwood drank his usual glass of wine before dinner. Nothing seemed out of the ordinary.",
		"If you'll excuse me, I have duties to attend to."
	};

	marcus->conditionalDialogue["found_diary"] =
	{
		"That diary, where did you find it?",
		"Lord Blackwood was a paranoid man. He wrote all sorts of nonsense.",
		"I suggest you stop digging into private matters that don't concern you."
	};

	marcus->conditionalDialogue["found_poison"] =
	{
		"...Where did you find that?",
		"I... I can explain. Lord Blackwood was already ill. I only",
		"You have no proof of anything. That bottle could belong to anyone."
	};

	marcus->conditionalDialogue["confronted"] =
	{
		"All right. ALL RIGHT.",
		"He was going to throw me out! Forty years of service and he was cutting me from the will over a single argument!",
		"I put a few drops in his wine. I didn't think- I only wanted him to be ill, not...",
		"I never meant for it to end like this."
	};

	// ELISA
	NPC* elisa = new NPC("Elisa",
		"A frightened maid who avoids eye contact. She clutches something tightly in her apron pocket.",
		library, detectiveBadge, 1, true);

	bloodyKey->m_owner = elisa;
	elisa->m_contains.emplace_back(bloodyKey);

	elisa->defaultDialogue =
	{
		"Please, I don't want any trouble.",
		"I found a strange key near the cellar stairs the morning after Lord Blackwood died.",
		"I'll only hand it over to someone official. Do you have identification?"
	};

	elisa->conditionalDialogue["has_key"] =
	{
		"You already have the key. Please find out what happened to the poor man.",
		"I heard Marcus arguing with Lord Blackwood two nights ago. Shouting about money."
	};

	// THOMAS
	NPC* thomas = new NPC("Thomas", "A tired gardener covered in mud, leaning on the garden fence.", garden);

	thomas->defaultDialogue =
	{
		"Terrible business, all this.",
		"I was digging new beds near the east hedge that night. Heard a door slam around midnight.",
		"Saw Marcus crossing the garden in a hurry. Thought nothing of it at the time.",
		"He was carrying something - a small bag, I think."
	};

	thomas->conditionalDialogue["found_poison"] =
	{
		"A poison bottle, you say? Lord almighty.",
		"There's an old chest in the cellar Marcus always kept locked. Never let anyone near it.",
		"If that's where it came from, well... you've got your answer, haven't you?"
	};

	// HENRI
	NPC* henri = new NPC("Henri", "A stressed chef smoking a cigarette near the kitchen door.", kitchen);

	henri->defaultDialogue =
	{
		"I prepare the food, not the wine. Whatever happened to Lord Blackwood, it wasn't my cooking.",
		"Marcus is the one who pours the wine. Always has been. That's butler's work.",
		"The night it happened, he sent me out of the kitchen early. Said he'd handle the wine service himself.",
		"Didn't think anything of it - he outranks me in this house."
	};

	henri->conditionalDialogue["found_diary"] =
	{
		"So the old lord suspected something?",
		"I knew Marcus was angry about the will - he told me so himself, drunk one night.",
		"Said Lord Blackwood was 'going to regret it'. I thought he meant he'd quit."
	};

	henri->conditionalDialogue["found_poison"] =
	{
		"Arsenic? In the wine? Mon Dieu...",
		"That explains the bitter smell I noticed on the bottle when I washed up.",
		"I thought it was just a bad vintage. I should have said something."
	};




	entities.reserve(24);

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
	entities.emplace_back(detectiveBadge);
	entities.emplace_back(bloodyKey);
	entities.emplace_back(tornDiary);
	entities.emplace_back(wineBottle);
	entities.emplace_back(silverKnife);
	entities.emplace_back(oldShovel);
	entities.emplace_back(lockedChest);
	entities.emplace_back(poisonBottle);
	entities.emplace_back(victimLetter);

	// NPCs
	entities.emplace_back(marcus);
	entities.emplace_back(elisa);
	entities.emplace_back(thomas);
	entities.emplace_back(henri);


	std::cout << "Lord Blackwood has been found dead in his mansion.\n";
	std::cout << "You, John Graves, have been hired to find the killer.\n";


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
	std::string parameter = (tokens.size() > 1) ? tokens[1] : "";


	if (instruction == "look")	return player->Look(parameter);
	if (instruction == "go")	return player->Go(parameter);
	if (instruction == "take")	return player->Take(parameter);
	if (instruction == "drop")	return player->Drop(parameter);
	if (instruction == "open")	return player->Open(parameter);
	if (instruction == "close")	return player->Close(parameter);
	if (instruction == "talk")
	{
		bool result = player->Talk(parameter);
		if (mysterySolved)
		{
			std::cout << "\n===============\n";
			std::cout << "  CASE CLOSED\n";
			std::cout << "===============\n";
			std::cout << "Marcus breaks down completely. Within the hour, Inspector\n";
			std::cout << "Holloway arrives and places him under arrest.\n\n";
			std::cout << "The poison bottle and Lord Blackwood's letter are handed\n";
			std::cout << "over as evidence. Marcus will hang for his crime.\n\n";
			std::cout << "You light a cigarette on the front steps of the mansion\n";
			std::cout << "and watch the police wagon roll away into the fog.\n";
			std::cout << "Another case closed, John Graves.\n";
		}
		return result;
	}

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
	bool hasPoison = false;
	bool hasLetter = false;
	for (Entity* e : player->m_contains)
	{
		if (e->type == Types::Item)
		{
			if (e->m_name == "poison_bottle") hasPoison = true;
			if (e->m_name == "letter")        hasLetter = true;
		}
	}
	return hasPoison && hasLetter;
}


