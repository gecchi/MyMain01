#include "stdafx.h"


CommonScene::CommonScene(string prm_name) : DefaultScene(prm_name) {
	GameGlobal::_pSceneCommon = this;

	//MyShip
	_pMyShipActor = NEW MyShipActor("MYSHIP", "ebi");
	getLordActor()->accept(KIND_MY, _pMyShipActor);
	_pMyShipActor->stopImmediately();

	//MyShots001
	_pMyShots001Rotation = NEW RotationActor("MYSHOTS");
	getLordActor()->accept(KIND_MY, _pMyShots001Rotation);
	Shot001Actor* pShot;
	for (int i = 0; i < 30; i++) { //自弾ストック３０個
		pShot = NEW Shot001Actor("S1", "moji2");
		pShot->stopImmediately();
		_pMyShots001Rotation->addSubLast(pShot);
	}
	_pMyShipActor->_pMyShots001Rotation = this->_pMyShots001Rotation;


	//EnemyShot001
	_pEnemyShots001Rotation = NEW RotationActor("TAMAS001");
	getLordActor()->accept(KIND_ENEMY, _pEnemyShots001Rotation);
	EnemyShot001Actor* pEnemyShot;
	for (int i = 0; i < 256; i++) { //ストック256個
		pEnemyShot = NEW EnemyShot001Actor("ET", "hoge");
		pEnemyShot->stopImmediately(); //最初非表示
		_pEnemyShots001Rotation->addSubLast(pEnemyShot);
	}

}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {
}

CommonScene::~CommonScene() {
}
