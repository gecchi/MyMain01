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
        throwGgafCriticalException("pOebius->pKurokoLeader_���ݒ肳��Ă܂��BpOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pOebius->getKuroko());
    }
//    double rate_z = pOebius->pKurokoLeader_->_pManufacture->_rate_z;
//
//    //Z = (prm_col*(0.4+0.4))*rate_z  //��{�Ԋu��0.4�B�{�ґ���mobius1.dat�Amobius3.dat�Amobius5.dat �ƈ��тȂ̂�0.4+0.4
//    //(0, 0, Z) �� Rz > Ry ��]�ړ��������
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(geo_.ry);
//    float cosRy = ANG_COS(geo_.ry);
//    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._43;
//    float Z = d_col*rate_z; //rate_z���|���邱�Ƃɂ��A������ Z ��coord�̒P�ʂƂȂ�B
//
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pOebius->pKurokoLeader_->setStartPosition(geo_.x + dx,
//                                              geo_.y + dy,
//                                              geo_.z + dz);
    pOebius->pKurokoLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pOebius->pKurokoLeader_->setStartAngle(geo_.rx, geo_.rz, geo_.ry);
    pOebius->setPosition( RND_ABOUT(geo_.x, PX_C(700)),
                          RND_ABOUT(geo_.y, PX_C(700)),
                          RND_ABOUT(geo_.z, PX_C(700)) );
    pOebius->setFaceAngTwd(geo_.x, geo_.y, geo_.z);
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

