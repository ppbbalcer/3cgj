#include "Enemy.h"
#include "GlobalData.h"
#include "Player.h"
#include "Engine/Engine.h"
#include <algorithm>
using namespace std;
Enemy::Enemy(RTexture *texture, IMap *map, int hp, int ai) : Character(texture, map)
{
	_type = TYPE_ENEMY;
	_time_to_attack = 0;
	_time_to_random_direction = 0;
	_health = hp;
	_ai = (enemy_ai)ai;
}

Enemy::~Enemy(void) {};

int Enemy::crucio(int howMuchCrucio)
{
	int hpRem = Character::crucio(howMuchCrucio);
	if (hpRem <= 0) {
		globalAudios[ENEMY_DEATH].res.sound->play();
	}
	return hpRem;
}

void Enemy::OnUpdate(int time_ms)
{
	Character::OnUpdate(time_ms/3);
	// Don't attack PC if I am dead
	if (GetState()!=ALIVE)
		return;
	_time_to_attack=max<int>(_time_to_attack-time_ms,
			       0);
	_time_to_random_direction=max<int>(_time_to_random_direction-time_ms,
					   0);

	if (_time_to_attack)
		return;
	
	/* inflicit damage on all player characters on neighboring 
	 * fields
	 */
	for (int i = getPosBeforeX()-1; i!= getPosBeforeX()+2; ++i) 
			for (int j = getPosBeforeY()-1; j!= getPosBeforeY()+2; ++j)
			{
				/*check if field is within boundaries
				 * of the map
				 */
				if (i>=_map->GetWidth()) continue;
				if (i<0) continue;
				if (j>=_map->GetHeight()) continue;
				if (j<0) continue;
				Character * wih = _map->GetFieldAt(i,j)->WhoIsHere();
				/* if field is occupied and a character
				 * who is there happens to be a players 
				 * character (don't harm AIs) */
				if (wih && dynamic_cast<Player*>(wih))
				{
					printf("Crucio!\n");
					wih->crucio(20);
				}
					
			}
	_time_to_attack=500;
}

DIRECT Enemy::getRandomDirection()
{
	clock_t now = clock();
	if (_time_to_random_direction) {
		return DIRECT_NO_WAY;
		;
	}

	_time_to_random_direction= RANDOM_DIRECTION_CHANGE_TIME_MS;
	return (static_cast<DIRECT>((rand() % (DIRECT_END - 1)) + 1));
}

void Enemy::OnRender(SDL_Renderer *renderer)
{
	//For debug A*
	//{ //Astar Example
	//	int tileSize = EngineInst->getTileSize();
	//	for(std::list<AStartPoint_t>::iterator step = way.begin(); step != way.end(); ++step) {
	//		int x = (*step).first;
	//		int y = (*step).second;
	//		//EngineInst->font()->printfLT(x*tileSize, y*tileSize, "X");
	//		_texture->renderTile(renderer, x*tileSize, y*tileSize);

	//	}
	//}
	Character::OnRender(renderer);
}
