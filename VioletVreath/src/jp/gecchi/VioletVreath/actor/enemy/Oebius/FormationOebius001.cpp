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
//    int col_num = getFormationColNum();
//    for (int col = 0; col < col_num; col++) {
//        SplineLine* sp = papSplManufConn_[col]->peek()->_sp;
//        sp->rotation(D_ANG(1.1), D_ANG(1.3), D_ANG(1.7));
//    }
}

void FormationOebius001::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("pOebius->pKurokoLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pOebius->getKuroko());
    }
//    double rate_z = pOebius->pKurokoLeader_->_pManufacture->_rate_z;
//
//    //Z = (prm_col*(0.4+0.4))*rate_z  //基本間隔は0.4。本編隊はmobius1.dat、mobius3.dat、mobius5.dat と一つ飛びなので0.4+0.4
//    //(0, 0, Z) を Rz > Ry 回転移動させると
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(geo_.ry);
//    float cosRy = ANG_COS(geo_.ry);
//    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._43;
//    float Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。
//
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pOebius->pKurokoLeader_->setStartPosition(geo_.x + dx,
//                                              geo_.y + dy,
//                                              geo_.z + dz);
    pOebius->pKurokoLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pOebius->pKurokoLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pOebius->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(700));
    pOebius->setFaceAngTwd(pOebius->_x - geo_.x,
                           pOebius->_y - geo_.y,
                           pOebius->_z - geo_.z);
    pOebius->getKuroko()->setMvAngByFaceAng();
    pOebius->getKuroko()->setMvVelo(0);
    pOebius->getKuroko()->setMvAcce(80);

//    float sr = ANG_SIN(RCNV(0, getFormationRowNum() , prm_row , D0ANG, D360ANG));
//    float sg = ANG_COS(RCNV(0, getFormationRowNum() , prm_row , D0ANG, D360ANG));
//    float sb = ANG_SIN(RCNV(0, getFormationColNum() , prm_col , D0ANG, D360ANG));
//
//    double r = RCNV(-1.0, 1.0, sr, 0.2, 1.1);
//    double g = RCNV(-1.0, 1.0, sg, 0.2, 1.1);
//    double b = RCNV(-1.0, 1.0, sb, 0.2, 1.1);

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

