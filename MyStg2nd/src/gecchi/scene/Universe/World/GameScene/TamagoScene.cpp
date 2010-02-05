#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    orderActorToFactory(100000001, EnemyTamago01, "gyoku");
}

void TamagoScene::reset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
    if (_frame_of_active == 1) {
        getLordActor()->addSubGroup(obtainActorFromFactory(100000001));
    }
}

void TamagoScene::processFinal() {
}

TamagoScene::~TamagoScene() {
}
