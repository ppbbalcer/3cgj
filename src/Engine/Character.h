#include "RTexture.h"

#define MAX_HEALTH 100

class Character
{
public:
	Character(RTexture *texture);
	~Character(void);

	int getHealth();
	int crucio(int howMuchCrucio);
	void heal(int howMuchHeal);

	void render(SDL_Renderer *renderer, RTexture *tiles);
	void setPos(int x, int y);
	int getPosX();
	int getPosY();
private:
	RTexture *_texture;
	int _health;
	int _speed;
};
