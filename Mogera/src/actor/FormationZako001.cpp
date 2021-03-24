#include "FormationZako001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/ggaf/dx/util/spline/SplineManufacture.h"
#include "jp/ggaf/dx/util/spline/SplineSource.h"

#include "MgrGod.h"
#include "Zako.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

FormationZako001::FormationZako001(const char* prm_name) :
        FormationZako(prm_name) {
    _class_name = "FormationZako001";

    int col = 1;

    papSplManufConn_ = NEW SplineManufactureConnection*[col];
    papSplManufConn_[0] = connectToSplineManufactureManager("FormationZako001_STEP,0");
//    papSplManufConn_[1] = connectToSplineManufactureManager("FormationZako001,1");
//    papSplManufConn_[2] = connectToSplineManufactureManager("FormationZako001,2");
//    papSplManufConn_[3] = connectToSplineManufactureManager("FormationZako001,3");
//    papSplManufConn_[4] = connectToSplineManufactureManager("FormationZako001,4");
//    papSplManufConn_[5] = connectToSplineManufactureManager("FormationZako001,5");
//    papSplManufConn_[6] = connectToSplineManufactureManager("FormationZako001,6");
//    papSplManufConn_[7] = connectToSplineManufactureManager("FormationZako001,7");
//    papSplManufConn_[8] = connectToSplineManufactureManager("FormationZako001");

    int num = 1;//papSplManufConn_[0]->peek()->_pSplSrc->_pSp->_rnum;
    addMember(col, num, 1);
}

void FormationZako001::processBehavior() {
    FormationZako::processBehavior();
}

void FormationZako001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    Zako* pZako = (Zako*)prm_pActor;
    if (pZako->pVecDriverLeader_) {
        throwCriticalException("pZako->pVecDriverLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpZako="<<pZako<<"("<<pZako->getName()<<")");
    } else {
        pZako->pVecDriverLeader_ = papSplManufConn_[prm_col]->peek()->
                                     createVecDriverLeader(pZako->callVecDriver());
    }
    double rate_x = pZako->pVecDriverLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_pSpl->_rotmat._41; //â°Ç∆ÇÃä‘äu
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
    pZako->pVecDriverLeader_->setStartPosition(entry_pos_.x + dx,
                                            entry_pos_.y + dy,
                                            entry_pos_.z + dz);
    pZako->pVecDriverLeader_->setStartAngle(0, entry_pos_.rz, entry_pos_.ry);

    pZako->setPosition(entry_pos_.x + dx,
                       entry_pos_.y + dy,
                       entry_pos_.z + dz );
    pZako->setFaceAngTwd(entry_pos_.rz,
                         entry_pos_.ry,
                         0);
    pZako->callVecDriver()->setMvAngByFaceAng();
}

void FormationZako001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationZako001::~FormationZako001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

