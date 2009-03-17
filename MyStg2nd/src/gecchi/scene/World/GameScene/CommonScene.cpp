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
        getLordActor()->accept(KIND_MY, _pMyShip);
        _pMyShip->inactImmediatelyAlone(); //�z���ɉ��o�^�̃��[�e�[�V�����Ƃ����邵Alone
    }

    { //EnemyShot001
        _pEnemyShots001Rotation = NEW RotationActor("TAMAS001");
        getLordActor()->accept(KIND_ENEMY_SHOT_GU, _pEnemyShots001Rotation);
        EnemyShot001* pEnemyShot;
        for (int i = 0; i < 1; i++) { //�X�g�b�N256��
            pEnemyShot = NEW EnemyShot001("EnemyShot001");
            pEnemyShot->inactImmediately(); //�ŏ���\��
            _pEnemyShots001Rotation->addSubLast(pEnemyShot);
        }
    }

    { //Effect EffectExplosion001
        _pEffectExplosion001Rotation = NEW RotationActor("RotExplo001");
        getLordActor()->accept(KIND_EFFECT, _pEffectExplosion001Rotation);
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 30; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactImmediately(); //�ŏ���\��
            _pEffectExplosion001Rotation->addSubLast(pEffectExplosion);
        }
    }

}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {
}

CommonScene::~CommonScene() {
}
