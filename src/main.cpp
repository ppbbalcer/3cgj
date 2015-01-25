//Using SDL and standard IO

#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "SceneExamples.h"
#include "SceneFont.h"
#include "level.h"
#include <stdio.h>
#include <string>

void preCalc() {
	//Precalculate variables

	int radius = 4;
	int radQuad =  radius * radius;
	for(int x=-radius; x<=radius; ++x) {
		int xQuad = x * x;
		for(int y=-radius; y<=radius; ++y) {
			int rq = (xQuad + y*y);
			if(rq <= radQuad ) {
				int alfa =  radius - (int) sqrt(rq);
				alfa =  alfa * 255 / radius;
				calcCircleAlfaRadius4[x + radius][y + radius] = 0 +alfa ;
			} else {
				calcCircleAlfaRadius4[x + radius][y + radius] = 0;
			}
		}
	}

	radius = 6;
	radQuad =  radius * radius;
	for(int x=-radius; x<=radius; ++x) {
		int xQuad = x * x;
		for(int y=-radius; y<=radius; ++y) {
			int rq = (xQuad + y*y);
			if(rq <= radQuad ) {
				int alfa =  radius - (int) sqrt(rq);
				alfa =  alfa * 255 / radius;
				calcCircleAlfaRadius6[x + radius][y + radius] = alfa ;
			} else {
				calcCircleAlfaRadius6[x + radius][y + radius] = 0;
			}
		}
	}
}


bool loadMedia() {
	 preCalc();
	//Loading success flag 
	bool success = true; 

	EngineInst->loadGlobalFont(GlobalFontPath, 18);
	EngineInst->showFPS(true);
	
	success &= EngineInst->loadResources(globalTextures, globalTexturesSize);
//	gScene = new MainScene();
	// uncomment this to instead get scene with first preview of map
	if (!EngineInst->loadAudioResources(globalAudios, globalAudiosSize))
		success = false;

	return success;
}

int main( int argc, char* args[] )
{
	printf("argc %d\n", argc);
	Level *level = NULL;
	if (argc == 3) {
		level = new Level(atoi(args[1]), atoi(args[2]));
	} else {
		level = new Level(1, 0);
	}
	if( !Engine::Create() )
	{
		printf( "Failed to initialize!\n" );
		PAUSE();
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
			PAUSE();
		}
		else
		{	
			EngineInst->setNextScene(level->getCurrentScene());
			EngineInst->mainLoop();
		}
	}

	EngineInst->unLoadResources(globalTextures, globalTexturesSize);
	EngineInst->unLoadGlobalFont();
	Engine::Destroy();

	delete level;
	return 0;
}
