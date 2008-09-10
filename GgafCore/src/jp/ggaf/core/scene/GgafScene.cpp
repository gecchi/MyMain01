#include "stdafx.h"
GgafHeadActor* GgafScene::_s_apHeadActor01[MAX_HEADACTOR_PER_SCENE];
GgafHeadActor* GgafScene::_s_apHeadActor02[MAX_HEADACTOR_PER_SCENE];

GgafScene::GgafScene(string prm_name) : GgafFactor<GgafScene>(prm_name)  {
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
	GgafFactor<GgafScene>::nextFrame();
	_pLordActor->nextFrame();
}

void GgafScene::behave() {
	TRACE("GgafScene::behave() "+getName());
	GgafFactor<GgafScene>::behave();
	_pLordActor->behave();
}

void GgafScene::judge() {
	TRACE("GgafScene::judge() "+getName());
	GgafFactor<GgafScene>::judge();
	_pLordActor->judge();
}

void GgafScene::drawPrior() {
	TRACE("GgafScene::drawPrior() "+getName());
	GgafFactor<GgafScene>::drawPrior();
	_pLordActor->drawPrior();
}

void GgafScene::drawMain() {
	TRACE("GgafScene::drawMain() "+getName());
	GgafFactor<GgafScene>::drawMain();
	_pLordActor->drawMain();
}

void GgafScene::drawTerminate() {
	TRACE("GgafScene::drawTerminate() "+getName());
	GgafFactor<GgafScene>::drawTerminate();
	_pLordActor->drawTerminate();
}

void GgafScene::happen(int prm_no) {
	GgafFactor<GgafScene>::happen(prm_no);
	_pLordActor->happen(prm_no);
}

void GgafScene::finally() {
	GgafFactor<GgafScene>::finally();
	_pLordActor->finally();
}

void GgafScene::declarePlay() {
	GgafFactor<GgafScene>::declarePlay();
	_pLordActor->declarePlay();
}

void GgafScene::playImmediately() {
	GgafFactor<GgafScene>::playImmediately();
	_pLordActor->playImmediately();
}

void GgafScene::declareStop() {
	GgafFactor<GgafScene>::declareStop();
	_pLordActor->declareStop();
}

void GgafScene::stopImmediately() {
	GgafFactor<GgafScene>::stopImmediately();
	_pLordActor->stopImmediately();
}

void GgafScene::declarePause() {
	GgafFactor<GgafScene>::declarePause();
	_pLordActor->declarePause();
}

void GgafScene::pauseImmediately() {
	GgafFactor<GgafScene>::pauseImmediately();
	_pLordActor->pauseImmediately();
}

void GgafScene::declareUnpause() {
	GgafFactor<GgafScene>::declareUnpause();
	_pLordActor->declareUnpause();
}

void GgafScene::unpauseImmediately() {
	GgafFactor<GgafScene>::unpauseImmediately();
	_pLordActor->unpauseImmediately();
}

void GgafScene::declareBlind() {
	GgafFactor<GgafScene>::declareBlind();
	_pLordActor->declareBlind();
}

void GgafScene::blindImmediately() {
	GgafFactor<GgafScene>::blindImmediately();
	_pLordActor->blindImmediately();
}

void GgafScene::declareUnblind() {
	GgafFactor<GgafScene>::declareUnblind();
	_pLordActor->declareUnblind();
}

void GgafScene::unblindImmediately() {
	GgafFactor<GgafScene>::unblindImmediately();
	_pLordActor->unblindImmediately();
}

void GgafScene::declareFinishLife() {
	GgafFactor<GgafScene>::declareFinishLife();
	_pLordActor->declareFinishLife();
}

void GgafScene::cleane() {
	GgafFactor<GgafScene>::cleane();
	_pLordActor->cleane();
}

GgafLordActor* GgafScene::getLordActor() {
	return _pLordActor;
}


/*
void GgafScene::executeBumpChkHeadActors(string prm_actor_kind_name01, string prm_actor_kind_name02) {
	if (prm_actor_kind_name01 == "" || prm_actor_kind_name02 == "") {
		throw_GgafCriticalException("[GgafScene::checkActorsHit] 引数がNULLです");
	}
	bool like01_flg;
	string::size_type iLen01 = prm_actor_kind_name01.length();
	string strNoAsterisk01;
	if (prm_actor_kind_name01.rfind('*') == iLen01-1) {
		strNoAsterisk01 = prm_actor_kind_name01.substr(0, iLen01-1);
		like01_flg = true;
	} else {
		like01_flg = false;
	}

	bool like02_flg;
	string::size_type iLen02 = prm_actor_kind_name02.length();
	string strNoAsterisk02;
	if (prm_actor_kind_name02.rfind('*') == iLen02-1) {
		strNoAsterisk02 = prm_actor_kind_name02.substr(0, iLen02-1);
		like02_flg = true;
	} else {
		like02_flg = false;
	}

	int iIndex01 = 0;
	GgafHeadActor* apHeadActor01[MAX_HEADACTOR_PER_SCENE];
	int iIndex02 = 0;
	GgafHeadActor* apHeadActor02[MAX_HEADACTOR_PER_SCENE];

	//自シーンのGgafHeadActor列検索追加
	GgafLordActor* pLordActor = getLordActor();
	GgafHeadActor* pHeadActor = (GgafHeadActor*)(pLordActor -> _pSubFirst);
	if (pHeadActor != NULL) {
		do {
			if (like01_flg) {
				if(pHeadActor -> getName().find(strNoAsterisk01) == 0) {
					apHeadActor01[iIndex01] = pHeadActor;
					iIndex01++;
				}
			} else {
				if(pHeadActor -> getName() == prm_actor_kind_name01) {
					apHeadActor01[iIndex01] = pHeadActor;
					iIndex01++;
				}
			}
			if (like02_flg) {
				if(pHeadActor -> getName().find(strNoAsterisk02) == 0) {
					apHeadActor02[iIndex02] = pHeadActor;
					iIndex02++;
				}
			} else {
				if(pHeadActor -> getName() == prm_actor_kind_name02) {
					apHeadActor02[iIndex02] = pHeadActor;
					iIndex02++;
				}
			}
			if (pHeadActor -> _isLast) {
				break;
			} else {
				pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
			}
		} while(true);
	}
	//サブシーンのGgafHeadActor列追加
	GgafScene* apScene_SubLevelBuffer[MAXSCENE_PER_LEVEL];
	GgafScene* apScene_ParentLevelBuffer[MAXSCENE_PER_LEVEL];

	bool has_sub_flg;
	GgafScene* pScene_Sub_tmp;
	int iCntSceneParentLevel;
	int iCntSceneSubLevel; //サブレベルのシーン数
	iCntSceneParentLevel = 1;
	apScene_ParentLevelBuffer[0] = this;
	while(true) {  //親レベル毎のループ
		iCntSceneSubLevel = 0;
		has_sub_flg = false;
		for (int i = 0; i < iCntSceneParentLevel; i++) { //親レベルのシーン数でループ
			pScene_Sub_tmp = apScene_ParentLevelBuffer[i]->_pSubFirst;
			if (pScene_Sub_tmp == NULL) {
				continue;
			} else {
				has_sub_flg = true;
			}
			do {  //同じ親を持つサブシーンでループ
				pLordActor = pScene_Sub_tmp->getLordActor();
				pHeadActor = (GgafHeadActor*)(pLordActor -> _pSubFirst);
				if (pHeadActor != NULL) {
					do {
						if (like01_flg) {
							if(pHeadActor -> getName().find(strNoAsterisk01) == 0) {
								apHeadActor01[iIndex01] = pHeadActor;
								iIndex01++;
							}
						} else {
							if(pHeadActor -> getName() == prm_actor_kind_name01) {
								apHeadActor01[iIndex01] = pHeadActor;
								iIndex01++;
							}
						}
						if (like02_flg) {
							if(pHeadActor -> getName().find(strNoAsterisk02) == 0) {
								apHeadActor02[iIndex02] = pHeadActor;
								iIndex02++;
							}
						} else {
							if(pHeadActor -> getName() == prm_actor_kind_name02) {
								apHeadActor02[iIndex02] = pHeadActor;
								iIndex02++;
							}
						}
						if (pHeadActor -> _isLast) {
							break;
						} else {
							pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
						}
					} while(true);
				}
				if (pScene_Sub_tmp->_isLast) {
					apScene_SubLevelBuffer[iCntSceneSubLevel] = pScene_Sub_tmp;
					iCntSceneSubLevel++;
					//同じ親を持つ最後のシーンだった場合
					break;
				} else {
					apScene_SubLevelBuffer[iCntSceneSubLevel] = pScene_Sub_tmp;
					pScene_Sub_tmp = pScene_Sub_tmp->_pNext; iCntSceneSubLevel++;
				}
				if (iCntSceneSubLevel >= MAXSCENE_PER_LEVEL) {
					break;//エラー
				}
			} while(true);
		}
		//そのレベルに1つもサブレベルのシーンが無い場合、終了
		if (has_sub_flg == false) {
			break;
		}
		//サブを親へ順繰りする
		for (int i = 0; i < iCntSceneSubLevel; i++) {
			apScene_ParentLevelBuffer[i] = apScene_SubLevelBuffer[i];
		}
		iCntSceneParentLevel = iCntSceneSubLevel;
	}
	//総当りの総当りでヒットチェックを行う
	for (int i = 0; i < iIndex01; i++) {
		for (int j = 0; j < iIndex02; j++) {
			if (apHeadActor01[i] == apHeadActor02[j]) {
				apHeadActor01[i]->executeBumpChkRoundRobin2(apHeadActor02[j]);
			} else {
				apHeadActor01[i]->executeBumpChkRoundRobin(apHeadActor02[j]);
			}
		}
	}
}
*/

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

//
//void GgafScene::executeBumpChkHeadActors(actorkind prm_actorkind01, actorkind prm_actorkind02) {
//	if (prm_actorkind01 == 0 || prm_actorkind02 == 0) {
//		throw_GgafCriticalException("[GgafScene::checkActorsHit] 引数のactorkind が 0 です。");
//	}
//	int iIndex01 = 0;
//	GgafHeadActor* apHeadActor01[MAX_HEADACTOR_PER_SCENE];
//	int iIndex02 = 0;
//	GgafHeadActor* apHeadActor02[MAX_HEADACTOR_PER_SCENE];
//
//	//自シーンのGgafHeadActor列検索追加
//	GgafLordActor* pLordActor = getLordActor();
//	GgafHeadActor* pHeadActor = (GgafHeadActor*)(pLordActor -> _pSubFirst);
//	if (pHeadActor != NULL) {
//		do {
//			if(pHeadActor -> _kind == prm_actorkind01) {
//				apHeadActor01[iIndex01] = pHeadActor;
//				iIndex01++;
//			}
//			if(pHeadActor -> _kind == prm_actorkind02) {
//				apHeadActor02[iIndex02] = pHeadActor;
//				iIndex02++;
//			}
//			if (pHeadActor -> _isLast) {
//				break;
//			} else {
//				pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
//			}
//		} while(true);
//	}
//	//サブシーンのGgafHeadActor列追加
//	GgafScene* apScene_SubLevelBuffer[MAXSCENE_PER_LEVEL];
//	GgafScene* apScene_ParentLevelBuffer[MAXSCENE_PER_LEVEL];
//
//	bool has_sub_flg;
//	GgafScene* pScene_Sub_tmp;
//	int iCntSceneParentLevel;
//	int iCntSceneSubLevel; //サブレベルのシーン数
//	iCntSceneParentLevel = 1;
//	apScene_ParentLevelBuffer[0] = this;
//	while(true) {  //親レベル毎のループ
//		iCntSceneSubLevel = 0;
//		has_sub_flg = false;
//		for (int i = 0; i < iCntSceneParentLevel; i++) { //親レベルのシーン数でループ
//			pScene_Sub_tmp = apScene_ParentLevelBuffer[i]->_pSubFirst;
//			if (pScene_Sub_tmp == NULL) {
//				continue;
//			} else {
//				has_sub_flg = true;
//			}
//			do {  //同じ親を持つサブシーンでループ
//				pLordActor = pScene_Sub_tmp->getLordActor();
//				pHeadActor = (GgafHeadActor*)(pLordActor -> _pSubFirst);
//				if (pHeadActor != NULL) {
//					do {
//						if(pHeadActor -> _kind == prm_actorkind01) {
//							apHeadActor01[iIndex01] = pHeadActor;
//							iIndex01++;
//						}
//						if(pHeadActor -> _kind == prm_actorkind02) {
//							apHeadActor02[iIndex02] = pHeadActor;
//							iIndex02++;
//						}
//						if (pHeadActor -> _isLast) {
//							break;
//						} else {
//							pHeadActor = (GgafHeadActor*)(pHeadActor -> _pNext);
//						}
//					} while(true);
//				}
//				if (pScene_Sub_tmp->_isLast) {
//					apScene_SubLevelBuffer[iCntSceneSubLevel] = pScene_Sub_tmp;
//					iCntSceneSubLevel++;
//					//同じ親を持つ最後のシーンだった場合
//					break;
//				} else {
//					apScene_SubLevelBuffer[iCntSceneSubLevel] = pScene_Sub_tmp;
//					pScene_Sub_tmp = pScene_Sub_tmp->_pNext; iCntSceneSubLevel++;
//				}
//				if (iCntSceneSubLevel >= MAXSCENE_PER_LEVEL) {
//					break;//エラー
//				}
//			} while(true);
//		}
//		//そのレベルに1つもサブレベルのシーンが無い場合、終了
//		if (has_sub_flg == false) {
//			break;
//		}
//		//サブを親へ順繰りする
//		for (int i = 0; i < iCntSceneSubLevel; i++) {
//			apScene_ParentLevelBuffer[i] = apScene_SubLevelBuffer[i];
//		}
//		iCntSceneParentLevel = iCntSceneSubLevel;
//	}
//	//総当りの総当りでヒットチェックを行う
//	for (int i = 0; i < iIndex01; i++) {
//		for (int j = 0; j < iIndex02; j++) {
//			if (apHeadActor01[i] == apHeadActor02[j]) {
//				apHeadActor01[i]->executeBumpChkRoundRobin2(apHeadActor02[j]);
//			} else {
//				apHeadActor01[i]->executeBumpChkRoundRobin(apHeadActor02[j]);
//			}
//		}
//	}
//}



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

