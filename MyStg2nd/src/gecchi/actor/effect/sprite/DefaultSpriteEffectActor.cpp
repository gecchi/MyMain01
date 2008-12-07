#include "stdafx.h"

DefaultSpriteEffectActor::DefaultSpriteEffectActor(string prm_name, string prm_model) : DefaultSpriteActor(prm_name, prm_model) {
	_class_name = "DefaultSpriteEffectActor";
	setBumpable(false);
}
//�I�[�o�[���C�h
void DefaultSpriteEffectActor::processHappen(int prm_event) {
	switch (prm_event) {

	case GGAF_EVENT_NOLOOP_ANIMATION_FINISHED:
		//�J��Ԃ��Ȃ��A�j���[�V�����I�����A���ʏ���
		declareStop();
		declareMoveFirst();
		break;

	default:
		break;
	}
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
