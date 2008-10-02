#include "stdafx.h"

DefaultSpriteEffectActor::DefaultSpriteEffectActor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
	setBumpable(false);
}
//�I�[�o�[���C�h
void DefaultSpriteEffectActor::happen(int prm_event) {
	switch (prm_event) {

	case EVENT_ORDER_NOLOOP_ANIMATION_FINISH:
		//���A�j���[�V�����I�������ʏ���
		declareStop();
		declareMoveFirst();
		break;
	case EVENT_REVERSE_NOLOOP_ANIMATION_FINISH:
		//�t�A�j���[�V�����I�������ʏ���
		declareStop();
		declareMoveFirst();
		break;
	default:
		break;
	}
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
