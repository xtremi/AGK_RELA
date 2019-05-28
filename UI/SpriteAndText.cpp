#include "SpriteAndText.h"


/****************************************************/
SpriteAndText::SpriteAndText(
	AgkImage* img, char* txt, const glm::vec3& textCol,
	const glm::vec2& size, float textSize, const glm::vec2& pos,
	AgkHAlign halign, AgkVAlign valign)
/****************************************************/
{
	sprite = new Sprite(img, pos, size, halign, valign);
	text = new TextSprite(txt, textCol, pos, textSize, halign, valign);
}

/****************************************************/
SpriteAndText::SpriteAndText(
	const glm::vec3& col, char* txt, const glm::vec3& textCol,
	const glm::vec2& size, float textSize, const glm::vec2& pos,
	AgkHAlign halign, AgkVAlign valign)
/****************************************************/
{
	sprite = new Sprite(col, pos, size, halign, valign);
	text = new TextSprite(txt, textCol, pos, textSize, halign, valign);
}


void SpriteAndText::setFont(AgkFont* font){
	text->setFont(font);
}
void SpriteAndText::setTextSize(float s) {
	text->setTextSize(s);
}
void SpriteAndText::setText(char* txt) {
	text->setText(txt);
}
void SpriteAndText::setImage(AgkImage* img) {
	sprite->setImage(img);
}
void SpriteAndText::setShape(AgkSpriteShape shape) {
	sprite->setShape(shape);
}

void SpriteAndText::fixToScreen()
{
	sprite->fixToScreen();
	text->fixToScreen();
	isFixedToScreen = true;
}
void SpriteAndText::deleteSprite() {
	deleteSprites();
}
void SpriteAndText::deleteSprites()
{
	sprite->deleteSprite();
	text->deleteSprite();
}


/* COLOR */
void SpriteAndText::setColor(UINT r, UINT g, UINT b, UINT a)
{
	this->sprite->setColor(r,g,b,a);
}
void SpriteAndText::setColorAlpha(float a) {
	this->sprite->setColorAlpha(a);
}
float SpriteAndText::getColorRed(){
	return this->sprite->getColorRed();
}
float SpriteAndText::getColorGreen() {
	return this->sprite->getColorGreen();
}
float SpriteAndText::getColorBlue() {
	return this->sprite->getColorBlue();
}
void SpriteAndText::setTextColor(UINT r, UINT g, UINT b, UINT a) {
	this->text->setColor(r, g, b, a);
}
float SpriteAndText::getTextColorRed() {
	return this->text->getColorRed();
}
float SpriteAndText::getTextColorGreen() {
	return this->text->getColorGreen();
}
float SpriteAndText::getTextColorBlue() {
	return this->text->getColorBlue();
}


/* POSITION */
void SpriteAndText::setPosition(float x, float y) {
	sprite->setPosition(x, y);
	text->setPosition(x, y);
}
float SpriteAndText::getX() {
	return sprite->getX();
}
float SpriteAndText::getY() {
	return sprite->getY();
}
void SpriteAndText::setX(float x) {
	sprite->setX(x);
	text->setX(x);
}
void SpriteAndText::setY(float y) {
	sprite->setY(y);
	text->setY(y);
}

/* SIZE */
float SpriteAndText::getSizeX(){
	return sprite->getSizeX();
}
float SpriteAndText::getSizeY() {
	return sprite->getSizeY();
}
void SpriteAndText::setSize(float sx, float sy) {
	sprite->setSize(sx, sy);
}

/* SCALE */
float SpriteAndText::getScaleX() {
	return sprite->getScaleX();
}
float SpriteAndText::getScaleY() {
	return sprite->getScaleY();
}
void SpriteAndText::setScale(float sx, float sy) {
	sprite->setScale(sx, sy);
	text->setScale(sx, sy);
}

/* ROTATION */
void SpriteAndText::setRotation(float angle) {
	sprite->setRotation(angle);
	text->setRotation(angle);
}
float SpriteAndText::getRotation() {
	return sprite->getRotation();
}



bool SpriteAndText::hitTest(float x, float y)
{
	return this->sprite->hitTest(x, y);
}	
void SpriteAndText::setState(bool state){
	this->sprite->setScale(state);
	this->text->setScale(state);
}

void SpriteAndText::setDepth(int depth) {
	this->sprite->setDepth(depth);
	setTextDepth(depth - 1);
}
void SpriteAndText::setTextDepth(int depth) {
	this->text->setDepth(depth);
}

void SpriteAndText::setAlignment(AgkHAlign halign, AgkVAlign valign) {
	sprite->setAlignment(halign, valign);
	text->setAlignment(halign, valign);
}

void SpriteAndText::realign(){
	text->realign();
}
void SpriteAndText::postProcess() {
	realign();
}