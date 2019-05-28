#include "UIButton.h"

UIButton::UIButton(UIButtonType _type) {

	type = _type;
}


void UIButton::processButtonState(bool pressed, bool released, bool cursState)
{
	if (!isActive()) 
		return;

	this->state			= false;
	
	bool overButton = cursorOverButton();

	if(pressed && overButton){
			
		switch (this->type)
		{
		case UIButtonType::press:
			this->state		= true;
			this->isPressed = true;
			break;
		case UIButtonType::press_and_hold:
		case UIButtonType::press_and_release:
			this->isPressed = true;
		default:
			break;
		}
	}
	else if (released) {
		
		if(overButton){
			switch (this->type) {
			case UIButtonType::press_and_release:
				if (this->isPressed) this->state = true;
				this->isPressed = false;
				break;
			case UIButtonType::release:
				this->state = true;
				this->isPressed = true;
				break;
			default:
				this->isPressed = false;
				break;
			}
		}
		
	}

	else if (cursState && overButton) {

		switch (this->type)
		{
		case UIButtonType::press_and_hold:
			if (this->isPressed) this->state = true;
			break;
		case UIButtonType::hold:
			this->state = true;
			this->isPressed = true;
			break;
		default:
			break;
		}
	}
	else
		this->isPressed = false;

	
	processDisplayState();
}


void UIButton::processDisplayState()
{
	if (this->isPressed && 
		this->displayState == UIButtonDisplayState::main) 
	{
		setSecondaryState();
		this->displayState = UIButtonDisplayState::secondary;
	}
	else if (
		!this->isPressed && 
		this->displayState == UIButtonDisplayState::secondary)
	{
		setMainState();
		this->displayState = UIButtonDisplayState::main;
	}

	if (!this->isActive() 
		&& this->displayState != UIButtonDisplayState::inactive) 
	{
		setInactiveState();
		this->displayState = UIButtonDisplayState::inactive;
	}
}

/****************************************************/
//void UIButton::setMainState()
/****************************************************/
/*{
	this->displayState = UIButtonDisplayState::main;

	switch (this->pressedMode)
	{
	case UIButtonPressedMode::change_color:
		this->sprite->setColor(mainColor);
		break;
	case UIButtonPressedMode::change_image:
		this->sprite->setImage(mainImage);
		this->sprite->setSize(mainImageSize);
		break;
	case UIButtonPressedMode::change_size:
		this->sprite->setScale(1.0f);
		break;
	case UIButtonPressedMode::none:
	default:
		break;
	}
}*/

/****************************************************/
//void UIButton::setSecondaryState()
/****************************************************/
/*{
	this->displayState = UIButtonDisplayState::secondary;
	glm::vec2 s;
	switch (this->pressedMode)
	{
	case UIButtonPressedMode::change_color:
		this->sprite->setColor(secondColor);
		break;
	case UIButtonPressedMode::change_image:
		this->sprite->setImage(secondImage);
		this->sprite->setSize(secondImageSize);
		break;
	case UIButtonPressedMode::change_size:
		this->sprite->setScale(secondSizeFactor);
		break;
	case UIButtonPressedMode::none:
	default:
		break;
	}
}
*/

/*
void UIButton::setSizeModifyWhenPressed(float sizeFactor)
{
	this->secondSizeFactor = sizeFactor;
	this->pressedMode = UIButtonPressedMode::change_size;
}
void UIButton::setImageWhenPressed(AgkImage* img, const glm::vec2& size)
{
	this->secondImage = img;
	this->pressedMode = UIButtonPressedMode::change_image;
	this->secondImageSize = size;
}
void UIButton::setImageWhenPressed(AgkImage* img, float sizeRatio)
{
	this->secondImage = img;
	this->pressedMode = UIButtonPressedMode::change_image;
	this->secondImageSize = this->mainImageSize * sizeRatio;
}
void UIButton::setColorWhenPressed(const glm::vec4& color)
{
	this->secondColor = color;
	this->pressedMode = UIButtonPressedMode::change_color;
}


*/


/*AnimatedTextAndSprite::AnimatedTextAndSprite(AgkImage* img, const glm::vec2& size)
	: SpriteAndText(glm::vec2(0.0f), size, img)
{
}

AnimatedTextAndSprite::AnimatedTextAndSprite(const glm::vec3& color, const glm::vec2& size, char* txt, const glm::vec3& txtcolor, float txtsize)
	: SpriteAndText(glm::vec2(0.0f), size, color, txtcolor, txt, txtsize)
{
}

void AnimatedTextAndSprite::init() {
	setPosition(fromPos);
}
glm::vec2 AnimatedTextAndSprite::currentPosition() {
	return sprite->getPos();
}
void AnimatedTextAndSprite::processMoveStep(const glm::vec2& step) {
	move(step);
}
void AnimatedTextAndSprite::processRotate() {
	sprite->rotate(rotationSpeed);
	text->rotate(rotationSpeed);
}
void AnimatedTextAndSprite::processScaling() {
	sprite->scale(scaleSpeed);
	text->scale(scaleSpeed);
}*/


/*
AnimatedUIButton::AnimatedUIButton(
	const glm::vec2& size, AgkImage* img,
	const glm::vec3& textColor, char* text, float textSize,
	UIButtonType type,	AgkSpriteShape shape, AgkHAlign hal, AgkVAlign val
)
	: UIButton(glm::vec2(0.0f), size, img, textColor, text, textSize, type, shape, hal, val)
{}

AnimatedUIButton::AnimatedUIButton(
	const glm::vec2& size, AgkImage* img,
	UIButtonType type, AgkSpriteShape shape, AgkHAlign hal, AgkVAlign val
)
	: UIButton(glm::vec2(0.0f), size, img, type, shape, hal, val)
{}


glm::vec2 AnimatedUIButton::currentPosition() {
	return sprite->getPos();
}
void AnimatedUIButton::setCurrentPosition(const glm::vec2& pos) {
	sprite->setPosition(pos);
	if(text) text->setPosition(pos);
}
void AnimatedUIButton::processMoveStep(const glm::vec2& step) {
	move(step);
}
void AnimatedUIButton::processRotate() {
	sprite->rotate(rotationSpeed);
	if(text) text->rotate(rotationSpeed);
}
void AnimatedUIButton::processScaling() {
	sprite->scale(scaleSpeed);
	if(text) text->scale(scaleSpeed);
}
void AnimatedUIButton::setDisplayState(bool state) {
	if (state) {
		sprite->show();
		if (text) sprite->show();
	}
	else {
		sprite->hide();
		if (text) sprite->hide();
	}
}
*/