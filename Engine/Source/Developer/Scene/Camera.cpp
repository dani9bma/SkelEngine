#include "Camera.h"
#include "..\Utils\Input.h"

namespace Skel
{
	Camera::Camera(float sensitivity, Window* window, Shader* shader)
	{
		m_sensitivity = sensitivity;
		m_window = window;
		m_shader = shader;
		m_cameraPos = glm::vec3(4.0f, 10.0f, -30.0f);
		m_cameraTarget = glm::vec3(0.0f, 0.0f, -10.0f);
		m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
		m_cameraRight = glm::normalize(glm::cross(m_cameraUp, m_cameraDirection));
		m_cameraFront = glm::vec3(0.0f, 0.0f, -10.0f);
		m_cameraUp = glm::vec3(0.0f, 3.0f, 0.0f);
		m_deltaTime = 0.0f;
		m_lastFrame = 0.0f;
		m_lastX = static_cast<float>(m_window->GetWidth()) / 2;
		m_lastY = static_cast<float>(m_window->GetHeight()) / 2;
		m_yaw = 0.0f;
		m_pitch = 0.0f;
		m_fov = 60.0f;

	
		m_projection = glm::perspective(glm::radians(m_fov), (float)m_window->GetWidth() / (float)m_window->GetHeight(), 0.1f, 500.0f);
		shader->setUniformMat4("projection", m_projection);
	}

	Camera::~Camera()
	{
	}

	void Camera::update()
	{
		float cameraSpeed = 70.0f * m_deltaTime;
		float currentFrame = static_cast<float>(glfwGetTime());
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		if (SKInput::isKeyPressed(m_window, KEY_W))
			m_cameraPos += cameraSpeed * m_cameraFront;
		if (SKInput::isKeyPressed(m_window, KEY_S))
			m_cameraPos -= cameraSpeed * m_cameraFront;
		if (SKInput::isKeyPressed(m_window, KEY_A))
			m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (SKInput::isKeyPressed(m_window, KEY_D))
			m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (SKInput::isKeyPressed(m_window, KEY_LEFT_SHIFT))
			m_cameraPos -= cameraSpeed * m_cameraUp;
		if (SKInput::isKeyPressed(m_window, KEY_SPACE))
			m_cameraPos += cameraSpeed * m_cameraUp;

		
		if (SKInput::isMouseButtonPressed(m_window, MOUSE_BUTTON_RIGHT))
		{
			SKInput::GetMousePosition(m_window, m_x, m_y);
			SKInput::ShowMouseCursor(m_window, false);
			timer++;
			if (timer < 5)
			{
				m_x = m_lastX;
				m_y = m_lastY;
				SKInput::SetMousePosition(m_window, m_x, m_y);
			}
		}
		else
		{
			SKInput::ShowMouseCursor(m_window, true);
			timer = 0;
		}


		float xoffset = static_cast<float>(m_x) - m_lastX;
		float yoffset = m_lastY - static_cast<float>(m_y);
		m_lastX = static_cast<float>(m_x);
		m_lastY = static_cast<float>(m_y);
		xoffset *= m_sensitivity;
		yoffset *= m_sensitivity;

		m_yaw += xoffset;

		m_pitch += yoffset;

		if (m_pitch > 89.f)
			m_pitch = 89.f;
		if (m_pitch < -89.f)
			m_pitch = -89.f;

		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_cameraFront = glm::normalize(front);
		m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
		m_shader->setUniformMat4("view", m_view);

		m_projection = glm::perspective(glm::radians(m_fov), (float)m_window->GetWidth() / (float)m_window->GetHeight(), 0.1f, 500.0f);
		m_shader->setUniformMat4("projection", m_projection);
	}

	void Camera::changeFOV(float value)
	{
		m_projection = glm::perspective(glm::radians(value), (float)1280 / (float)720, 0.1f, 500.0f);
		m_shader->setUniformMat4("projection", m_projection);
	}

}