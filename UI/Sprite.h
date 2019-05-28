#pragma once
#include "agk.h"
#include "AgkSprite.h"
#include "AgkImage.h"


#define DEFAULT_SPRITE_DEPTH    8
#define DEFAULT_TEXT_DEPTH      7

#define UI_BUTTON_SPRITE_DEPTH	5
#define UI_BUTTON_TEXT_DEPTH	4
#define UI_WINDOW_DEPTH			6
#define UI_BG_DEPTH				25

enum class AgkSpriteShape
{
	no_shape = 0,
	circle = 1,
	box = 2,
	polygon = 3
};



/***********************************************/
class Sprite : public AgkSprite
/***********************************************/
{
public:
	Sprite();
	Sprite(AgkImage* img, const glm::vec2& pos = glm::vec2(0.0f), const glm::vec2& size = glm::vec2(1.0f), AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	Sprite(const glm::vec3& color, const glm::vec2& pos = glm::vec2(0.0f), const glm::vec2& size = glm::vec2(1.0f), AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	Sprite(const glm::vec4& color, const glm::vec2& pos = glm::vec2(0.0f), const glm::vec2& size = glm::vec2(1.0f), AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	
public:
	using AgkSprite::setColor;
	using AgkSprite::setPosition;
	using AgkSprite::hitTest;
	using AgkSprite::setSize;
	using AgkSprite::setScale;
	
	void setImage(AgkImage* img);
	void setShape(AgkSpriteShape shape);
	float getWidth();
	float getHeight();

	void fixToScreen();
	virtual void deleteSprite();

	/* COLOR */
	void setColor(UINT r, UINT g, UINT b, UINT a = 255);
	void setColorAlpha(float a);
	float getColorRed();
	float getColorGreen();
	float getColorBlue();

	/* POSITION */
	virtual void setPosition(float x, float y);
	float getX();
	float getY();
	virtual void setX(float x);
	virtual void setY(float y);

	/* MOVE */
	//void move(float x, float y);

	/* SIZE */
	float getSizeX();
	float getSizeY();
	virtual void setSize(float sx, float sy);

	/* SCALE */
	float getScaleX();
	float getScaleY();
	virtual void setScale(float sx, float sy);

	/* ROTATION */
	virtual void setRotation(float angle);
	float getRotation();

	void addSpriteAnimationFrame(AgkImage* img);
	void playSprite(float fps = 10, int iLoop = 1, int iFromFrame = -1, int iToFrame = -1);

	bool hitTest(float x, float y);
	
	virtual void setState(bool state);

	virtual void setDepth(int depth);

	void setAlignment(AgkHAlign halign, AgkVAlign valign);

	void setOffset(const glm::vec2& offset);
	void setOffset(AgkHAlign halign, AgkVAlign valign);
	void setOffsetCenter();

protected:
	bool byOffset = false;

};
