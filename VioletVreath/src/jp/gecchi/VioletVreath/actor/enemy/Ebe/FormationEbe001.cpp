#include "stdafx.h"
#include "FormationEbe001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/EnemyEbe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEbe001::FormationEbe001(const char* prm_name) :
        FormationEbe(prm_name, "FormationEbe001") {
    _class_name = "FormationEbe001";
    //スプライン定義ファイルを読み込む
    pSplManufConnection_ = connect_SplineManufactureManager("FormationEbe001");
}
void FormationEbe001::onCallUpEbe(EnemyEbe* pEnemyEbe) {
//    pEnemyEbe->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_X_front_, //X方向倍率
//                                       -1.0 * MyShip::lim_Y_top_,   //Y方向倍率
//                                        MyShip::lim_Z_left_  //Z方向倍率
//                                    );
//    pEnemyEbe->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyEbe->pKurokoLeader_->adjustAxisYFlip();
//    pEnemyEbe->pKurokoLeader_->setAbsoluteBeginCoord();
    pEnemyEbe->position(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyEbe->_pKurokoA->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationEbe001::processBehavior() {
    FormationEbe::processBehavior();
}

SplineManufacture* FormationEbe001::getSplManuf() {
    return pSplManufConnection_->peek();
}

FormationEbe001::~FormationEbe001() {
    pSplManufConnection_->close();
}
