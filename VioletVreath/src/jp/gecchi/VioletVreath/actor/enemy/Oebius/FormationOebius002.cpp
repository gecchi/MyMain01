#include "FormationOebius002.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius002::FormationOebius002(const char* prm_name) :
        FormationOebius(prm_name, 6, 23, 7) {
    _class_name = "FormationOebius002";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = getConnection_SplineManufactureManager(("FormationOebius002_"+XTOS(col)).c_str());
    }
}

void FormationOebius002::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius002::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_col, int prm_row) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("FormationOebius002::onCallUp pOebius->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        SplineKurokoLeader* pKurokoLeader = papSplManufConn_[prm_col]->peek()->
                                                createKurokoLeader(pOebius->getKuroko());
        pOebius->pKurokoLeader_ = pKurokoLeader;
    }
    double rate_y = pOebius->pKurokoLeader_->_pManufacture->_rate_y;

//    pOebius->position(entry_pos_.x,
//                      entry_pos_.y + ((prm_col*0.4) * rate_y) ,
//                      entry_pos_.z);

    pOebius->pKurokoLeader_->fixStartPosition(entry_pos_.x,
                                              entry_pos_.y + ((prm_col*0.4) * rate_y) ,
                                              entry_pos_.z);
    pOebius->pKurokoLeader_->fixStartMvAngle(0, 0);

    pOebius->position( RND_AROUND(entry_pos_.x, PX_C(400)),
                       RND_AROUND(entry_pos_.y, PX_C(400)),
                       RND_AROUND(entry_pos_.z, PX_C(400)) );
    pOebius->setFaceAngTwd(RND_AROUND(pOebius->_x, PX_C(400)),
                           RND_AROUND(pOebius->_y, PX_C(400)),
                           RND_AROUND(pOebius->_z, PX_C(400)) );
    pOebius->getKuroko()->setMvAngByFaceAng();

    double r = RANGE_TRANS(prm_col*prm_row, 0, getFormationColNum()*getFormationRowNum(), 0.6, 1.0);
    double g = RANGE_TRANS(prm_col, 0, getFormationColNum(), 0.4, 1.0);
    double b = RANGE_TRANS(prm_row, 0, getFormationRowNum(), 0.4, 1.0);
    pOebius->setMaterialColor(r, g, b);
}

FormationOebius002::~FormationOebius002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

