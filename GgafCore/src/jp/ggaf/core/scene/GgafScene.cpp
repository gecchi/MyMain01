#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafHeadActor* GgafScene::_apHeadActor01[MAX_HEADACTOR_PER_SCENE];
GgafHeadActor* GgafScene::_apHeadActor02[MAX_HEADACTOR_PER_SCENE];

GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _pLordActor = NEW GgafLordActor(this);
    _progress = -1;
    _progress_prev = -2;
    DWORD x = UINT_MAX/2;
    for (int i = 0; i < 100; i++) {
        _dwFrame_ProgressChange[i] = x; //有りえないフレームなら良い
        }
    }

GgafScene::~GgafScene() {
    TRACE("GgafScene::~GgafScene() " << getName() << " start-->");
    //所属アクターを解放
    DELETE_POSSIBLE_NULL(_pLordActor);
    TRACE("GgafScene::~GgafScene() " << getName() <<  " <---end");
}

void GgafScene::nextFrame() {
    TRACE("GgafScene::nextFrame() " << getName());
    GgafElement<GgafScene>::nextFrame();
    _pLordActor->nextFrame();
    //進捗を更新
    _progress_prev = _progress;
    _progress = _progress_nextframe;
}

void GgafScene::behave() {
    TRACE("GgafScene::behave() " << getName());
    GgafElement<GgafScene>::behave();
    _pLordActor->behave();
}

void GgafScene::judge() {
    TRACE("GgafScene::judge() " << getName());
    GgafElement<GgafScene>::judge();
    _pLordActor->judge();
}

void GgafScene::drawPrior() {
    TRACE("GgafScene::drawPrior() " << getName());
    GgafElement<GgafScene>::drawPrior();
    _pLordActor->drawPrior();
}

void GgafScene::drawMain() {
    TRACE("GgafScene::drawMain() " << getName());
    GgafElement<GgafScene>::drawMain();
    _pLordActor->drawMain();
}

void GgafScene::drawTerminate() {
    TRACE("GgafScene::drawTerminate() " << getName());
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

void GgafScene::activateTree() {
    GgafElement<GgafScene>::activateTree();
    _pLordActor->activateTree();
}

void GgafScene::activateTreeAfter(DWORD prm_dwFrameOffset) {
    GgafElement<GgafScene>::activateTreeAfter(prm_dwFrameOffset);
    _pLordActor->activateTreeAfter(prm_dwFrameOffset);
}

void GgafScene::activateAlone() {
    GgafElement<GgafScene>::activateAlone();
    _pLordActor->activateAlone();
}

void GgafScene::activateTreeNow() {
    GgafElement<GgafScene>::activateTreeNow();
    _pLordActor->activateTreeNow();
}

void GgafScene::activateAloneNow() {
    GgafElement<GgafScene>::activateAloneNow();
    _pLordActor->activateAloneNow();
}

void GgafScene::inactivateTree() {
    GgafElement<GgafScene>::inactivateTree();
    _pLordActor->inactivateTree();
}

void GgafScene::inactivateTreeAfter(DWORD prm_dwFrameOffset) {
    GgafElement<GgafScene>::inactivateTreeAfter(prm_dwFrameOffset);
    _pLordActor->inactivateTreeAfter(prm_dwFrameOffset);
}

void GgafScene::inactivateAlone() {
    GgafElement<GgafScene>::inactivateAlone();
    _pLordActor->inactivateAlone();
}

void GgafScene::inactivateTreeNow() {
    GgafElement<GgafScene>::inactivateTreeNow();
    _pLordActor->inactivateTreeNow();
}

void GgafScene::inactivateAloneNow() {
    GgafElement<GgafScene>::inactivateAloneNow();
    _pLordActor->inactivateAloneNow();
}

void GgafScene::pauseTree() {
    GgafElement<GgafScene>::pauseTree();
    _pLordActor->pauseTree();
}

void GgafScene::pauseAlone() {
    GgafElement<GgafScene>::pauseAlone();
    _pLordActor->pauseAlone();
}

void GgafScene::pauseTreeNow() {
    GgafElement<GgafScene>::pauseTreeNow();
    _pLordActor->pauseTreeNow();
}

void GgafScene::pauseAloneNow() {
    GgafElement<GgafScene>::pauseAloneNow();
    _pLordActor->pauseAloneNow();
}

void GgafScene::unpauseTree() {
    GgafElement<GgafScene>::unpauseTree();
    _pLordActor->unpauseTree();
}

void GgafScene::unpauseAlone() {
    GgafElement<GgafScene>::unpauseAlone();
    _pLordActor->unpauseAlone();
}

void GgafScene::unpauseTreeNow() {
    GgafElement<GgafScene>::unpauseTreeNow();
    _pLordActor->unpauseTreeNow();
}

void GgafScene::unpauseAloneNow() {
    GgafElement<GgafScene>::unpauseAloneNow();
    _pLordActor->unpauseAloneNow();
}

void GgafScene::hideTree() {
    GgafElement<GgafScene>::hideTree();
    _pLordActor->hideTree();
}

void GgafScene::hideAlone() {
    GgafElement<GgafScene>::hideAlone();
    _pLordActor->hideAlone();
}

void GgafScene::hideTreeNow() {
    GgafElement<GgafScene>::hideTreeNow();
    _pLordActor->hideTreeNow();
}

void GgafScene::hideAloneNow() {
    GgafElement<GgafScene>::hideAloneNow();
    _pLordActor->hideAloneNow();
}

void GgafScene::showTree() {
    GgafElement<GgafScene>::showTree();
    _pLordActor->showTree();
}

void GgafScene::showAlone() {
    GgafElement<GgafScene>::showAlone();
    _pLordActor->showAlone();
}

void GgafScene::showTreeNow() {
    GgafElement<GgafScene>::showTreeNow();
    _pLordActor->showTreeNow();
}

void GgafScene::showAloneNow() {
    GgafElement<GgafScene>::showAloneNow();
    _pLordActor->showAloneNow();
}

void GgafScene::seeYa(DWORD prm_dwFrameOffset) {
    GgafElement<GgafScene>::seeYa(prm_dwFrameOffset);
    _pLordActor->seeYa(prm_dwFrameOffset);
}

void GgafScene::cleane(int prm_num_cleaning) {
    GgafElement<GgafScene>::cleane(prm_num_cleaning);
    _pLordActor->cleane(prm_num_cleaning);
}

GgafLordActor* GgafScene::getLordActor() {
    return _pLordActor;
}

void GgafScene::executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
    static GgafScene* pScene;
    pScene = this;
    static GgafHeadActor* pHeadActor;
    pHeadActor = NULL;
    static int index01, index02;
    index01 = 0;
    index02 = 0;

    do {
        pHeadActor = (GgafHeadActor*)(pScene->getLordActor()->_pSubFirst);
        if (pHeadActor != NULL) {
            do {
                if ((pHeadActor->_kind & prm_actorkindmask01) > 0) {
                    _apHeadActor01[index01] = pHeadActor;
                    index01++;
                }
                if ((pHeadActor->_kind & prm_actorkindmask02) > 0) {
                    _apHeadActor02[index02] = pHeadActor;
                    index02++;
                }
                if (pHeadActor->_isLastFlg) {
                    break;
                } else {
                    pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
                    continue;
                }
            } while (true);
        }

        if (pScene->_pSubFirst != NULL) {
            pScene = pScene->_pSubFirst;
            continue;
        }

        loop: if (pScene->_isLastFlg) {
            if (pScene == this) {
                break;
            } else {
                if (pScene->_pParent == this) {
                    break;
                } else {
                    pScene = pScene->_pParent;
                    goto loop;
                }
            }
        } else {
            pScene = pScene->_pNext;
            continue;
        }
    } while (true);

    for (int i = 0; i < index01; i++) {
        for (int j = 0; j < index02; j++) {
            if (_apHeadActor01[i] == _apHeadActor02[j]) {
                _apHeadActor01[i]->executeBumpChkRoundRobin2(_apHeadActor02[j]);
            } else {
                _apHeadActor01[i]->executeBumpChkRoundRobin(_apHeadActor02[j]);
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
    _TRACE_("●"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_isActiveFlg<<_wasPausedFlg<<_wasHiddenFlg<<_canLiveFlg<<","<<_willActivateAtNextFrameFlg<<_willPauseAtNextFrameFlg<<_willBlindAtNextFrameFlg<<_willBeAliveAtNextFrameFlg<<","<<_willActivateAfterFrameFlg<<"("<<_dwGodFremeWhenActive<<")");
    _pLordActor->dump();
    GgafScene* pScene_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pScene_tmp->dump("\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pScene_tmp->_isFirstFlg) {
                break;
            }
        }
    }
}

void GgafScene::dump(string prm_parent) {
    _TRACE_(prm_parent+"●"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_isActiveFlg<<_wasPausedFlg<<_wasHiddenFlg<<_canLiveFlg<<","<<_willActivateAtNextFrameFlg<<_willPauseAtNextFrameFlg<<_willBlindAtNextFrameFlg<<_willBeAliveAtNextFrameFlg<<","<<_willActivateAfterFrameFlg<<"("<<_dwGodFremeWhenActive<<")");
    _pLordActor->dump(prm_parent + "\t\t\t\t\t\t\t\t");
    GgafScene* pScene_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pScene_tmp->dump(prm_parent + "\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pScene_tmp->_isFirstFlg) {
                break;
            }
        }
    }
}

