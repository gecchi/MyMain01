#include "FormationErelman002.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};


FormationErelman002::FormationErelman002(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name,  prm_pController) {
    _class_name = "FormationErelman002";
    formation_col_num_ = 6;
    formation_row_num_ = 200;
    num_Erelman_ = formation_col_num_ * formation_row_num_;
    call_up_cnt_ = 0;
    papa_frame_of_call_up_ = NEW frame*[formation_col_num_];
    pa_spent_frames_ = NEW frame[formation_col_num_];
    pa_call_up_row_idx_ = NEW int[formation_col_num_];
    papSplManufConn_ = NEW SplineManufactureConnection*[formation_col_num_];

    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        appendFormationMember(NEW EnemyErelman(name.c_str()));
    }

    for (int col = 0; col < formation_col_num_; col++) {
        papa_frame_of_call_up_[col] = NEW frame[formation_row_num_];
        pa_call_up_row_idx_[col] = 0;
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationErelman002,"+XTOS(col)).c_str());
        FixedFrameSplineManufacture* Manuf =  ((FixedFrameSplineManufacture*)(papSplManufConn_[col])->peek());
        pa_spent_frames_[col] = Manuf->getSpentFrames();
    }

    for (int col = 0; col < formation_col_num_; col++) {
        for (int row = 0; row < formation_row_num_; row++) {
            //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
            papa_frame_of_call_up_[col][row] = (frame)( ( (1.0*pa_spent_frames_[col]*(1+row))  /  formation_row_num_)  ) + 1;
        }
    }
    useProgress(PROG_BANPEI);
}
void FormationErelman002::onActive() {
    getProgress()->reset(PROG_INIT);
}
void FormationErelman002::processBehavior() {
    FormationErelman::processBehavior();

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {
            }
            if (call_up_cnt_ < num_Erelman_) {
                frame f = pProg->getFrame();
                for (int col = 0; col < formation_col_num_; col++) {
                    if (f == papa_frame_of_call_up_[col][pa_call_up_row_idx_[col]]) {
                        EnemyErelman* pErelman = (EnemyErelman*)callUpMember();
                        if (pErelman) {
                            onCallUp(pErelman, pa_call_up_row_idx_[col], col);
                        }
                        call_up_cnt_++;
                        pa_call_up_row_idx_[col]++;
                    }
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_WAIT: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

void FormationErelman002::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pKurokoLeader_) {
        throwCriticalException("pErelman->pKurokoLeader_が設定されてます。pErelman="<<pErelman<<"("<<pErelman->getName()<<")");
    } else {
        pErelman->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pErelman->getKuroko());
    }
    pErelman->pKurokoLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pErelman->pKurokoLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pErelman->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(100));
    pErelman->setFaceAngTwd(pErelman->_x + (pErelman->_x - geo_.x),
                            pErelman->_y + (pErelman->_y - geo_.y),
                            pErelman->_z + (pErelman->_z - geo_.z) );
    pErelman->getKuroko()->setMvAngByFaceAng();
    pErelman->getKuroko()->setMvVelo(0);
    pErelman->getKuroko()->setMvAcce(80);

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
        papSplManufConn_[col]->close();
        frame* p = papa_frame_of_call_up_[col];
        GGAF_DELETEARR(p);
    }
    GGAF_DELETEARR(papSplManufConn_);
    GGAF_DELETEARR(papa_frame_of_call_up_);
    GGAF_DELETEARR(pa_spent_frames_);
    GGAF_DELETEARR(pa_call_up_row_idx_);
}

