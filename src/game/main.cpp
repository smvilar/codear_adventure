#if 0

#include <fstream>
#include <iostream>
#include <util/easyzlib.h>

using namespace std;

int main()
{
	ifstream ifs("data.pack", ios::binary);
	if (!ifs.is_open())
		cerr << "Error opening data.pack" << endl;

	while (ifs.good())
	{
		char filename[64];
		int filesize;
		unsigned char *compressedFile;
		// get the filename
		ifs.getline(filename, 64);
		cout << filename << ": " << ifs.gcount() << endl;
		// now get the filesize
		ifs.read((char*)&filesize, sizeof(filesize));
		cout << filesize << ": " << ifs.gcount() << endl;
		// now get the compressed file!
		compressedFile = new unsigned char[filesize];
		ifs.read((char*)compressedFile, filesize);

		ezbuffer bufSrc(filesize);
		bufSrc.pBuf = compressedFile;
		ezbuffer bufDest;
		ezuncompress(bufDest, bufSrc);

		string fn(filename);
		if (fn.find("json") != string::npos)
		{
			cout << bufDest.pBuf << endl;
		}

		/*
		ofstream ofs("temp.gz");
		ofs << compressedFile;
		ofs.close();

		igzstream igzs("temp.gz");
		string fn(filename);
		if (fn.find("json") != string::npos)
		{
			while (igzs.good())
			{
				char line[128];
				igzs.getline(line, 128);
				cout << line << endl;
			}
		}
		*/
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
