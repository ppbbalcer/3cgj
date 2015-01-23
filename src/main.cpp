//Using SDL and standard IO

#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "SceneExamples.h"
#include "SceneFont.h"
#include "MapLogic/map.h"
#include <stdio.h>
#include <string>

bool loadMedia() { 
	//Loading success flag 
	bool success = true; 

	EngineInst->loadGlobalFont(GlobalFontPath, 18);
	EngineInst->showFPS(true);

	success &= EngineInst->loadResources(globalTextures, globalTexturesSize);
	gScene = new Scene03Object();

	if (!EngineInst->loadAudioResources(globalAudios, globalAudiosSize))
		success = false;

	return success;
}

int main( int argc, char* args[] )
{
	
	//Start up SDL and create window
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
			EngineInst->setNextScene(gScene);
			EngineInst->mainLoop();
		}
	}

	EngineInst->unLoadResources(globalTextures, globalTexturesSize);
	EngineInst->unLoadGlobalFont();
	Engine::Destroy();


	delete gScene;
	return 0;
}
