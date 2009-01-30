#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafHeadActor* GgafScene::_s_apHeadActor01[MAX_HEADACTOR_PER_SCENE];
GgafHeadActor* GgafScene::_s_apHeadActor02[MAX_HEADACTOR_PER_SCENE];

GgafScene::GgafScene(string prm_name) : GgafElement<GgafScene>(prm_name)  {
	TRACE("GgafScene::GgafScene() "+prm_name);
	_class_name = "GgafScene";
	_pLordActor = NEW GgafLordActor(this);
}

GgafScene::~GgafScene() {
	TRACE("GgafScene::~GgafScene() "+getName() + " start-->");

	//èäëÆÉAÉNÉ^Å[Çâï˙
	DELETE_POSSIBLE_NULL(_pLordActor);

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

void GgafScene::play() {
	GgafElement<GgafScene>::play();
	_pLordActor->play();
}

void GgafScene::playImmediately() {
	GgafElement<GgafScene>::playImmediately();
	_pLordActor->playImmediately();
}

void GgafScene::stop() {
	GgafElement<GgafScene>::stop();
	_pLordActor->stop();
}

void GgafScene::stopImmediately() {
	GgafElement<GgafScene>::stopImmediately();
	_pLordActor->stopImmediately();
}

void GgafScene::pause() {
	GgafElement<GgafScene>::pause();
	_pLordActor->pause();
}

void GgafScene::pauseImmediately() {
	GgafElement<GgafScene>::pauseImmediately();
	_pLordActor->pauseImmediately();
}

void GgafScene::unpause() {
	GgafElement<GgafScene>::unpause();
	_pLordActor->unpause();
}

void GgafScene::unpauseImmediately() {
	GgafElement<GgafScene>::unpauseImmediately();
	_pLordActor->unpauseImmediately();
}

void GgafScene::blind() {
	GgafElement<GgafScene>::blind();
	_pLordActor->blind();
}

void GgafScene::blindImmediately() {
	GgafElement<GgafScene>::blindImmediately();
	_pLordActor->blindImmediately();
}

void GgafScene::unblind() {
	GgafElement<GgafScene>::unblind();
	_pLordActor->unblind();
}

void GgafScene::unblindImmediately() {
	GgafElement<GgafScene>::unblindImmediately();
	_pLordActor->unblindImmediately();
}

void GgafScene::farewell(DWORD prm_dwFrameOffset) {
	GgafElement<GgafScene>::farewell(prm_dwFrameOffset);
	_pLordActor->farewell(prm_dwFrameOffset);
}

void GgafScene::cleane(int prm_iNumCleanNode) {
	GgafElement<GgafScene>::cleane(prm_iNumCleanNode);
	_pLordActor->cleane(prm_iNumCleanNode);
}

GgafLordActor* GgafScene::getLordActor() {
	return _pLordActor;
}


void GgafScene::executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
	static GgafScene* pScene;
	pScene = this;
	static GgafHeadActor* pHeadActor;
	pHeadActor = NULL;
	static int iIndex01,iIndex02;
	iIndex01 = 0;
	iIndex02 = 0;

	do {
		pHeadActor = (GgafHeadActor*)(pScene->getLordActor()->_pSubFirst);
		if (pHeadActor != NULL) {
			do {
				if((pHeadActor->_kind & prm_actorkindmask01) > 0) {
					_s_apHeadActor01[iIndex01] = pHeadActor;
					iIndex01++;
				}
				if((pHeadActor->_kind & prm_actorkindmask02) > 0) {
					_s_apHeadActor02[iIndex02] = pHeadActor;
					iIndex02++;
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
	_TRACE_("Åú"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_isPlaying<<_wasPaused<<_wasBlinded<<_isAlive<<","<<_willPlayNextFrame<<_willPauseNextFrame<<_willBlindNextFrame<<_willBeAliveNextFrame<<","<<_willPlayAfterFrame<<"("<<_dwGodFremeWhenPlay<<")");
	_pLordActor->dump();
	GgafScene* pScene_tmp = _pSubFirst;
	if (_pSubFirst != NULL) {
		while(true) {
			pScene_tmp -> dump("\t");
			if (pScene_tmp -> _pNext) {
				pScene_tmp = pScene_tmp -> _pNext;
			} else {
				_TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
				break;
			}
			if (pScene_tmp -> _isFirst) {
				break;
			}
		}
	}
}

void GgafScene::dump(string prm_parent) {
	_TRACE_(prm_parent+"Åú"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_isPlaying<<_wasPaused<<_wasBlinded<<_isAlive<<","<<_willPlayNextFrame<<_willPauseNextFrame<<_willBlindNextFrame<<_willBeAliveNextFrame<<","<<_willPlayAfterFrame<<"("<<_dwGodFremeWhenPlay<<")");
	_pLordActor->dump(prm_parent+"\t\t\t\t\t\t\t\t");
	GgafScene* pScene_tmp = _pSubFirst;
	if (_pSubFirst != NULL) {
		while(true) {
			pScene_tmp -> dump(prm_parent+"\t");
			if (pScene_tmp -> _pNext) {
				pScene_tmp = pScene_tmp -> _pNext;
			} else {
				_TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
				break;
			}
			if (pScene_tmp -> _isFirst) {
				break;
			}
		}
	}
}

