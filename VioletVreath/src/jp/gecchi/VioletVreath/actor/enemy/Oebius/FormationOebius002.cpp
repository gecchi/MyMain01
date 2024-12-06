#include "FormationOebius002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/core/util/Xpm.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
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

FormationOebius002::FormationOebius002(const char* prm_name, EnemyOebiusController* prm_pController) :
        FormationOebius(prm_name, prm_pController, StatusReset(FormationOebius002)) {
    _class_name = "FormationOebius002";

    pXpmCon_ = connectToXpmManager("FormationOebius002_Xpm");
    GgafCore::Xpm* pXpM = pXpmCon_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Oebius_ = pXpM->getPixelNum();
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        appendFormationMember(NEW EnemyOebius(name.c_str()));
        Sleep(1);
    }

    papCurveManufConn_ = NEW CurveManufactureConnection*[formation_col_num_];
    for (int col = 0; col < formation_col_num_; col++) {
        papCurveManufConn_[col] = connectToCurveManufactureManager(("FormationOebius002,"+XTOS(col)).c_str());
    }
    FixedFrameCurveManufacture* Manuf =  ((FixedFrameCurveManufacture*)(papCurveManufConn_[0])->peek());


    //スプライン座標はは、メビウスなんで、２週分ある
    //でも、列が偶数本（８列）なんで、２週しない。
    //編隊の長さを半分にする。（＝出現間隔半分）
    //    frame spent_frames = Manuf->getSpentFrames();
    double spent_frames = Manuf->getSpentFrames() / 2.0;

    pa_frame_of_summon_ = NEW frame[formation_row_num_];
    for (int row = 0; row < formation_row_num_; row++) {
        //出現フレーム(最後の +1は getFrame() が 1フレームから始まる為
        //pa_frame_of_summon_[row] = (frame)( ( (1.0*spent_frames*(1+row))  /  formation_row_num_)  ) + 1;
        pa_frame_of_summon_[row] = (frame)( ( (1.0*spent_frames*(1+row))  /  formation_row_num_)  ) + 1;
    }
    summon_row_idx_ = 0;

}
void FormationOebius002::onActive() {
    summon_row_idx_ = 0;
    getPhase()->reset(PHASE_INIT);
}
void FormationOebius002::processBehavior() {
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
                        //xpm編隊
                        if (!pXpmCon_->peek()->isNonColor(summon_row_idx_, col)) {
                            EnemyOebius* pOebius = (EnemyOebius*)summonMember();
                            if (pOebius) {
                                onSummon(pOebius, summon_row_idx_, col);
                            }
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

void FormationOebius002::onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pVehicleLeader_) {
        throwCriticalException("pOebius->pVehicleLeader_が設定されてます。pOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pVehicleLeader_ = pOebius->createCurveVehicleLeader(papCurveManufConn_[prm_col]->peek());
    }
//    double rate_z = pOebius->pVehicleLeader_->_pManufacture->_rate_z; //MAG_Z=100000
//
//    //Z = (prm_col*0.4)*rate_z //0.4は隣の列との間隔
//    //(0, 0, Z) を Rz > Ry 回転移動させると
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(geo_.ry);
//    float cosRy = ANG_COS(geo_.ry);
//    double d_col = -1.0 * papCurveManufConn_[prm_col]->peek()->_pCurve->_rotmat._43;
//    dxcoord Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。(ようにMAG_X,MAG_Y,MAG_Zを設定してある）
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pOebius->pVehicleLeader_->setStartPosition(geo_.x + dx,
//                                              geo_.y + dy,
//                                              geo_.z + dz);
    pOebius->pVehicleLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pOebius->pVehicleLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pOebius->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(700));
    pOebius->setFaceAngTwd(pOebius->_x + (pOebius->_x - geo_.x),
                           pOebius->_y + (pOebius->_y - geo_.y),
                           pOebius->_z + (pOebius->_z - geo_.z) );
    pOebius->getLocusVehicle()->setMvAngByFaceAng();
    pOebius->getLocusVehicle()->setMvVelo(0);
    pOebius->getLocusVehicle()->setMvAcce(80);

    //色を設定
    GgafCore::Xpm* pXpM = pXpmCon_->peek();
    pOebius->setMaterialColor(pXpM->getColor(prm_row, prm_col));
}

void FormationOebius002::onFinshLeading(GgafDx::FigureActor* prm_pActor) {

}

FormationOebius002::~FormationOebius002() {
    if (pXpmCon_) {
        pXpmCon_->close();
    }
    for (int col = 0; col < formation_col_num_; col++) {
        papCurveManufConn_[col]->close();
    }
    GGAF_DELETEARR(papCurveManufConn_);
    GGAF_DELETEARR(pa_frame_of_summon_);
}

