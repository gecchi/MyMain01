#include "FormationEmilia.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmilia.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationEmilia::FormationEmilia(const char* prm_name)
   : DefaultGeometricActor(prm_name) {
    _class_name = "FormationEmilia";
    pConn_depo_Fragment3_ = connectToDepositoryManager("EmiliaFragment3");
    pConn_depo_Fragment2_ = connectToDepositoryManager("EmiliaFragment2");
    pConn_depo_Fragment_ = connectToDepositoryManager("EmiliaFragment");
    pConn_depo_Emilia_ = connectToDepositoryManager("Emilia");
    R_interval_frames_   = RF_FormationEmilia_LaunchInterval(G_RANK); //ä‘äu
    R_num_ =  RF_EnemyEmilia_ShotWay(G_RANK);
}

void FormationEmilia::updateRankParameter() {
    R_interval_frames_   = RF_FormationEmilia_LaunchInterval(G_RANK); //ä‘äu
    R_num_ =  RF_EnemyEmilia_ShotWay(G_RANK);
}

void FormationEmilia::initialize() {

}

void FormationEmilia::onActive() {
    updateRankParameter();
}

void FormationEmilia::processBehavior() {
    if (getActiveFrame() >= RF_FormationEmilia_DurationFrames(G_RANK)) { //èoåªÇµë±ÇØÇÈéûä‘
        sayonara(SEC_F(180));
    } else {
        if (getActiveFrame() % R_interval_frames_ == 0) {
            EnemyEmilia* pEmilia = (EnemyEmilia*)(pConn_depo_Emilia_->peek()->dispatch());
            if (pEmilia) {
                pEmilia->onDispatched(nullptr, this);
            }
        }
    }
}
void FormationEmilia::appearFragment(EnemyEmiliaBase* prm_pOrg) {
    updateRankParameter();
    //ífï–èoåª
    for (int i = 0; i < R_num_; i++) {
        EnemyEmiliaBase* pFragment = (EnemyEmiliaBase*)pConn_depo_Fragment_->peek()->dispatch();
        if (pFragment) {
            pFragment->onDispatched(prm_pOrg, this);
        }
    }
}
void FormationEmilia::appearFragment2(EnemyEmiliaBase* prm_pOrg) {
    updateRankParameter();
    //ífï–ÇÃífï–èoåª
    for (int i = 0; i < R_num_; i++) {
        EnemyEmiliaBase* pFragment = (EnemyEmiliaBase*)pConn_depo_Fragment2_->peek()->dispatch();
        if (pFragment) {
            pFragment->onDispatched(prm_pOrg, this);
        }
    }
}
void FormationEmilia::appearFragment3(EnemyEmiliaBase* prm_pOrg) {
    updateRankParameter();
    //ífï–ÇÃífï–ÇÃífï–èoåª
    for (int i = 0; i < R_num_; i++) {
        EnemyEmiliaBase* pFragment = (EnemyEmiliaBase*)pConn_depo_Fragment3_->peek()->dispatch();
        if (pFragment) {
            pFragment->onDispatched(prm_pOrg, this);
        }
    }
}
FormationEmilia::~FormationEmilia() {
    pConn_depo_Fragment3_->close();
    pConn_depo_Fragment2_->close();
    pConn_depo_Fragment_->close();
    pConn_depo_Emilia_->close();
}
