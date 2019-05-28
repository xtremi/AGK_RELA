#include "ViewController.h"

static bool colred = true;
void changePrintTextColor() {
	if (colred)
		agk::SetPrintColor(0, 255, 0);		
	else
		agk::SetPrintColor(255, 0, 0);	
	colred = !colred;	
}

ViewController::ViewController(int _mode, float xmin, float xmax, float ymin, float ymax, float zoommin, float zoommax, float dw, float dh)
{
	limits = VClimits(xmin, xmax, ymin, ymax, zoommin, zoommax);
	dsize[0] = dw > 0.0f ? dw : agk::GetDeviceWidth();
	dsize[1] = dh > 0.0f ? dh : agk::GetDeviceHeight();
	mode = _mode;
	checkZoomLimit();	
}

bool ViewController::processZoomPan(bool* tapped) {
	wasPannedOrZoomed	= false;
	wasTapped			= false;
	switch (mode)
	{
	case 0: zoomPan_touch(); break;
	case 1: zoomPan_mouse(); break;
	default: break;
	}

	(*tapped) = wasTapped;
	return wasPannedOrZoomed;
}

void ViewController::zoomPan_mouse() {
	float zoomf = zoom_mouse();
	pan_mouse(zoomf);	
}

float ViewController::zoom_mouse() {
	float mwd = agk::GetRawMouseWheelDelta();

	float zoomf0 = agk::GetViewZoom();
	float zoomf1 = zoomf0;
	if (std::abs(mwd) > 0.00f) {
		zoomf1 += (mwd * mouseZoomWeight);
		setZoomWithinLimits(zoomf1);
		
		float offs[2], ppos[2];
		getViewOffset(offs);		
		getPointerPos(ppos);

		float s0[2], s1[2];
		divideVec2(s0, ppos, zoomf0);
		divideVec2(s1, ppos, zoomf1);
		
		float ds[2];
		substractVec2(ds, s1, s0);
		substractVec2(offs, ds);
		
		setViewOffsetWithinLimits(offs[0], offs[1], zoomf1);
		wasPannedOrZoomed = true;
		
	}
	return zoomf1;
}

void ViewController::pan_mouse(float zoomf) {
	if (agk::GetPointerPressed()) {
		getPointerPos(pan_pressed);
		getViewOffset(pan_currOffs);
		isPanning = true;
		timepressed = 0.0f;
	}
	else if (isPanning) {
		timepressed += dt;
		
		float ppos[2], ds[2];
		getPointerPos(ppos);
		substractVec2(ds, ppos, pan_pressed);
		float l = vec2length(ds);

		divideVec2(ds, zoomf);

		float newOffs[2];
		substractVec2(newOffs, pan_currOffs, ds);		

		if (l > 0.6f) {
			wasPannedOrZoomed = true;
			setViewOffsetWithinLimits(newOffs[0], newOffs[1], zoomf);
		}

		if (agk::GetPointerReleased()){
			isPanning = false;		
			if (l < 0.6f)
				wasTapped = true;
		}
	}
}



void ViewController::checkZoomLimit() {
	float minZw = dsize[0] / limits.width();
	float minZh = dsize[1] / limits.height();
	float max_minZwh = fmaxf(minZw, minZh);
	if (limits.zmin < max_minZwh) limits.zmin = max_minZwh;
}

void ViewController::updateMultiTouchCoordinates(MultiTouchData* mtd) {
	mtd->s[0] = agk::GetRawTouchStartX(mtd->id);
	mtd->s[1] = agk::GetRawTouchStartY(mtd->id);
	mtd->l[0] = agk::GetRawTouchLastX(mtd->id);
	mtd->l[1] = agk::GetRawTouchLastY(mtd->id);
	mtd->c[0] = agk::GetRawTouchCurrentX(mtd->id);
	mtd->c[1] = agk::GetRawTouchCurrentY(mtd->id);
}

void ViewController::updateExistingMultiTouchData(MultiTouchData* mtd) {
	mtd->updated = true;
	mtd->pressed = false;
	updateMultiTouchCoordinates(mtd);
	mtd->released = (agk::GetRawTouchReleased(mtd->id) == 1);
	if (mtd->released){
		mtd->state = false;
		//wasPannedOrZoomed = true;
	}
	mtd->timepressed += dt;
}

void ViewController::updateNewMultiTouchData(MultiTouchData* mtd) {	
	mtd->updated	= true;			
	updateMultiTouchCoordinates(mtd);
	mtd->released = (agk::GetRawTouchReleased(mtd->id) == 1);
	mtd->state = true;
	mtd->timepressed = 0.0f;
}

void ViewController::zoomPan_touch() {
	getMultiTouchInput();

	switch (touchCount)
	{
	case 0: processZeroTouch(); break;
	case 1: 
		if (!isTapped())
			processOneTouch();
		else
			onTap();
		break;
	case 2:	processTwoTouch();  break;
	case 3: processThreeTouch(); break;
	default:
		break;
	}
}

bool ViewController::checkIfTouchEventExist(UINT touchEventId) {
	for (int i = 0; i < VC_MAX_MULTI_TOUCHS; i++) {
		MultiTouchData* currMtd = &multiTouch[i];
		if (touchEventId == currMtd->id) {
			updateExistingMultiTouchData(currMtd);
			return true;
		}
	}
	return false;
}

int ViewController::findFreeMultiTouchSlot() {	
	for (int i = 0; i < VC_MAX_MULTI_TOUCHS; i++) {
		if (multiTouch[i].id == 0) {
			return i;
		}
	}
	return -1;
}

void ViewController::processNewTouchEvent(UINT touchEventId) {
	
	int freeSlot = findFreeMultiTouchSlot();

	if (freeSlot > -1) {
		MultiTouchData* currMtd = &multiTouch[freeSlot];
		currMtd->id = touchEventId;
		updateNewMultiTouchData(currMtd);

		switch (touchCount)
		{
		case 1: touchID1 = freeSlot; break;
		case 2:
			if (touchID1 == -1)
				touchID1 = freeSlot;
			else {
				touchID2 = freeSlot;
				currMtd->startZoom	= agk::GetViewZoom();
				getViewOffset(currMtd->startPos);
			}
			break;
		default:
			break;
		}
	}
}

void ViewController::getMultiTouchInput() {

	for (int i = 0; i < VC_MAX_MULTI_TOUCHS; i++)
		multiTouch[i].updated = false;

	UINT ptc = touchCount;
	if (ptc == 0) {
		touchID1 = -1;
		touchID2 = -1;
	}
	touchCount = agk::GetRawTouchCount(1);
	pressed = false;

	UINT touchEventId = agk::GetRawFirstTouchEvent(1);
	while (touchEventId > 0) {

		if (!checkIfTouchEventExist(touchEventId)) {
			processNewTouchEvent(touchEventId);
		}							
		touchEventId = agk::GetRawNextTouchEvent();
	}

	//check data:
	for (int i = 0; i < VC_MAX_MULTI_TOUCHS; i++) {
		if (!multiTouch[i].updated){	
			multiTouch[i].id = 0;
		}
	}

	//swap from multitouch to single touch drag:
	if ((ptc == 2) && (touchCount == 1) && (multiTouch[touchID1].id == 0)){
		touchID1 = touchID2;
	}
}




void ViewController::processOneTouch() {	
	float vz = agk::GetViewZoom();
	float offs[2], ds[2];
	getViewOffset(offs);
	substractVec2(ds, multiTouch[touchID1].c, multiTouch[touchID1].l);

	float doffs[2];	
	divideVec2(doffs, ds, vz);
	substractVec2(offs, doffs);
	

	float dragL, dragVec[2];
	float ddragL, ddragVec[2];
	substractVec2(dragVec, multiTouch[touchID1].c, multiTouch[touchID1].s);
	substractVec2(ddragVec, multiTouch[touchID1].c, multiTouch[touchID1].l);

	dragL = vec2length(dragVec);	
	ddragL = vec2length(ddragVec);


	if(ddragL > 1.f && dragL > 2.0f){
		setViewOffsetWithinLimits(offs[0], offs[1], vz);
		wasPannedOrZoomed = true;
	}
	/*agkPrint("timePressed: ", multiTouch[touchID1].timepressed);
	if (multiTouch[touchID1].timepressed > 0.1)
		wasPannedOrZoomed = true;*/
}

bool ViewController::isTapped() {
	//agkPrint("timepressed: ", multiTouch[touchID1].timepressed);
	if (multiTouch[touchID1].released) {
		//if (multiTouch[touchID1].timepressed < maxTapTime) {
		float dsv[2];
		float ds;
		substractVec2(dsv, multiTouch[touchID1].c, multiTouch[touchID1].s);
		ds = vec2length(dsv);
		if (ds < 30.0f) {
			wasTapped = true;
			return true;
		}
		//}
	}
	return false;
}

bool ViewController::isClicked() {
	return true;
}

void ViewController::onTap() {
	changePrintTextColor();
}

void ViewController::processTwoTouch() 
{
	float vz = agk::GetViewZoom();
	float sz = multiTouch[touchID2].startZoom;
	float sOffs[2];
	copyVec2(sOffs, multiTouch[touchID2].startPos);

	float dsv[2], dcv[2];
	substractVec2(dsv, multiTouch[touchID2].s, multiTouch[touchID1].s);
	substractVec2(dcv, multiTouch[touchID2].c, multiTouch[touchID1].c);
	float ds = vec2length(dsv);
	float dc = vec2length(dcv);

	vz = sz * (dc / ds);
	vz = setZoomWithinLimits(vz);

	float centerS[2], centerC[2];
	center2points(centerS, multiTouch[touchID1].s, multiTouch[touchID2].s);
	center2points(centerC, multiTouch[touchID1].c, multiTouch[touchID2].c);
	divideVec2(centerS, sz);
	divideVec2(centerC, vz);

	float doffs[2];
	substractVec2(doffs, centerC, centerS);
	substractVec2(sOffs, doffs);

	setViewOffsetWithinLimits(sOffs[0], sOffs[1], vz);	

	wasPannedOrZoomed = true;
}

float ViewController::setZoomWithinLimits(float vz) {
	if (vz < (limits.zmin + 0.0001))
		vz = limits.zmin;
	else if (vz > limits.zmax)
		vz = limits.zmax;
	agk::SetViewZoom(vz);
	return vz;
}

void ViewController::setViewOffsetWithinLimits(float x, float y, float vz) {
	float minx = limits.xmin;
	float maxx = limits.xmax - dsize[0] / vz;
	float miny = limits.ymin;
	float maxy = limits.ymax - dsize[1] / vz;

	if (x < minx) x = minx;
	else if (x > maxx) x = maxx;
	if (y < miny) y = miny;
	else if (y > maxy) y = maxy;
	agk::SetViewOffset(x, y);
}

/*optional*/
void ViewController::processZeroTouch() {}
void ViewController::processThreeTouch() {
	agk::SetViewOffset(0.f, 0.f);
	agk::SetViewZoom(1.f);
}

/*Convinient functions*/
void ViewController::getViewOffset(float offs[2]) {
	offs[0] = agk::GetViewOffsetX();
	offs[1] = agk::GetViewOffsetY();
}
void ViewController::getPointerPos(float pos[2]) {
	pos[0] = agk::GetPointerX();
	pos[1] = agk::GetPointerY();
}
void ViewController::divideVec2(float vecOut[2], float vecIn[2], float d) {
	vecOut[0] = vecIn[0] / d;
	vecOut[1] = vecIn[1] / d;
}
void ViewController::divideVec2(float vec[2], float d) {
	vec[0] /= d;
	vec[1] /= d;
}
void ViewController::substractVec2(float vecOut[2], float vec1[2], float vec2[2]) {
	vecOut[0] = vec1[0] - vec2[0];
	vecOut[1] = vec1[1] - vec2[1];
}
void ViewController::substractVec2(float vec[2], float vecS[2]) {
	vec[0] -= vecS[0];
	vec[1] -= vecS[1];
}
void ViewController::multiplyVec2(float vec[2], float f) {
	vec[0] *= f;
	vec[1] *= f;
}
void ViewController::copyVec2(float target[2], float source[2]) {
	target[0] = source[0];
	target[1] = source[1];
}
float ViewController::vec2length(float v[2]) {
	return sqrtf(v[0] * v[0] + v[1] * v[1]);
}
void ViewController::center2points(float cp[2], float p1[2], float p2[2]) {
	cp[0] = p1[0] + (p2[0] - p1[0])*0.5f;
	cp[1] = p1[1] + (p2[1] - p1[1])*0.5f;
}