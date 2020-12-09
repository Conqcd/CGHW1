#pragma once


#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include"vec.h"
#include"Matrix.h"
#include"common.h"
#include <vector>
#include<cmath>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
	//属性
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;
	//欧拉角
	float Yaw;
	float Pitch;
	//选项
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	//构造函数
	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = vec3(posX, posY, posZ);
		WorldUp = vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix()
	{
		vec3 zaxis = normalize(-Front);
		vec3 xaxis = normalize(cross(normalize(WorldUp), zaxis));
		vec3 yaxis = cross(zaxis, xaxis);

		mat4 translation = mat4(1.0f);
		translation[3][0] = -Position.getx();
		translation[3][1] = -Position.gety();
		translation[3][2] = -Position.getz();
		mat4 rotate = mat4(1.0f);
		rotate[0][0] = xaxis.getx();
		rotate[1][0] = xaxis.gety();
		rotate[2][0] = xaxis.getz();
		rotate[0][1] = yaxis.getx();
		rotate[1][1] = yaxis.gety();
		rotate[2][1] = yaxis.getz();
		rotate[0][2] = zaxis.getx();
		rotate[1][2] = zaxis.gety();
		rotate[2][2] = zaxis.getz();
		return rotate * translation;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float cameraSpeed = 2.5f * deltaTime;
		if (direction == FORWARD)
			Position += cameraSpeed * Front;
		if (direction == BACKWARD)
			Position -= cameraSpeed * Front;
		if (direction == LEFT)
			Position -= Right * cameraSpeed;
		if (direction == RIGHT)
			Position += Right * cameraSpeed;
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{

		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch)
		{
			if (Pitch >= 89.9f)
				Pitch = 89.9f;
			if (Pitch <= -89.9f)
				Pitch = -89.9f;
		}
		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}
private:
	void updateCameraVectors()
	{
		vec3 front;
		front.set(cos(radians(Yaw)) * cos(radians(Pitch)), sin(radians(Pitch)), sin(radians(Yaw)) * cos(radians(Pitch)));
		Front = normalize(front);
		Right = normalize(cross(Front, WorldUp));
		Up = normalize(cross(Right, Front));
	}
	vec3 getGroundDirection()
	{
		return normalize(vec3(Front.getx(), 0.0f, Front.getz()));
	}
};