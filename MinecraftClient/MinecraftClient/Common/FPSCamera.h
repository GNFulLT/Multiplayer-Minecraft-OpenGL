#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FPSCamera
{
	public:

		FPSCamera(float fov, float aspect, float zNear, float zFar, float sensivity = 0.25f);
		~FPSCamera() = default;



		const glm::mat4& GetModelMatrix()
		{
			return m_viewMatrix;
		}

		const glm::mat4& GetViewProjectionMatrix()
		{
			return m_viewProjectionMatrix;
		}

		void MoveCameraZ(float x);
		void MoveCameraX(float x);

		void CameraRotateYAxis(float x);
		

		void CameraChangeDirection(float xOffSet, float yOffSet);


		void CameraRotateYAxisSlow(float x);
		void RefreshCamera()
		{
			RecalculateViewMatrix();
			RecalculateProjectionMatrix();
		}

		const glm::vec3& GetPos()
		{
			return m_position;
		}

	private:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix();

		float m_rotation;

		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;

		glm::vec3 direction;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		glm::mat4 m_viewProjectionMatrix;


		float m_sensitivity = 0.2;
		float m_prevMx = 0.0f;
		float m_prevMy = 0.0f;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;

		float m_aspect;


		float m_fov;

		float m_zNear;
		float m_zFar;
		//! For Physics
		
		glm::vec3 m_Acceleration;
		glm::vec3 m_Velocity;

};
