#include "AnimatedSprite.h"


/****************************************************/
AnimatedSprite::AnimatedSprite(AgkImage* img, const glm::vec2& size) 
	: Sprite(img, glm::vec2(0.0f), size)
/****************************************************/
{}

glm::vec2 AnimatedSprite::anim_getPos(){
	return getPos();
}
void AnimatedSprite::anim_setPos(const glm::vec2& pos) {
	setPosition(pos);
}
float AnimatedSprite::anim_getRot() {
	return getRotation();
}
void AnimatedSprite::anim_setRot(float r) {
	setRotation(r);
}
float AnimatedSprite::anim_getScale() {
	return getScale().x;
}
void AnimatedSprite::anim_setScale(float s) {
	setScale(s);
}

