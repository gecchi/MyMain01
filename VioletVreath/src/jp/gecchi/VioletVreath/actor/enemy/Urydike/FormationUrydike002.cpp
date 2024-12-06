#include "FormationUrydike002.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"
#include "jp/ggaf/core/util/Xpm.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike002::FormationUrydike002(const char* prm_name) :
        FormationUrydike(prm_name, "FormationUrydike002_Xpm", 8, StatusReset(FormationUrydike002)) {
    _class_name = "FormationUrydike002";

    papCurveManufConn_ = NEW CurveManufactureConnection*[getFormationColNum()];
    papCurveManufConn_[0] = connectToCurveManufactureManager("FormationUrydike002,0");
    papCurveManufConn_[1] = connectToCurveManufactureManager("FormationUrydike002,1");
    papCurveManufConn_[2] = connectToCurveManufactureManager("FormationUrydike002,2");
    papCurveManufConn_[3] = connectToCurveManufactureManager("FormationUrydike002,3");
    papCurveManufConn_[4] = connectToCurveManufactureManager("FormationUrydike002,4");
    papCurveManufConn_[5] = connectToCurveManufactureManager("FormationUrydike002,5");
    papCurveManufConn_[6] = connectToCurveManufactureManager("FormationUrydike002,6");
    papCurveManufConn_[7] = connectToCurveManufactureManager("FormationUrydike002,7");
    papCurveManufConn_[8] = connectToCurveManufactureManager("FormationUrydike002,8");
}

void FormationUrydike002::processBehavior() {
    FormationUrydike::processBehavior();
}

void FormationUrydike002::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pVehicleLeader_) {
        throwCriticalException("pUrydike->pVehicleLeader_が設定されてます。pUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        pUrydike->pVehicleLeader_ = pUrydike->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    double rate_x = pUrydike->pVehicleLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._41; //横との間隔
    float X = d_col*rate_x; //rate_xを掛けることにより、ここで X はcoordの単位となる。

    double sinRz = ANG_SIN(entry_pos_.rz);
    double cosRz = ANG_COS(entry_pos_.rz);
    double sinRy = ANG_SIN(entry_pos_.ry);
    double cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) を Rz > Ry 回転移動させると
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pUrydike->pVehicleLeader_->setStartPosition(entry_pos_.x + dx,
                                               entry_pos_.y + dy,
                                               entry_pos_.z + dz);
    pUrydike->pVehicleLeader_->setStartAngle(entry_pos_.rx, entry_pos_.ry, entry_pos_.rz);

    pUrydike->setPosition( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                           RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                           RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(entry_pos_.x + dx,
                            entry_pos_.y + dy,
                            entry_pos_.z + dz);
    pUrydike->getLocusVehicle()->setMvAngByFaceAng();
    pUrydike->getLocusVehicle()->setMvVelo(0);
    pUrydike->getLocusVehicle()->setMvAcce(80);

    //色を設定
    GgafCore::Xpm* pXpM = pXpmCon_->peek();
    pUrydike->setMaterialColor(pXpM->getColor(prm_row, prm_col));
}

void FormationUrydike002::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationUrydike002::~FormationUrydike002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
}

