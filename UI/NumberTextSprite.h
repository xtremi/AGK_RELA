#pragma once
#include "TextSprite.h"


/***********************************************/
class NumberTextSprite : public TextSprite
/***********************************************/
{
public:
	NumberTextSprite(
		float v = 0.0f, const glm::vec3& color = glm::vec3(0.0f), 
		const glm::vec2& pos = glm::vec2(0.0f), float textSize = 1.0f, 
		AgkHAlign halign = AgkHAlign::left, AgkVAlign valign = AgkVAlign::top);
public:
	void setValue(float v, int p = 2);
	float getValue();

private:
	float value = 0.0f;
};
