#include "VvvSpacetime.h"

#include "scene/VvvSpacetime/VvvWorld.h"

using namespace VVViewer;

VvvSpacetime::VvvSpacetime(const char* prm_name, VvvCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;

    //「この世」コンストラクタ内で、シーンの new は行わないで下さい。
}

void VvvSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = desireScene(VVViewer::VvvWorld);
    appendChild(pWorld_);
}

void VvvSpacetime::processBehavior() {

    executeWorldHitCheck(KIND_POINTER_RAY, KIND_ACTOR);

}

VvvSpacetime::~VvvSpacetime() {
}

