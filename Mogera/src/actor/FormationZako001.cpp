#include <actor/FormationZako001.h>

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "MgrGod.h"
#include "actor/Zako.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"

#include "jp/ggaf/lib/util/spline/SplineSource.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

FormationZako001::FormationZako001(const char* prm_name) :
        FormationZako(prm_name) {
    _class_name = "FormationZako001";

    int col = 1;

    papSplManufConn_ = NEW SplineManufactureConnection*[col];
    papSplManufConn_[0] = getConnection_SplineManufactureManager("FormationZako001_STEP/0");
//    papSplManufConn_[1] = getConnection_SplineManufactureManager("FormationZako001/1");
//    papSplManufConn_[2] = getConnection_SplineManufactureManager("FormationZako001/2");
//    papSplManufConn_[3] = getConnection_SplineManufactureManager("FormationZako001/3");
//    papSplManufConn_[4] = getConnection_SplineManufactureManager("FormationZako001/4");
//    papSplManufConn_[5] = getConnection_SplineManufactureManager("FormationZako001/5");
//    papSplManufConn_[6] = getConnection_SplineManufactureManager("FormationZako001/6");
//    papSplManufConn_[7] = getConnection_SplineManufactureManager("FormationZako001/7");
//    papSplManufConn_[8] = getConnection_SplineManufactureManager("FormationZako001");

    int num = 1;//papSplManufConn_[0]->peek()->_pSplSrc->_pSp->_rnum;
    createMember(col, num, 1);
}

void FormationZako001::processBehavior() {
    FormationZako::processBehavior();
}

void FormationZako001::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    Zako* pZako = (Zako*)prm_pActor;
    if (pZako->pKurokoLeader_) {
        throwGgafCriticalException("FormationZako001::onCallUp pZako->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpZako="<<pZako<<"("<<pZako->getName()<<")");
    } else {
        pZako->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                     createKurokoLeader(pZako->getKuroko());
    }
    double rate_x = pZako->pKurokoLeader_->_pManufacture->_rate_x;
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
    pZako->pKurokoLeader_->fixStartPosition(entry_pos_.x + dx,
                                            entry_pos_.y + dy,
                                            entry_pos_.z + dz);
    pZako->pKurokoLeader_->fixStartMvAngle(entry_pos_.rz, entry_pos_.ry);

    pZako->position(entry_pos_.x + dx,
                    entry_pos_.y + dy,
                    entry_pos_.z + dz );
    pZako->setFaceAngTwd(entry_pos_.rz,
                         entry_pos_.ry,
                         0);
    pZako->getKuroko()->setMvAngByFaceAng();
}

void FormationZako001::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationZako001::~FormationZako001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

