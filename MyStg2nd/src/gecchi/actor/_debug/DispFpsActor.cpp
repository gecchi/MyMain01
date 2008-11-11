#include "stdafx.h"

DispFpsActor::DispFpsActor(string prm_name, string prm_model) : FontPlateActor(prm_name, prm_model) {
}

void DispFpsActor::initialize() {
	FontPlateActor::initialize();
	_z = 0.0f; //Å‘O–Ê
	//0.999;
}

void DispFpsActor::processBehavior() {
	//sprintf_s(_aBuf, 17, "%06d %.1f fps", prm_dwFrame, askGod()->_fFps);
	sprintf(_aBuf, "%06u %.1f fps", (unsigned int)askGod()->_dwFrame_God, askGod()->_fFps);
	setStringPlate(0,0,string(_aBuf));
}

DispFpsActor::~DispFpsActor() {
}
