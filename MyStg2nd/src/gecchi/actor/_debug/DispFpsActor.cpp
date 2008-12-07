#include "stdafx.h"

DispFpsActor::DispFpsActor(string prm_name, string prm_model) : FontPlateActor(prm_name, prm_model) {
	_class_name = "DispFpsActor";
}

void DispFpsActor::initialize() {
	FontPlateActor::initialize();
	_z = 0.0f; //�őO��
	//0.999;
}

void DispFpsActor::processBehavior() {
	//sprintf_s(_aBuf, 17, "%06d %.1f fps", prm_dwFrame, askGod()->_fFps);
	sprintf(_aBuf, "%05u %07u %.1f fps", GgafGod::_iNumPlayingActor, (unsigned int)askGod()->_dwFrame_God, askGod()->_fFps);
	setString(0,0,string(_aBuf));
}

DispFpsActor::~DispFpsActor() {
}
