#if 1

#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data.pack", ios::binary);
	if (!ifs.is_open())
		cerr << "Error opening data.pack" << endl;

	while (ifs.good())
	{
		const size_t TEMP_BUFFER_SIZE = 512;
		char filename[TEMP_BUFFER_SIZE];
		int dataSize;
		char *packedData;
		// get the filename
		ifs.getline(filename, TEMP_BUFFER_SIZE);
		if (ifs.eof()) break;
		cout << filename << endl;
		// now get the filesize
		ifs.read((char*)&dataSize, sizeof(dataSize));
		cout << dataSize << endl;
		// now get the compressed file!
		packedData = new char[dataSize];
		ifs.read(packedData, dataSize);

		delete [] packedData;
	}

	return 0;
}

#else
#include "hierophantengine.h"
#include "logobehavior.h"
#include "dialoguecontrolbehavior.h"
#include "conditiononclickbehavior.h"
#include "addbehaviorbehavior.h"
#include "phonecontrollerbehavior.h"

using namespace he;

void setupWorld(World &world)
{
	// game specific
	world.registerBehavior("Logo", new LogoBehavior);
	world.registerBehavior("DialogueControl", new DialogueControlBehavior);
	world.registerBehavior("ConditionOnClick", new ConditionOnClickBehavior);
	world.registerBehavior("AddBehavior", new AddBehaviorBehavior);
	world.registerBehavior("PhoneController", new PhoneControllerBehavior);
}

int main()
{
	World world;
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
#endif
