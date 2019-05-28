#pragma once
#include "agk.h"
#include <string>

#define VC_MAX_MULTI_TOUCHS 5

void changePrintTextColor();

class ViewController {

	struct MultiTouchData {
		UINT id = 0;
		float s[2];
		float l[2];
		float c[2];
		bool pressed = false;
		bool state = false;
		bool released = false;
		bool updated = false;
		float startPos[2];
		float startZoom = 1.0;
		float timepressed = 0.0f;
	};

	struct VClimits {
		VClimits() {};
		VClimits(float _xmin, float _xmax, float _ymin, float _ymax, float _zmin, float _zmax) {
			xmin = _xmin; xmax = _xmax;
			ymin = _ymin; ymax = _ymax;
			zmin = _zmin; zmax = _zmax;
		};

		float xmin;
		float xmax;
		float ymin;
		float ymax;
		float zmin;
		float zmax;
		float width() { return (xmax - xmin); }
		float height() { return (ymax - ymin); }
	};

public:
	ViewController(int _mode, float xmin, float xmax, float ymin, float ymax, float zoommin, float zoommax, float dw = -1.0f, float dh = -1.0f);	
	bool processZoomPan(bool* wasTapped = NULL);
	void setMouseZoomWeight(float w) {
		mouseZoomWeight = w;
	}
	float getMouseZoomWeight() {
		return mouseZoomWeight;
	}

private:
	int mode = 0;

	VClimits limits;
	MultiTouchData multiTouch[VC_MAX_MULTI_TOUCHS];
	float dsize[2];
	int touchID1 = -1;
	int touchID2 = -1;
	UINT touchCount = 0;
	bool pressed = false;
	
	float timepressed = 0.0f;
	bool isPanning = false;
	float pan_currOffs[2];
	float pan_pressed[2];

	float mouseZoomWeight = 0.1f;

	float dt	= 0.01f;
	float maxTapTime = 0.1f;

	bool wasPannedOrZoomed	= false;
	bool wasTapped			= false;

private:
	//tap:
	bool isTapped();
	bool isClicked();
	void onTap();

	//touch:
	void zoomPan_touch();
	void checkZoomLimit();
	void getMultiTouchInput();
	void processZeroTouch();
	void processOneTouch();
	void processTwoTouch();
	void processThreeTouch();
	void updateExistingMultiTouchData(MultiTouchData* mtd);
	void updateNewMultiTouchData(MultiTouchData* mtd);
	void updateMultiTouchCoordinates(MultiTouchData* mtd);
	bool checkIfTouchEventExist(UINT touchEventId);
	void processNewTouchEvent(UINT touchEventId);
	int findFreeMultiTouchSlot();

	//mouse:
	void zoomPan_mouse();
	float zoom_mouse();
	void pan_mouse(float zoomf);

	//touch+mouse:
	void setViewOffsetWithinLimits(float x, float y, float vz);
	float setZoomWithinLimits(float vz);

	//convinient functions:
	void getViewOffset(float offs[2]);
	void getPointerPos(float pos[2]);
	void divideVec2(float vecOut[2], float vecIn[2], float d);
	void divideVec2(float vec[2], float d);
	void substractVec2(float vecOut[2], float vec1[2], float vec2[2]);
	void substractVec2(float vec[2], float vecS[2]);
	void multiplyVec2(float vec[2], float f);
	void copyVec2(float target[2], float source[2]);
	float vec2length(float v[2]);
	void center2points(float cp[2], float p1[2], float p2[2]);

	template<typename T>
	void agkPrint(const std::string& prefix, T v) {
		std::string str = prefix + std::to_string(v);
		agk::Print(&str[0]);
	}

	template<typename T>
	void agkPrint(const std::string& prefix, T v1, T v2) {
		std::string str = prefix + std::to_string(v1) + ", " + std::to_string(v2);
		agk::Print(&str[0]);
	}


	void agkPrintVec2(const std::string& prefix, float vec[2]) {
		agkPrint(prefix, vec[0], vec[1]);
	}
};