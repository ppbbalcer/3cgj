#include <list>
#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include <SDL.h>
#include "GlobalData.h"
#include "victoryscene.h"

const char * Congratulations =
	"You won...\n"
	"Or more accurately you survived.\n"
	"Congratulations. Our game wasn't meant to be easy - we hope,\n"
	"your playthrough was as exciting as our effort developing it.\n"

	"\n\nRevenge of the GM is (c) 2015.\nDevelopment team:\n- Pawlowski Slawomir\n- Kaminski Maciej\n- Naruszewicz Maciej\n- Balcer Piotr"
	"\n\nPress [ESCAPE] to return to desktop...";

float cur_char=0;
void VictoryScene::OnUpdate(int timems) {
		//Event handler
	SDL_Event e;
	cur_char += 0.005*timems;
	while( SDL_PollEvent( &e ) != 0 )
	{
		Engine::eventDebug(&e);
		
		//User requests quit, Press Esc
		if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
		{
			EngineInst->breakMainLoop();
		} else if( e.type == SDL_KEYDOWN )
		{
			//EngineInst->breakMainLoop();
		}
	}
};
void VictoryScene::OnRender(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texturesScene[0].texture, NULL, NULL ); //Update screen 
	int cur=(int)cur_char;
	int line=0;
	int col=0;
	char buf[1000];
	for (int i = 0 ; i!= cur ; ++i) {
		if (Congratulations[i]==0) {
			break;
		} else if (Congratulations[i]=='\n') {
			line++;
			col=0;
		} else {
			
			EngineInst->font()->printfLT(17*col,25*line,
						     "%c", Congratulations[i]);
			col++;
		}
	}
	
	
	
};
