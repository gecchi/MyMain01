#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres002::FormationCeres002(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres002";
//    pDepo_EnemyMeshShots001_ = NEW GgafActorDepository("FmtCeres002RotEnemyMeshS001_");
//    EnemyCeresShot001* pShot;
//    for (int i = 0; i < 30; i++) { //弾ストック
//        Sleep(1);
//        pShot = NEW EnemyCeresShot001("EnemyMeshShot");
//        pShot->inactivateImmed(); //最初非表示
//        pDepo_EnemyMeshShots001_->addSubLast(pShot);
//    }

    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        Sleep(1);
        pEnemyCeres_[i] = NEW EnemyCeres("Ceres01");
        pEnemyCeres_[i]->inactivate();
        pEnemyCeres_[i]->Y_turn_ = -1*(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2) + (i * ((GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002));
        pEnemyCeres_[i]->_Z = -1500000;
        addSubLast(pEnemyCeres_[i] );
    }


//    addSubGroup(pDepo_EnemyMeshShots001_);
}

void FormationCeres002::initialize() {
    //出現予約
    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        pEnemyCeres_[i]->activateDelay(i * 80 + 1);
    }
}

FormationCeres002::~FormationCeres002() {
}
