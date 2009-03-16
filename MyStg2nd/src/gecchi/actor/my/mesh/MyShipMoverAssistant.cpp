#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipMoverAssistant::MyShipMoverAssistant(const char* prm_name, const char* prm_model) : DefaultMeshActor(prm_name, prm_model, "DefaultMeshTechnique") {
    _class_name = "MyShipMoverAssistant";
    blindImmediatelyAlone();
    setBumpableAlone(false);
}

void MyShipMoverAssistant::initialize() {
}

void MyShipMoverAssistant::processBehavior() {
    //À•W‚É”½‰f
    _pGeoMover->behave();
}

MyShipMoverAssistant::~MyShipMoverAssistant() {
}

