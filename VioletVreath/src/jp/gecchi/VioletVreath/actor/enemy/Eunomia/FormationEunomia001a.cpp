#include "stdafx.h"
#include "FormationEunomia001a.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/EnemyEunomia.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001a::FormationEunomia001a(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001a";
}
void FormationEunomia001a::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                        MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->pKurokoLeader_->adjustCoordOffset(PX_C(0), PX_C(col*50), PX_C(col*50));
    pEnemyEunomia->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationEunomia001a::~FormationEunomia001a() {
}
