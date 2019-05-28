#include "Sprite.h"

/****************************************************/
Sprite::Sprite() : AgkSprite()
/****************************************************/
{
	id = agk::CreateSprite(0);
}


/****************************************************/
Sprite::Sprite(
	AgkImage* img, const glm::vec2& pos, const glm::vec2& size, 
	AgkHAlign halign, AgkVAlign valign) : AgkSprite()
/****************************************************/
{
	id = agk::CreateSprite(img->getID());	
	setSize(size);
	setAlignment(halign, valign);
	setPosition(pos);
}

/****************************************************/
Sprite::Sprite(
	const glm::vec3& color, const glm::vec2& pos, 
	const glm::vec2& size, AgkHAlign halign, AgkVAlign valign) : AgkSprite()
/****************************************************/
{
	id = agk::CreateSprite(0);
	setColor(color);	
	setSize(size);
	setAlignment(halign, valign);
	setPosition(pos);
}

Sprite::Sprite(const glm::vec4& color, const glm::vec2& pos, const glm::vec2& size, AgkHAlign halign, AgkVAlign valign) :
	Sprite(glm::vec3(color.r, color.g, color.b), pos, size, halign, valign)
{
	setColorAlpha(color.a);
}





void Sprite::setImage(AgkImage* img) {
	agk::SetSpriteImage(id, img->getID());
}
void Sprite::setShape(AgkSpriteShape shape) {
	agk::SetSpriteShape(id, (int)shape);
}

float Sprite::getWidth() {
	return agk::GetSpriteWidth(id);
}
float Sprite::getHeight() {
	return agk::GetSpriteHeight(id);
}

void Sprite::fixToScreen() {
	agk::FixSpriteToScreen(id, 1);
	isFixedToScreen = true;
}
void Sprite::deleteSprite() {
	agk::DeleteSprite(id);
}

/* COLOR */
void Sprite::setColor(UINT r, UINT g, UINT b, UINT a) {
	agk::SetSpriteColor(id, r, g, b, a);
}
void Sprite::setColorAlpha(float a) {
	agk::SetSpriteColorAlpha(id, (UINT)(255.0f*a));
}
float Sprite::getColorRed() {
	return 	((float)agk::GetSpriteColorRed(id)) / 255.0f;
}
float Sprite::getColorGreen() {
	return 	((float)agk::GetSpriteColorGreen(id)) / 255.0f;
}
float Sprite::getColorBlue() {
	return 	((float)agk::GetSpriteColorBlue(id)) / 255.0f;
}

/* POSITION */
void Sprite::setPosition(float x, float y) {
	if (!byOffset)
		agk::SetSpritePosition(id, x, y);
	else
		agk::SetSpritePositionByOffset(id, x, y);
}
float Sprite::getX() {
	if (!byOffset)
		return agk::GetSpriteX(id);
	else
		return agk::GetSpriteXByOffset(id);
}
float Sprite::getY() {
	if (!byOffset)
		return agk::GetSpriteY(id);
	else
		return agk::GetSpriteYByOffset(id);
}
void Sprite::setX(float x) {
	if (!byOffset)
		agk::SetSpriteX(id, x);
	else
		agk::SetSpritePositionByOffset(id, x, agk::GetSpriteYByOffset(id));
}
void Sprite::setY(float y) {
	if (!byOffset)
		agk::SetSpriteY(id, y);
	else
		agk::SetSpritePositionByOffset(id, agk::GetSpriteXByOffset(id), y);
}

/* SIZE */
float Sprite::getSizeX() {
	return getWidth();;
}
float Sprite::getSizeY() {
	return getHeight();;
}
void Sprite::setSize(float sx, float sy){
	agk::SetSpriteSize(id, sx, sy);
}

/* SCALE */
float Sprite::getScaleX() {
	return agk::GetSpriteScaleX(id);
}
float Sprite::getScaleY() {
	return agk::GetSpriteScaleY(id);
}
void Sprite::setScale(float sx, float sy) {
	if (!byOffset)
		agk::SetSpriteScale(id, sx, sy);
	else
		agk::SetSpriteScaleByOffset(id, sx, sy);
}


/* ROTATION */
void Sprite::setRotation(float angle) {
	agk::SetSpriteAngle(id, angle);
}
float Sprite::getRotation() {
	return agk::GetSpriteAngle(id);
}


bool Sprite::hitTest(float x, float y)
{
	if (isFixedToScreen)
		return agk::GetSpriteHitTest(id, agk::ScreenToWorldX(x), agk::ScreenToWorldY(y));
	else
		return agk::GetSpriteHitTest(id, x, y);
}
void Sprite::setState(bool state) {
	agk::SetSpriteVisible(id, state);
}
void Sprite::setDepth(int depth) {
	agk::SetSpriteDepth(id, depth);
}
void Sprite::setAlignment(AgkHAlign halign, AgkVAlign valign) {
	if (halign == AgkHAlign::left && valign == AgkVAlign::top)
		byOffset = false;
	else
		byOffset = true;

	setOffset(halign, valign);
}
void Sprite::setOffset(AgkHAlign halign, AgkVAlign valign) {
	
	float hf = 0.0f, vf = 0.0f;

	if (byOffset){
		if (halign == AgkHAlign::center)
			hf = 0.5f;
		else if(halign == AgkHAlign::right)
			hf = 1.0f;

		if (valign == AgkVAlign::center)
			vf = 0.5f;
		else if (valign == AgkVAlign::bottom)
			vf = 1.0f;
	}
	agk::SetSpriteOffset(id, hf*getWidth(), vf*getHeight());
}
void Sprite::setOffset(const glm::vec2& offset) {
	byOffset = true;
	agk::SetSpriteOffset(id, offset.x, offset.y);
}
void Sprite::setOffsetCenter() {
	setOffset(getSize() / 2.0f);
}

void Sprite::addSpriteAnimationFrame(AgkImage* img) {
	agk::AddSpriteAnimationFrame(id, img->getID());
}
void Sprite::playSprite(float fps, int iLoop, int iFromFrame, int iToFrame) {
	agk::PlaySprite(id, fps, iLoop, iFromFrame, iToFrame);
}



