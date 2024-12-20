#include "FormationErelman003.h"

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


FormationErelman003::FormationErelman003(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name,  prm_pController, StatusReset(FormationErelman003)) {
    _class_name = "FormationErelman003";
    formation_col_num_ = 10;
    formation_row_num_ = 140;
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
        papCurveManufConn_[col] = connectToCurveManufactureManager(("FormationErelman003,"+XTOS(col)).c_str());
        FixedFrameCurveManufacture* Manuf = ((FixedFrameCurveManufacture*)(papCurveManufConn_[col])->peek());
        pa_spent_frames_[col] = Manuf->getSpentFrames();
    }

//    速度     距離
//     1/2 → 2倍
//     1/3 → 3倍
//     2/3 → 3/2倍
//
//     3/5 (意味：1.0 - (2/5))   →  5/3 倍
//     1/5 (意味：1.0 - (2/5)*2) →  5 倍
    pa_spent_frames_[0] *= 1.0;       //順☆
    pa_spent_frames_[1] *= (5.0/3.0); //順 速度  3/5
    pa_spent_frames_[2] *= 5.0;       //順 速度  1/5
    pa_spent_frames_[3] *= 5.0;       //逆 速度 -1/5
    pa_spent_frames_[4] *= (5.0/3.0); //逆 速度 -3/5
    pa_spent_frames_[5] *= 1.0;       //逆☆
    pa_spent_frames_[6] *= (5.0/3.0); //逆 速度 -3/5
    pa_spent_frames_[7] *= 5.0;       //逆 速度 -1/5
    pa_spent_frames_[8] *= 5.0;       //順 速度  1/5
    pa_spent_frames_[9] *= (5.0/3.0); //順 速度  3/5
    for (int col = 0; col < formation_col_num_; col++) {
        FixedFrameCurveManufacture* pManuf =  ((FixedFrameCurveManufacture*)(papCurveManufConn_[col])->peek());
        pManuf->recalculateBySpentFrame(pa_spent_frames_[col]);
    }
    for (int col = 0; col < formation_col_num_; col++) {
        for (int row = 0; row < formation_row_num_; row++) {
            //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
            papa_frame_of_summon_[col][row] = (frame)( ( (1.0*pa_spent_frames_[col]*(1+row))  /  formation_row_num_)  ) + 1;
        }
    }
}

void FormationErelman003::onActive() {
    getPhase()->reset(PHASE_INIT);
}

void FormationErelman003::processBehavior() {
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

void FormationErelman003::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pVehicleLeader_) {
        throwCriticalException("pErelman->pVehicleLeader_が設定されてます。pErelman="<<pErelman<<"("<<pErelman->getName()<<")");
    } else {
        pErelman->pVehicleLeader_ = pErelman->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
    pErelman->pVehicleLeader_->setStartPosition(_x, _y, _z);
    pErelman->pVehicleLeader_->setStartAngle(_rx, _ry, _rz);
    pErelman->setPositionAround(_x, _y, _z, PX_C(100));
//    pErelman->setFaceAngTwd(pErelman->_x + (pErelman->_x - _x),
//                            pErelman->_y + (pErelman->_y - _y),
//                            pErelman->_z + (pErelman->_z - _z) );
//    pErelman->getLocusVehicle()->setMvAngByFaceAng();

    pErelman->getLocusVehicle()->setMvAngTwd(pErelman->_x + (pErelman->_x - _x),
                                       pErelman->_y + (pErelman->_y - _y),
                                       pErelman->_z + (pErelman->_z - _z) );
    pErelman->getLocusVehicle()->setMvVelo(0);
    pErelman->getLocusVehicle()->setMvAcce(80);

//    if (prm_row == 0) {
//        pErelman->setMaterialColor(1, 1, 1);
//    } else {
//        pErelman->setMaterialColor(1, 1, 0.5);
//    }

    double r = RCNV(0, getFormationColNum()                      , prm_col         , 0.8, 1.5);
    double g = RCNV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.8, 1.5);
    double b = RCNV(0, getFormationRowNum()                      , prm_row         , 0.8, 1.5);
    pErelman->setMaterialColor(r, g, b);
}

void FormationErelman003::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

void FormationErelman003::freeMenber(frame prm_free_interval) {
    EnemyErelman* pErelman = (EnemyErelman*)getChildFirst();
    while (pErelman) {
        pErelman->setFreeInterval(prm_free_interval);
        if (pErelman->isLast()) {
            break;
        } else {
            pErelman = (EnemyErelman*)(pErelman->getNext());
        }
    }
}

FormationErelman003::~FormationErelman003() {
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

