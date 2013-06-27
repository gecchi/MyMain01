#include "stdafx.h"
#include "FormationMassalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassalia.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationMassalia::FormationMassalia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationMassalia";
    pDepoConnection_Massalia_ = connect_DepositoryManager("Massalia");
    pDepoConnection_Fragment_ = connect_DepositoryManager("MassaliaFragment");
    pDepoConnection_Fragment_2_ = connect_DepositoryManager("MassaliaFragment2");
    pDepoConnection_Fragment_3_ = connect_DepositoryManager("MassaliaFragment3");


    setFormationMember(pDepoConnection_Massalia_->peek());
}

void FormationMassalia::updateRankParameter() {
    R_interval_frames_   = RF_FormationMassalia_LaunchInterval(G_RANK); //�Ԋu
    R_mv_velo_           = RF_FormationMassalia_MvVelo(G_RANK);         //���x
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
    if (getActiveFrame() >= RF_FormationMassalia_DurationFrames(G_RANK)) {
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
