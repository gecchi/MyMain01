#include "FormationOebius001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/ggaf/dx/util/spline/SplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/ggaf/dx/util/spline/FixedFrameSplineManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};

FormationOebius001::FormationOebius001(const char* prm_name, EnemyOebiusController* prm_pController) :
        FormationOebius(prm_name, prm_pController) {
    _class_name = "FormationOebius001";

    formation_col_num_ = 3;
    formation_row_num_ = 50;
    num_Oebius_ = formation_col_num_  * formation_row_num_;
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        appendFormationMember(NEW EnemyOebius(name.c_str()));
    }

    call_up_row_idx_ = 0;

    papSplManufConn_ = NEW SplineManufactureConnection*[formation_col_num_];
    for (int col = 0; col < formation_col_num_; col++) {
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationOebius001,"+XTOS(col)).c_str());
    }
    FixedFrameSplineManufacture* Manuf =  ((FixedFrameSplineManufacture*)(papSplManufConn_[0])->peek());
    frame spent_frames = Manuf->getSpentFrames();
    pa_frame_of_call_up_ = NEW frame[formation_row_num_];
    for (int row = 0; row < formation_row_num_; row++) {
        //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
        pa_frame_of_call_up_[row] = (frame)( ( (1.0*spent_frames*(1+row))  /  formation_row_num_)  ) + 1;
    }

}
void FormationOebius001::onActive() {
    call_up_row_idx_ = 0;
    getProgress()->reset(PROG_INIT);
}
void FormationOebius001::processBehavior() {
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
                        EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                        if (pOebius) {
                            onCallUp(pOebius, call_up_row_idx_, col);
                        }
                    }
                    call_up_row_idx_ ++;
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

void FormationOebius001::onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pVecDriverLeader_) {
        throwCriticalException("pOebius->pVecDriverLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pVecDriverLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createVecDriverLeader(pOebius->callVecDriver());
    }
//    double rate_z = pOebius->pVecDriverLeader_->_pManufacture->_rate_z;
//
//    //Z = (prm_col*(0.4+0.4))*rate_z  //基本間隔は0.4。本編隊はmobius1.dat、mobius3.dat、mobius5.dat と一つ飛びなので0.4+0.4
//    //(0, 0, Z) を Rz > Ry 回転移動させると
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(geo_.ry);
//    float cosRy = ANG_COS(geo_.ry);
//    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_pSpl->_rotmat._43;
//    float Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。
//
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pOebius->pVecDriverLeader_->setStartPosition(geo_.x + dx,
//                                              geo_.y + dy,
//                                              geo_.z + dz);
    pOebius->pVecDriverLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pOebius->pVecDriverLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pOebius->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(700));
    pOebius->setFaceAngTwd(pOebius->_x + (pOebius->_x - geo_.x),
                           pOebius->_y + (pOebius->_y - geo_.y),
                           pOebius->_z + (pOebius->_z - geo_.z) );
    pOebius->callVecDriver()->setMvAngByFaceAng();
    pOebius->callVecDriver()->setMvVelo(0);
    pOebius->callVecDriver()->setMvAcce(80);

//    float sr = ANG_SIN(RCNV(0, formation_row_num_ , prm_row , D0ANG, D360ANG));
//    float sg = ANG_COS(RCNV(0, formation_row_num_ , prm_row , D0ANG, D360ANG));
//    float sb = ANG_SIN(RCNV(0, formation_col_num_ , prm_col , D0ANG, D360ANG));
//
//    double r = RCNV(-1.0, 1.0, sr, 0.2, 1.1);
//    double g = RCNV(-1.0, 1.0, sg, 0.2, 1.1);
//    double b = RCNV(-1.0, 1.0, sb, 0.2, 1.1);

    double r = RCNV(0, formation_col_num_                      , prm_col         , 0.3, 1.0);
    double g = RCNV(0, formation_col_num_*formation_row_num_ , prm_col*prm_row , 0.3, 1.0);
    double b = RCNV(0, formation_row_num_                      , prm_row         , 0.3, 1.0);

    pOebius->setMaterialColor(r, g, b);
}

void FormationOebius001::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationOebius001::~FormationOebius001() {
    for (int col = 0; col < formation_col_num_; col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
    GGAF_DELETEARR(pa_frame_of_call_up_);
}

