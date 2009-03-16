#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParent::MyOptionParent(const char* prm_name, const char* prm_model) : DefaultMeshActor(prm_name, prm_model, "DefaultMeshTechnique") {
    blindImmediately(); //”ñ•\Ž¦
}

void MyOptionParent::initialize() {
}

void MyOptionParent::processBehavior() {
}

void MyOptionParent::processJudgement() {
}

void MyOptionParent::processOnHit(GgafActor* prm_pActor_Opponent) {
}

MyOptionParent::~MyOptionParent() {
}
