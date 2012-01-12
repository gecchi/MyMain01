#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationMassalia::FormationMassalia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationMassalia";
    _pDepoCon_Massalia = connectDepositoryManager("DpCon_Massalia", this);
    setFormationAbleActorDepository(_pDepoCon_Massalia->use());
}

void FormationMassalia::updateRankParameter() {
    _R_interval_frames   = R_FormationMassalia_LaunchInterval; //�Ԋu
    _R_mv_velo           = R_FormationMassalia_MvVelo;         //���x
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
    if (getActivePartFrame() >= R_FormationMassalia_DurationFreams) {
        sayonara(20*60);
    } else {
        if (!isAllCalledUp() && (getActivePartFrame() % _R_interval_frames == 0)) {
            EnemyMassalia* pMassalia = (EnemyMassalia*)callUpUntil();
            if (pMassalia) {
                pMassalia->_pKurokoA->setMvVelo(_R_mv_velo);
            }
        }
    }
}

FormationMassalia::~FormationMassalia() {
    _pDepoCon_Massalia->close();
}
