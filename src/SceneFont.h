#ifndef __SCENE_FONT_H__
#define __SCENE_FONT_H__

#include "GlobalData.h"
#include <stdio.h>
#include <string>
#include "Engine/Scene.h"
#include "Engine/Engine.h"

class SceneFont2D: public Scene {
public:
	virtual void OnLoad() {
		_drawType = DrawType_Paint;
		bool success = EngineInst->loadResources(texturesScene, texturesSceneSize);
		//Load media
		if( !success )
		{
			printf( "Failed to load media SceneInit !\n" );
			PAUSE();
		}
		nextScene = 2;
		strcpy(sceneName, "SceneFont2D");
	};

	virtual void OnFree(){
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);
	};

	virtual void OnUpdate(int timems) {
		//Event handler
		SDL_Event e;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
			{
				//Quit the game
				EngineInst->breakMainLoop();
			} else if( e.type == SDL_KEYDOWN )
			{
				//Change scene
				//EngineInst->setNextScene(gScenes[nextScene]);
			}
		}


		int width = EngineInst->screen_width();
		int height = EngineInst->screen_height();

		SDL_Color textColor = { 255, 255, 255, 255 };
		SDL_Color borderColor = { 255, 0, 0, 255 };
		int border = 1;
		float scale = 0.5f; // Not work
		EngineInst->font()->printf(width/2, height/2, textColor, borderColor, border, 0, 2.0f, sceneName);

		EngineInst->font()->printf(0, 0,				textColor, borderColor, border, ALIGN_LEFT | ALIGN_TOP, scale, "Text LEFT TOP");
		EngineInst->font()->printf(0, height/2,		textColor, borderColor, border, ALIGN_LEFT,				scale, "Text LEFT CENTER");
		EngineInst->font()->printf(0, height,		textColor, borderColor, border, ALIGN_LEFT | ALIGN_BOTTOM,	scale, "Text LEFT BOTTOM");

		EngineInst->font()->printf(width/2, 0,		textColor, borderColor, border, ALIGN_TOP,				scale, "Text CENTER TOP");
		EngineInst->font()->printf(width/2, height,	textColor, borderColor, border, ALIGN_BOTTOM,			scale, "Text CENTER BOTTOM");


		EngineInst->font()->printf(width, 0,				textColor, borderColor, border, ALIGN_RIGHT | ALIGN_TOP, scale, "Text RIGHT TOP");
		EngineInst->font()->printf(width, height/2,		textColor, borderColor, border, ALIGN_RIGHT,				scale, "Text RIGHT CENTER");
		EngineInst->font()->printf(width, height,		textColor, borderColor, border, ALIGN_RIGHT | ALIGN_BOTTOM,	scale, "Text RIGHT BOTTOM");

	};

protected:
	int nextScene;
	char sceneName[1024];
};

class SceneFont3D: public SceneFont2D {
public:
	virtual void OnLoad() {
		SceneFont2D::OnLoad();
		nextScene = 3;
		strcpy(sceneName, "SceneFont3D");
		_drawType = DrawType_Render;
	};

	virtual void OnFree(){
		SceneFont2D::OnFree();
	};
};


#endif /* __SCENE_FONT_H__ */

