#include "stdafx.h"
#include "EnemyAidaBase.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAidaBase::EnemyAidaBase(const char* prm_name) :
        DefaultGeometricActor(prm_name) {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActorÇÕïKóvÅI
}

void EnemyAidaBase::initialize() {
}

void EnemyAidaBase::onActive() {
}

void EnemyAidaBase::processBehavior() {
}

void EnemyAidaBase::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAidaBase::onInactive() {
}

EnemyAidaBase::~EnemyAidaBase() {
}


