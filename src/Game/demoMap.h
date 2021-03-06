#pragma once

#ifdef _WIN32
#define GAME_API __declspec(dllexport)
#endif

#include <iostream>

#include <EXP_Game.h>
#include <EXP_Level.h>
#include <EXP_MapLoader.h>
#include <EXP_HotLoad.h>
#include <EXP_InputHandler.h>
#include <EXP_RigidBody.h>
#include <EXP_Camera.h>

#include "demoActor.h"

class demoMap : public EXP_Level
{
public:
	demoMap(EXP_Game*, EXP_MapLoader*);
	~demoMap();

	virtual void OnStart() override;
	virtual void OnTick() override;

	void KeyTest();
	void MoveForward();

private:
	EXP_Game* m_game;
	EXP_MapLoader* m_load;

	demoActor* m_actor;

	//EXP_Camera* cam;

	EXP_KeyboardCallback* m_key;
	//EXP_KeyboardCallback* m_mfwd;

	EXP_RB_Box* m_floor;
};

EXPGE_LEVEL_HEADER(demoMap);