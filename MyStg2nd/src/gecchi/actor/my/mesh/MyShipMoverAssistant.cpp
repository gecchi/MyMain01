#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipMoverAssistant::MyShipMoverAssistant(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "MyShipMoverAssistant";
	blindAloneImmediately();
	setBumpableAlone(false);
}

void MyShipMoverAssistant::initialize() {

}

void MyShipMoverAssistant::processBehavior() {


	//���W�ɔ��f
	_pGeoMover -> behave();
}


MyShipMoverAssistant::~MyShipMoverAssistant() {
}


