#include "FormationEbe001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/EnemyEbe.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationEbe001::FormationEbe001(const char* prm_name) :
        FormationEbe(prm_name, "FormationEbe001", StatusReset(FormationEbe001)) {
    _class_name = "FormationEbe001";
    //曲線移動の情報ファイルを読み込む
    pConn_pCurveManuf_ = connectToCurveManufactureManager("FormationEbe001");
}
void FormationEbe001::onSummonEbe(EnemyEbe* pEnemyEbe) {
//    pEnemyEbe->pVehicleLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X方向倍率
//                                       -1.0 * MyShip::lim_y_top_,   //Y方向倍率
//                                        MyShip::lim_z_left_  //Z方向倍率
//                                    );
//    pEnemyEbe->pVehicleLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyEbe->pVehicleLeader_->adjustAxisYFlip();
//    pEnemyEbe->pVehicleLeader_->setAbsoluteBeginCoord();
    pEnemyEbe->setPosition(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyEbe->getLocusVehicle()->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationEbe001::processBehavior() {
    FormationEbe::processBehavior();
}

CurveManufacture* FormationEbe001::getSplManuf() {
    return pConn_pCurveManuf_->peek();
}

FormationEbe001::~FormationEbe001() {
    pConn_pCurveManuf_->close();
}
