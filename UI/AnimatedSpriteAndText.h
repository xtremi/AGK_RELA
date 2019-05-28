#pragma once
#include "SpriteAndText.h"
#include "SpriteAnimation.h"

/***********************************************/
class AnimatedSpriteAndTextSprite : public SpriteAndText, public SpriteAnimation
/***********************************************/
{
public:
	AnimatedSpriteAndTextSprite(
		AgkImage* img, char* txt, 
		const glm::vec3& textCol = glm::vec3(0), 
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f);

private:
	glm::vec2 anim_getPos();
	void anim_setPos(const glm::vec2& pos);
	float anim_getRot();
	void anim_setRot(float r);
	float anim_getScale();
	void anim_setScale(float s);
	void postProcessAnim();
};