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
		getLordActor()->accept(KIND_MY_SHOT_GU, _pMyShots001Rotation);
		MyShot001* pShot;
		for (int i = 0; i < 50; i++) { //自弾ストック３０個
			pShot = NEW MyShot001("MY_S"+GgafUtil::itos(i), "moji2");
			pShot->stopImmediately();
			_pMyShots001Rotation->addSubLast(pShot);
		}
	}

	{ //MyLaser001
		_pMyLaser001Rotation = NEW RotationActor("RotLaser001");
		getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaser001Rotation);
		MyLaserChip* pLaser;
		for (int i = 0; i < 50; i++) { //レーザーストック３０個
			pLaser = NEW MyLaserChip("MY_L"+GgafUtil::itos(i), "laserchip7");
			pLaser->stopImmediately();
			_pMyLaser001Rotation->addSubLast(pLaser);
		}
	}

	{ //EnemyShot001
		_pEnemyShots001Rotation = NEW RotationActor("TAMAS001");
		getLordActor()->accept(KIND_ENEMY_SHOT_GU, _pEnemyShots001Rotation);
		EnemyShot001* pEnemyShot;
		for (int i = 0; i < 256; i++) { //ストック256個
			pEnemyShot = NEW EnemyShot001("EneShot"+GgafUtil::itos(i), "hoge");
			pEnemyShot->stopImmediately(); //最初非表示
			_pEnemyShots001Rotation->addSubLast(pEnemyShot);
		}
	}

	{ //Effect EffectExplosion001
		_pEffectExplosion001Rotation = NEW RotationActor("RotExplo001");
		getLordActor()->accept(KIND_EFFECT, _pEffectExplosion001Rotation);
		EffectExplosion001* pEffectExplosion;
		for (int i = 0; i < 100; i++) { //ストック100個
			pEffectExplosion = NEW EffectExplosion001("Explo"+GgafUtil::itos(i), "EffectExplosion001");
			pEffectExplosion->stopImmediately(); //最初非表示
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
