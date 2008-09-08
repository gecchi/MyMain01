#include "stdafx.h"


MyShipScene::MyShipScene(string prm_name) : DefaultScene(prm_name) {
	MyShipActor* pMyShipActor = NEW MyShipActor("MYSHIP", "ebi");
	getLordActor()->accept(KIND_MY, pMyShipActor);
	GgafDummyActor* pDummy = NEW GgafDummyActor("MYSHOTS");
	getLordActor()->accept(KIND_MY, pDummy);

	pDummy->addSubLast(NEW Shot001Actor("S1", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S2", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S3", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S4", "hoge"));
	pDummy->addSubLast(NEW Shot001Actor("S5", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S6", "hoge"));
	pDummy->addSubLast(NEW Shot001Actor("S7", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S8", "moji2"));
	pDummy->addSubLast(NEW Shot001Actor("S9", "moji2"));
	pMyShipActor->_pShotParent = pDummy;
}

void MyShipScene::initialize() {
}

void MyShipScene::processBehavior() {
}

MyShipScene::~MyShipScene() {
}
