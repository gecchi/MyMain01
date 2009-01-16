#include "stdafx.h"

using namespace GgafCore;

GgafHeadActor::GgafHeadActor(actorkind prm_kind) : GgafActor("_kind="+GgafUtil::itos(prm_kind)) {
	_class_name = "GgafHeadActor";
	_kind = prm_kind;
    setBumpable(false);
}

void GgafHeadActor::processJudgement() {
	//サブが無ければ自殺
	if (getSubFirst() == NULL) {
		declareFinishLife();
	}
}


GgafGod* GgafHeadActor::askGod() {
	if (_pGod == NULL) {
		if (getParent() == NULL) {
			throw_GgafCriticalException("GgafHeadActor::askGod 神は世界からのみ謁見できます。まずは世界に属しなさい！！("<<getName()<<")");
		} else {
			_pGod = getParent()->askGod();
		}
	}
	return _pGod;
}


GgafHeadActor::~GgafHeadActor() {
}
