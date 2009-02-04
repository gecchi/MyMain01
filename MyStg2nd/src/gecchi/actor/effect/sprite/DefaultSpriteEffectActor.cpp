#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultSpriteEffectActor::DefaultSpriteEffectActor(char* prm_name, char* prm_model) : DefaultSpriteActor(prm_name, prm_model) {
	_class_name = "DefaultSpriteEffectActor";
	setBumpable(false);
}
//�I�[�o�[���C�h
void DefaultSpriteEffectActor::processHappen(int prm_event) {
	switch (prm_event) {

	case GGAF_EVENT_NOLOOP_ANIMATION_FINISHED:
		//�J��Ԃ��Ȃ��A�j���[�V�����I�����A���ʏ���
		stop();
		moveFirst();
		break;

	default:
		break;
	}
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
