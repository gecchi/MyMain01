#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Scene::GgafDx9Scene(const char* prm_name) : GgafMainScene(prm_name) {
    _scene_class |= Obj_GgafDx9Scene;
    _class_name = "GgafDx9Scene";
    _pAlphaCurtain = NEW GgafDx9AlphaCurtain(this);
}

void GgafDx9Scene::processJudgement() {
    _pAlphaCurtain->behave();
}

void GgafDx9Scene::fadein(float prm_velocity_alpha) {
}

void GgafDx9Scene::fadeinTree(float prm_velocity_alpha){
}

void GgafDx9Scene::fadeout(float prm_velocity_alpha){
}

void GgafDx9Scene::fadeoutTree(float prm_velocity_alpha){
}

GgafDx9Scene::~GgafDx9Scene() {
    DELETE_IMPOSSIBLE_NULL(_pAlphaCurtain);
}
