#pragma once
#include "glm/glm.hpp"
#include <string>
#include <map>
#include <vector>
#include "agk.h"
#define ANIMATION_DELTA_TIME 0.01f


float bounceEaseOut(float t, float b, float c, float d);
float bounceEaseIn(float t, float b, float c, float d);
float bouncEaseInOut(float t, float b, float c, float d);

enum class interpolation_type {
	linear,
	quadratic,
	cubic,

	bounce_ease_out,
	bounce_ease_in,
	bounce_ease_in_out,

	square_root,
	none
};

enum class movement_type {
	linear,
	bezier_2,
	bezier_3,
	bezier_4
};

class SpriteAnimation
{
public:
	class animation_state {
		
	public:
		animation_state(){}
		animation_state(float t, const glm::vec2& p, float rot, float sc, movement_type mvt = movement_type::linear, interpolation_type itp = interpolation_type::linear, interpolation_type itr = interpolation_type::linear, interpolation_type its = interpolation_type::linear) {
			time	= t;
			pos		= p;
			rotation = rot;
			scale	= sc;
			iplPos	= itp;
			iplRot	= itr;
			iplSc	= its;
			moveType = mvt;
		}
		void addBezierWPoint(const glm::vec2& bwp) {
			bezierWpoints.push_back(bwp);
		}
	public:
		friend class SpriteAnimation;

		glm::vec2 pos	= glm::vec2(0.0f);
		float rotation	= 0.0f;
		float scale		= 0.0f;
		interpolation_type iplPos;
		interpolation_type iplRot;
		interpolation_type iplSc;
		movement_type moveType;
		float time = 1.0f;

		std::vector<glm::vec2> bezierWpoints;
	};

public:
	void processAnimation();
	void animateFromTo(const std::string& idFrom, const std::string& idTo);
	void animateTo(const std::string& id);
	void animateSequence();
	void goToDefault();
	void continueAnimation();
	void pauseAnimation();	
	void setDefaultState(const animation_state& as);
	void addState(const std::string& id, const animation_state& as);
	
	std::string getCurrentToState() {
		return currentToState;
	}

protected:
	virtual glm::vec2 anim_getPos() = 0;
	virtual void anim_setPos(const glm::vec2& pos) = 0;
	virtual float anim_getRot() = 0;
	virtual void anim_setRot(float r) = 0;
	virtual float anim_getScale() = 0;
	virtual void anim_setScale(float s) = 0;

	virtual void postProcessAnim(){}
	virtual void onAnimationEnd(){}
	virtual void processInterpolation(glm::vec2& v, float t, interpolation_type it);
	virtual void processInterpolation(float& v, float t, interpolation_type it);

private:
	animation_state* getState(const std::string& s) {
		if (stateExist(s))
			return &animStates[animStateMap[s]];
		return NULL;
	}
	void moveToState(animation_state* as) {
		anim_setPos(as->pos);
		anim_setRot(as->rotation);
		anim_setScale(as->scale);
		postProcessAnim();
	}
	void moveToState(int index) {
		if (index < animStates.size())
			moveToState(&animStates[index]);
	}
	void moveToState(const std::string& id) {
		if (stateExist(id))
			moveToState(animStateMap[id]);
	}
	void createTempState();
	void removeTempState();

protected:
	std::map<std::string, int>		animStateMap;
	std::vector<animation_state>	animStates;
	std::string						currentToState = "";

	int currentToStateIndex		= 0;
	int currentFromStateIndex	= 0;

	float currentTime		= 0.0f;

	bool animationON		= false;
	bool animateAll			= false;

	bool stateExist(const std::string& id) {
		return (animStateMap.find(id) != animStateMap.end());
	}
};


/***********************************************/
//class SpriteAnimation
/***********************************************/
/*{
public:
	void startAnimation() {
		animationON = true;
		setDisplayState(true);
	}
	void stopAnimation() {
		animationON = false;
		if (hideAfterEnd) setDisplayState(false);
	}
	void setHideShowMode(bool _hideBeforeStart, bool _hideAfterEnd) {
		hideBeforeStart = _hideBeforeStart;
		hideAfterEnd = _hideAfterEnd;
	}
	void setAnimationSpeed(float _speed) {
		speed = _speed;
	}
	void setLinearMovement(const glm::vec2& _fromPos, const glm::vec2& _toPos, float _speed = 0.01f) {
		fromPos = _fromPos;
		toPos = _toPos;
		speed = _speed;
		moveON = true;
		init();
	}
	void setRotationSpeed(float _rotationSpeed) {
		rotationSpeed = _rotationSpeed;
		rotateON = true;
		init();
	}
	void setScaling(float _scaleSpeed) {
		scaleSpeed = _scaleSpeed;
		scalingON = true;
		init();
	}
	void setMaxTime(float _maxTime) {
		maxTime = _maxTime;
	}

	void init() {
		reset();
		if (hideBeforeStart) setDisplayState(false);
	}
	void reset() {
		setCurrentPosition(fromPos);
		currentTime = 0.0;
	}

	virtual glm::vec2 currentPosition() = 0;
	virtual void setCurrentPosition(const glm::vec2& pos) = 0;
	virtual void processMoveStep(const glm::vec2& step) = 0;
	virtual void processRotate() = 0;
	virtual void processScaling() = 0;
	virtual void setDisplayState(bool state) = 0;
	virtual void processCustomAnimation() {};

	void processAnimation();

protected:
	float currentTime	= 0.0f;
	float maxTime		= -1.0f;

	float speed			= 0.0f;
	float rotationSpeed = 0.0f;
	float scaleSpeed	= 0.0f;

	glm::vec2 fromPos;
	glm::vec2 toPos;

	bool animationON	= false;
	bool rotateON		= false;
	bool moveON			= false;
	bool scalingON		= false;
	bool customAnimationON = false;

	bool hideBeforeStart = true;
	bool hideAfterEnd = false;
};
*/




