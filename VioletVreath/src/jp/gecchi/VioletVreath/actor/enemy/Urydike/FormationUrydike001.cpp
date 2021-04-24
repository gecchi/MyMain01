#include "FormationUrydike001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike001::FormationUrydike001(const char* prm_name) :
//        FormationUrydike(prm_name, 9, 256, 8) {
    FormationUrydike(prm_name, 1, 300, 1) {
    _class_name = "FormationUrydike001";

    papCurveManufConn_ = NEW CurveManufactureConnection*[getFormationColNum()];
    papCurveManufConn_[0] = connectToCurveManufactureManager("FormationUrydike001_STEP,0");
//    papCurveManufConn_[1] = connectToCurveManufactureManager("FormationUrydike001,1");
//    papCurveManufConn_[2] = connectToCurveManufactureManager("FormationUrydike001,2");
//    papCurveManufConn_[3] = connectToCurveManufactureManager("FormationUrydike001,3");
//    papCurveManufConn_[4] = connectToCurveManufactureManager("FormationUrydike001,4");
//    papCurveManufConn_[5] = connectToCurveManufactureManager("FormationUrydike001,5");
//    papCurveManufConn_[6] = connectToCurveManufactureManager("FormationUrydike001,6");
//    papCurveManufConn_[7] = connectToCurveManufactureManager("FormationUrydike001,7");
//    papCurveManufConn_[8] = connectToCurveManufactureManager("FormationUrydike001");
}

void FormationUrydike001::processBehavior() {
    FormationUrydike::processBehavior();
}

void FormationUrydike001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pDriverLeader_) {
        throwCriticalException("pUrydike->pDriverLeader_���ݒ肳��Ă܂��BpUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        pUrydike->pDriverLeader_ = papCurveManufConn_[prm_col]->peek()->
                                     createVecDriverLeader(pUrydike->getVecDriver());
    }
    double rate_x = pUrydike->pDriverLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._41; //���Ƃ̊Ԋu
    float X = d_col*rate_x; //rate_x���|���邱�Ƃɂ��A������ X ��coord�̒P�ʂƂȂ�B

    float sinRz = ANG_SIN(entry_pos_.rz);
    float cosRz = ANG_COS(entry_pos_.rz);
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) �� Rz > Ry ��]�ړ��������
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pUrydike->pDriverLeader_->setStartPosition(entry_pos_.x + dx,
                                               entry_pos_.y + dy,
                                               entry_pos_.z + dz);
    pUrydike->pDriverLeader_->setStartAngle(entry_pos_.rx, entry_pos_.ry, entry_pos_.rz);


    pUrydike->setPosition( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                           RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                           RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(entry_pos_.x + dx,
                            entry_pos_.y + dy,
                            entry_pos_.z + dz);
    pUrydike->getVecDriver()->setMvAngByFaceAng();
    pUrydike->getVecDriver()->setMvVelo(0);
    pUrydike->getVecDriver()->setMvAcce(80);

//    double r = RCNV(0, getFormationColNum()                      , prm_col         , 0.3, 1.0);
//    double g = RCNV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.3, 1.0);
//    double b = RCNV(0, getFormationRowNum()                      , prm_row         , 0.3, 1.0);
//    pUrydike->setMaterialColor(r, g, b);
}

void FormationUrydike001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationUrydike001::~FormationUrydike001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
}

