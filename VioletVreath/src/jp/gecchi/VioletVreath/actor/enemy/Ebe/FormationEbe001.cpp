#include "FormationEbe001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    pConn_pSplManuf_ = connectToSplineManufactureManager("FormationEbe001");
}
void FormationEbe001::onCallUpEbe(EnemyEbe* pEnemyEbe) {
//    pEnemyEbe->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X方向倍率
//                                       -1.0 * MyShip::lim_y_top_,   //Y方向倍率
//                                        MyShip::lim_z_left_  //Z方向倍率
//                                    );
//    pEnemyEbe->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyEbe->pKurokoLeader_->adjustAxisYFlip();
//    pEnemyEbe->pKurokoLeader_->setAbsoluteBeginCoord();
    pEnemyEbe->locate(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyEbe->getKuroko()->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationEbe001::processBehavior() {
    FormationEbe::processBehavior();
}

SplineManufacture* FormationEbe001::getSplManuf() {
    return pConn_pSplManuf_->peek();
}

FormationEbe001::~FormationEbe001() {
    pConn_pSplManuf_->close();
}
