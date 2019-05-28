#pragma once
#include "Sprite.h"
#include "TextSprite.h"


/***********************************************/
class SpriteAndText : public AgkSprite
/***********************************************/
{
public:
	SpriteAndText(
		AgkImage* img, char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);

	SpriteAndText(
		const glm::vec3& col, char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);


public:
	using AgkSprite::setColor;
	using AgkSprite::setPosition;
	using AgkSprite::hitTest;
	using AgkSprite::setSize;
	using AgkSprite::setScale;

	void setFont(AgkFont* font);
	void setTextSize(float s);
	void setText(char* txt);
	void setImage(AgkImage* img);
	void setShape(AgkSpriteShape shape);
	//float getWidth();
	//float getHeight();
	
	void fixToScreen();
	void deleteSprite();
	void deleteSprites();


	/* COLOR */
	void setColor(UINT r, UINT g, UINT b, UINT a = 255);
	void setColorAlpha(float a);
	float getColorRed();
	float getColorGreen();
	float getColorBlue();
	
	void setTextColor(UINT r, UINT g, UINT b, UINT a = 255);
	float getTextColorRed();
	float getTextColorGreen();
	float getTextColorBlue();
	
	/* POSITION */
	void setPosition(float x, float y);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	/* SIZE */
	float getSizeX();
	float getSizeY();
	void setSize(float sx, float sy);

	/* SCALE */
	float getScaleX();
	float getScaleY();
	void setScale(float sx, float sy);

	/* ROTATION */
	void setRotation(float angle);
	float getRotation();

	bool hitTest(float x, float y);
	
	void setState(bool state);

	void setDepth(int depth);
	void setTextDepth(int depth);
	
	void setAlignment(AgkHAlign halign, AgkVAlign valign);

	void postProcess();
	void realign();

	
	Sprite* getSprite() {
		return sprite;
	}
	TextSprite* getText() {
		return text;
	}
	

protected:
	Sprite*		sprite	= NULL;
	TextSprite* text	= NULL;

	bool isFixedToScreen = false;
};