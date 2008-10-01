#include "stdafx.h"


CommonScene::CommonScene(string prm_name) : DefaultScene(prm_name) {
	GameGlobal::_pSceneCommon = this;

	{ //MyShip
		_pMyShipActor = NEW MyShipActor("MYSHIP", "ebi");
		getLordActor()->accept(KIND_MY, _pMyShipActor);
		_pMyShipActor->stopImmediately();
	}

	{ //MyShots001
		_pMyShots001Rotation = NEW RotationActor("RotShot001");
		getLordActor()->accept(KIND_MY, _pMyShots001Rotation);
		Shot001Actor* pShot;
		for (int i = 0; i < 50; i++) { //���e�X�g�b�N�R�O��
			pShot = NEW Shot001Actor("S1", "moji2");
			pShot->stopImmediately();
			_pMyShots001Rotation->addSubLast(pShot);
		}
		_pMyShipActor->_pMyShots001Rotation = this->_pMyShots001Rotation;
	}

	{ //MyLaser001
		_pMyLaser001Rotation = NEW RotationActor("RotLaser001");
		getLordActor()->accept(KIND_MY, _pMyLaser001Rotation);
		Laser001Actor* pLaser;
		for (int i = 0; i < 50; i++) { //���[�U�[�X�g�b�N�R�O��
			pLaser = NEW Laser001Actor("L1", "MyLaser001");
			pLaser->stopImmediately();
			_pMyLaser001Rotation->addSubLast(pLaser);
		}
		_pMyShipActor->_pMyLaser001Rotation = this->_pMyLaser001Rotation;
	}

	{ //EnemyShot001
		_pEnemyShots001Rotation = NEW RotationActor("TAMAS001");
		getLordActor()->accept(KIND_ENEMY, _pEnemyShots001Rotation);
		EnemyShot001Actor* pEnemyShot;
		for (int i = 0; i < 256; i++) { //�X�g�b�N256��
			pEnemyShot = NEW EnemyShot001Actor("EneShot001", "hoge");
			pEnemyShot->stopImmediately(); //�ŏ���\��
			_pEnemyShots001Rotation->addSubLast(pEnemyShot);
		}
	}

	{ //Effect Explosion001
		_pEffectExplosion001Rotation = NEW RotationActor("RotExplo001");
		getLordActor()->accept(KIND_ENEMY, _pEffectExplosion001Rotation);
		Explosion001Actor* pEffectExplosion;
		for (int i = 0; i < 100; i++) { //�X�g�b�N100��
			pEffectExplosion = NEW Explosion001Actor("Explo001", "hoge");
			pEffectExplosion->stopImmediately(); //�ŏ���\��
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
