#include "AnimatedTextSprite.h"

/****************************************************/
AnimatedTextSprite::AnimatedTextSprite(char* txt, const glm::vec3& color, float size) 
	: TextSprite(txt, color, glm::vec2(0.0f), size, AgkHAlign::center, AgkVAlign::center)
/****************************************************/
{}

glm::vec2 AnimatedTextSprite::anim_getPos() {
	return getPos();
}
void AnimatedTextSprite::anim_setPos(const glm::vec2& pos) {
	setPosition(pos);
}
float AnimatedTextSprite::anim_getRot() {
	return getRotation();
}
void AnimatedTextSprite::anim_setRot(float r) {
	setRotation(r);
}
float AnimatedTextSprite::anim_getScale() {
	return getScale().x;
}
void AnimatedTextSprite::anim_setScale(float s) {
	setScale(s);
}
void AnimatedTextSprite::postProcessAnim() {
	realign();
}