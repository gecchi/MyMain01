#include "FormationThagoras001.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/core/util/Xpm.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras001::FormationThagoras001(const char* prm_name) :
        FormationThagoras(prm_name, "jiki") {
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

void FormationThagoras001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyThagoras* pThagoras = (EnemyThagoras*)prm_pActor;
    if (pThagoras->pDriverLeader_) {
        throwCriticalException("pThagoras->pDriverLeader_���ݒ肳��Ă܂��BpThagoras="<<pThagoras<<"("<<pThagoras->getName()<<")");
    } else {
        pThagoras->pDriverLeader_ = pThagoras->createCurveDriverLeader(papCurveManufConn_[prm_col]->peek());
    }
    pThagoras->pDriverLeader_->setStartPosition(entry_pos_.x                      ,
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

