#pragma once
//#include "agk.h"

enum class UIButtonType
{
	release,
	press_and_release,
	press_and_hold,
	press,
	hold
};

/*enum class UIButtonPressedMode
{
	change_size,
	change_image,
	change_color,
	none
};*/

enum class UIButtonDisplayState
{
	main,
	secondary,
	inactive
};


class UIButton
{
public:
	UIButton(UIButtonType _type = UIButtonType::press_and_release);


	void processButtonState(bool pressed, bool released, bool state);
	
	UIButtonType getType() {
		return type;
	}
	bool getButtonState() {
		return state;
	}
	void activate() {
		setActiveState(true);
	}
	void deactivate() {
		setActiveState(false);
	}
	bool isActive() {
		return active;
	}
	void setActiveState(bool _active) {
		active = _active;
		if (!active)
			setInactiveState();
		else
			setMainState();
	}

	UIButtonDisplayState getButtonDisplayState() {
		return displayState;
	}

private:
	bool active 	= true;
	bool isPressed  = false;	
	bool state		= false;

	void processDisplayState();
	UIButtonDisplayState	displayState = UIButtonDisplayState::main;

	virtual void setMainState() = 0;
	virtual void setSecondaryState() = 0;
	virtual void setInactiveState() = 0;
	virtual bool cursorOverButton() = 0;

	UIButtonType type = UIButtonType::press_and_release;
};


/*
AgkImage* mainImage		= NULL;
	AgkImage* secondImage	= NULL;
	AgkImage* inactiveImage = NULL;

	glm::vec2 mainImageSize;
	glm::vec2 secondImageSize;

	glm::vec4 mainColor;
	glm::vec4 secondColor;
	glm::vec4 inactiveColor;

	float secondSizeFactor = 1.0f;

void setSize(const glm::vec2& size) {
	sprite->setSize(size);
	mainImageSize = size;
}
void setImagePressedSize(const glm::vec2& size) {
	secondImageSize = size;
}
void setImageInactive(AgkImage* img) {
	inactiveImage = img;
}

void setSizeModifyWhenPressed(float sizeFactor);
void setImageWhenPressed(AgkImage* img, const glm::vec2& size);
void setImageWhenPressed(AgkImage* img, float sizeRatio);
void setColorWhenPressed(const glm::vec4& color);
*/



/***********************************************/
//class AnimatedUIButton : public UIButton, public SpriteAnimation
/***********************************************/
/*{
public:
	AnimatedUIButton(
		const glm::vec2& size, AgkImage* image,
		const glm::vec3& textColor, char* text = NULL, float textSize = 0.0f,
		UIButtonType type = UIButtonType::press_and_release,
		AgkSpriteShape shape = AgkSpriteShape::box, AgkHAlign hal = AgkHAlign::center, AgkVAlign val = AgkVAlign::center
	);

	AnimatedUIButton(
		const glm::vec2& size, AgkImage* image,
		UIButtonType type = UIButtonType::press_and_release,
		AgkSpriteShape shape = AgkSpriteShape::box, AgkHAlign hal = AgkHAlign::center, AgkVAlign val = AgkVAlign::center
	);

private:
	void processMoveStep(const glm::vec2& step);
	void processRotate();
	void processScaling();

	void setDisplayState(bool state);
	glm::vec2 currentPosition();
	void setCurrentPosition(const glm::vec2& pos);

};

*/