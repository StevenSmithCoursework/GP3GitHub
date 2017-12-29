#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	//Creates the camera
	Camera(const glm::vec3& pos, const glm::vec3& rot, float fov, float aspect, float cNear, float cFar)
	{
		//Sets the persective using the fov and near and far clipping planes
		m_perspective = glm::perspective(fov, aspect, cNear, cFar);
		//Sets the position of the camera
		m_position = pos;
		//Tells the camera which way is forward
		m_forward = rot;
		//Tells the camera which way is up
		m_up = glm::vec3(0, 1, 0);
	}
	//Allows for movement with the mouse
	void cameraUpdate(const glm::vec2& rotAngle)
	{
		m_forward = glm::mat3(glm::rotate(rotAngle.x, m_up)) * m_forward;
	}
	//Getters
	inline glm::vec3& GetCameraRot() { return m_forward; }
	inline glm::vec3& GetCameraPos() { return m_position; }
	//Setters
	inline void SetCameraRot(const glm::vec3& rot) { m_forward = rot; }
	inline void SetCameraPos(const glm::vec3& pos) { m_position = pos; }
	//Works out the projection matrix by multiplying the perspective with the view matrix
	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};