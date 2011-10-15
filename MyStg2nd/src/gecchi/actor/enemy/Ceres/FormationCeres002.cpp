#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationCeres002::FormationCeres002(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres002";
//    _pDepo_EnemyMeshShots001 = NEW GgafActorDepository("FmtCeres002_RotEnemyMeshS001");
//    EnemyCeresShot001* pShot;
//    for (int i = 0; i < 30; i++) { //弾ストック
//        Sleep(1);
//        pShot = NEW EnemyCeresShot001("EnemyMeshShot");
//        pShot->inactivateImmediately(); //最初非表示
//        _pDepo_EnemyMeshShots001->addSubLast(pShot);
//    }

    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        Sleep(1);
        _pEnemyCeres[i] = NEW EnemyCeres("Ceres01");
        _pEnemyCeres[i]->inactivate();
        _pEnemyCeres[i]->_Y_turn = -1*(CFG_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2) + (i * ((CFG_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002));
        _pEnemyCeres[i]->_veloBegin = 5000;
        _pEnemyCeres[i]->_Z = -1500000;
        addSubLast(_pEnemyCeres[i] );
    }


//    addSubGroup(_pDepo_EnemyMeshShots001);
}

void FormationCeres002::initialize() {
    //出現予約
    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        _pEnemyCeres[i]->activateDelay(i * 80 + 1);
    }
}

FormationCeres002::~FormationCeres002() {
}
