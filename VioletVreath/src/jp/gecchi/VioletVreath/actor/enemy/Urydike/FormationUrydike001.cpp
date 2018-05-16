#include "FormationUrydike001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike001::FormationUrydike001(const char* prm_name) :
//        FormationUrydike(prm_name, 9, 256, 8) {
    FormationUrydike(prm_name, 1, 300, 1) {
    _class_name = "FormationUrydike001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    papSplManufConn_[0] = connectToSplineManufactureManager("FormationUrydike001_STEP/0");
//    papSplManufConn_[1] = connectToSplineManufactureManager("FormationUrydike001/1");
//    papSplManufConn_[2] = connectToSplineManufactureManager("FormationUrydike001/2");
//    papSplManufConn_[3] = connectToSplineManufactureManager("FormationUrydike001/3");
//    papSplManufConn_[4] = connectToSplineManufactureManager("FormationUrydike001/4");
//    papSplManufConn_[5] = connectToSplineManufactureManager("FormationUrydike001/5");
//    papSplManufConn_[6] = connectToSplineManufactureManager("FormationUrydike001/6");
//    papSplManufConn_[7] = connectToSplineManufactureManager("FormationUrydike001/7");
//    papSplManufConn_[8] = connectToSplineManufactureManager("FormationUrydike001");
}

void FormationUrydike001::processBehavior() {
    FormationUrydike::processBehavior();
}

void FormationUrydike001::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pKurokoLeader_) {
        throwGgafCriticalException("pUrydike->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        pUrydike->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                     createKurokoLeader(pUrydike->getKuroko());
    }
    double rate_x = pUrydike->pKurokoLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._41; //â°Ç∆ÇÃä‘äu
    float X = d_col*rate_x; //rate_xÇä|ÇØÇÈÇ±Ç∆Ç…ÇÊÇËÅAÇ±Ç±Ç≈ X ÇÕcoordÇÃíPà Ç∆Ç»ÇÈÅB

    float sinRz = ANG_SIN(entry_pos_.rz);
    float cosRz = ANG_COS(entry_pos_.rz);
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) Ç Rz > Ry âÒì]à⁄ìÆÇ≥ÇπÇÈÇ∆
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pUrydike->pKurokoLeader_->setStartPosition(entry_pos_.x + dx,
                                               entry_pos_.y + dy,
                                               entry_pos_.z + dz);
    pUrydike->pKurokoLeader_->setStartAngle(entry_pos_.rx, entry_pos_.rz, entry_pos_.ry);


    pUrydike->setPosition( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                           RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                           RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(entry_pos_.x + dx,
                            entry_pos_.y + dy,
                            entry_pos_.z + dz);
    pUrydike->getKuroko()->setMvAngByFaceAng();
    pUrydike->getKuroko()->setMvVelo(0);
    pUrydike->getKuroko()->setMvAcce(80);

//    double r = RCNV(0, getFormationColNum()                      , prm_col         , 0.3, 1.0);
//    double g = RCNV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.3, 1.0);
//    double b = RCNV(0, getFormationRowNum()                      , prm_row         , 0.3, 1.0);
//    pUrydike->setMaterialColor(r, g, b);
}

void FormationUrydike001::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationUrydike001::~FormationUrydike001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

