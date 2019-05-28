#include "AnimatedSpriteAndText.h"

/****************************************************/
AnimatedSpriteAndTextSprite::AnimatedSpriteAndTextSprite(
	AgkImage* img, char* txt, const glm::vec3& textCol, 
	const glm::vec2& size, float textSize
)
	: SpriteAndText(img, txt, textCol, size, textSize)
/****************************************************/
{}


glm::vec2 AnimatedSpriteAndTextSprite::anim_getPos() {
	return getPos();
}
void AnimatedSpriteAndTextSprite::anim_setPos(const glm::vec2& pos) {
	setPosition(pos);
}
float AnimatedSpriteAndTextSprite::anim_getRot() {
	return getRotation();
}
void AnimatedSpriteAndTextSprite::anim_setRot(float r) {
	setRotation(r);
}
float AnimatedSpriteAndTextSprite::anim_getScale() {
	return getScale().x;
}
void AnimatedSpriteAndTextSprite::anim_setScale(float s) {
	setScale(s);
}
void AnimatedSpriteAndTextSprite::postProcessAnim() {
	realign();
}