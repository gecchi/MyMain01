#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParent::MyOptionParent(string prm_name,  string prm_model) : DefaultMeshActor(prm_name, prm_model) {
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
