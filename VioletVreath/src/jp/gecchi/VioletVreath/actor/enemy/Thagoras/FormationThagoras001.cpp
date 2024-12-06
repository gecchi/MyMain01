#include "FormationThagoras001.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/core/util/Xpm.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras001::FormationThagoras001(const char* prm_name) :
        FormationThagoras(prm_name, "jiki", StatusReset(FormationThagoras001)) {
    _class_name = "FormationThagoras001";
    int col_num = getXpm()->getWidth();
    papCurveManufConn_ = NEW CurveManufactureConnection*[col_num];
    for (int i = 0; i < col_num; i++) {
        papCurveManufConn_[i] = connectToCurveManufactureManager("FormationThagoras001");
    }
}

void FormationThagoras001::processBehavior() {
    FormationThagoras::processBehavior();
}

void FormationThagoras001::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyThagoras* pThagoras = (EnemyThagoras*)prm_pActor;
    if (pThagoras->pVehicleLeader_) {
        throwCriticalException("pThagoras->pVehicleLeader_が設定されてます。pThagoras="<<pThagoras<<"("<<pThagoras->getName()<<")");
    } else {
        pThagoras->pVehicleLeader_ = pThagoras->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    pThagoras->pVehicleLeader_->setStartPosition(entry_pos_.x                      ,
                                                entry_pos_.y + (prm_col*PX_C(30)) ,
                                                entry_pos_.z                       );

    pThagoras->setPosition( RND(PX_C(-2600), PX_C(2600)),
                            RND(PX_C(-2600), PX_C(2600)),
                            RND(PX_C(-2600), PX_C(2600)) );
}

FormationThagoras001::~FormationThagoras001() {
    int col_num = getXpm()->getWidth();
    for (int i = 0; i < col_num; i++) {
        papCurveManufConn_[i]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
}

