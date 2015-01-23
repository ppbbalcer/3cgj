#include "GlobalData.h"
#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"

void MainScene::OnLoad() {
	bool success = EngineInst->loadResources(texturesScene03, texturesScene03Size);

	_background = new RTexture(texturesScene03[1]);
	_player = new RTexture(texturesScene03[2]);
	_player->setPos(240, 190);

	_tiles = new RTexture(texturesScene03[3]);
	_tiles->setTileSizeSrc(32);
	_tiles->setTileSizeDst(32);

	if (!success)
	{
		printf( "Failed to load media Scene02Renderer !\n" );
		PAUSE();
	}

	globalAudios[1].res.sound->setVolume(0.3f);
	globalAudios[1].res.sound->play(-1, 0, 2000);
};

void MainScene::OnFree(){
	delete 	_background;
	_background = NULL;
	delete 	_player;
	_player = NULL;
	delete 	_tiles;
	_tiles = NULL;

	EngineInst->unLoadResources(texturesScene03, texturesScene03Size);
};

void MainScene::OnUpdate(int timems) {
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 )
	{
		Engine::eventDebug(&e);

		if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
		{
			EngineInst->breakMainLoop();
			return;
		}
	}

	int dist = timems;
	int posX = _player->getPosX();
	int posY = _player->getPosY();
	int width = _player->getWidth();

	int delay = (int)(2000 * (posX/600.f));
	if (delay < 400)
		delay = 400;

	globalAudios[1].res.sound->setDelay(delay);

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL ); 
	if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
		globalAudios[0].res.sound->play(1, 0);
		posY -= dist;
		if(posY < 0) {
			posY = 0;
		}
	} else {
		posY += dist;
		if(posY > 190) {
			posY = 190;
		}
	}

	if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
		posX -= dist;
		if (posX<0) {
			posX = 0;
		}
	}

	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
		posX += dist;
		if (posX > EngineInst->screen_width() - width) {
			posX = EngineInst->screen_width() - width;
		}
	}

	_player->setPos(posX, posY);

	globalAudios[1].res.sound->update(timems);

	EngineInst->font()->printfLT(100, 100, "Hello test text!!!");
};

void MainScene::OnRender(SDL_Renderer* renderer) {
	_background->render(renderer);
	_player->render(renderer);

	int sizeDst = _tiles->getTileSizeDst() + 5;
	int tilesNums = _tiles->getTilesNums();
	for (int i =  0 ; i<tilesNums; ++i) {
		int col = i % 20 + 2;
		int row = i / 20 + 2;

		_tiles->renderTile(renderer, col * sizeDst, row * sizeDst, i);

		EngineInst->font()->printfLT(col * sizeDst, row * sizeDst, "%i", i);
	}
};
