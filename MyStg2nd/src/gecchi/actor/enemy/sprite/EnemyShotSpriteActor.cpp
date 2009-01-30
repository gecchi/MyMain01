#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyShotSpriteActor::EnemyShotSpriteActor(string prm_name, string prm_model) : DefaultSpriteEnemyActor(prm_name, prm_model) {
	_class_name = "EnemyShotSpriteActor";
	_pEffectBegin = NULL;
	_pEffectFinish = NULL;
	_iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);
	setBumpableAlone(true);
}

void EnemyShotSpriteActor::processBehavior() {
	//標準処理（たぶんオーバーライドされるだろうけども)
	nextAnimationFrame();
	_pGeoMover -> behave();
}

void EnemyShotSpriteActor::processJudgement() {
	if (isOffScreen()) {
		stop();
	}

}

void EnemyShotSpriteActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	//_TRACE_("EnemyShotSpriteActorヒットしました。("<<_X<<","<<_Y<<")");
	stop();
}



EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
