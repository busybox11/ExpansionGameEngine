#pragma once

#ifndef _EXP_COMPONENT_H__
#define _EXP_COMPONENT_H__

#ifdef _WIN32

#ifdef EXPANSIONGAMEENGINECORE_EXPORTS
#define EXPGE_API __declspec(dllexport)
#else
#define EXPGE_API __declspec(dllimport)
#endif

#else

#define EXPGE_API

#endif //_WIN32

#include <string>

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vec3.h>

class EXPGE_API EXP_Component
{
public:
	EXP_Component(vec3f pos, vec3f rot, vec3f scale);
	~EXP_Component();

	virtual vec3f GetPosition();
	virtual vec3f GetRotation();
	virtual vec3f GetScale();

	virtual void SetPosition(vec3f nPos);
	virtual void SetRotation(vec3f nRot);
	virtual void SetScale(vec3f nScale);

	virtual void UseParentMatrix(glm::mat4 mat);
	virtual glm::mat4 GetParentMatrix();

	void SetNameTag(std::string);
	std::string GetNameTag();

protected:

	vec3f m_pos;
	vec3f m_rot;
	vec3f m_scale;

	glm::mat4 m_parent_mat;

	std::string m_nameTag;
};

#endif //_EXP_COMPONENT_H__