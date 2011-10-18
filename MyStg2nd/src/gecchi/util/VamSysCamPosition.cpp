#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


VamSysCamPosition::VamSysCamPosition(MyShip* prm_pMyShip)  : GgafObject() {
    Pos* pPos_Right_SX = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, D0ANG, D90ANG);
    Pos* pPos_Right_UX = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, D0ANG, D90ANG);
    Pos* pPos_Right_SY = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, D0ANG, D90ANG);
    Pos* pPos_Right_UY = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, D0ANG, D90ANG);

    Pos* pPos_Behind_SY = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, D0ANG, D90ANG);
    Pos* pPos_Behind_UY = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, D0ANG, D90ANG);
    Pos* pPos_Behind_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, D0ANG, D90ANG);
    Pos* pPos_Behind_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, D0ANG, D90ANG);

    Pos* pPos_Left_SX = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, D0ANG, D90ANG);
    Pos* pPos_Left_UX = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, D0ANG, D90ANG);
    Pos* pPos_Left_SY = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, D0ANG, D90ANG);
    Pos* pPos_Left_UY = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, D0ANG, D90ANG);

    Pos* pPos_Front_SY = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, D0ANG, D90ANG);
    Pos* pPos_Front_UY = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, D0ANG, D90ANG);
    Pos* pPos_Front_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, D0ANG, D90ANG);
    Pos* pPos_Front_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, D0ANG, D90ANG);


    Pos* pPos_Top_SX = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, D0ANG, D90ANG);
    Pos* pPos_Top_UX = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, D0ANG, D90ANG);
    Pos* pPos_Top_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, D0ANG, D90ANG);
    Pos* pPos_Top_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, D0ANG, D90ANG);

    Pos* pPos_Bottom_SX = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, D0ANG, D90ANG);
    Pos* pPos_Bottom_UX = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, D0ANG, D90ANG);
    Pos* pPos_Bottom_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, D0ANG, D90ANG);
    Pos* pPos_Bottom_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, D0ANG, D90ANG);


}

VamSysCamPosition::~VamSysCamPosition() {
}
