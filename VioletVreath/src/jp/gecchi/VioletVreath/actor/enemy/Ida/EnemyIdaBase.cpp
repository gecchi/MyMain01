#include "EnemyIdaBase.h"

#include "jp/ggaf/dx/util/Util.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyIdaBase::EnemyIdaBase(const char* prm_name) :
        DefaultGeometricActor(prm_name) {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActorÇÕïKóvÅI
}

void EnemyIdaBase::initialize() {
}

void EnemyIdaBase::onActive() {
}

void EnemyIdaBase::processBehavior() {
}

void EnemyIdaBase::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyIdaBase::onInactive() {
}

EnemyIdaBase::~EnemyIdaBase() {
}


