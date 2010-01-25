#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyShotSpriteActor::EnemyShotSpriteActor(const char* prm_name, const char* prm_model) : DefaultSpriteEnemyActor(prm_name, prm_model) {
    _class_name = "EnemyShotSpriteActor";
    _pEffectBegin = NULL;
    _pEffectFinish = NULL;
    _iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
    setAnimationMethod(ORDER_LOOP, 1);
    setHitAble(true);
}

void EnemyShotSpriteActor::processBehavior() {
    //�W�������i���Ԃ�I�[�o�[���C�h����邾�낤���ǂ�)
    addNextAnimationFrame();
    _pMover->behave();
}

void EnemyShotSpriteActor::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
    }

}

void EnemyShotSpriteActor::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyShotSpriteActor�q�b�g���܂����B("<<_X<<","<<_Y<<")");
    inactivateTree();
}

EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
