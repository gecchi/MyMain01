#include "stdafx.h"

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


