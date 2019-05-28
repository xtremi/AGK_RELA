#pragma once
#include "agk.h"
#include "glm/glm.hpp"


enum class AgkHAlign {
	left = 0,
	center = 1,
	right = 2
};

enum class AgkVAlign {
	top = 0,
	center = 1,
	bottom = 2
};

/***********************************************/
class AgkSprite
/***********************************************/
{
public:
	AgkSprite();
	~AgkSprite();

	UINT getID() { return id; }

	virtual void fixToScreen() = 0;
	virtual void deleteSprite() = 0;

	/* COLOR */
	glm::vec3 getColor();
	void setColor(const glm::vec3& color, float alpha = 1.0f);
	void setColor(const glm::vec4& color);
	void setColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
	virtual void setColor(UINT r, UINT g, UINT b, UINT a = 255) = 0;
	virtual float getColorRed() = 0;
	virtual float getColorGreen() = 0;
	virtual float getColorBlue() = 0;

	/* POSITION */
	glm::vec2 getPos();
	void setPosition(const glm::vec2& pos);
	virtual void setPosition(float x, float y);
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual void setX(float x) = 0;
	virtual void setY(float y) = 0;

	/* MOVE */
	void move(const glm::vec2& pos);
	virtual void move(float x, float y);
	void moveX(float x);
	void moveY(float y);

	/* SIZE */
	glm::vec2 getSize();
	void setSize(const glm::vec2& s);
	void setSize(float s);
	virtual float getSizeX() = 0;
	virtual float getSizeY() = 0;
	virtual void setSize(float sx, float sy) = 0;

	/* SCALE */
	glm::vec2 getScale();	
	void setScale(const glm::vec2& s);
	void setScale(float s);
	void scale(float s);
	virtual float getScaleX() = 0;
	virtual float getScaleY() = 0;
	virtual void setScale(float sx, float sy) = 0;

	/* ROTATION */
	void rotate(float angle);
	virtual void setRotation(float angle) {}
	virtual float getRotation() = 0;

			
	bool isHoovered();
	bool isHoovered_world();
	bool hitTest(const glm::vec2& pos);
	virtual bool hitTest(float x, float y) = 0;

	void hide() { setState(false); }
	void show() { setState(true); }
	virtual void setState(bool state) = 0;

	virtual void setDepth(int depth) = 0;

	virtual void setAlignment(AgkHAlign halign, AgkVAlign valign) = 0;

	virtual void postProcess(){}

protected:
	UINT id = -1;

	bool isFixedToScreen = false;
};
