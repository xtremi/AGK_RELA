#pragma once
#include "AgkSprite.h"
#include "AgkFont.h"
#include "glm/glm.hpp"
#include <string>

/***********************************************/
class TextSprite : public AgkSprite
/***********************************************/
{
public:
	TextSprite(
		char* txt, const glm::vec3& color = glm::vec3(0.0f), 
		const glm::vec2& pos = glm::vec2(0.0f), float textSize = 1.0f, 
		AgkHAlign halign = AgkHAlign::left, AgkVAlign valign = AgkVAlign::top);

public:
	using AgkSprite::setColor;
	using AgkSprite::setPosition;
	using AgkSprite::hitTest;
	using AgkSprite::setSize;
	using AgkSprite::setScale;

	void setFont(AgkFont* font);
	void setBold(bool state);
	void setTextSize(float s);
	void setTextSpacing(float s);
	void setText(char* txt);
	std::string getText();

	void fixToScreen();
	void deleteSprite();
	

	/* COLOR */
	void setColor(UINT r, UINT g, UINT b, UINT a);
	float getColorRed();
	float getColorGreen();
	float getColorBlue();


	/* POSITION */
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

	/* ROTATION*/
	void setRotation(float angle);
	float getRotation();


	bool hitTest(float x, float y);

	void setState(bool state);

	void setDepth(int depth);

	void setAlignment(AgkHAlign halign, AgkVAlign valign);

	void realign();
	void postProcess();
	void setVertOffset(float voffs);

private:
	glm::vec2 pos				= glm::vec2(0.0f);
	float currentAngle			= 0.0f;
	float vertOffset			= 0.0f;
	glm::vec2 currentScale		= glm::vec2(1.0f);
	glm::vec2 rotOffset			= glm::vec2(0.f);
	/*glm::vec2 scaleOffset		= glm::vec2(0.f);*/
	float initialTextHeight		= 1.0f;
	float assignedTextSpacing	= 1.0f;

	void setVertOffset();
	
	AgkVAlign vertAlignment;
	
	

};
