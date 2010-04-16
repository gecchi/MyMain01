﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    GameGlobal::_pSceneCommon = this;

    { //MyShip
        _pMyShip = NEW MyShip("MYSHIP");
        _pMyShip->inactivateImmediately(); //配下に仮登録のアクター発送者とかあるし
        getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);
    }


    { //EnemyShot001
        _pDispatcher_EnemyShots001 = NEW GgafActorDispatcher("TAMAS001");
        EnemyCeresShot001* pEnemyShot;
        for (int i = 0; i < 36*7; i++) { //ストック256個
            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
            pEnemyShot->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EnemyShots001->addSubLast(pEnemyShot);
        }
        getLordActor()->addSubGroup(_pDispatcher_EnemyShots001);
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion001 = NEW GgafActorDispatcher("RotExplo001");
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 256; i++) { //ストック100個
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectExplosion001->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion001);
    }

    {
        _pDispatcher_LaserChipDispatcher = NEW GgafActorDispatcher("LCDD");
        LaserChipDispatcher* pLaserChipDispatcher;
        EnemyAstraeaLaserChip001* pChip;
        for (int nLaser = 0; nLaser < 12; nLaser++) {
            stringstream name;
            name <<  "LaserChipDispatcher["<<nLaser<<"]";
            pLaserChipDispatcher = NEW LaserChipDispatcher(name.str().c_str());
            for (int nChip = 0; nChip < 30; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip001["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip001(name.str().c_str());
                pChip->inactivateImmediately();
                pLaserChipDispatcher->addSubLast(pChip);
            }
            pLaserChipDispatcher->inactivateImmediately();
            _pDispatcher_LaserChipDispatcher->addSubLast(pLaserChipDispatcher);
        }
        getLordActor()->addSubGroup(_pDispatcher_LaserChipDispatcher);
    }

}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {
}

CommonScene::~CommonScene() {
}
