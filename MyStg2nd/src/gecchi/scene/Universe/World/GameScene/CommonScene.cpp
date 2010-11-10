#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

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

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion003 = NEW GgafActorDispatcher("RotExplo003");
        EffectExplosion003* pEffectExplosion;
        for (int i = 0; i < 50; i++) { //ストック100個
            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
            pEffectExplosion->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectExplosion003->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion003);
    }



    { //Effect EffectTurbo002 ターボ噴射
        _pDispatcher_EffectTurbo002 = NEW GgafActorDispatcher("RotExplo002");
        EffectTurbo002* pEffectTurbo;
        for (int i = 0; i < 10; i++) { //ストック100個
            pEffectTurbo = NEW EffectTurbo002("EffectTurbo002");
            pEffectTurbo->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectTurbo002->addSubLast(pEffectTurbo);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectTurbo002);
    }

//    {
//        _pDispatcher_LaserChipDispatcher = NEW GgafActorDispatcher("LCDD");
//        LaserChipDispatcher* pLaserChipDispatcher;
//        EnemyAstraeaLaserChip002* pChip;
//        for (int nLaser = 0; nLaser < 27; nLaser++) {
//            stringstream name;
//            name <<  "LaserChipDispatcher["<<nLaser<<"]";
//            pLaserChipDispatcher = NEW LaserChipDispatcher(name.str().c_str());
//            for (int nChip = 0; nChip < 50; nChip++) {
//                stringstream name;
//                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
//                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
//                pChip->inactivateImmediately();
//                pLaserChipDispatcher->addSubLast(pChip);
//            }
//            pLaserChipDispatcher->inactivateImmediately();
//            _pDispatcher_LaserChipDispatcher->addSubLast(pLaserChipDispatcher);
//        }
//        getLordActor()->addSubGroup(_pDispatcher_LaserChipDispatcher);
//    }
}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {


}

CommonScene::~CommonScene() {
}
