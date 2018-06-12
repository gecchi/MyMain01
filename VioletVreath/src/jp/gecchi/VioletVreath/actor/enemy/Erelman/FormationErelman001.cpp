#include "FormationErelman001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    formation_row_num_ = 120;
    call_up_interval_base_ = 10; //出現間隔
    call_up_cnt_ = 0;
    pa_call_up_interval_ = NEW frame[formation_col_num_];
    pa_call_up_row_idx_ = NEW int[formation_col_num_];

    num_Erelman_ = formation_col_num_  * formation_row_num_;
    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        addFormationMember(NEW EnemyErelman(name.c_str()));
    }

    papSplManufConn_ = NEW SplineManufactureConnection*[formation_col_num_];
    for (int col = 0; col < formation_col_num_; col++) {
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationErelman001/"+XTOS(col)).c_str());
        FixedFrameSplineManufacture* Manuf =  ((FixedFrameSplineManufacture*)(papSplManufConn_[col])->peek());
        frame spent_frames = Manuf->getSpentFrames();
        double rate = RCNV(0.0, formation_col_num_-1, col ,1.0, 1.0);
        Manuf->recalculateBySpentFrame(spent_frames * rate);
        pa_call_up_interval_[col] = call_up_interval_base_ * rate;
        pa_call_up_row_idx_[col] = 0;

    }
    useProgress(PROG_BANPEI);
}
void FormationErelman001::onActive() {
    call_up_cnt_ = 0;
    getProgress()->reset(PROG_INIT);
}
void FormationErelman001::processBehavior() {
    FormationErelman::processBehavior();

    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {
            }

            for (int col = 0; col < formation_col_num_; col++) {
                if (canCallUp() && call_up_cnt_ < num_Erelman_) {
                    if (getActiveFrame() % pa_call_up_interval_[col] == 0) {
                        EnemyErelman* pErelman = (EnemyErelman*)callUpMember();
                        if (pErelman) {
                            onCallUp(pErelman, pa_call_up_row_idx_[col], col);
                        }
                        call_up_cnt_ ++;
                        pa_call_up_row_idx_[col] ++;
                    }
                } else {
                   pProg->changeNext();
                   break;
               }
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

void FormationErelman001::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pKurokoLeader_) {
        throwGgafCriticalException("pErelman->pKurokoLeader_が設定されてます。pErelman="<<pErelman<<"("<<pErelman->getName()<<")");
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

void FormationErelman001::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationErelman001::~FormationErelman001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
    GGAF_DELETEARR(pa_call_up_interval_);
    GGAF_DELETEARR(pa_call_up_row_idx_);
}

