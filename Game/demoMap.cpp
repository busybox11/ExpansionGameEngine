#include "pch.h"
#include "demoMap.h"

EXPGE_LEVEL_CODE(demoMap);

demoMap::demoMap(EXP_Game* game, EXP_MapLoader* mload) : EXP_Level(true, true) {
	m_game = game;
	m_load = mload;

	cam = new EXP_Camera(game, vec3f(0.0f, -10.0f, 5.0f), vec3f(), vec3f(), vec3f(90.0f), 60.0f, 0.1f, 100.0f);
	cam->Use();
}

void demoMap::OnStart() {
	m_load->GetStaticMeshByName("shaderBall1")->SetPosition(vec3f(0.0f, 0.5f, 0.0f));
	rot = vec3f(0.0f, 45.0f, 0.0f);
}

void demoMap::OnTick() {
	if (glfwGetKey(m_game->GetRenderer()->GetGLFWwindow(), GLFW_KEY_H) == GLFW_PRESS) {
		m_game->UnloadCurrentMap();
	}

	rot = rot + vec3f(0.0f, 0.0f, 0.01f);

	m_load->GetStaticMeshByName("shaderBall1")->addRotation(vec3f(0.0f, 0.0f, 0.01f));
	m_load->GetStaticMeshByName("shaderBall1")->SetWorldRotation(rot);
}