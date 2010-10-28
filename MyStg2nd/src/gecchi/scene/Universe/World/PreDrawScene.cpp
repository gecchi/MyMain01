#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";

//    orderActorToFactory(10, LaserChipEffectActor, "LaserChipEffectActor");
}

void PreDrawScene::reset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
}

void PreDrawScene::processBehavior() {
//    LaserChipEffectActor* p = (LaserChipEffectActor*)obtainActorFromFactory(10);
//    getLordActor()->addSubGroup(p);
}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
