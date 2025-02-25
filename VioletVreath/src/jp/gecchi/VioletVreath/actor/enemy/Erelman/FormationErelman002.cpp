#include "FormationErelman002.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_CALL_UP ,
    PHASE_WAIT  ,
    PHASE_BANPEI,
};


FormationErelman002::FormationErelman002(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name,  prm_pController, StatusReset(FormationErelman002)) {
    _class_name = "FormationErelman002";
    formation_col_num_ = 6;
    formation_row_num_ = 200;
    num_Erelman_ = formation_col_num_ * formation_row_num_;
    summon_cnt_ = 0;
    papa_frame_of_summon_ = NEW frame*[formation_col_num_];
    pa_spent_frames_ = NEW frame[formation_col_num_];
    pa_summon_row_idx_ = NEW int[formation_col_num_];
    papCurveManufConn_ = NEW CurveManufactureConnection*[formation_col_num_];

    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        appendFormationMember(NEW EnemyErelman(name.c_str()));
    }

    for (int col = 0; col < formation_col_num_; col++) {
        papa_frame_of_summon_[col] = NEW frame[formation_row_num_];
        pa_summon_row_idx_[col] = 0;
        papCurveManufConn_[col] = connectToCurveManufactureManager(("FormationErelman002,"+XTOS(col)).c_str());
        FixedFrameCurveManufacture* Manuf =  ((FixedFrameCurveManufacture*)(papCurveManufConn_[col])->peek());
        pa_spent_frames_[col] = Manuf->getSpentFrames();
    }

    for (int col = 0; col < formation_col_num_; col++) {
        for (int row = 0; row < formation_row_num_; row++) {
            //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
            papa_frame_of_summon_[col][row] = (frame)( ( (1.0*pa_spent_frames_[col]*(1+row))  /  formation_row_num_)  ) + 1;
        }
    }
}
void FormationErelman002::onActive() {
    getPhase()->reset(PHASE_INIT);
}
void FormationErelman002::processBehavior() {
    FormationErelman::processBehavior();

    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_CALL_UP: {
            if (pPhase->hasJustChanged()) {
            }
            if (summon_cnt_ < num_Erelman_) {
                frame f = pPhase->getFrame();
                for (int col = 0; col < formation_col_num_; col++) {
                    if (f == papa_frame_of_summon_[col][pa_summon_row_idx_[col]]) {
                        EnemyErelman* pErelman = (EnemyErelman*)summonMember();
                        if (pErelman) {
                            onSummon(pErelman, pa_summon_row_idx_[col], col);
                        }
                        summon_cnt_++;
                        pa_summon_row_idx_[col]++;
                    }
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

void FormationErelman002::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pVehicleLeader_) {
        throwCriticalException("pErelman->pVehicleLeader_が設定されてます。pErelman="<<pErelman<<"("<<pErelman->getName()<<")");
    } else {
        pErelman->pVehicleLeader_ = pErelman->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    pErelman->pVehicleLeader_->setStartPosition(_x, _y, _z);
    pErelman->pVehicleLeader_->setStartAngle(_rx, _ry, _rz);
    pErelman->setPositionAround(_x, _y, _z, PX_C(100));
    pErelman->setFaceAngTwd(pErelman->_x + (pErelman->_x - _x),
                            pErelman->_y + (pErelman->_y - _y),
                            pErelman->_z + (pErelman->_z - _z) );
    pErelman->getLocusVehicle()->setMvAngByFaceAng();
    pErelman->getLocusVehicle()->setMvVelo(0);
    pErelman->getLocusVehicle()->setMvAcce(80);

//    float sr = ANG_SIN(RCNV(0, getFormationRowNum() , prm_row , D0ANG, D360ANG));
//    float sg = ANG_COS(RCNV(0, getFormationRowNum() , prm_row , D0ANG, D360ANG));
//    float sb = ANG_SIN(RCNV(0, getFormationColNum() , prm_col , D0ANG, D360ANG));
//
//    double r = RCNV(-1.0, 1.0, sr, 0.2, 1.1);
//    double g = RCNV(-1.0, 1.0, sg, 0.2, 1.1);
//    double b = RCNV(-1.0, 1.0, sb, 0.2, 1.1);

//    double r = RCNV(0, getFormationColNum()                      , prm_col         , 0.5, 1.5);
//    double g = RCNV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.5, 1.5);
//    double b = RCNV(0, getFormationRowNum()                      , prm_row         , 0.5, 1.5);
//    pErelman->setMaterialColor(r, g, b);
    if (prm_row % 20) {
        pErelman->setMaterialColor(1, 0.6, 0.6);
    } else {
        pErelman->setMaterialColor(0.6, 1, 1);
    }
}

void FormationErelman002::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationErelman002::~FormationErelman002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papCurveManufConn_[col]->close();
        frame* p = papa_frame_of_summon_[col];
        GGAF_DELETEARR(p);
    }
    GGAF_DELETEARR(papCurveManufConn_);
    GGAF_DELETEARR(papa_frame_of_summon_);
    GGAF_DELETEARR(pa_spent_frames_);
    GGAF_DELETEARR(pa_summon_row_idx_);
}

