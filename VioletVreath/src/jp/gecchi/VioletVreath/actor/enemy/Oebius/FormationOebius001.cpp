#include "FormationOebius001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius001::FormationOebius001(const char* prm_name) :
        FormationOebius(prm_name, 3, 38, 8) {
    _class_name = "FormationOebius001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = getConnection_SplineManufactureManager(("FormationOebius001_"+XTOS(col)).c_str());
    }
}

void FormationOebius001::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius001::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("FormationOebius001::onCallUp pOebius->pKurokoLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        SplineKurokoLeader* pKurokoLeader = papSplManufConn_[prm_col]->peek()->
                                                createKurokoLeader(pOebius->getKuroko());
        pOebius->pKurokoLeader_ = pKurokoLeader;
    }
    double rate_z = pOebius->pKurokoLeader_->_pManufacture->_rate_z;

    //Z = (prm_col*0.4)*rate_z
    //(0, 0, Z) を Rz > Ry 回転移動させると
    //(Z*sinRy, 0, Z*cosRy)
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);
    float Z = (prm_col*(0.4+0.4))*rate_z;   //基本間隔は0.4。本編隊はmobius1.dat、mobius3.dat、mobius5.dat と一つ飛びなので0.4+0.4

    coord dx = Z*sinRy;
    coord dy = 0;
    coord dz = Z*cosRy;
    pOebius->pKurokoLeader_->fixStartPosition(entry_pos_.x + dx,
                                              entry_pos_.y + dy,
                                              entry_pos_.z + dz);
    pOebius->pKurokoLeader_->fixStartMvAngle(entry_pos_.rz, entry_pos_.ry);


    pOebius->position( RND_AROUND(entry_pos_.x + dx, PX_C(700)),
                       RND_AROUND(entry_pos_.y + dy, PX_C(700)),
                       RND_AROUND(entry_pos_.z + dz, PX_C(700)) );
    pOebius->setFaceAngTwd(entry_pos_.x + dx,
                           entry_pos_.y + dy,
                           entry_pos_.z + dz);
    pOebius->getKuroko()->setMvAngByFaceAng();
    pOebius->getKuroko()->setMvVelo(0);
    pOebius->getKuroko()->setMvAcce(80);

    double r = RANGE_TRANS(prm_col, 0, getFormationColNum(), 0.3, 1.0);
    double g = RANGE_TRANS(prm_col*prm_row, 0, getFormationColNum()*getFormationRowNum(), 0.3, 1.0);
    double b = RANGE_TRANS(prm_row, 0, getFormationRowNum(), 0.3, 1.0);
    pOebius->setMaterialColor(r, g, b);
}

void FormationOebius001::onFinshLeading(GgafDxCore::GgafDxDrawableActor* prm_pActor) {
    GgafDxKuroko* pKuroko =  prm_pActor->getKuroko();
    pKuroko->turnRzRyMvAngTo(RND_AROUND(pKuroko->_ang_rz_mv, D_ANG(120)), RND_AROUND(pKuroko->_ang_rz_mv, D_ANG(120)),
                             D_ANG(2), 0, TURN_CLOSE_TO,false);
    pKuroko->setMvAcce(300);
}

FormationOebius001::~FormationOebius001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

