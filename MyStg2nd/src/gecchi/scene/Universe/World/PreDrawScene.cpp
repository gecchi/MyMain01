#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";

    orderActorToFactory(10, LaserChipEffectActor, "LaserChipEffectActor");
    orderActorToFactory(11, DefaultMeshEffectActor, "DefaultMeshEffectActor");
}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
}

void PreDrawScene::processBehavior() {
    getLordActor()->addSubGroup(obtainActorFromFactory(10));
}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
