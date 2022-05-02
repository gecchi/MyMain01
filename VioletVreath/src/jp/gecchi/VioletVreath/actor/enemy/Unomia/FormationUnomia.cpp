#include "FormationUnomia.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_CALL_UP ,
    PHASE_WAIT1,
    PHASE_SHOT,
    PHASE_WAIT2,
    PHASE_BANPEI,
};

FormationUnomia::FormationUnomia(const char* prm_name, const char* prm_ldr_id)
   : TreeFormation(prm_name, 20*60) {
    _class_name = "FormationUnomia";
    num_formation_col_ = 0;
    num_formation_row_ = 0;
    num_formation_member_ = 0;
    launch_interval_   = 0;
    mv_velo_           = 0;
    //�Ȑ��ړ��̏��t�@�C����ǂݍ���
    pConn_pCurveManuf_ = connectToCurveManufactureManager(prm_ldr_id);
    pDepo_shot_ = CommonScene_getDepository(Shot004);


    int col_num = RF_FormationUnomia001_Col(G_MAX_RANK);
    int row_num = RF_FormationUnomia001_Num(G_MAX_RANK);
    for (int row = 0; row < row_num; row++ ) {
        for (int col = 0; col < col_num; col++ ) {
            std::string name = "EnemyUnomia"+XTOS(row)+"_"+XTOS(col);
            EnemyUnomia* pEnemyUnomia = NEW EnemyUnomia(name.c_str());
            appendFormationMember(pEnemyUnomia);
        }
    }
}

void FormationUnomia::updateRankParameter() {

    num_formation_member_ = num_formation_col_*num_formation_row_;
}

void FormationUnomia::initialize() {
    getPhase()->reset(PHASE_INIT);
//    if (pConn_depo_Unomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_depo_Unomia_ �́A���V(this="<<NODE_INFO<<")����Ă��G�w���I")
//        getPlatformScene()->bringSceneMediator()->appendGroupChild(
//                pConn_depo_Unomia_->peek()->extract()
//                );
//    }
}

void FormationUnomia::onActive() {
    num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //�ґ���
    num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //�P��̕ґ���
    num_formation_member_ = num_formation_col_ * num_formation_row_;
    launch_interval_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //�E�[�m�~�A�̊Ԋu(frame)
    mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //���x
}

void FormationUnomia::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
   GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_CALL_UP: {
            if (canCalledUp()) {
                if (getActiveFrame() % launch_interval_ == 0) {
                    for (int col = 0; col < num_formation_col_; col++) {
                        EnemyUnomia* pUnomia = (EnemyUnomia*)calledUpMember(num_formation_member_);
                        if (pUnomia) {
                            pUnomia->config(pConn_pCurveManuf_->peek(), nullptr, nullptr);
                            pUnomia->getVecVehicle()->setMvVelo(mv_velo_);
                            onCalledUpUnomia(pUnomia, col); //�t�H�[���[�V�����ʎ����̏���
                        }
                    }
                }
            } else {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_WAIT1: {
            if (pPhase->hasArrivedFrameAt(1200)) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_SHOT: {
            MyShip* pMy = pMYSHIP;
            GgafCore::Actor* pFollower = getChildFirst();
            while(true) {
                EnemyUnomia* pUnomia =  (EnemyUnomia*)pFollower;
                if (pUnomia->isActive()) {
                    GgafDx::GeometricActor* pShot = (GgafDx::GeometricActor*)pDepo_shot_->dispatch();
                    if (pShot) {
                        pShot->setPositionAt(pUnomia);
                        GgafDx::VecVehicle* pShot_pVecVehicle = pShot->getVecVehicle();
                        pShot_pVecVehicle->setMvAngTwd(pMy);
                        pShot_pVecVehicle->setMvVelo(PX_C(10));
                        pShot_pVecVehicle->setMvAcce(0);
                    }
                }
                if (pFollower->isLast()) {
                    break;
                }
                pFollower = pFollower->getNext();
            }
            pPhase->changeNext();
            break;
        }
        case PHASE_WAIT2: {
            //�����܂�
            break;
        }
        default :
            break;
    }
}

FormationUnomia::~FormationUnomia() {
    pConn_pCurveManuf_->close();
}

