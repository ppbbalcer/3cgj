//Using SDL and standard IO

#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "SceneExamples.h"
#include "SceneFont.h"
#include <stdio.h>
#include <string>

bool loadMedia() { 
	//Loading success flag 
	bool success = true; 

	EngineInst->loadGlobalFont(GlobalFontPath, 18);
	EngineInst->showFPS(true);

	success &= EngineInst->loadResources(globalTextures, globalTexturesSize);
	gScenes[0] = new SceneInit();
	gScenes[1] = new SceneFont2D();
	gScenes[2] = new SceneFont3D();
	gScenes[3] = new Scene01Image();
	gScenes[4] = new Scene02Renderer();
	gScenes[5] = new Scene03Object();

	return success;
}

int main( int argc, char* args[] )
{
	IMap * mapa = IMap::Factory(0,"Resources/map_example.txt");
	
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
			Scene* startScene = gScenes[0];
			EngineInst->setNextScene(startScene);
			EngineInst->mainLoop();
		}
	}

	EngineInst->unLoadResources(globalTextures, globalTexturesSize);

	for(unsigned i=0; i<gScenesSize; ++i) {
		if (gScenes[i]) {
			delete gScenes[i];
			gScenes[i] = NULL;
		}
	}

	EngineInst->unLoadGlobalFont();
	
	//Free resources and close SDL
	Engine::Destroy();




	return 0;
}
