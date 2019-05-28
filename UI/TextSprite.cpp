#include "NumberTextSprite.h"


/****************************************************/
TextSprite::TextSprite(char* txt, const glm::vec3& color, const glm::vec2& pos, float textSize, AgkHAlign halign, AgkVAlign valign) : AgkSprite()
/****************************************************/
{
	id = agk::CreateText(txt);
	setColor(color);
	setTextSize(textSize);
	setAlignment(halign, valign);
	setPosition(pos);	
	realign();
}


void TextSprite::setFont(AgkFont* font) {
	agk::SetTextFont(id, font->getId());
}
void TextSprite::setBold(bool state) {
	agk::SetTextBold(id, state);
}
void TextSprite::setTextSize(float s) {
	agk::SetTextSize(id, s);
	initialTextHeight = agk::GetTextTotalHeight(id);
}
void TextSprite::setTextSpacing(float s) {
	agk::SetTextSpacing(id, s);
}
void TextSprite::setText(char* txt) {
	agk::SetTextString(id, txt);

}
std::string TextSprite::getText() {	
	return agk::GetTextString(id);
}
void TextSprite::fixToScreen() {
	agk::FixTextToScreen(id, 1);
	isFixedToScreen = true;
}
void TextSprite::deleteSprite() {
	agk::DeleteText(id);
}



/* COLOR */
void TextSprite::setColor(UINT r, UINT g, UINT b, UINT a) {
	agk::SetTextColor(id, r, g, b, a);
}
float TextSprite::TextSprite::getColorRed() {
	return 	((float)agk::GetTextColorRed(id))/255.0f;
}
float TextSprite::getColorGreen() {
	return 	((float)agk::GetTextColorGreen(id)) / 255.0f;
}
float TextSprite::getColorBlue() {
	return 	((float)agk::GetTextColorBlue(id)) / 255.0f;
}


/* POSITION */
float TextSprite::getX() {
	//return agk::GetTextX(id) - rotOffset.x;
	return pos.x;// +rotOffset.x;
}
float TextSprite::getY() {
	//return agk::GetTextY(id) - rotOffset.y/* - vertOffset*/;
	return pos.y;// +rotOffset.y;
}
void TextSprite::setX(float x) {
	pos.x = x;
	if(vertOffset < 1e-3)
		agk::SetTextX(id, x);
}
void TextSprite::setY(float y) {	
	pos.y = y;
	if (!vertOffset < 1e-3)		//WHAT?
		agk::SetTextY(id, y/* + vertOffset*/);
}

void TextSprite::postProcess() {
	realign();
}
void TextSprite::realign()
{
	float s = currentScale.x;

	//rotate:
	rotOffset.x = agk::Cos(currentAngle + 90.f) * -vertOffset;
	rotOffset.y = agk::Sin(currentAngle + 90.f) * -vertOffset;

	glm::vec2 finalPos = pos - rotOffset * s;

	agk::SetTextPosition(id, finalPos.x, finalPos.y);
}

/* SIZE */
float TextSprite::getSizeX() {
	return agk::GetTextTotalWidth(id);
}
float TextSprite::getSizeY() {
	return agk::GetTextTotalHeight(id);
}
void TextSprite::setSize(float sx, float sy) {
	agk::SetTextSize(id, sy);
}

/* SCALE */
float TextSprite::getScaleX() {
	return currentScale.x;
}
float TextSprite::getScaleY() {
	return currentScale.y;
}
void TextSprite::setScale(float sx, float sy) {
	agk::SetTextSize(id, initialTextHeight * sx);
	currentScale = glm::vec2(sx, sy);
}




/* ROTATION */
void TextSprite::setRotation(float angle) {	
	agk::SetTextAngle(id, angle);
	currentAngle = angle;
}
float TextSprite::getRotation() {
	return currentAngle;
}




bool TextSprite::hitTest(float x, float y)
{
	if (isFixedToScreen)
		return agk::GetTextHitTest(id, agk::ScreenToWorldX(x), agk::ScreenToWorldY(y));
	else
		return agk::GetTextHitTest(id, x, y);
}
void TextSprite::setState(bool state) {
	agk::SetTextVisible(id, state);
}
void TextSprite::setDepth(int depth) {
	agk::SetTextDepth(id, depth);
}

void TextSprite::setAlignment(AgkHAlign halign, AgkVAlign valign) {
	vertAlignment = valign;
	setVertOffset();
	agk::SetTextAlignment(id, (int)halign);
}


void TextSprite::setVertOffset(float voffs) {
	//moveY(-vertOffset);
	vertOffset = voffs;
	//moveY(vertOffset);
}

void TextSprite::setVertOffset()
{
	//moveY(-vertOffset);
	vertOffset = 0.0f;
	if (vertAlignment == AgkVAlign::center)
		vertOffset = -agk::GetTextTotalHeight(id) / 2.0f;
	else if (vertAlignment == AgkVAlign::bottom)
		vertOffset = -agk::GetTextTotalHeight(id);
	//moveY(vertOffset);
}













