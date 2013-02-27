#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres002::FormationCeres002(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres002";
//    pDepo_EnemyMeshShots001_ = NEW GgafActorDepository("FmtCeres002RotEnemyMeshS001_");
//    EnemyCeresShot001* pShot;
//    for (int i = 0; i < 30; i++) { //�e�X�g�b�N
//        Sleep(1);
//        pShot = NEW EnemyCeresShot001("EnemyMeshShot");
//        pShot->inactivateImmed(); //�ŏ���\��
//        pDepo_EnemyMeshShots001_->addSubLast(pShot);
//    }

    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        Sleep(1);
        pEnemyCeres_[i] = NEW EnemyCeres("Ceres01");
        pEnemyCeres_[i]->inactivate();
        pEnemyCeres_[i]->Y_turn_ = -1*(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2) + (i * ((PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT)/NUM_CERES_FORMATION002));
        pEnemyCeres_[i]->_Z = -1500000;
        addSubLast(pEnemyCeres_[i] );
    }


//    addSubGroup(pDepo_EnemyMeshShots001_);
}

void FormationCeres002::initialize() {
    //�o���\��
    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        pEnemyCeres_[i]->activateDelay(i * 80 + 1);
    }
}

void FormationCeres002::onDestroyedAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationCeres002::~FormationCeres002() {
}
