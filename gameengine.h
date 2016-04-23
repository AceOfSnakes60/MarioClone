
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//#include "SDL.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class CGameState;

class CGameEngine
{
public:

	void Init(const char* title, int width=800, int height=600,
		      bool fullscreen=false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

//	SDL_Surface* screen;
    sf::RenderWindow MarioClone;

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
