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
        FormationOebius(prm_name, 3, 40, 15) {
    _class_name = "FormationOebius001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = getConnection_SplineManufactureManager(("FormationOebius001_"+XTOS(col)).c_str());
    }
}

void FormationOebius001::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius001::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_col, int prm_row) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("FormationOebius001::onCallUp pOebius->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        SplineKurokoLeader* pKurokoLeader = papSplManufConn_[prm_col]->peek()->
                                                createKurokoLeader(pOebius->getKuroko());
        pOebius->pKurokoLeader_ = pKurokoLeader;
    }
    double rate_y = pOebius->pKurokoLeader_->_pManufacture->_rate_y;

    pOebius->position(entry_pos_.x                      ,
                      entry_pos_.y + ( ((prm_col*0.4) *rate_y) *2 ) ,
                      entry_pos_.z                       );
    pOebius->getKuroko()->setRzRyMvAng(0, 0);
    if (prm_col == 0) {
        pOebius->setMaterialColor(1.0, 0.5, 0.5);
    } else if (prm_col == 1) {
        pOebius->setMaterialColor(0.5, 1.0, 0.5);
    } else if (prm_col == 2) {
        pOebius->setMaterialColor(0.5, 0.5, 1.0);
    }

}

FormationOebius001::~FormationOebius001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

