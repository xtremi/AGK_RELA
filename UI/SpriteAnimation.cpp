#include "SpriteAnimation.h"

void SpriteAnimation::processAnimation()
{
	if (!animationON) return;

	animation_state* s0 = &animStates[currentFromStateIndex];
	animation_state* s1 = &animStates[currentToStateIndex];

	float t = currentTime / s1->time;
	
	glm::vec2	p;
	if(s1->moveType == movement_type::linear){		
		p.x = (s1->pos.x - s0->pos.x);
		p.y = (s1->pos.y - s0->pos.y);
		processInterpolation(p, t, s1->iplPos);

		p += s0->pos;
	}
	else if (s1->moveType == movement_type::bezier_2) {
		std::vector<float> bz;
		float ti = t;		
		processInterpolation(ti, t, s1->iplPos);
		
		bz.push_back(std::powf((1 - ti), 3.0f));
		bz.push_back(3.0f*ti*std::powf(1.0f - ti, 2.0f));
		bz.push_back(3.0f*(1.0f - ti)*std::powf(ti, 2.0f));
		bz.push_back(std::powf(ti, 3.0f));

		p = bz[0] * s0->pos + bz[1] * s1->bezierWpoints[0] + bz[2] * s1->bezierWpoints[1] + bz[3] * s1->pos;
	}

	
	float r = (s1->rotation - s0->rotation);
	float s = (s1->scale - s0->scale);	
	processInterpolation(r, t, s1->iplRot);
	processInterpolation(s, t, s1->iplSc);
	
	
	r += s0->rotation;
	s += s0->scale;

	anim_setPos(p);
	anim_setRot(r);
	anim_setScale(s);

	postProcessAnim();

	currentTime += ANIMATION_DELTA_TIME;

	if (currentTime >= s1->time) {
		moveToState(currentToStateIndex); //make sure it arrived to the right position
		
		onAnimationEnd();

		currentTime = 0.0;		
		currentFromStateIndex++;
		currentToStateIndex++;		

		if (animateAll && (currentToStateIndex < animStates.size())) {
			s0 = s1;
			s1 = &animStates[currentToStateIndex];
		}
		else {
			pauseAnimation();
			if (stateExist("temp-state"))
				removeTempState();
		}
	}
}

void SpriteAnimation::processInterpolation(glm::vec2& v, float t, interpolation_type it) {
	switch (it)
	{	
	case interpolation_type::cubic:
		v *= t;
	case interpolation_type::quadratic:
		v *= t;	
	case interpolation_type::linear:
		v *= t;
		break;
	case interpolation_type::square_root:
		v *= std::sqrtf(t);
		break;
	case interpolation_type::bounce_ease_out:
		v *= bounceEaseOut(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::bounce_ease_in:
		v *= bounceEaseIn(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::bounce_ease_in_out:
		v *= bouncEaseInOut(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::none:
	default:
		break;
	}
}
void SpriteAnimation::processInterpolation(float& v, float t, interpolation_type it) {
	switch (it)
	{
	case interpolation_type::cubic:
		v *= t;
	case interpolation_type::quadratic:
		v *= t;
	case interpolation_type::linear:
		v *= t;
		break;
	case interpolation_type::square_root:
		v *= std::sqrtf(t);
		break;
	case interpolation_type::bounce_ease_out:
		v *= bounceEaseOut(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::bounce_ease_in:
		v *= bounceEaseIn(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::bounce_ease_in_out:
		v *= bouncEaseInOut(t, 0.0f, 1.0f, 1.0f);
		break;
	case interpolation_type::none:
	default:
		break;
	}
}


void SpriteAnimation::addState(const std::string& id, const animation_state& as) {
	if (stateExist(id))
		animStates[animStateMap[id]] = as;
	else{
		animStates.push_back(as);
		animStateMap[id] = animStates.size() - 1;
	}
}
void SpriteAnimation::setDefaultState(const animation_state& as) {
	addState("default", as);
	goToDefault();
}

void SpriteAnimation::animateFromTo(const std::string& idFrom, const std::string& idTo) {
	if (!stateExist(idFrom) || !stateExist(idTo))
		return;

	currentToState = idTo;

	animationON = true;
	animateAll = false;
	currentTime = 0.0f;	
	moveToState(idFrom);
	currentFromStateIndex	= animStateMap[idFrom];
	currentToStateIndex		= animStateMap[idTo];
}
void SpriteAnimation::animateTo(const std::string& id){
	currentToState = id;
	
	animationON = true;
	animateAll = false;
	currentToStateIndex = animStateMap[id];
	currentTime = 0.0f;
	createTempState();
	currentFromStateIndex = animStateMap["temp-state"];
}
void SpriteAnimation::animateSequence() {
	animationON = true;
	animateAll = true;
	
	currentTime = 0.0f;
	goToDefault();
	if (animStates.size() > 1){
		currentFromStateIndex = 0;
		currentToStateIndex = 1;
	}
	if (stateExist("temp-state"))
		removeTempState();
}
void SpriteAnimation::goToDefault() {
	currentToState = "default";
	moveToState(&animStates[0]);
}
void SpriteAnimation::createTempState() {
	addState("temp-state", animation_state(0.0, anim_getPos(), anim_getRot(), anim_getScale()));
}
void SpriteAnimation::removeTempState() {
	animStates.erase(animStates.begin() + animStateMap["temp-state"]);
	animStateMap.erase("temp-state");
}

void SpriteAnimation::pauseAnimation() {
	animationON = false;
}
void SpriteAnimation::continueAnimation() {
	animationON = true;
}




float bounceEaseIn(float t, float b, float c, float d) {
	return c - bounceEaseOut(d - t, 0, c, d) + b;
}
float bouncEaseInOut(float t, float b, float c, float d) {
	if (t < d / 2) return bounceEaseIn(t * 2, 0, c, d) * .5f + b;
	else return bounceEaseOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
}
float bounceEaseOut(float t, float b, float c, float d) {
	if ((t /= d) < (1 / 2.75f)) {
		return c * (7.5625f*t*t) + b;
	}
	else if (t < (2 / 2.75f)) {
		float postFix = t -= (1.5f / 2.75f);
		return c * (7.5625f*(postFix)*t + .75f) + b;
	}
	else if (t < (2.5 / 2.75)) {
		float postFix = t -= (2.25f / 2.75f);
		return c * (7.5625f*(postFix)*t + .9375f) + b;
	}
	else {
		float postFix = t -= (2.625f / 2.75f);
		return c * (7.5625f*(postFix)*t + .984375f) + b;
	}
}

/*
void SpriteAnimation::processAnimation()
{
	if (animationON) {

		if (maxTime > 0.0 && currentTime > maxTime) {
			currentTime = 0.0f;
			stopAnimation();
		}
		currentTime += ANIMATION_DELTA_TIME;

		if (moveON) {

			float d = glm::distance(currentPosition(), toPos);
			if (d < std::abs(1.1f*speed)) {
				stopAnimation();
				setCurrentPosition(toPos);
			}
			else {
				glm::vec2 dir = glm::normalize(this->toPos - currentPosition());
				processMoveStep(dir * speed);
			}
		}
		if (rotateON)
			processRotate();
		if (scalingON)
			processScaling();
		if (customAnimationON)
			processCustomAnimation();
	}
}
*/