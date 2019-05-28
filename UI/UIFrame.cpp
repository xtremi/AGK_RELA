#include "UIFrame.h"

glm::vec2 UIFrame::getPosition() {
	return pos;
}
void UIFrame::move(const glm::vec2& dpos) {
	setPosition(getPosition() + dpos);
}

void UIFrame::setScale(const glm::vec2& sc) {
	SpriteMapIterator sit;
	for (sit = sprites.begin(); sit != sprites.end(); sit++)
		sit->second->setScale(sc);

	FrameMapIterator fit;
	for (fit = frames.begin(); fit != frames.end(); fit++)
		fit->second->setScale(sc);
}

void UIFrame::setScale(float sc) {
	setScale(glm::vec2(sc));
}
void UIFrame::setLocalPosition(const glm::vec2& _lpos) {
	if (active) {

		glm::vec2 dpos = _lpos - localPos;
		localPos = _lpos;

		SpriteMapIterator sit;
		for (sit = sprites.begin(); sit != sprites.end(); sit++)
			sit->second->move(dpos);

		FrameMapIterator fit;
		for (fit = frames.begin(); fit != frames.end(); fit++)
			fit->second->move(dpos);
	}
}
void UIFrame::setPosition(const glm::vec2& _pos) {
	if(active){

		glm::vec2 dpos = _pos - pos;
		pos = _pos;
		
		/*glm::vec2 newPos = pos + _pos;
		glm::vec2 dpos = newPos - dpos;*/

		SpriteMapIterator sit;
		for (sit = sprites.begin(); sit != sprites.end(); sit++)
			sit->second->move(dpos);

		FrameMapIterator fit;
		for (fit = frames.begin(); fit != frames.end(); fit++)
			fit->second->move(dpos);
	}
}


void UIFrame::addSprite(AgkSprite* s, const std::string& id, const glm::vec2& _pos, bool relative){
	if (isNotInMap<AgkSprite>(id, &sprites)){
		sprites[id] = s;
		relative ? s->setPosition(_pos + pos) : s->setPosition(_pos);
		s->postProcess();
	}
	else {/*log error: */}
}
void UIFrame::addButton(UIButton* s, const std::string& id, const glm::vec2& _pos, bool relative) {
	if (isNotInMap<UIButton>(id, &buttons)) {
		buttons[id] = s;
		addSprite(dynamic_cast<AgkSprite*>(s), id, _pos, relative);
	}
	else {/*log error: */ }
}
void UIFrame::addFrame(UIFrame* s, const std::string& id, const glm::vec2& _pos, bool relative) {
	if (isNotInMap<UIFrame>(id, &frames)) {
		frames[id] = s;
		relative ? s->setPosition(_pos + pos) : s->setPosition(_pos);
	}
	else {/*log error: */ }
}

void UIFrame::addSpriteAnimation(SpriteAnimation* s, const std::string& id){
	if (isNotInMap<SpriteAnimation>(id, &animations)) {
		animations[id] = s;
	}
	else {/*log error: */ }
}

bool UIFrame::isActive() {
	return active;
}

void UIFrame::enable() {
	setActiveState(true);
}
void UIFrame::disable() {
	setActiveState(false);
}
void UIFrame::hide() {
	setState(false);
}
void UIFrame::show() {
	setState(true);
}
void UIFrame::setState(bool state) {
	SpriteMapIterator sit;
	for (sit = sprites.begin(); sit != sprites.end(); sit++)
		sit->second->setState(state);

	ButtonMapIterator bit;
	for (bit = buttons.begin(); bit != buttons.end(); bit++)
		bit->second->setActiveState(state);

	FrameMapIterator fit;
	for (fit = frames.begin(); fit != frames.end(); fit++)
		fit->second->setState(state);

	visible = state;
}

void UIFrame::setActiveState(bool state) {
	ButtonMapIterator bit;
	for (bit = buttons.begin(); bit != buttons.end(); bit++)
		bit->second->setActiveState(state);

	FrameMapIterator fit;
	for (fit = frames.begin(); fit != frames.end(); fit++)
		fit->second->setActiveState(state);

	active = state;
}
bool UIFrame::isVisible() {
	return visible;
}

AgkSprite* UIFrame::getSprite(const std::string& id) {
	if (isInMap<AgkSprite>(id, &sprites))
		return sprites[id];
	return NULL;
}
UIButton* UIFrame::getButton(const std::string& id) {
	if (isInMap<UIButton>(id, &buttons))
		return buttons[id];
	return NULL;
}
UIFrame* UIFrame::getFrame(const std::string& id) {
	if (isInMap<UIFrame>(id, &frames))
		return frames[id];
	return NULL;
}

bool UIFrame::getButtonState(const std::string& buttonID) {
	if (isInMap<UIButton>(buttonID, &buttons))
		return buttons[buttonID]->getButtonState();
	return false;
}

void UIFrame::processButtons(bool pressed, bool released, bool pstate) {
	if(active){
		ButtonMapIterator bit;
		for (bit = buttons.begin(); bit != buttons.end(); bit++)
			bit->second->processButtonState(pressed, released, pstate);

		FrameMapIterator fit;
		for (fit = frames.begin(); fit != frames.end(); fit++)
			fit->second->processButtons(pressed, released, pstate);
	}
}
void UIFrame::processAnimations() {
	if (active) {
		AnimationMapIterator ait;
		for (ait = animations.begin(); ait != animations.end(); ait++)
			ait->second->processAnimation();

		FrameMapIterator fit;
		for (fit = frames.begin(); fit != frames.end(); fit++)
			fit->second->processAnimations();
	}
}


void UIFrame::realignSprites() {
	SpriteMapIterator sit;
	for (sit = sprites.begin(); sit != sprites.end(); sit++)
		sit->second->postProcess();

	FrameMapIterator fit;
	for (fit = frames.begin(); fit != frames.end(); fit++)
		fit->second->realignSprites();
}

void UIFrame::postProcess() {
	SpriteMapIterator sit;
	for (sit = sprites.begin(); sit != sprites.end(); sit++)
		sit->second->postProcess();

	FrameMapIterator fit;
	for (fit = frames.begin(); fit != frames.end(); fit++)
		fit->second->postProcess();
}