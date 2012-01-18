#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationMassalia::FormationMassalia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationMassalia";
    _pDepoCon_Massalia = connectToDepositoryManager("DpCon_Massalia", this);
    _pDepoCon_Fragment = connectToDepositoryManager("DpCon_MassaliaFragment", this);
    _pDepoCon_Fragment2 = connectToDepositoryManager("DpCon_MassaliaFragment2", this);
    _pDepoCon_Fragment3 = connectToDepositoryManager("DpCon_MassaliaFragment3", this);


    setFormationAbleActorDepository(_pDepoCon_Massalia->use());
}

void FormationMassalia::updateRankParameter() {
    _R_interval_frames   = R_FormationMassalia_LaunchInterval; //ŠÔŠu
    _R_mv_velo           = R_FormationMassalia_MvVelo;         //‘¬“x
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
    _pDepoCon_Fragment->close();
    _pDepoCon_Fragment2->close();
    _pDepoCon_Fragment3->close();
}
