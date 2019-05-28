#pragma once
#include "UIButton.h"
#include "SpriteAndText.h"
#include "SpriteAnimation.h"
#include <map>

class UIFrame;

typedef std::map<std::string, AgkSprite*> SpriteMap;
typedef std::map<std::string, UIButton*> ButtonMap;
typedef std::map<std::string, UIFrame*> FrameMap;
typedef std::map<std::string, SpriteAnimation*> AnimationMap;

typedef std::map<std::string, AgkSprite*>::iterator SpriteMapIterator;
typedef std::map<std::string, UIButton*>::iterator ButtonMapIterator;
typedef std::map<std::string, UIFrame*>::iterator FrameMapIterator;
typedef std::map<std::string, SpriteAnimation*>::iterator AnimationMapIterator;

template<class T>
bool isInMap(const std::string& id, std::map<std::string, T*>* m) {
	if (m->find(id) != m->end())
		return true;
	return false;
}
template<class T>
bool isNotInMap(const std::string& id, std::map<std::string, T*>* m) {
	return !isInMap(id, m);
}



class UIFrame
{
public:
	UIFrame(const glm::vec2& _pos =  glm::vec2(0.f)){
		pos = _pos;
	}
	~UIFrame() {};

	AgkSprite* getSprite(const std::string& id);
	UIButton* getButton(const std::string& id);
	UIFrame* getFrame(const std::string& id);

	void addSprite(AgkSprite* s, const std::string& id, const glm::vec2& _pos, bool relative = true);
	void addButton(UIButton* s, const std::string& id, const glm::vec2& _pos, bool relative = true);
	void addFrame(UIFrame* s, const std::string& id, const glm::vec2& _pos, bool relative = true);
	void addSpriteAnimation(SpriteAnimation* s, const std::string& id);

	virtual void setPosition(const glm::vec2& _pos);
	void setLocalPosition(const glm::vec2& _lpos);
	glm::vec2 getPosition();
	void move(const glm::vec2& dpos);
	void setScale(float sc);
	void setScale(const glm::vec2& sc);

	void hide();
	void show();
	void enable();
	void disable();
	virtual void setState(bool state);
	virtual void setActiveState(bool state);
	bool isVisible();
	bool isActive();

	virtual bool getButtonState(const std::string& buttonID);
	virtual void processButtons(bool pressed, bool released, bool pstate);
	virtual void processAnimations();

	void realignSprites();
	virtual void postProcess();

protected:
	SpriteMap sprites;
	ButtonMap buttons;
	FrameMap frames;
	AnimationMap animations;

	glm::vec2 pos;
	glm::vec2 localPos = glm::vec2(0.0f);

	bool active = true;
	bool visible = true;


};

