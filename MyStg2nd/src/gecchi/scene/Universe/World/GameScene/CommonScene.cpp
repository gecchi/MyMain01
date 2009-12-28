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
        getLordActor()->addSubGroup(KIND_MY_BODY, _pMyShip);
        _pMyShip->inactivateImmediately(); //�z���ɉ��o�^�̃A�N�^�[�����҂Ƃ����邵
    }


    { //EnemyShot001
        _pDispatcher_EnemyShots001 = NEW ActorDispatcher("TAMAS001");
        getLordActor()->addSubGroup(KIND_ENEMY_SHOT_GU, _pDispatcher_EnemyShots001);
        EnemyCeresShot001* pEnemyShot;
        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
            pEnemyShot->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EnemyShots001->addSubLast(pEnemyShot);
        }
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion001 = NEW ActorDispatcher("RotExplo001");
        getLordActor()->addSubGroup(KIND_EFFECT, _pDispatcher_EffectExplosion001);
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 512; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EffectExplosion001->addSubLast(pEffectExplosion);
        }
    }

}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {
}

CommonScene::~CommonScene() {
}
