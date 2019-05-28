#pragma once
#include "Sprite.h"
#include "SpriteAnimation.h"

/***********************************************/
class AnimatedSprite : public Sprite, public SpriteAnimation
/***********************************************/
{
public:
	AnimatedSprite(AgkImage* img, const glm::vec2& size);

private:
	glm::vec2 anim_getPos();
	void anim_setPos(const glm::vec2& pos);
	float anim_getRot();
	void anim_setRot(float r);
	float anim_getScale();
	void anim_setScale(float s);

	

};