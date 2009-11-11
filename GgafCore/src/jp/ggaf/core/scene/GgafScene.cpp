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
        _aFrame_ProgressChange[i] = x; //óLÇËÇ¶Ç»Ç¢ÉtÉåÅ[ÉÄÇ»ÇÁó«Ç¢
    }
}

GgafScene::~GgafScene() {
    TRACE("GgafScene::~GgafScene() " << getName() << " start-->");
    //èäëÆÉAÉNÉ^Å[Çâï˙
    DELETE_POSSIBLE_NULL(_pLordActor);
    TRACE("GgafScene::~GgafScene() " << getName() <<  " <---end");
}

void GgafScene::nextFrame() {
    TRACE("GgafScene::nextFrame() " << getName());
    GgafElement<GgafScene>::nextFrame();
    _pLordActor->nextFrame();
    //êiíªÇçXêV
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

void GgafScene::preDraw() {
    TRACE("GgafScene::preDraw() " << getName());
    GgafElement<GgafScene>::preDraw();
    _pLordActor->preDraw();
}

void GgafScene::draw() {
    TRACE("GgafScene::draw() " << getName());
    GgafElement<GgafScene>::draw();
    _pLordActor->draw();
}

void GgafScene::afterDraw() {
    TRACE("GgafScene::afterDraw() " << getName());
    GgafElement<GgafScene>::afterDraw();
    _pLordActor->afterDraw();
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

void GgafScene::activateAfter(DWORD prm_frame_offset) {
    GgafElement<GgafScene>::activateAfter(prm_frame_offset);
    _pLordActor->activateAfter(prm_frame_offset);
}

void GgafScene::activate() {
    GgafElement<GgafScene>::activate();
    _pLordActor->activate();
}

void GgafScene::activateTreeImmediately() {
    GgafElement<GgafScene>::activateTreeImmediately();
    _pLordActor->activateTreeImmediately();
}

void GgafScene::activateImmediately() {
    GgafElement<GgafScene>::activateImmediately();
    _pLordActor->activateImmediately();
}

void GgafScene::inactivateTree() {
    GgafElement<GgafScene>::inactivateTree();
    _pLordActor->inactivateTree();
}

void GgafScene::inactivateAfter(DWORD prm_frame_offset) {
    GgafElement<GgafScene>::inactivateAfter(prm_frame_offset);
    _pLordActor->inactivateAfter(prm_frame_offset);
}

void GgafScene::inactivate() {
    GgafElement<GgafScene>::inactivate();
    _pLordActor->inactivate();
}

void GgafScene::inactivateTreeImmediately() {
    GgafElement<GgafScene>::inactivateTreeImmediately();
    _pLordActor->inactivateTreeImmediately();
}

void GgafScene::inactivateImmediately() {
    GgafElement<GgafScene>::inactivateImmediately();
    _pLordActor->inactivateImmediately();
}

void GgafScene::pauseTree() {
    GgafElement<GgafScene>::pauseTree();
    _pLordActor->pauseTree();
}

void GgafScene::pause() {
    GgafElement<GgafScene>::pause();
    _pLordActor->pause();
}

void GgafScene::pauseTreeImmediately() {
    GgafElement<GgafScene>::pauseTreeImmediately();
    _pLordActor->pauseTreeImmediately();
}

void GgafScene::pauseImmediately() {
    GgafElement<GgafScene>::pauseImmediately();
    _pLordActor->pauseImmediately();
}

void GgafScene::unpauseTree() {
    GgafElement<GgafScene>::unpauseTree();
    _pLordActor->unpauseTree();
}

void GgafScene::unpause() {
    GgafElement<GgafScene>::unpause();
    _pLordActor->unpause();
}

void GgafScene::unpauseTreeImmediately() {
    GgafElement<GgafScene>::unpauseTreeImmediately();
    _pLordActor->unpauseTreeImmediately();
}

void GgafScene::unpauseImmediately() {
    GgafElement<GgafScene>::unpauseImmediately();
    _pLordActor->unpauseImmediately();
}

void GgafScene::adios(DWORD prm_frame_offset) {
    GgafElement<GgafScene>::adios(prm_frame_offset);
    _pLordActor->adios(prm_frame_offset);
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
                if (pHeadActor->_is_last_flg) {
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

        loop: if (pScene->_is_last_flg) {
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
                _apHeadActor01[i]->executeBumpChk_RoundRobin2(_apHeadActor02[j]);
            } else {
                _apHeadActor01[i]->executeBumpChk_RoundRobin(_apHeadActor02[j]);
            }
        }
    }
}




void GgafScene::executeBumpChkHeadActors2(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
    GgafLinearOctree* pLinearOctree = StgChecker::_pLinearOctree;
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
                if (pHeadActor->_is_last_flg) {
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

        loop: if (pScene->_is_last_flg) {
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
                _apHeadActor01[i]->executeBumpChk_RoundRobin2(_apHeadActor02[j]);
            } else {
                _apHeadActor01[i]->executeBumpChk_RoundRobin(_apHeadActor02[j]);
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
    _TRACE_("Åú"<<_class_name<<"["<<getName()<<"]@"<<_lifeframe<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");
    _pLordActor->dump();
    GgafScene* pScene_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pScene_tmp->dump("\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pScene_tmp->_is_first_flg) {
                break;
            }
        }
    }
}

void GgafScene::dump(string prm_parent) {
    _TRACE_(prm_parent+"Åú"<<_class_name<<"["<<getName()<<"]@"<<_lifeframe<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");
    _pLordActor->dump(prm_parent + "\t\t\t\t\t\t\t\t");
    GgafScene* pScene_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pScene_tmp->dump(prm_parent + "\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pScene_tmp->_is_first_flg) {
                break;
            }
        }
    }
}

