#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultSpriteEffectActor::DefaultSpriteEffectActor(string prm_name, string prm_model) : DefaultSpriteActor(prm_name, prm_model) {
	_class_name = "DefaultSpriteEffectActor";
	setBumpable(false);
}
//オーバーライド
void DefaultSpriteEffectActor::processHappen(int prm_event) {
	switch (prm_event) {

	case GGAF_EVENT_NOLOOP_ANIMATION_FINISHED:
		//繰り返さないアニメーション終了時、共通処理
		declareStop();
		declareMoveFirst();
		break;

	default:
		break;
	}
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
