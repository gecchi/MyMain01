#include "FormationErelman001.h"

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


FormationErelman001::FormationErelman001(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name,  prm_pController) {
    _class_name = "FormationErelman001";
    formation_col_num_ = 4;
    formation_row_num_ = 130;
    call_up_cnt_ = 0;
    call_up_row_idx_ = 0;
    pa_frame_of_call_up_ = NEW frame[formation_row_num_];


    num_Erelman_ = formation_col_num_  * formation_row_num_;
    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        appendFormationMember(NEW EnemyErelman(name.c_str()));
    }

    papSplManufConn_ = NEW SplineManufactureConnection*[formation_col_num_];
    for (int col = 0; col < formation_col_num_; col++) {
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationErelman001,"+XTOS(col)).c_str());
    }

    FixedFrameSplineManufacture* Manuf =  ((FixedFrameSplineManufacture*)(papSplManufConn_[0])->peek());
    spent_frames_ = Manuf->getSpentFrames();
//    double call_up_interval_ = spent_frames / formation_row_num_;  //出現間隔

    for (int row = 0; row < formation_row_num_; row++) {
        //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
//        pa_frame_of_call_up_[row] = ((spent_frames / formation_row_num_) + (spent_frames / formation_row_num_)*row    ) + 1;
        pa_frame_of_call_up_[row] = (frame)( ( (1.0*spent_frames_*(1+row))  /  formation_row_num_)  ) + 1;
    }
    useProgress(PROG_BANPEI);
}
void FormationErelman001::onActive() {
    getProgress()->reset(PROG_INIT);
}
void FormationErelman001::processBehavior() {
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
            if (call_up_row_idx_ < formation_row_num_) {
                if (pProg->getFrame() == pa_frame_of_call_up_[call_up_row_idx_]) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        EnemyErelman* pErelman = (EnemyErelman*)callUpMember();
                        if (pErelman) {
                            onCallUp(pErelman, call_up_row_idx_, col);
                        }
                    }
                    call_up_row_idx_++;
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

void FormationErelman001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
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
    pErelman->setMaterialColor(2, 2, 2);
}

void FormationErelman001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationErelman001::~FormationErelman001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

