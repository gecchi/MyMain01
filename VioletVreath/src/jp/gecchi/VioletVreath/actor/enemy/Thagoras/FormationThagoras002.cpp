#include "FormationThagoras002.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

#include "jp/ggaf/core/util/Xpm.h"


using namespace GgafLib;
using namespace VioletVreath;


FormationThagoras002::FormationThagoras002(const char* prm_name) :
        FormationThagoras(prm_name, "jikir") {
    _class_name = "FormationThagoras002";
    int col_num = getXpm()->getWidth();
    papSplManufConn_ = NEW SplineManufactureConnection*[col_num];
    for (int i = 0; i < col_num; i++) {
        papSplManufConn_[i] = connectToSplineManufactureManager("FormationThagoras001");
    }
}

void FormationThagoras002::processBehavior() {
    FormationThagoras::processBehavior();
}

void FormationThagoras002::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyThagoras* pThagoras = (EnemyThagoras*)prm_pActor;
    if (pThagoras->pKurokoLeader_) {
        throwCriticalException("pThagoras->pKurokoLeader_‚ªİ’è‚³‚ê‚Ä‚Ü‚·BpThagoras="<<pThagoras<<"("<<pThagoras->getName()<<")");
    } else {
        pThagoras->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pThagoras->getKuroko());
    }
    pThagoras->pKurokoLeader_->setStartPosition(entry_pos_.x                      ,
                                                entry_pos_.y + (prm_col*PX_C(30)) ,
                                                entry_pos_.z                       );

    pThagoras->setPosition( RND(PX_C(-2600), PX_C(2600)),
                            RND(PX_C(-2600), PX_C(2600)),
                            RND(PX_C(-2600), PX_C(2600)) );
}

FormationThagoras002::~FormationThagoras002() {
    int col_num = getXpm()->getWidth();
    for (int i = 0; i < col_num; i++) {
        papSplManufConn_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

