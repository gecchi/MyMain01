#include "FormationZako001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"

#include "MgrGod.h"
#include "Zako.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

FormationZako001::FormationZako001(const char* prm_name) :
        FormationZako(prm_name) {
    _class_name = "FormationZako001";

    int col = 1;

    papCurveManufConn_ = NEW CurveManufactureConnection*[col];
    papCurveManufConn_[0] = connectToCurveManufactureManager("FormationZako001_STEP,0");
//    papCurveManufConn_[1] = connectToCurveManufactureManager("FormationZako001,1");
//    papCurveManufConn_[2] = connectToCurveManufactureManager("FormationZako001,2");
//    papCurveManufConn_[3] = connectToCurveManufactureManager("FormationZako001,3");
//    papCurveManufConn_[4] = connectToCurveManufactureManager("FormationZako001,4");
//    papCurveManufConn_[5] = connectToCurveManufactureManager("FormationZako001,5");
//    papCurveManufConn_[6] = connectToCurveManufactureManager("FormationZako001,6");
//    papCurveManufConn_[7] = connectToCurveManufactureManager("FormationZako001,7");
//    papCurveManufConn_[8] = connectToCurveManufactureManager("FormationZako001");

    int num = 1;//papCurveManufConn_[0]->peek()->_pCurveSrc->_pSp->_rnum;
    addMember(col, num, 1);
}

void FormationZako001::processBehavior() {
    FormationZako::processBehavior();
}

void FormationZako001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    Zako* pZako = (Zako*)prm_pActor;
    if (pZako->pDriverLeader_) {
        throwCriticalException("pZako->pDriverLeader_が設定されてます。pZako="<<pZako<<"("<<pZako->getName()<<")");
    } else {
        pZako->pDriverLeader_ = papCurveManufConn_[prm_col]->peek()->
                                     createVecDriverLeader(pZako->getVecDriver());
    }
    double rate_x = pZako->pDriverLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._41; //横との間隔
    float X = d_col*rate_x; //rate_xを掛けることにより、ここで X はcoordの単位となる。

    float sinRz = ANG_SIN(entry_pos_.rz);
    float cosRz = ANG_COS(entry_pos_.rz);
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) を Rz > Ry 回転移動させると
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pZako->pDriverLeader_->setStartPosition(entry_pos_.x + dx,
                                            entry_pos_.y + dy,
                                            entry_pos_.z + dz);
    pZako->pDriverLeader_->setStartAngle(0, entry_pos_.rz, entry_pos_.ry);

    pZako->setPosition(entry_pos_.x + dx,
                       entry_pos_.y + dy,
                       entry_pos_.z + dz );
    pZako->setFaceAngTwd(entry_pos_.rz,
                         entry_pos_.ry,
                         0);
    pZako->getVecDriver()->setMvAngByFaceAng();
}

void FormationZako001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationZako001::~FormationZako001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
}

