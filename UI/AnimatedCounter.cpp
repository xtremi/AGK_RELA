#include "AnimatedCounter.h"


AnimatedCounter::AnimatedCounter(const glm::vec3& color, float txtsize)
	: AnimatedTextSprite("", color, txtsize)
{
	customAnimationON = true;
	setAlignment(AgkHAlign::right, AgkVAlign::top);
}
