#pragma once

#ifndef _RAINDROP_RENDERER_H__
#define _RAINDROP_RENDERER_H__

#ifdef _WIN32
#ifdef RAINDROPRENDERER_EXPORTS
#define RAINDROPRENDERER_API __declspec(dllexport)
#else
#define RAINDROPRENDERER_API __declspec(dllimport)
#endif

#else

#define RAINDROPRENDERER_API

#endif //_WIN32

#ifdef _DEBUG
	#define RENDER_DEBUG_ENABLED true
#else
	#define RENDER_DEBUG_ENABLED false
#endif //_DEBUG

#include "RD_ShaderLoader.h"
#include "RD_FrameLimiter.h"
#include "RD_PointLight.h"
#include "RD_GUI.h"
#include "RD_Texture.h"
#include "RD_Materials.h"
#include "RD_Texture.h"

#include <BD_StructMan.h>
#include <BD_MatRW.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <vec3.h>

#ifdef _WIN32
	#include <Windows.h>
#endif

//Frwd Declaration
class RD_DirLight;
class RD_Mesh;
class RD_Quad;
class RD_FrameBuffer;
class RD_Camera;
class RD_MaterialLibrary;

class RAINDROPRENDERER_API RaindropRenderer {
public:
	RaindropRenderer(int w, int h, std::string windowName, int maxFramerate = 60, bool minInit = false);
	~RaindropRenderer();

	bool initGlad(bool minInit = false);
	void MinInit();

	void initWindow(int w, int h, std::string name);
	void ClearWindow(vec3f refreshColor);
	void SwapWindow();
	GLFWwindow* GetGLFWwindow();
	bool WantToClose();

	int getWindowHeigh();
	int getWindowWidth();
	void SetFullscreenMode(bool fullscr);

	double GetLastDeltaTime();

	void SetAASampling(int nbrSample);

	void RenderMeshes(RD_Camera* cam);
	void RenderShadowMeshes();

	void RenderLightPass(vec3f camPos);
	void RenderLightsDepth(vec3f camPos);

	void RenderGbuff(RD_Camera*);
	void RecreateGbuff();

	RD_Texture* GetBlankTexture();
	
	void AddToTextureGarbageCollector(unsigned int texID);
	void EmptyTextureGarbageCollector();

	void AddToFramebufferGarbageCollector(unsigned int fboID);
	void EmptyFramebufferGarbageCollector();

	//Lighting
	void SetAmbientStrength(float strength);
	void SetAmbientColor(vec3f nColor);

	int AppendLight(RD_PointLight* ptLight);
	int AppendDirLight(RD_DirLight* dirLight);
	void RegisterMesh(RD_Mesh* mesh);

	void UnregisterMesh(RD_Mesh*);
	void UnregisterPointLight(RD_PointLight*);
	void UnregisterDirLight(RD_DirLight*);

	//Shading
	void SwitchShader(RD_ShaderLoader*);
	RD_ShaderLoader* GetShadowShader();
	RD_ShaderLoader* GetCurrentShader();
	RD_ShaderMaterial* FetchShaderFromFile(std::string ref);

	//Debug
	void RenderDbg(RD_Camera*);
	float GetFramerate();

	//Renderer Feature
	void EnableFeature(RendererFeature ftr);
	void DisableFeature(RendererFeature ftr);
	bool IsFeatureEnabled(RendererFeature ftr);
	void SendFeaturesToShader(RD_ShaderLoader* shader);

	void UpdatePointsLighting();

	//GUI
	void InitGUI();
	void RegisterGUI(RD_GUI*);

	int GetFrameLimit();
	bool GetErrorFlag();
private:
	void UpdateAmbientLighting();
	void UpdateDirLighting();

	void FillPtLightIndice(int index);
	void FillDirLightIndice(int index);

	void FillFeaturesStringArray();
	void FillFeatureStateArray();
	void EnableAllFeatures();

	bool CreateGbuff();
	void DeleteGbuff();

	void SetErrorFlag(bool val);

	GLFWwindow* win;

	int m_height;
	int m_width;

	bool m_error_flag;

	std::string m_features_string[3];
	bool m_features_state[3];

	float ambientStrength;
	vec3f ambientColor;

	std::unique_ptr<RD_FrameLimiter> m_frmLmt;

	std::vector<RD_PointLight*> m_pt_lights;
	std::vector<RD_DirLight*> m_DirLights;
	std::vector<RD_GUI*> m_guis;
	std::vector<RD_Mesh*> m_meshes;

	std::unique_ptr<RD_Mesh> m_DBG_light_mdl;
	std::unique_ptr<RD_Mesh> m_DBG_sound_emitter_mdl;

	std::shared_ptr<RD_Texture> m_defTex;
	std::shared_ptr<RD_Texture> m_blankTexture;

	std::vector<unsigned int> m_textureGarbageCollector;
	std::vector<unsigned int> m_framebufferGarbageCollector;

	//Deffered Rendering
	Gbuff m_g_buffer;
	std::unique_ptr<RD_Quad> m_quad;

	std::unique_ptr<RD_ShaderLoader> m_shadowShader;
	std::unique_ptr<RD_ShaderLoader> m_light_shader;

	RD_ShaderLoader* m_CurrentShader;

	//Materials
	std::unique_ptr<RD_MaterialLibrary> m_matlib;
};

template<class T>
int GetElemIndex(std::vector<T> array, T element) {
	auto it = std::find(array.begin(), array.end(), element);

	if (it != array.end()) {
		return std::distance(array.begin(), it);
	}
	else {
		std::cerr << "ERROR: Element cannot be found !" << std::endl;
		return -1;
	}
}

void glfwWinCallback(GLFWwindow* win, int w, int h);

RAINDROPRENDERER_API std::wstring StrToWStr(std::string str);

#endif // !_RAINDROP_RENDERER_H__
