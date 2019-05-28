#pragma once
#include "UIButton.h"
#include "SpriteAndText.h"

/**************************************************************************/
class UISpriteButton : public Sprite, public UIButton
/**************************************************************************/
{
public:
	UISpriteButton(AgkImage* img, const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release);
	UISpriteButton(const glm::vec3& color, const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release);
	UISpriteButton(const glm::vec4& color, const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release);
	
	void setWorldMode() {
		worldMode = true;
	}
	void setScreenMode() {
		worldMode = false;
	}

protected:
	bool worldMode = true;

	virtual void setMainState() = 0;
	virtual void setSecondaryState() = 0;
	virtual void setInactiveState() = 0;
	virtual bool cursorOverButton() {
		if (worldMode)
			return this->isHoovered_world();
		return this->isHoovered();
	}
};


/**************************************************************************/
class UITextButton : public TextSprite, public UIButton
/**************************************************************************/
{
public:
	UITextButton(char* txt, const glm::vec3& col, float size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release);

protected:
	virtual void setMainState() = 0;
	virtual void setSecondaryState() = 0;
	virtual void setInactiveState() = 0;
	virtual bool cursorOverButton() = 0;
};

/**************************************************************************/
class UISpriteAndTextButton : public SpriteAndText, public UIButton
/**************************************************************************/
{
public:
	UISpriteAndTextButton(
		AgkImage* img, char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center,
		UIButtonType _type = UIButtonType::press_and_release);

	UISpriteAndTextButton(
		const glm::vec3& col, char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center,
		UIButtonType _type = UIButtonType::press_and_release);

protected:
	virtual void setMainState() = 0;
	virtual void setSecondaryState() = 0;
	virtual void setInactiveState() = 0;
	virtual bool cursorOverButton() = 0;
};


class UISpriteButton_T1 : public UISpriteButton
{
public:
	UISpriteButton_T1(AgkImage* img, AgkImage* imgP, AgkImage* imgI, const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release) :
		UISpriteButton(img, size, pos, _type)
	{
		mainImage = img;
		secImage = imgP;
		inactiveImage = imgI;
	}

protected:
	void setMainState() {
		this->setImage(mainImage);
	}
	void setSecondaryState() {
		this->setImage(secImage);
	}
	void setInactiveState() {
		this->setImage(inactiveImage);
	}
	/*bool cursorOverButton() {
		return this->isHoovered();
	}*/

private:
	AgkImage* mainImage = NULL;
	AgkImage* secImage = NULL;
	AgkImage* inactiveImage = NULL;
};



class UISpriteButton_T2 : public UISpriteButton
{
public:
	UISpriteButton_T2(
		const glm::vec3& colN, const glm::vec3& colP, const glm::vec3& colI,
		const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release) :
		UISpriteButton(colN, size, pos, _type)
	{
		mainCol = glm::vec4(colN, 1.0f);
		secCol = glm::vec4(colP, 1.0f);
		inactiveCol= glm::vec4(colI, 1.0f);
	}
	
	UISpriteButton_T2(
		const glm::vec4& colN, const glm::vec4& colP, const glm::vec4& colI,
		const glm::vec2& size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release) :
		UISpriteButton(colN, size, pos, _type)
	{
		mainCol = colN;
		secCol = colP;
		inactiveCol = colI;
	}


protected:
	void setMainState() {
		this->setColor(mainCol);
	}
	void setSecondaryState() {
		this->setColor(secCol);
	}
	void setInactiveState() {
		this->setColor(inactiveCol);
	}
	/*bool cursorOverButton() {
		return this->isHoovered_world();
	}*/

private:
	glm::vec4 mainCol;
	glm::vec4 secCol;
	glm::vec4 inactiveCol;
};




class UITextButton_T1 : public UITextButton
{
public:
	UITextButton_T1(
		char* txtN, char* txtP, char* txtI,
		const glm::vec3& colN, const glm::vec3& colP, const glm::vec3& colI,
		float size, const glm::vec2& pos = glm::vec2(0), UIButtonType _type = UIButtonType::press_and_release) 
		: UITextButton(txtN, colN, size, pos, _type)
	{
		mainTxt		= txtN;
		secTxt		= txtP;
		inactiveTxt = txtI;

		mainCol		= colN;
		secCol		= colP;
		inactiveCol = colI;
	}

protected:
	void setMainState() {
		this->setText(mainTxt);
		this->setColor(mainCol);
	}
	void setSecondaryState() {
		this->setText(secTxt);
		this->setColor(secCol);
	}
	void setInactiveState() {
		this->setText(inactiveTxt);
		this->setColor(inactiveCol);
	}
	bool cursorOverButton() {
		return this->isHoovered();
	}

private:
	char* mainTxt = NULL;
	char* secTxt = NULL;
	char* inactiveTxt = NULL;

	glm::vec3 mainCol;
	glm::vec3 secCol;
	glm::vec3 inactiveCol;

};


class UISpriteAndTextButton_T1 : public UISpriteAndTextButton
{
public:
	UISpriteAndTextButton_T1(
		const glm::vec3& colN, const glm::vec3& colP, const glm::vec3& colI,
		char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center,
		UIButtonType _type = UIButtonType::press_and_release)
		: UISpriteAndTextButton(colN, txt, textCol, size, textSize, pos, halign, valign, _type)
	{
		mainCol = colN;
		secCol = colP;
		inactiveCol = colI;
	}

protected:
	void setMainState() {
		this->setColor(mainCol);
	}
	void setSecondaryState() {
		this->setColor(secCol);
	}
	void setInactiveState() {
		this->setColor(inactiveCol);
	}
	bool cursorOverButton() {
		return this->isHoovered();
	}

private:
	glm::vec3 mainCol;
	glm::vec3 secCol;
	glm::vec3 inactiveCol;

};

class UISpriteAndTextButton_T2 : public UISpriteAndTextButton
{
public:
	UISpriteAndTextButton_T2(
		AgkImage* imgN, AgkImage* imgP, AgkImage* imgI,
		char* txt, const glm::vec3& textCol = glm::vec3(0),
		const glm::vec2& size = glm::vec2(1.0f), float textSize = 1.0f, const glm::vec2& pos = glm::vec2(0),
		AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center,
		UIButtonType _type = UIButtonType::press_and_release)
		: UISpriteAndTextButton(imgN, txt, textCol, size, textSize, pos, halign, valign, _type)
	{
		mainImg = imgN;
		secImg = imgP;
		inactiveImg = imgI;
	}

protected:
	void setMainState() {
		this->setImage(mainImg);
	}
	void setSecondaryState() {
		this->setImage(secImg);
	}
	void setInactiveState() {
		this->setImage(inactiveImg);
	}
	bool cursorOverButton() {
		return this->isHoovered();
	}

private:
	AgkImage* mainImg = NULL;
	AgkImage* secImg = NULL;
	AgkImage* inactiveImg = NULL;

};