#include "FormationOebius001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_CALL_UP ,
    PHASE_WAIT  ,
    PHASE_BANPEI,
};

FormationOebius001::FormationOebius001(const char* prm_name, EnemyOebiusController* prm_pController) :
        FormationOebius(prm_name, prm_pController, StatusReset(FormationOebius001)) {
    _class_name = "FormationOebius001";

    formation_col_num_ = 3;
    formation_row_num_ = 50;
    num_Oebius_ = formation_col_num_  * formation_row_num_;
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        appendFormationMember(NEW EnemyOebius(name.c_str()));
    }

    summon_row_idx_ = 0;

    papCurveManufConn_ = NEW CurveManufactureConnection*[formation_col_num_];
    for (int col = 0; col < formation_col_num_; col++) {
        papCurveManufConn_[col] = connectToCurveManufactureManager(("FormationOebius001,"+XTOS(col)).c_str());
    }
    FixedFrameCurveManufacture* Manuf =  ((FixedFrameCurveManufacture*)(papCurveManufConn_[0])->peek());
    frame spent_frames = Manuf->getSpentFrames();
    pa_frame_of_summon_ = NEW frame[formation_row_num_];
    for (int row = 0; row < formation_row_num_; row++) {
        //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
        pa_frame_of_summon_[row] = (frame)( ( (1.0*spent_frames*(1+row))  /  formation_row_num_)  ) + 1;
    }

}
void FormationOebius001::onActive() {
    summon_row_idx_ = 0;
    getPhase()->reset(PHASE_INIT);
}
void FormationOebius001::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_CALL_UP: {
            if (pPhase->hasJustChanged()) {
            }
            if (summon_row_idx_ < formation_row_num_) {
                if (pPhase->getFrame() == pa_frame_of_summon_[summon_row_idx_]) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        EnemyOebius* pOebius = (EnemyOebius*)summonMember();
                        if (pOebius) {
                            onSummon(pOebius, summon_row_idx_, col);
                        }
                    }
                    summon_row_idx_ ++;
                }
            } else {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_WAIT: {
            if (pPhase->hasJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

void FormationOebius001::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pVehicleLeader_) {
        throwCriticalException("pOebius->pVehicleLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pVehicleLeader_ = pOebius->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
//    double rate_z = pOebius->pVehicleLeader_->_pManufacture->_rate_z;
//
//    //Z = (prm_col*(0.4+0.4))*rate_z  //基本間隔は0.4。本編隊はmobius1.spl、mobius3.spl、mobius5.spl と一つ飛びなので0.4+0.4
//    //(0, 0, Z) を Rz > Ry 回転移動させると
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(_ry);
//    float cosRy = ANG_COS(_ry);
//    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._43;
//    float Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。
//
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pOebius->pVehicleLeader_->setStartPosition(_x + dx,
//                                               _y + dy,
//                                               _z + dz);
    pOebius->pVehicleLeader_->setStartPosition(_x, _y, _z);
    pOebius->pVehicleLeader_->setStartAngle(_rx, _ry, _rz);
    pOebius->setPositionAround(_x, _y, _z, PX_C(700));
    pOebius->setFaceAngTwd(pOebius->_x + (pOebius->_x - _x),
                           pOebius->_y + (pOebius->_y - _y),
                           pOebius->_z + (pOebius->_z - _z) );
    pOebius->getLocusVehicle()->setMvAngByFaceAng();
    pOebius->getLocusVehicle()->setMvVelo(0);
    pOebius->getLocusVehicle()->setMvAcce(80);

//    float sr = ANG_SIN(RCNV(0, formation_row_num_ , prm_row , D0ANG, D360ANG));
//    float sg = ANG_COS(RCNV(0, formation_row_num_ , prm_row , D0ANG, D360ANG));
//    float sb = ANG_SIN(RCNV(0, formation_col_num_ , prm_col , D0ANG, D360ANG));
//
//    double r = RCNV(-1.0, 1.0, sr, 0.2, 1.1);
//    double g = RCNV(-1.0, 1.0, sg, 0.2, 1.1);
//    double b = RCNV(-1.0, 1.0, sb, 0.2, 1.1);

    double r = RCNV(0, formation_col_num_                    , prm_col         , 0.3, 1.0);
    double g = RCNV(0, formation_col_num_*formation_row_num_ , prm_col*prm_row , 0.3, 1.0);
    double b = RCNV(0, formation_row_num_                    , prm_row         , 0.3, 1.0);

    pOebius->setMaterialColor(r, g, b);
}

void FormationOebius001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationOebius001::~FormationOebius001() {
    for (int col = 0; col < formation_col_num_; col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
    GGAF_DELETEARR(pa_frame_of_summon_);
}

