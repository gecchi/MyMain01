#include "stdafx.h"
#include "FormationAssalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Assalia/EnemyAssalia.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAssalia::FormationAssalia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationAssalia";
    pDepoConnection_Assalia_ = connect_DepositoryManager("Assalia");
    pDepoConnection_Fragment_ = connect_DepositoryManager("AssaliaFragment");
    pDepoConnection_Fragment_2_ = connect_DepositoryManager("AssaliaFragment2");
    pDepoConnection_Fragment_3_ = connect_DepositoryManager("AssaliaFragment3");


    setFormationMember(pDepoConnection_Assalia_->peek());
}

void FormationAssalia::updateRankParameter() {
    R_interval_frames_   = RF_FormationAssalia_LaunchInterval(G_RANK); //ŠÔŠu
    R_mv_velo_           = RF_FormationAssalia_MvVelo(G_RANK);         //‘¬“x
}

void FormationAssalia::initialize() {

}

void FormationAssalia::onActive() {
    updateRankParameter();
}

void FormationAssalia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationAssalia::processBehavior() {
    updateRankParameter();
    if (getActiveFrame() >= RF_FormationAssalia_DurationFrames(G_RANK)) {
        sayonara(20*60);
    } else {
        if (canCallUp() && (getActiveFrame() % R_interval_frames_ == 0)) {
            EnemyAssalia* pAssalia = (EnemyAssalia*)callUpMember();
            if (pAssalia) {
                pAssalia->_pKurokoA->setMvVelo(R_mv_velo_);
            }
        }
    }
}

FormationAssalia::~FormationAssalia() {
    pDepoConnection_Assalia_->close();
    pDepoConnection_Fragment_->close();
    pDepoConnection_Fragment_2_->close();
    pDepoConnection_Fragment_3_->close();
}
