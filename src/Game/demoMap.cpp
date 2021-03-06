#include "pch.h"
#include "demoMap.h"

EXPGE_LEVEL_CODE(demoMap);

demoMap::demoMap(EXP_Game* game, EXP_MapLoader* mload) : EXP_Level(true, true) {
	m_game = game;
	m_load = mload;

	//cam = new EXP_Camera(game, vec3f(0.0f, -15.0f, 5.0f), vec3f(), vec3f(), vec3f(90.0f, 90.0f, 0.0f), 60.0f, 0.1f, 100.0f);
	//cam->Use();

	m_key = new EXP_KeyboardCallback(m_game, CL_VDFUNCPTR(demoMap::KeyTest), GLFW_KEY_H);
	//m_mfwd = new EXP_KeyboardCallback(m_game, CL_VDFUNCPTR(demoMap::MoveForward), GLFW_KEY_Z);

	m_floor = new EXP_RB_Box(m_game, vec3f(), vec3f(), vec3f(20.0f, 20.0f, 1.0f), 0.0f);
	m_actor = new demoActor(m_game, vec3f(0.0f, 0.0f, 22.0f));
}

demoMap::~demoMap() {
	delete m_key;
	//delete m_mfwd;
	//delete m_floor;
	//delete m_actor;
}

void demoMap::OnStart() {
	//m_game->GetInputHandler()->CaptureCursor(true);

	m_game->GetRenderer()->SetAmbientStrength(0.2f);
	m_game->GetRenderer()->SetAmbientColor(vec3f(0.1f, 0.2f, 0.2f));
}

void demoMap::OnTick() {
	//cam->AddYaw(m_game->GetInputHandler()->GetMouseXaxis() / -10);
	//cam->AddPitch(m_game->GetInputHandler()->GetMouseYaxis() / -10);
}

void demoMap::KeyTest() {
	m_game->LoadMap("/Maps/map2.json");
}

void demoMap::MoveForward() {
	//cam->Translate(cam->GetForwardVector());
}
