#include "stdafx.h"

GgafOrder::GgafOrder(string prm_id) {
	_id = prm_id;
	_pOrder_Next = NULL;
	_pOrder_Prev = NULL;
	_isFirstOrder = false;
	_isLastOrder  = false;
	_pObject_Creation = NULL;
	_functionForBuild = NULL;
	_argumentForBuild1 = NULL;
	_argumentForBuild2 = NULL;
	_progress = 0;
}

GgafOrder::~GgafOrder() {
	if (_pObject_Creation != NULL) {
		delete _pObject_Creation;
		_pObject_Creation = NULL;
	}
}
/*
//以前
GgafOrder::~GgafOrder() {
	if (_pObject_Creation != NULL) {

		GgafActor* pActor = dynamic_cast<GgafActor*>(_pObject_Creation);
		if (pActor != 0) {
			delete pActor;
			pActor = NULL;
			_pObject_Creation = NULL;
		} else {
			GgafScene* pScene = dynamic_cast<GgafScene*>(_pObject_Creation);
			if (pScene != 0) {
				delete pScene;
				pScene = NULL;
				_pObject_Creation = NULL;
			} else {
				throw_GgafCriticalException("GgafOrder::~GgafOrder Error! 未知の GgafOrder オブジェクトです。解放できません。");
			}
		}
	}
}

*/

