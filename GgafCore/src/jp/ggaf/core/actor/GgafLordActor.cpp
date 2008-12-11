#include "stdafx.h"

GgafLordActor::GgafLordActor(GgafScene* prm_pScene_Platform) : GgafActor((prm_pScene_Platform->getName())+"'s Lord") {
    _pScene_Platform = prm_pScene_Platform;
	_class_name = "GgafLordActor";
    setBumpable(false);
}

void GgafLordActor::remove() {
    throw_GgafCriticalException("[GgafLordActor::remove] Error! GgafLordActorはremove()によって削除は行えません！");
}

void GgafLordActor::accept(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
	GgafHeadActor* pHeadActor = NULL;
    if (hasSubHeadActor(prm_kind)) {
        pHeadActor = getSubHeadActor(prm_kind);
    } else {
        pHeadActor = NEW GgafHeadActor(prm_kind);
        addSubLast(pHeadActor);
    }
	pHeadActor -> addSubLast(prm_pMainActor);
	prm_pMainActor -> setLordActor(this);
    prm_pMainActor -> setHeadActor(pHeadActor);
    prm_pMainActor -> setScenePlatform(_pScene_Platform);
}

void GgafLordActor::accept(GgafMainActor* prm_pMainActor) {
	accept(0, prm_pMainActor);
}

bool GgafLordActor::hasSubHeadActor(actorkind prm_kind) {
	if (_pSubFirst == NULL) {
		return false;
	} else {
		GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
		do {
			if(pHeadActor -> _kind == prm_kind) {
				return true;
			}
			if (pHeadActor -> _isLast) {
				return false;
			} else {
				pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
			}
		} while(true);
	}

}


GgafHeadActor* GgafLordActor::getSubHeadActor(actorkind prm_kind) {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("[GgafLordActor::getSubHeadActor] Error! _pSubFirstがNULLです。");
	}
	GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
	do {
		if(pHeadActor -> _kind == prm_kind) {
			break;
		}
		if (pHeadActor -> _isLast) {
			throw_GgafCriticalException("[GgafLordActor::getSubHeadActor] Error! 子ノードは存在しません。(actorkind="<<prm_kind<<")");
		} else {
			pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
		}
	} while(true);
	return pHeadActor;
}


/*
GgafHeadActor* GgafLordActor::getHeadActor(string prm_kind) {

}
*/


GgafGod* GgafLordActor::askGod() {
	if (_pGod == NULL) {
		if (getPlatformScene() == NULL) {
			throw_GgafCriticalException("GgafLordActor::askGod 神は世界からのみ謁見できます。まずは世界に属しなさい！！("<<getName()<<")");
		} else {
			_pGod = getPlatformScene()->askGod();
		}
	}
	return _pGod;
}




GgafLordActor::~GgafLordActor() {
}
