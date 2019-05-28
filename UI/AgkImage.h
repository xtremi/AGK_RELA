#pragma once
#include "agk.h"
#include "glm/glm.hpp"

/***********************************************/
class AgkImage
/***********************************************/
{
public:
	AgkImage(char* imgpath);
	AgkImage(const glm::vec4& color);
	AgkImage(const glm::vec3& color, float alpha = 1.0f);
	AgkImage(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, unsigned int a = 255);
	AgkImage(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

	unsigned int getID() {
		return id;
	}

private:
	unsigned int id = -1;

};
