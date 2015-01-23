#ifndef __SCENE_H__
#define __SCENE_H__

#include <SDL.h>
#include <SDL_image.h>

/* Interface for Scene */

class Scene {
public:
	enum DrawType {
		DrawType_Paint = 0,
		DrawType_Render = 1,
	};
	virtual void OnLoad() = 0;
	virtual void OnFree() = 0;
	virtual void OnUpdate(int timems) = 0;
	virtual void OnPaint(SDL_Surface* screenSurface){};
	virtual void OnRender(SDL_Renderer* renderer){};
	
	Scene():_drawType(DrawType_Render){};
	virtual ~Scene(){};

	void OnLoadBase() {
		OnLoad();
	};

	void OnFreeBase() {
		OnFree();
	};

	DrawType getDrawType() { 
		return _drawType;
	};

protected:
	DrawType _drawType;
private:
	Scene* operator=(const Scene&);
};

#endif /* __SCENE_H__ */