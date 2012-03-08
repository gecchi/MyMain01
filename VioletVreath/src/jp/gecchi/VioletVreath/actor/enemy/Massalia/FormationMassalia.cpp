#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationMassalia::FormationMassalia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationMassalia";
    pDepoCon_Massalia_ = connectToDepositoryManager("DpCon_Massalia", this);
    pDepoCon_Fragment_ = connectToDepositoryManager("DpCon_MassaliaFragment", this);
    pDepoCon_Fragment_2_ = connectToDepositoryManager("DpCon_MassaliaFragment2", this);
    pDepoCon_Fragment_3_ = connectToDepositoryManager("DpCon_MassaliaFragment3", this);


    setFormationAbleActorDepository(pDepoCon_Massalia_->use());
}

void FormationMassalia::updateRankParameter() {
    R_interval_frames_   = R_FormationMassalia_LaunchInterval; //ŠÔŠu
    R_mv_velo_           = R_FormationMassalia_MvVelo;         //‘¬“x
}

void FormationMassalia::initialize() {

}

void FormationMassalia::onActive() {
    updateRankParameter();
}

void FormationMassalia::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
}

void FormationMassalia::processBehavior() {
    updateRankParameter();
    if (getActivePartFrame() >= R_FormationMassalia_DurationFrames) {
        sayonara(20*60);
    } else {
        if (!isAllCalledUp() && (getActivePartFrame() % R_interval_frames_ == 0)) {
            EnemyMassalia* pMassalia = (EnemyMassalia*)callUpUntil();
            if (pMassalia) {
                pMassalia->_pKurokoA->setMvVelo(R_mv_velo_);
            }
        }
    }
}

FormationMassalia::~FormationMassalia() {
    pDepoCon_Massalia_->close();
    pDepoCon_Fragment_->close();
    pDepoCon_Fragment_2_->close();
    pDepoCon_Fragment_3_->close();
}
