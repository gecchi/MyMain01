#include "FormationZako001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"

#include "MgrCaretaker.h"
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

void FormationZako001::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    Zako* pZako = (Zako*)prm_pActor;
    if (pZako->pVehicleLeader_) {
        throwCriticalException("pZako->pVehicleLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpZako="<<pZako<<"("<<pZako->getName()<<")");
    } else {
        pZako->pVehicleLeader_ = pZako->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    double rate_x = pZako->pVehicleLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._41; //â°Ç∆ÇÃä‘äu
    float X = d_col*rate_x; //rate_xÇä|ÇØÇÈÇ±Ç∆Ç…ÇÊÇËÅAÇ±Ç±Ç≈ X ÇÕcoordÇÃíPà Ç∆Ç»ÇÈÅB

    double sinRz = ANG_SIN(entry_pos_.rz);
    double cosRz = ANG_COS(entry_pos_.rz);
    double sinRy = ANG_SIN(entry_pos_.ry);
    double cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) Ç Rz > Ry âÒì]à⁄ìÆÇ≥ÇπÇÈÇ∆
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pZako->pVehicleLeader_->setStartPosition(entry_pos_.x + dx,
                                            entry_pos_.y + dy,
                                            entry_pos_.z + dz);
    pZako->pVehicleLeader_->setStartAngle(0, entry_pos_.rz, entry_pos_.ry);

    pZako->setPosition(entry_pos_.x + dx,
                       entry_pos_.y + dy,
                       entry_pos_.z + dz );
    pZako->setFaceAngTwd(entry_pos_.rz,
                         entry_pos_.ry,
                         0);
    pZako->getLocusVehicle()->setMvAngByFaceAng();
}

void FormationZako001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationZako001::~FormationZako001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
}

