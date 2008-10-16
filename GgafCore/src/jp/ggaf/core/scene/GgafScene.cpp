#include "stdafx.h"
GgafHeadActor* GgafScene::_s_apHeadActor01[MAX_HEADACTOR_PER_SCENE];
GgafHeadActor* GgafScene::_s_apHeadActor02[MAX_HEADACTOR_PER_SCENE];

GgafScene::GgafScene(string prm_name) : GgafElement<GgafScene>(prm_name)  {
	TRACE("GgafScene::GgafScene() "+prm_name);
	_class_name = "GgafScene";
	_pLordActor = NEW GgafLordActor(this);
}

GgafScene::~GgafScene() {
	TRACE("GgafScene::~GgafScene() "+getName() + " start-->");

	//所属アクターを解放
	if (_pLordActor != NULL) {
		delete _pLordActor;
	}

	TRACE("GgafScene::~GgafScene() "+getName() + " <---end");
}

void GgafScene::nextFrame() {
	TRACE("GgafScene::nextFrame() "+getName());
	GgafElement<GgafScene>::nextFrame();
	_pLordActor->nextFrame();
}

void GgafScene::behave() {
	TRACE("GgafScene::behave() "+getName());
	GgafElement<GgafScene>::behave();
	_pLordActor->behave();
}

void GgafScene::judge() {
	TRACE("GgafScene::judge() "+getName());
	GgafElement<GgafScene>::judge();
	_pLordActor->judge();
}

void GgafScene::drawPrior() {
	TRACE("GgafScene::drawPrior() "+getName());
	GgafElement<GgafScene>::drawPrior();
	_pLordActor->drawPrior();
}

void GgafScene::drawMain() {
	TRACE("GgafScene::drawMain() "+getName());
	GgafElement<GgafScene>::drawMain();
	_pLordActor->drawMain();
}

void GgafScene::drawTerminate() {
	TRACE("GgafScene::drawTerminate() "+getName());
	GgafElement<GgafScene>::drawTerminate();
	_pLordActor->drawTerminate();
}

void GgafScene::happen(int prm_no) {
	GgafElement<GgafScene>::happen(prm_no);
	_pLordActor->happen(prm_no);
}

void GgafScene::finally() {
	GgafElement<GgafScene>::finally();
	_pLordActor->finally();
}

void GgafScene::declarePlay() {
	GgafElement<GgafScene>::declarePlay();
	_pLordActor->declarePlay();
}

void GgafScene::playImmediately() {
	GgafElement<GgafScene>::playImmediately();
	_pLordActor->playImmediately();
}

void GgafScene::declareStop() {
	GgafElement<GgafScene>::declareStop();
	_pLordActor->declareStop();
}

void GgafScene::stopImmediately() {
	GgafElement<GgafScene>::stopImmediately();
	_pLordActor->stopImmediately();
}

void GgafScene::declarePause() {
	GgafElement<GgafScene>::declarePause();
	_pLordActor->declarePause();
}

void GgafScene::pauseImmediately() {
	GgafElement<GgafScene>::pauseImmediately();
	_pLordActor->pauseImmediately();
}

void GgafScene::declareUnpause() {
	GgafElement<GgafScene>::declareUnpause();
	_pLordActor->declareUnpause();
}

void GgafScene::unpauseImmediately() {
	GgafElement<GgafScene>::unpauseImmediately();
	_pLordActor->unpauseImmediately();
}

void GgafScene::declareBlind() {
	GgafElement<GgafScene>::declareBlind();
	_pLordActor->declareBlind();
}

void GgafScene::blindImmediately() {
	GgafElement<GgafScene>::blindImmediately();
	_pLordActor->blindImmediately();
}

void GgafScene::declareUnblind() {
	GgafElement<GgafScene>::declareUnblind();
	_pLordActor->declareUnblind();
}

void GgafScene::unblindImmediately() {
	GgafElement<GgafScene>::unblindImmediately();
	_pLordActor->unblindImmediately();
}

void GgafScene::declareFinishLife() {
	GgafElement<GgafScene>::declareFinishLife();
	_pLordActor->declareFinishLife();
}

void GgafScene::cleane() {
	GgafElement<GgafScene>::cleane();
	_pLordActor->cleane();
}

GgafLordActor* GgafScene::getLordActor() {
	return _pLordActor;
}


void GgafScene::executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
	GgafScene* pScene = this;
	GgafHeadActor* pHeadActor = NULL;
	int iIndex01 = 0;
	int iIndex02 = 0;

	do {
		pHeadActor = (GgafHeadActor*)(pScene->getLordActor()->_pSubFirst);
		if (pHeadActor != NULL) {
			do {
				if((pHeadActor->_kind & prm_actorkindmask01) > 0) {
					_s_apHeadActor01[iIndex01] = pHeadActor;
					++iIndex01;
				}
				if((pHeadActor->_kind & prm_actorkindmask02) > 0) {
					_s_apHeadActor02[iIndex02] = pHeadActor;
					++iIndex02;
				}
				if (pHeadActor->_isLast) {
					break;
				} else {
					pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
					continue;
				}
			} while(true);
		}

		if (pScene->_pSubFirst != NULL) {
			pScene = pScene->_pSubFirst;
     		continue;
		}

		loop:
		if (pScene->_isLast) {
			if (pScene == this) {
				break;
			} else {
				if (pScene->_pParent == this) {
					break;
				} else {
					pScene = pScene ->_pParent;
					goto loop;
				}
			}
		} else {
			pScene = pScene -> _pNext;
			continue;
		}
	} while(true);

	for (int i = 0; i < iIndex01; i++) {
		for (int j = 0; j < iIndex02; j++) {

			if (_s_apHeadActor01[i] == _s_apHeadActor02[j]) {
				_s_apHeadActor01[i]->executeBumpChkRoundRobin2(_s_apHeadActor02[j]);
			} else {
				_s_apHeadActor01[i]->executeBumpChkRoundRobin(_s_apHeadActor02[j]);
			}
		}
	}
}


GgafGod* GgafScene::askGod() {
	if (_pGod == NULL) {
		_pGod = getParent()->askGod();
	}
	return _pGod;
}

void GgafScene::dump() {
	_TRACE_("●"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<"&"<<_isPlaying<<_wasPaused<<_wasBlinded<<_isAlive<<","<<_willPlayNextFrame<<_willPauseNextFrame<<_willBlindNextFrame<<_willBeAliveNextFrame<<","<<_willPlayAfterFrame<<"("<<_dwGodFremeWhenPlay<<")");
	_pLordActor->dump();
	GgafScene* tmp = _pSubFirst;
	if (_pSubFirst != NULL) {
		while(true) {
			tmp -> dump("\t");
			tmp = tmp -> _pNext;
			if (tmp -> _isFirst) {
				break;
			}
		}
	}
}

void GgafScene::dump(string prm_parent) {
	_TRACE_(prm_parent+"●"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<"&"<<_isPlaying<<_wasPaused<<_wasBlinded<<_isAlive<<","<<_willPlayNextFrame<<_willPauseNextFrame<<_willBlindNextFrame<<_willBeAliveNextFrame<<","<<_willPlayAfterFrame<<"("<<_dwGodFremeWhenPlay<<")");
	_pLordActor->dump(prm_parent+"\t\t\t\t\t\t\t\t");
	GgafScene* tmp = _pSubFirst;
	if (_pSubFirst != NULL) {
		while(true) {
			tmp -> dump(prm_parent+"\t");
			tmp = tmp -> _pNext;
			if (tmp -> _isFirst) {
				break;
			}
		}
	}
}

