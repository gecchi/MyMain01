#include "SmpWorld.h"

#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) :
        GgafLib::DefaultScene(prm_name) {
    SmpActor* pActor = new SmpActor("TEST");  //キャラクター作成
    getSceneChief()->appendGroupChild(pActor);  //キャラクターをシーン監督の配下に所属（表示される）
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
}

SmpWorld::~SmpWorld() {
}
