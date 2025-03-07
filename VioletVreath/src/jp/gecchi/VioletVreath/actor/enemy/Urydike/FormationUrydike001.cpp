#include "FormationUrydike001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike001::FormationUrydike001(const char* prm_name) :
//        FormationUrydike(prm_name, 9, 256, 8) {
    FormationUrydike(prm_name, 1, 300, 1, StatusReset(FormationUrydike001)) {
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

void FormationUrydike001::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pVehicleLeader_) {
        throwCriticalException("pUrydike->pVehicleLeader_が設定されてます。pUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        pUrydike->pVehicleLeader_ = pUrydike->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    double rate_x = pUrydike->pVehicleLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._41; //横との間隔
    float X = d_col*rate_x; //rate_xを掛けることにより、ここで X はcoordの単位となる。

    double sinRz = ANG_SIN(_rz);
    double cosRz = ANG_COS(_rz);
    double sinRy = ANG_SIN(_ry);
    double cosRy = ANG_COS(_ry);

    //(X,0,0) を Rz > Ry 回転移動させると
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pUrydike->pVehicleLeader_->setStartPosition(_x + dx,
                                                _y + dy,
                                                _z + dz);
    pUrydike->pVehicleLeader_->setStartAngle(_rx, _ry, _rz);


    pUrydike->setPosition( RND_ABOUT(_x + dx, PX_C(700)),
                           RND_ABOUT(_y + dy, PX_C(700)),
                           RND_ABOUT(_z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(_x + dx,
                            _y + dy,
                            _z + dz);
    pUrydike->getLocusVehicle()->setMvAngByFaceAng();
    pUrydike->getLocusVehicle()->setMvVelo(0);
    pUrydike->getLocusVehicle()->setMvAcce(80);

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

