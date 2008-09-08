#include "stdafx.h"

//GgafMainScene* MyFactory::createGameScene(void* x) {
//	GameScene* pGameScene = NEW GameScene("Game");
//	return pGameScene;
//}
//
//GgafMainScene* MyFactory::createGameDemoScene(void* x) {
//	GameDemoScene* pGameDemoScene = NEW GameDemoScene("GameDemo");
//	return pGameDemoScene;
//}

//GgafMainScene* MyFactory::createGameMainScene(void* x) {
//	GameMainScene* pGameMainScene = NEW GameMainScene("GameMain");
//	return pGameMainScene;
//}

GgafMainScene* MyFactory::createStage01Scene(void* x) {
_TRACE_("工場：Stage01Scene 作ってます");
	Stage01Scene* pStage01Scene = NEW Stage01Scene("Stage01");
	Stage01MainScene* pStage01MainScene = NEW Stage01MainScene("Stage01Main");
	BackGround01Plate* pBack = NEW BackGround01Plate("BACKGOROUND01");
	pStage01Scene->getLordActor()->accept(KIND_EFFECT, pBack);
	pStage01Scene->addSubLast(pStage01MainScene);
	pStage01Scene->_bgm_st1 = GgafDx9BgmManager::get("JM5");
	pStage01Scene->_bgm_st1->play();

_TRACE_("工場：Stage01Scene 感動の大完成");
	return pStage01Scene;
}

GgafMainScene* MyFactory::createStage02Scene(void* x) {
	Stage02Scene* pStage02Scene = NEW Stage02Scene("Stage02");
	return pStage02Scene;
}

GgafMainScene* MyFactory::createStage03Scene(void* x) {
	Stage03Scene* pStage03Scene = NEW Stage03Scene("Stage03");
	return pStage03Scene;
}

GgafMainScene* MyFactory::createStage04Scene(void* x) {
	Stage04Scene* pStage04Scene = NEW Stage04Scene("Stage04");
	return pStage04Scene;
}

GgafMainScene* MyFactory::createStage05Scene(void* x) {
	Stage05Scene* pStage05Scene = NEW Stage05Scene("Stage05");
	return pStage05Scene;
}

//GgafMainScene* MyFactory::createMyShipScene(void* x) {
//	MyShipScene* pMyShipScene = NEW MyShipScene("MyShip");
//
//	MyShipActor* pMyShipActor = NEW MyShipActor("MYSHIP", "ebi");
//
//	GgafDummyActor* pDummy = NEW GgafDummyActor("MYSHOTS");
//	pDummy->addSubLast(NEW Shot001Actor("S1", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S2", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S3", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S4", "hoge"));
//	pDummy->addSubLast(NEW Shot001Actor("S5", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S6", "hoge"));
//	pDummy->addSubLast(NEW Shot001Actor("S7", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S8", "moji2"));
//	pDummy->addSubLast(NEW Shot001Actor("S9", "moji2"));
//
//	pMyShipActor->_pShotParent = pDummy;
//	pMyShipScene->getLordActor()->accept(KIND_MY, pMyShipActor);
//	pMyShipScene->getLordActor()->accept(KIND_MY, pDummy);
//
//	return pMyShipScene;
//}



//GgafMainActor* MyFactory::createDispFpsActor(void* x) {
//	DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
//	return pDispFpsActor;
//}
GgafMainActor* MyFactory::createDebugDelineateActor(void* x) {
	DelineateActor* pDelineateActor = NEW DelineateActor("HITAREA", "DelineateSprite");
	return pDelineateActor;
}


//GgafMainActor* MyFactory::createBackGroundPlateSet01(void* x) {
//	GgafDummyActor* pDummyActor = NEW GgafDummyActor("DUMMY");
//
//
//}



GgafMainActor* MyFactory::createTamagoSet01(void* x) {

	GgafDummyActor* pDummyActor = NEW GgafDummyActor("DUMMY");
	for (int i = 1; i < 5; i++) {
		stringstream str_stream;
		str_stream << "TAMAGO" << i;
		TamagoActor* tamago = NEW TamagoActor(str_stream.str(), "tamago");
		tamago -> _X = i*50000;
		tamago -> _Y = i*50000;
		pDummyActor -> addSubLast(tamago);
	}
	for (int i = 1; i < 5; i++) {
		stringstream str_stream;
		str_stream << "vic2" << i;
		TamagoActor* vic2 = NEW TamagoActor(str_stream.str(), "vic2");
		vic2 -> _X = i*50000;
		vic2 -> _Y = i*-50000;
		pDummyActor -> addSubLast(vic2);
	}
	for (int i = 1; i < 5; i++) {
		stringstream str_stream;
		str_stream << "kappa" << i;
		TamagoActor* vic2 = NEW TamagoActor(str_stream.str(), "kappa");
		vic2 -> _X = i*-50000;
		vic2 -> _Y = i*-50000;
		pDummyActor -> addSubLast(vic2);
	}
	for (int i = 1; i < 5; i++) {
		stringstream str_stream;
		str_stream << "cakeBerry" << i;
		TamagoActor* vic2 = NEW TamagoActor(str_stream.str(), "yunomi_blue");
		vic2 -> _X = i*-50000;
		vic2 -> _Y = i*50000;
		pDummyActor -> addSubLast(vic2);
	}
	//TamagoActor* pot = NEW TamagoActor("POT", "pot");
	//pDummyActor -> addSubLast(pot);
	return pDummyActor;
}


GgafMainActor* MyFactory::createEnemyCeres(void* x) {
	EnemyCeres* pEnemyCeres = NEW EnemyCeres("Ceres01", "ebi");
	return pEnemyCeres;
}


GgafMainActor* MyFactory::createEnemyFormation001(void* x) {
	EnemyFormation001* pEnemyFormation001 = NEW EnemyFormation001("Formation001");
	return pEnemyFormation001;
}

