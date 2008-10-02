#include "stdafx.h"


CommonScene::CommonScene(string prm_name) : DefaultScene(prm_name) {
	GameGlobal::_pSceneCommon = this;

	{ //MyShip
		_pMyShip = NEW MyShip("MYSHIP", "ebi");
		getLordActor()->accept(KIND_MY, _pMyShip);
		_pMyShip->stopImmediately();
	}

	{ //MyShots001
		_pMyShots001Rotation = NEW RotationActor("RotShot001");
		getLordActor()->accept(KIND_MY, _pMyShots001Rotation);
		MyShot001* pShot;
		for (int i = 0; i < 50; i++) { //���e�X�g�b�N�R�O��
			pShot = NEW MyShot001("S1", "moji2");
			pShot->stopImmediately();
			_pMyShots001Rotation->addSubLast(pShot);
		}
	}

	{ //MyLaser001
		_pMyLaser001Rotation = NEW RotationActor("RotLaser001");
		getLordActor()->accept(KIND_MY, _pMyLaser001Rotation);
		MyLaser001* pLaser;
		for (int i = 0; i < 50; i++) { //���[�U�[�X�g�b�N�R�O��
			pLaser = NEW MyLaser001("L1", "MyLaser001");
			pLaser->stopImmediately();
			_pMyLaser001Rotation->addSubLast(pLaser);
		}
	}

	{ //EnemyShot001
		_pEnemyShots001Rotation = NEW RotationActor("TAMAS001");
		getLordActor()->accept(KIND_ENEMY, _pEnemyShots001Rotation);
		EnemyMyShot001* pEnemyShot;
		for (int i = 0; i < 256; i++) { //�X�g�b�N256��
			pEnemyShot = NEW EnemyMyShot001("EneShot001", "hoge");
			pEnemyShot->stopImmediately(); //�ŏ���\��
			_pEnemyShots001Rotation->addSubLast(pEnemyShot);
		}
	}

	{ //Effect EffectExplosion001
		_pEffectEffectExplosion001Rotation = NEW RotationActor("RotExplo001");
		getLordActor()->accept(KIND_ENEMY, _pEffectEffectExplosion001Rotation);
		EffectExplosion001* pEffectEffectExplosion;
		for (int i = 0; i < 100; i++) { //�X�g�b�N100��
			pEffectEffectExplosion = NEW EffectExplosion001("Explo001", "EffectEffectExplosion001");
			pEffectEffectExplosion->stopImmediately(); //�ŏ���\��
			_pEffectEffectExplosion001Rotation->addSubLast(pEffectEffectExplosion);
		}
	}

}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {
}

CommonScene::~CommonScene() {
}
