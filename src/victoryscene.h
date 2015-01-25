#ifndef __VICTORY_SCENE_H
#define __VICTORY_SCENE_H

class VictoryScene: public Scene {
public:
	virtual void OnLoad() {
		timer = 0;
		bool success = EngineInst->loadResources(texturesScene,texturesSceneSize);
		//Load media
		if( !success )
		{
			printf( "Failed to load media VictoryScene !\n" );
			PAUSE();
		}

	}

	virtual void OnFree(){
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);
	}

	virtual void OnUpdate(int timems);

	virtual void OnRender(SDL_Renderer* renderer) ;
private:
	int timer;

};


#endif
