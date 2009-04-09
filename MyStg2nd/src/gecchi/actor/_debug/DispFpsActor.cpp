#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DispFpsActor::DispFpsActor(const char* prm_name, const char* prm_model) : GgafDx9StringBoardActor(prm_name, prm_model) {
    _class_name = "DispFpsActor";
}

void DispFpsActor::initialize() {
    GgafDx9StringBoardActor::initialize();
    _z = 0.01f; //�őO��
    //0.999;
}

void DispFpsActor::processBehavior() {
    //sprintf_s(_aBuf, 17, "%06d %.1f fps", prm_dwFrame, askGod()->_fFps);
    sprintf(_aBuf, "%05u %07u %.1f fps", GgafGod::_num_actor_playing, (unsigned int)askGod()->_dwFrame_God, askGod()->_fFps);
    update(0, 0, _aBuf);
}

DispFpsActor::~DispFpsActor() {
}
