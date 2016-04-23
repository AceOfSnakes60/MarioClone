
#include <stdio.h>
#include <SFML/Graphics.hpp>
//#include "SDL.h"
#include "gameengine.h"
#include "gamestate.h"

void CGameEngine::Init(const char* title, int width, int height,
						 bool fullscreen)
{
	int flags = 0;
	// initialize SDL
//	SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
//	SDL_WM_SetCaption(title, title);

	if ( fullscreen ) {
//		flags = SDL_FULLSCREEN;
	}
    sf::RenderWindow MarioClone(sf::VideoMode(width, height), title, sf::Style::Default);

    /**
     *
     *
     *         DELETE FPS LATERON
     *
     *
     */

    MarioClone.setFramerateLimit(1);
	// create the screen surface
//	screen = SDL_SetVideoMode(width, height, bpp, flags);

	m_fullscreen = fullscreen;
	m_running = true;

	printf("CGameEngine Init\n");
}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other
	// programs won't get accidentally resized
	if ( m_fullscreen ) {
        MarioClone.setSize(sf::Vector2u(480, 320));
//		screen = SDL_SetVideoMode(640, 480, 0, 0);
	}

	printf("CGameEngine Cleanup\n");

	// shutdown SDL
//	SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void CGameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
}
