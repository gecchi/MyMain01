#include "stdafx.h"


MyShipScene::MyShipScene(string prm_name) : DefaultScene(prm_name) {
	MyShipActor* pMyShipActor = NEW MyShipActor("MYSHIP", "ebi");
	getLordActor()->accept(KIND_MY, pMyShipActor);
	RotationActor* pRotation = NEW RotationActor("MYSHOTS");
	getLordActor()->accept(KIND_MY, pRotation);

	pRotation->addSubLast(NEW Shot001Actor("S1", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S2", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S3", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S4", "hoge"));
	pRotation->addSubLast(NEW Shot001Actor("S5", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S6", "hoge"));
	pRotation->addSubLast(NEW Shot001Actor("S7", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S8", "moji2"));
	pRotation->addSubLast(NEW Shot001Actor("S9", "moji2"));
	pMyShipActor->_pShot001Rotation = pRotation;
}

void MyShipScene::initialize() {
}

void MyShipScene::processBehavior() {
}

MyShipScene::~MyShipScene() {
}
