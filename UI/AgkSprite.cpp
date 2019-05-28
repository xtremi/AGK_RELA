#include "AgkSprite.h"


/****************************************************/
AgkSprite::AgkSprite()
/****************************************************/
{}
/****************************************************/
AgkSprite::~AgkSprite()
/****************************************************/
{
}

/* COLOR */
glm::vec3 AgkSprite::getColor() {
	return glm::vec3(getColorRed(), getColorGreen(), getColorBlue());
}
void AgkSprite::setColor(const glm::vec3& color, float alpha) {
	setColor(color.x, color.y, color.z, alpha);
}
void AgkSprite::setColor(const glm::vec4& color) {
	setColor(color.x, color.y, color.z, color.w);
}
void AgkSprite::setColor(float r, float g, float b, float a) {
	setColor((UINT)(255.0f*r), (UINT)(255.0f*g), (UINT)(255.0f*b), (UINT)(255.0f*a));
}



/* POSITION */
glm::vec2 AgkSprite::getPos() {
	return glm::vec2(getX(), getY());
}
void AgkSprite::setPosition(const glm::vec2& pos) {
	setPosition(pos.x, pos.y);
}
void AgkSprite::setPosition(float x, float y) {
	setX(x);
	setY(y);
}


/* MOVE */
void AgkSprite::move(const glm::vec2& dpos) {
	move(dpos.x, dpos.y);
}
void AgkSprite::move(float dx, float dy) {
	setPosition(getX() + dx, getY() + dy);
}
void AgkSprite::moveX(float dx) {
	setX(getX() + dx);
}
void AgkSprite::moveY(float dy) {
	setY(getY() + dy);
}

/* SIZE */
glm::vec2 AgkSprite::getSize() {
	return glm::vec2(getSizeX(), getSizeY());
}
void AgkSprite::setSize(const glm::vec2& s) {
	setSize(s.x, s.y);
}
void AgkSprite::setSize(float s) {
	setSize(s, s);
}

/* SCALE */
glm::vec2 AgkSprite::getScale() {
	return glm::vec2(getScaleX(), getScaleY());
}
void AgkSprite::setScale(const glm::vec2& s) {
	setScale(s.x, s.y);
}
void AgkSprite::setScale(float s) {
	setScale(s, s);
}
void AgkSprite::scale(float s) {
	setScale(getScale() * s);
}


/* ROTATION */
void AgkSprite::rotate(float angle) {
	setRotation(getRotation() + angle);
}


bool AgkSprite::isHoovered_world() {
	return hitTest(agk::ScreenToWorldX(agk::GetPointerX()), agk::ScreenToWorldY(agk::GetPointerY()));
}
bool AgkSprite::isHoovered() {
	return hitTest(agk::GetPointerX(), agk::GetPointerY());
}
bool AgkSprite::hitTest(const glm::vec2& pos) {
	return hitTest(pos.x, pos.y);
}