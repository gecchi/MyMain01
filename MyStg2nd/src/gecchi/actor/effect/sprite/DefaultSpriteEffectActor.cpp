#include "stdafx.h"

DefaultSpriteEffectActor::DefaultSpriteEffectActor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
	setBumpable(false);
}
//オーバーライド
void DefaultSpriteEffectActor::happen(int prm_event) {
	switch (prm_event) {

	case EVENT_ORDER_NOLOOP_ANIMATION_FINISH:
		//順アニメーション終了時共通処理
		declareStop();
		declareMoveFirst();
		break;
	case EVENT_REVERSE_NOLOOP_ANIMATION_FINISH:
		//逆アニメーション終了時共通処理
		declareStop();
		declareMoveFirst();
		break;
	default:
		break;
	}
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
