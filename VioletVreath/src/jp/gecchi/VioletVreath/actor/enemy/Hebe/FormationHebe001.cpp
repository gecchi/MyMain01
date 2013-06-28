#include "stdafx.h"
#include "FormationHebe001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/EnemyHebe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe001::FormationHebe001(const char* prm_name) :
        FormationHebe(prm_name, "FormationHebe001") {
    _class_name = "FormationHebe001";
    //スプライン定義ファイルを読み込む
    pSplManufConnection_ = connect_SplineManufactureManager("FormationHebe001");
}
void FormationHebe001::onCallUpHebe(EnemyHebe* pEnemyHebe) {
//    pEnemyHebe->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_X_front_, //X方向倍率
//                                       -1.0 * MyShip::lim_Y_top_,   //Y方向倍率
//                                        MyShip::lim_Z_left_  //Z方向倍率
//                                    );
//    pEnemyHebe->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyHebe->pKurokoLeader_->adjustAxisYFlip();
//    pEnemyHebe->pKurokoLeader_->setAbsoluteBeginCoord();
    pEnemyHebe->position(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyHebe->_pKurokoA->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationHebe001::processBehavior() {
    FormationHebe::processBehavior();
}
SplineManufacture* FormationHebe001::getSplManuf() {
    return pSplManufConnection_->peek();
}

FormationHebe001::~FormationHebe001() {
    pSplManufConnection_->close();
}
