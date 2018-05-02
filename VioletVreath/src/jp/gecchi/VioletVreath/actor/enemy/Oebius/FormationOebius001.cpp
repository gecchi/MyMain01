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

FormationOebius001::FormationOebius001(const char* prm_name, EnemyOebiusController* prm_pController) :
        FormationOebius(prm_name, 3, 38, 8, prm_pController) {
    _class_name = "FormationOebius001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationOebius001/"+XTOS(col)).c_str());
    }
}

void FormationOebius001::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius001::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("pOebius->pKurokoLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pOebius->getKuroko());
    }
    double rate_z = pOebius->pKurokoLeader_->_pManufacture->_rate_z;

    //Z = (prm_col*(0.4+0.4))*rate_z  //基本間隔は0.4。本編隊はmobius1.dat、mobius3.dat、mobius5.dat と一つ飛びなので0.4+0.4
    //(0, 0, Z) を Rz > Ry 回転移動させると
    //(Z*sinRy, 0, Z*cosRy)
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);
    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._43;
    float Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。

    coord dx = Z*sinRy;
    coord dy = 0;
    coord dz = Z*cosRy;
    pOebius->pKurokoLeader_->fixStartPosition(entry_pos_.x + dx,
                                              entry_pos_.y + dy,
                                              entry_pos_.z + dz);
    pOebius->pKurokoLeader_->fixStartAngle(entry_pos_.rx, entry_pos_.rz, entry_pos_.ry);


    pOebius->setPosition( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                          RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                          RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pOebius->setFaceAngTwd(entry_pos_.x + dx,
                           entry_pos_.y + dy,
                           entry_pos_.z + dz);
    pOebius->getKuroko()->setMvAngByFaceAng();
    pOebius->getKuroko()->setMvVelo(0);
    pOebius->getKuroko()->setMvAcce(80);

    double r = RCNV(0, getFormationColNum()                      , prm_col         , 0.3, 1.0);
    double g = RCNV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.3, 1.0);
    double b = RCNV(0, getFormationRowNum()                      , prm_row         , 0.3, 1.0);
    pOebius->setMaterialColor(r, g, b);
}

void FormationOebius001::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationOebius001::~FormationOebius001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

