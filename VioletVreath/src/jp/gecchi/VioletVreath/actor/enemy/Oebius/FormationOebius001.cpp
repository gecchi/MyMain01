#include "FormationOebius001.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius001::FormationOebius001(const char* prm_name) :
        FormationOebius(prm_name, 3) {
    _class_name = "FormationOebius001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationRowNum()]; //getFormationRowNum() = 3
    papSplManufConn_[0] = getConnection_SplineManufactureManager("FormationOebius001_0");
    papSplManufConn_[1] = getConnection_SplineManufactureManager("FormationOebius001_1");
    papSplManufConn_[2] = getConnection_SplineManufactureManager("FormationOebius001_2");
}

void FormationOebius001::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius001::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("FormationOebius001::onCallUp pOebius->pKurokoLeader_‚ªİ’è‚³‚ê‚Ä‚Ü‚·BpOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        SplineKurokoLeader* pKurokoLeader = papSplManufConn_[prm_row]->peek()->
                                                createKurokoLeader(pOebius->getKuroko());
        pOebius->pKurokoLeader_ = pKurokoLeader;
    }
    double rate_y = pOebius->pKurokoLeader_->_pManufacture->_rate_y;

    pOebius->position(entry_pos_.x                      ,
                      entry_pos_.y + ( ((prm_row*0.4) *rate_y) *2 ) ,
                      entry_pos_.z                       );
    pOebius->getKuroko()->setRzRyMvAng(0, 0);
    pOebius->getKuroko()->setMvVelo(PX_C(2));
    if (prm_row == 0) {
        pOebius->setMaterialColor(1.0, 0.5, 0.5);
    } else if (prm_row == 1) {
        pOebius->setMaterialColor(0.5, 1.0, 0.5);
    } else if (prm_row == 2) {
        pOebius->setMaterialColor(0.5, 0.5, 1.0);
    }

}

FormationOebius001::~FormationOebius001() {
    for (int i = 0; i < getFormationRowNum(); i++) {
        papSplManufConn_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

