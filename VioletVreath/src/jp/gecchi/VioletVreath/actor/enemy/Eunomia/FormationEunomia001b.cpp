#include "stdafx.h"
#include "FormationEunomia001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/EnemyEunomia.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001b::FormationEunomia001b(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001b";
}

void FormationEunomia001b::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_X_front_, //X�����{��
//                                       -1.0 * MyShip::lim_Y_top_,   //Y�����{��
//                                        MyShip::lim_Z_left_  //Z�����{��
//                                    );
    pEnemyEunomia->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
    pEnemyEunomia->pKurokoLeader_->adjustAxisYFlip();
    pEnemyEunomia->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationEunomia001b::~FormationEunomia001b() {
}
