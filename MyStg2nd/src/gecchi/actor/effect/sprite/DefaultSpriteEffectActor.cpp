#include "stdafx.h"

DefaultSpriteEffectActor::DefaultSpriteEffectActor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
	setBumpable(false);
}
//オーバーライド
void DefaultSpriteEffectActor::happen(int prm_event) {
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
