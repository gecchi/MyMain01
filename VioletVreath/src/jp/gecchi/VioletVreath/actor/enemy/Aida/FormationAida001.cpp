#include "stdafx.h"
#include "FormationAida001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/EnemyAida.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAida001::FormationAida001(const char* prm_name) :
        FormationAida(prm_name, "FormationAida001") {
    _class_name = "FormationAida001";
    //スプライン定義ファイルを読み込む
    pSplManufConnection_ = connectToSplineManufactureManager("FormationAida001");
}
void FormationAida001::onCallUpAida(EnemyAida* pEnemyAida) {
//    pEnemyAida->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_X_front_, //X方向倍率
//                                       -1.0 * MyShip::lim_Y_top_,   //Y方向倍率
//                                        MyShip::lim_Z_left_  //Z方向倍率
//                                    );
//    pEnemyAida->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyAida->pKurokoLeader_->adjustAxisYFlip();
//    pEnemyAida->pKurokoLeader_->setAbsoluteBeginCoord();
    pEnemyAida->locate(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyAida->_pKurokoA->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationAida001::processBehavior() {
    FormationAida::processBehavior();
}
SplineManufacture* FormationAida001::getSplManuf() {
    return pSplManufConnection_->peek();
}

FormationAida001::~FormationAida001() {
    pSplManufConnection_->close();
}
