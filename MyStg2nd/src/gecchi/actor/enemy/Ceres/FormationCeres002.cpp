﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationCeres002::FormationCeres002(const char* prm_name) : FormationActor(prm_name) {
    _class_name = "FormationCeres002";

    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        Sleep(1);
        _pEnemyCeres[i] = NEW EnemyCeres("Ceres01");
        _pEnemyCeres[i]->inactivate();
        _pEnemyCeres[i]->_Y_turn = -1*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) + (i * ((GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002));
        _pEnemyCeres[i]->_veloBegin = 5000;
        _pEnemyCeres[i]->_Z = -1500000;
        addSubLast(_pEnemyCeres[i] );
    }

    _pDispatcher_EnemyMeshShots001 = NEW GgafActorDispatcher("FmtCeres002_RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 30; i++) { //弾ストック
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivate(); //最初非表示
        _pDispatcher_EnemyMeshShots001->addSubLast(pEnemyMeshShot);
    }

    addSubGroup(_pDispatcher_EnemyMeshShots001);
}

void FormationCeres002::initialize() {
    //出現予約
    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        _pEnemyCeres[i]->activateAfter(i * 80 + 1);
    }
}

FormationCeres002::~FormationCeres002() {
}
