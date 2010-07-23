#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    GameGlobal::_pSceneCommon = this;

    { //MyShip
        _pMyShip = NEW MyShip("MYSHIP");
        _pMyShip->inactivateImmediately(); //�z���ɉ��o�^�̃A�N�^�[�����҂Ƃ����邵
        getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);
    }


    { //EnemyShot001
        _pDispatcher_EnemyShots001 = NEW GgafActorDispatcher("TAMAS001");
        EnemyCeresShot001* pEnemyShot;
        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
            pEnemyShot->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EnemyShots001->addSubLast(pEnemyShot);
        }
        getLordActor()->addSubGroup(_pDispatcher_EnemyShots001);
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion001 = NEW GgafActorDispatcher("RotExplo001");
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 256; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EffectExplosion001->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion001);
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion003 = NEW GgafActorDispatcher("RotExplo003");
        EffectExplosion003* pEffectExplosion;
        for (int i = 0; i < 100; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EffectExplosion003->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion003);
    }



    { //Effect EffectTurbo002 �^�[�{����
        _pDispatcher_EffectTurbo002 = NEW GgafActorDispatcher("RotExplo002");
        EffectTurbo002* pEffectTurbo;
        for (int i = 0; i < 256; i++) { //�X�g�b�N100��
            pEffectTurbo = NEW EffectTurbo002("EffectTurbo002");
            pEffectTurbo->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EffectTurbo002->addSubLast(pEffectTurbo);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectTurbo002);
    }

    {
        _pDispatcher_LaserChipDispatcher = NEW GgafActorDispatcher("LCDD");
        LaserChipDispatcher* pLaserChipDispatcher;
        EnemyAstraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 63; nLaser++) {
            stringstream name;
            name <<  "LaserChipDispatcher["<<nLaser<<"]";
            pLaserChipDispatcher = NEW LaserChipDispatcher(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
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
