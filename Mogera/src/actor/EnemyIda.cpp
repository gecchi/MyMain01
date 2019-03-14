#include "EnemyIda.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "MgrGod.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_ENTRY,
    PROG_MOVE01,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyIda::EnemyIda(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida") {
    _class_name = "EnemyIda";
}

void EnemyIda::onCreateModel() {
}

void EnemyIda::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
}

void EnemyIda::onActive() {
    getProgress()->reset(PROG_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //ローカル座標系へ

    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            break;
        }
        case PROG_ENTRY: {
            break;
        }
        case PROG_MOVE01: {
            break;
        }
    }
    pKuroko->behave();

    changeGeoFinal(); //絶対座標系へ
}

void EnemyIda::processJudgement() {
}

void EnemyIda::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
}


