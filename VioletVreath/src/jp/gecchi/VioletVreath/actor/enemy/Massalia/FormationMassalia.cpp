#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationMassalia::FormationMassalia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationMassalia";
    pDepoConnection_Massalia_ = connectToDepositoryManager("Massalia");
    pDepoConnection_Fragment_ = connectToDepositoryManager("MassaliaFragment");
    pDepoConnection_Fragment_2_ = connectToDepositoryManager("MassaliaFragment2");
    pDepoConnection_Fragment_3_ = connectToDepositoryManager("MassaliaFragment3");


    setFormationMemberDepo(pDepoConnection_Massalia_->peek());
}

void FormationMassalia::updateRankParameter() {
    R_interval_frames_   = RR_FormationMassalia_LaunchInterval(_RANK_); //ŠÔŠu
    R_mv_velo_           = RR_FormationMassalia_MvVelo(_RANK_);         //‘¬“x
}

void FormationMassalia::initialize() {

}

void FormationMassalia::onActive() {
    updateRankParameter();
}

void FormationMassalia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationMassalia::processBehavior() {
    updateRankParameter();
    if (getActiveFrame() >= RR_FormationMassalia_DurationFrames(_RANK_)) {
        sayonara(20*60);
    } else {
        if (canCallUp() && (getActiveFrame() % R_interval_frames_ == 0)) {
            EnemyMassalia* pMassalia = (EnemyMassalia*)callUpMember();
            if (pMassalia) {
                pMassalia->_pKurokoA->setMvVelo(R_mv_velo_);
            }
        }
    }
}

FormationMassalia::~FormationMassalia() {
    pDepoConnection_Massalia_->close();
    pDepoConnection_Fragment_->close();
    pDepoConnection_Fragment_2_->close();
    pDepoConnection_Fragment_3_->close();
}
