#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Item::Item(const char* prm_name, const char* prm_model)
               : DefaultMeshSetActor(prm_name, prm_model) {
    _class_name = "Item";
    _no_hitchk_out_of_view = true; //Ž‹–ìŠO‚Í“–‚½‚è”»’è–³Œø

}

void Item::initialize() {
}

void Item::onReset() {
}

void Item::onActive() {
}

void Item::processBehavior() {
}

void Item::processJudgement() {
}

void Item::onInactive() {
}

Item::~Item() {
}
