#include "FormationEbe001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/EnemyEbe.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationEbe001::FormationEbe001(const char* prm_name) :
        FormationEbe(prm_name, "FormationEbe001") {
    _class_name = "FormationEbe001";
    //�Ȑ��ړ��̏��t�@�C����ǂݍ���
    pConn_pCurveManuf_ = connectToCurveManufactureManager("FormationEbe001");
}
void FormationEbe001::onCalledUpEbe(EnemyEbe* pEnemyEbe) {
//    pEnemyEbe->pDriverLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X�����{��
//                                       -1.0 * MyShip::lim_y_top_,   //Y�����{��
//                                        MyShip::lim_z_left_  //Z�����{��
//                                    );
//    pEnemyEbe->pDriverLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyEbe->pDriverLeader_->adjustAxisYFlip();
//    pEnemyEbe->pDriverLeader_->setAbsoluteBeginCoord();
    pEnemyEbe->setPosition(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyEbe->getVecDriver()->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
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
