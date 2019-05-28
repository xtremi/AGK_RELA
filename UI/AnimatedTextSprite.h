#pragma once
#include "TextSprite.h"
#include "SpriteAnimation.h"

/***********************************************/
class AnimatedTextSprite : public TextSprite, public SpriteAnimation
/***********************************************/
{
public:
	AnimatedTextSprite(char* txt, const glm::vec3& color, float txtsize);

private:
	glm::vec2 anim_getPos();
	void anim_setPos(const glm::vec2& pos);
	float anim_getRot();
	void anim_setRot(float r);
	float anim_getScale();
	void anim_setScale(float s);
	void postProcessAnim();
};