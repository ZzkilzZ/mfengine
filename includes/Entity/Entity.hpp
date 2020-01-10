#pragma once

#include "Camera.hpp"

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace mf
{

class Entity
{
protected:
	Camera			*mCamera = NULL;

	glm::vec3		mPos = glm::vec3(0, 500, 0);
	glm::vec3		mDir = glm::vec3(0, 0.5, 1);
	glm::vec3		mVelocity = glm::vec3(0, 0, 0);
	double			mAcceleration = 0.1;

public:
	Entity();
	~Entity();

	virtual void	Update() = 0;
	virtual void	HandleEvents() = 0;

	void			MoveForward();
	void			MoveLeft();
	void			MoveRight();
	void			MoveBackward();

	glm::vec3		GetPosition(){return (mPos);}
	glm::vec3		GetDirection(){return (mDir);}

	void			SetCamera(Camera *tCamera);
};

} // namespace mf
