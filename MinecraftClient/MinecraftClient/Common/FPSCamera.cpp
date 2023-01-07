#include "FPSCamera.h"
#include "Utils/UtilsMath.h"
#include "FPSCamera.h"
#include "FPSCamera.h"
#include "FPSCamera.h"
#include "FPSCamera.h"
#include "FPSCamera.h"
#include "FPSCamera.h"

FPSCamera::FPSCamera(float fov, float aspect, float zNear, float zFar, float sensitivity)
{
	m_fov = fov;
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	//m_rotation = 0.0f;
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_front = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Acceleration = glm::vec3(0.0f);
	m_Velocity = glm::vec3(0.0f);

	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_sensitivity = sensitivity;

	m_viewMatrix = glm::lookAt(m_position, m_front + m_position, m_up);
	m_projectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

	m_rotation = 0;
}
void FPSCamera::MoveCameraZ(float x)
{
	m_position += (x * m_front);
	m_viewMatrix = glm::lookAt(m_position, m_front + m_position, m_up);

}
void FPSCamera::MoveCameraX(float x)
{
	m_position += glm::normalize(glm::cross(m_front, m_up)) * x;
	m_viewMatrix = glm::lookAt(m_position, m_front + m_position, m_up);
}
void FPSCamera::CameraChangeDirection(float xOffSet, float yOffSet)
{
	xOffSet *= m_sensitivity;
	yOffSet *= m_sensitivity;

	m_yaw += xOffSet;
	m_pitch += yOffSet;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(direction);

	m_viewMatrix = glm::lookAt(m_position, m_front + m_position, m_up);

}

void FPSCamera::CameraRotateYAxis(float x)
{	
	m_rotation += (Math::PI / (x / 360));

	m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));


}

void FPSCamera::CameraRotateYAxisSlow(float x)
{
	m_rotation = x;
	m_viewMatrix = glm::lookAt(m_position, m_front + m_position, m_up);

	m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation, glm::vec3(1.0f, 1.0f, 0.0f));
}
void FPSCamera::RecalculateViewMatrix()
{

	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}
void FPSCamera::RecalculateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);

	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

