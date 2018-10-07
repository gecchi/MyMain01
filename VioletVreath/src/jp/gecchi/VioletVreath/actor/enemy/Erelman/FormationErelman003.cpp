#include "FormationErelman003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
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


FormationErelman003::FormationErelman003(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name,  prm_pController) {
    _class_name = "FormationErelman003";
    formation_col_num_ = 10;
    formation_row_num_ = 140;
    num_Erelman_ = formation_col_num_ * formation_row_num_;
    call_up_cnt_ = 0;
    papa_frame_of_call_up_ = NEW frame*[formation_col_num_];
    pa_spent_frames_ = NEW frame[formation_col_num_];
    pa_call_up_row_idx_ = NEW int[formation_col_num_];
    papSplManufConn_ = NEW SplineManufactureConnection*[formation_col_num_];

    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        addFormationMember(NEW EnemyErelman(name.c_str()));
    }

    for (int col = 0; col < formation_col_num_; col++) {
        papa_frame_of_call_up_[col] = NEW frame[formation_row_num_];
        pa_call_up_row_idx_[col] = 0;
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationErelman003/"+XTOS(col)).c_str());
        FixedFrameSplineManufacture* Manuf = ((FixedFrameSplineManufacture*)(papSplManufConn_[col])->peek());
        pa_spent_frames_[col] = Manuf->getSpentFrames();
    }

//    ���x     ����
//     1/2 �� 2�{
//     1/3 �� 3�{
//     2/3 �� 3/2�{
//
//     3/5 (�Ӗ��F1.0 - (2/5))   ��  5/3 �{
//     1/5 (�Ӗ��F1.0 - (2/5)*2) ��  5 �{
    pa_spent_frames_[0] *= 1.0;       //����
    pa_spent_frames_[1] *= (5.0/3.0); //�� ���x  3/5
    pa_spent_frames_[2] *= 5.0;       //�� ���x  1/5
    pa_spent_frames_[3] *= 5.0;       //�t ���x -1/5
    pa_spent_frames_[4] *= (5.0/3.0); //�t ���x -3/5
    pa_spent_frames_[5] *= 1.0;       //�t��
    pa_spent_frames_[6] *= (5.0/3.0); //�t ���x -3/5
    pa_spent_frames_[7] *= 5.0;       //�t ���x -1/5
    pa_spent_frames_[8] *= 5.0;       //�� ���x  1/5
    pa_spent_frames_[9] *= (5.0/3.0); //�� ���x  3/5
    for (int col = 0; col < formation_col_num_; col++) {
        FixedFrameSplineManufacture* pManuf =  ((FixedFrameSplineManufacture*)(papSplManufConn_[col])->peek());
        pManuf->recalculateBySpentFrame(pa_spent_frames_[col]);
    }
    for (int col = 0; col < formation_col_num_; col++) {
        for (int row = 0; row < formation_row_num_; row++) {
            //�o���t���[��(�Ō�� +1�� getFrame() �� 1�t���[������n�܂��
            papa_frame_of_call_up_[col][row] = (frame)( ( (1.0*pa_spent_frames_[col]*(1+row))  /  formation_row_num_)  ) + 1;
        }
    }
    useProgress(PROG_BANPEI);
}

void FormationErelman003::onActive() {
    getProgress()->reset(PROG_INIT);
}

void FormationErelman003::processBehavior() {
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

void FormationErelman003::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pKurokoLeader_) {
        throwGgafCriticalException("pErelman->pKurokoLeader_���ݒ肳��Ă܂��BpErelman="<<pErelman<<"("<<pErelman->getName()<<")");
    } else {
        pErelman->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pErelman->getKuroko());
    }
    pErelman->pKurokoLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pErelman->pKurokoLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pErelman->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(100));
//    pErelman->setFaceAngTwd(pErelman->_x + (pErelman->_x - geo_.x),
//                            pErelman->_y + (pErelman->_y - geo_.y),
//                            pErelman->_z + (pErelman->_z - geo_.z) );
//    pErelman->getKuroko()->setMvAngByFaceAng();

    pErelman->getKuroko()->setMvAngTwd(pErelman->_x + (pErelman->_x - geo_.x),
                                       pErelman->_y + (pErelman->_y - geo_.y),
                                       pErelman->_z + (pErelman->_z - geo_.z) );
    pErelman->getKuroko()->setMvVelo(0);
    pErelman->getKuroko()->setMvAcce(80);

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

void FormationErelman003::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

void FormationErelman003::freeMenber(frame prm_free_interval) {
    EnemyErelman* pErelman = (EnemyErelman*)getSubFirst();
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
        papSplManufConn_[col]->close();
        frame* p = papa_frame_of_call_up_[col];
        GGAF_DELETEARR(p);
    }
    GGAF_DELETEARR(papSplManufConn_);
    GGAF_DELETEARR(papa_frame_of_call_up_);
    GGAF_DELETEARR(pa_spent_frames_);
    GGAF_DELETEARR(pa_call_up_row_idx_);
}
