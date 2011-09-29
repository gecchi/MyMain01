#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


VamSysCamPosition::VamSysCamPosition(MyShip* prm_pMyShip)  : GgafObject() {
    Pos* pPos_Right_SX = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, ANGLE0, ANGLE90);
    Pos* pPos_Right_UX = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, ANGLE0, ANGLE90);
    Pos* pPos_Right_SY = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, ANGLE0, ANGLE90);
    Pos* pPos_Right_UY = NEW Pos(VAM_POS_CAM_MYSHIP_RIGHT, ANGLE0, ANGLE90);

    Pos* pPos_Behind_SY = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, ANGLE0, ANGLE90);
    Pos* pPos_Behind_UY = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, ANGLE0, ANGLE90);
    Pos* pPos_Behind_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, ANGLE0, ANGLE90);
    Pos* pPos_Behind_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_BEHIND, ANGLE0, ANGLE90);

    Pos* pPos_Left_SX = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, ANGLE0, ANGLE90);
    Pos* pPos_Left_UX = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, ANGLE0, ANGLE90);
    Pos* pPos_Left_SY = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, ANGLE0, ANGLE90);
    Pos* pPos_Left_UY = NEW Pos(VAM_POS_CAM_MYSHIP_LEFT, ANGLE0, ANGLE90);

    Pos* pPos_Front_SY = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, ANGLE0, ANGLE90);
    Pos* pPos_Front_UY = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, ANGLE0, ANGLE90);
    Pos* pPos_Front_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, ANGLE0, ANGLE90);
    Pos* pPos_Front_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_FRONT, ANGLE0, ANGLE90);


    Pos* pPos_Top_SX = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, ANGLE0, ANGLE90);
    Pos* pPos_Top_UX = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, ANGLE0, ANGLE90);
    Pos* pPos_Top_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, ANGLE0, ANGLE90);
    Pos* pPos_Top_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_TOP, ANGLE0, ANGLE90);

    Pos* pPos_Bottom_SX = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, ANGLE0, ANGLE90);
    Pos* pPos_Bottom_UX = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, ANGLE0, ANGLE90);
    Pos* pPos_Bottom_SZ = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, ANGLE0, ANGLE90);
    Pos* pPos_Bottom_UZ = NEW Pos(VAM_POS_CAM_MYSHIP_BOTTOM, ANGLE0, ANGLE90);


}

VamSysCamPosition::~VamSysCamPosition() {
}
