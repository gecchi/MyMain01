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
_TRACE_("çHèÍÅFStage01Scene çÏÇ¡ÇƒÇ‹Ç∑");
	Stage01Scene* pStage01Scene = NEW Stage01Scene("Stage01");
_TRACE_("çHèÍÅFStage01Scene ä¥ìÆÇÃëÂäÆê¨");
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
GgafMainActor* MyFactory::createDebugDelineateActor(void* x) {
	DelineateActor* pDelineateActor = NEW DelineateActor("HITAREA");
	return pDelineateActor;
}


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


GgafMainActor* MyFactory::createFormationCeres001(void* x) {
	FormationCeres001* pFormationCeres001 = NEW FormationCeres001("F_CER001");
	return pFormationCeres001;
}

GgafMainActor* MyFactory::createFormationCeres002(void* x) {
	FormationCeres002* pFormationCeres002 = NEW FormationCeres002("F_CER002");
	return pFormationCeres002;
}


GgafMainActor* MyFactory::createFormationJuno001First(void* x) {
	FormationJuno001* pFormationJuno001 = NEW FormationJuno001("F_JUN001F");
	FormationJuno001::_s_X_FormationWhole = *((int*)(x));
	delete (int*)(x);
	return pFormationJuno001;
}

GgafMainActor* MyFactory::createFormationJuno001(void* x) {
	FormationJuno001* pFormationJuno001 = NEW FormationJuno001("F_JUN001");
	return pFormationJuno001;
}

