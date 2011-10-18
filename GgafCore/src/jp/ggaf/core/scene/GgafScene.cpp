#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//GgafGroupHead* GgafScene::_apGroupHead01[MAX_GROUPACTOR_PER_SCENE];
//GgafGroupHead* GgafScene::_apGroupHead02[MAX_GROUPACTOR_PER_SCENE];

GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _obj_class = Obj_GgafScene;

    _pDirector = NEW GgafDirector(this);
    _n_once = 1;
#ifdef MY_DEBUG
    _TRACE_("new "<<_class_name<<"("<<this<<")["<<prm_name<<"]");
#else

#endif
}

GgafScene::~GgafScene() {

#ifdef MY_DEBUG
    _TRACE_("delete "<<_class_name<<"("<<this<<")["<<getName()<<"]");
#else
    //OutputDebugStringA("*");
#endif
    DELETE_POSSIBLE_NULL(_pDirector);
}
void GgafScene::setRunFrameOnce(int prm_n_once) {
    if (isActiveScene()) {
        if (prm_n_once <= 1) {
            _n_once = 1;
        } else {
            _n_once = prm_n_once;
        }
    }
}

void GgafScene::setRunFrameOnceTree(int prm_n_once) {
    if (isActiveScene()) {
        if (prm_n_once <= 1) {
            _n_once = 1;
        } else {
            _n_once = prm_n_once;
        }
    }
    if (_pSubFirst) {
        GgafScene* pSceneTemp = _pSubFirst;
        while(true) {
            pSceneTemp->setRunFrameOnceTree(prm_n_once);
            if (pSceneTemp->_is_last_flg) {
                break;
            } else {
                pSceneTemp = pSceneTemp->_pNext;
            }
        }
    }
}
void GgafScene::nextFrame() {
    if (!isActiveScene()) {
        _n_once = 1;
    }

    TRACE("GgafScene::nextFrame() " << getName());
    GgafElement<GgafScene>::nextFrame();
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        _pDirector->nextFrame();
    }
}

void GgafScene::behave() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        TRACE("GgafScene::behave() " << getName());
        GgafElement<GgafScene>::behave();
        _pDirector->behave();
    }
}

void GgafScene::settleBehavior() {
    TRACE("GgafScene::settleBehavior() " << getName());
    GgafElement<GgafScene>::settleBehavior();
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        _pDirector->settleBehavior();
    }
}

void GgafScene::judge() {
    TRACE("GgafScene::judge() " << getName());
    GgafElement<GgafScene>::judge();
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        _pDirector->judge();
    }
}

void GgafScene::preDraw() {
    TRACE("GgafScene::preDraw() " << getName());
    GgafElement<GgafScene>::preDraw();
    _pDirector->preDraw();
}

void GgafScene::draw() {
    TRACE("GgafScene::draw() " << getName());
    GgafElement<GgafScene>::draw();
    _pDirector->draw();
}

void GgafScene::afterDraw() {
    TRACE("GgafScene::afterDraw() " << getName());
    GgafElement<GgafScene>::afterDraw();
    _pDirector->afterDraw();
}

void GgafScene::throwEventToLowerTree(UINT32 prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventToLowerTree(prm_no, prm_pSource);
    _pDirector->throwEventToLowerTree(prm_no, prm_pSource);
}

void GgafScene::throwEventToUpperTree(UINT32 prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventToUpperTree(prm_no, prm_pSource);
}


void GgafScene::doFinally() {
    GgafElement<GgafScene>::doFinally();
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        _pDirector->doFinally();
    }
}

void GgafScene::activateTree() {
    GgafElement<GgafScene>::activateTree();
    _pDirector->activateTree();
}

void GgafScene::activateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::activateDelay(prm_offset_frames);
    _pDirector->activateDelay(prm_offset_frames);
}

void GgafScene::activate() {
    GgafElement<GgafScene>::activate();
    _pDirector->activate();
}

void GgafScene::activateTreeImmediately() {
    GgafElement<GgafScene>::activateTreeImmediately();
    _pDirector->activateTreeImmediately();
}

void GgafScene::activateImmediately() {
    GgafElement<GgafScene>::activateImmediately();
    _pDirector->activateImmediately();
}

void GgafScene::inactivateTree() {
    GgafElement<GgafScene>::inactivateTree();
    _pDirector->inactivateTree();
}

void GgafScene::inactivateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::inactivateDelay(prm_offset_frames);
    _pDirector->inactivateDelay(prm_offset_frames);
}

void GgafScene::inactivate() {
    GgafElement<GgafScene>::inactivate();
    _pDirector->inactivate();
}

void GgafScene::inactivateTreeImmediately() {
    GgafElement<GgafScene>::inactivateTreeImmediately();
    _pDirector->inactivateTreeImmediately();
}

void GgafScene::inactivateImmediately() {
    GgafElement<GgafScene>::inactivateImmediately();
    _pDirector->inactivateImmediately();
}

void GgafScene::pauseTree() {
    GgafElement<GgafScene>::pauseTree();
    _pDirector->pauseTree();
}

void GgafScene::pause() {
    GgafElement<GgafScene>::pause();
    _pDirector->pause();
}

void GgafScene::pauseTreeImmediately() {
    GgafElement<GgafScene>::pauseTreeImmediately();
    _pDirector->pauseTreeImmediately();
}

void GgafScene::pauseImmediately() {
    GgafElement<GgafScene>::pauseImmediately();
    _pDirector->pauseImmediately();
}

void GgafScene::unpauseTree() {
    GgafElement<GgafScene>::unpauseTree();
    _pDirector->unpauseTree();
}

void GgafScene::unpause() {
    GgafElement<GgafScene>::unpause();
    _pDirector->unpause();
}

void GgafScene::unpauseTreeImmediately() {
    GgafElement<GgafScene>::unpauseTreeImmediately();
    _pDirector->unpauseTreeImmediately();
}

void GgafScene::unpauseImmediately() {
    GgafElement<GgafScene>::unpauseImmediately();
    _pDirector->unpauseImmediately();
}

void GgafScene::executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    GgafElement<GgafScene>::executeFuncToLowerTree(pFunc, prm1, prm2);
    _pDirector->executeFuncToLowerTree(pFunc, prm1, prm2);
}

void GgafScene::reset() {
    GgafElement<GgafScene>::reset();
    _pDirector->reset();

}
void GgafScene::resetTree() {
    GgafElement<GgafScene>::resetTree();
    _pDirector->resetTree();
}


void GgafScene::end(frame prm_offset_frames) {
    _pDirector->end(prm_offset_frames);
    GgafElement<GgafScene>::end(prm_offset_frames);
    //Ç±ÇÃèáî‘ÇÕèdóvÅBãtÇ…Ç∑ÇÈÇ∆ÉSÉ~î†ÇÃâï˙éûÇ…ïsê≥É|ÉCÉìÉ^Ç…Ç»ÇËÇ§ÇÈÇΩÇﬂÅB
}

void GgafScene::clean(int prm_num_cleaning) {
    if (_pDirector) {
        _pDirector->clean(prm_num_cleaning);
        if (_pDirector->_pSubFirst == NULL) {
            DELETE_IMPOSSIBLE_NULL(_pDirector);
        }
    } else {
        GgafElement<GgafScene>::clean(prm_num_cleaning);
    }
}

GgafDirector* GgafScene::getDirector() {
    return _pDirector;
}

//void GgafScene::executeHitChkGroupActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
//    static GgafScene* pScene;
//    pScene = this;
//    static GgafGroupHead* pGroupHead;
//    pGroupHead = NULL;
//    static int index01, index02;
//    index01 = 0;
//    index02 = 0;
//
//    do {
//        pGroupHead = (GgafGroupHead*)(pScene->getDirector()->_pSubFirst);
//        if (pGroupHead) {
//            do {
//                if ((pGroupHead->_kind & prm_actorkindmask01) > 0) {
//                    _apGroupHead01[index01] = pGroupHead;
//                    index01++;
//                }
//                if ((pGroupHead->_kind & prm_actorkindmask02) > 0) {
//                    _apGroupHead02[index02] = pGroupHead;
//                    index02++;
//                }
//                if (pGroupHead->_is_last_flg) {
//                    break;
//                } else {
//                    pGroupHead = (GgafGroupHead*)(pGroupHead->_pNext);
//                    continue;
//                }
//            } while (true);
//        }
//
//        if (pScene->_pSubFirst) {
//            pScene = pScene->_pSubFirst;
//            continue;
//        }
//
//        loop: if (pScene->_is_last_flg) {
//            if (pScene == this) {
//                break;
//            } else {
//                if (pScene->_pParent == this) {
//                    break;
//                } else {
//                    pScene = pScene->_pParent;
//                    goto loop;
//                }
//            }
//        } else {
//            pScene = pScene->_pNext;
//            continue;
//        }
//    } while (true);
//
//    for (int i = 0; i < index01; i++) {
//        for (int j = 0; j < index02; j++) {
//            if (_apGroupHead01[i] == _apGroupHead02[j]) {
//                _apGroupHead01[i]->executeHitChk_RoundRobin2(_apGroupHead02[j]);
//            } else {
//                _apGroupHead01[i]->executeHitChk_RoundRobin(_apGroupHead02[j]);
//            }
//        }
//    }
//}



GgafGod* GgafScene::askGod() {
    if (_pGod == NULL) {
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

void GgafScene::dump() {
    _TRACE_("Åú"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving_since_onActive<<
                                                                "/"<<
                                                                _frame_of_behaving<<
                                                                "/"<<
                                                                _frame_of_life<<
                                                                ","<<
                                                                _was_initialize_flg<<
                                                                ","<<
                                                                _can_live_flg<<
                                                                _is_active_flg<<
                                                                ","<<
                                                                _will_activate_after_flg<<
                                                                "("<<_frame_of_life_when_activation<<")"<<
                                                                _on_change_to_active_flg<<
                                                                ","<<
                                                                _will_inactivate_after_flg<<
                                                                "("<<_frame_of_life_when_inactivation<<")"<<
                                                                _on_change_to_inactive_flg<<
                                                                ","<<
                                                                _will_end_after_flg<<
                                                                "("<<(_frame_of_life_when_end==MAXDWORD ? 0 : _frame_of_life_when_end)<<")"<<
                                                                ","<<
                                                                 _was_paused_flg<<
                                                                _was_paused_flg_in_next_frame<<
                                                                _will_mv_first_in_next_frame_flg<<
                                                                _will_mv_last_in_next_frame_flg
                                                                );
    if (_pDirector) {
        _pDirector->dump();
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst) {
            while (true) {
                pScene_tmp->dump("\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ¡ÇƒÇ¢Ç‹Ç∑");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

void GgafScene::dump(string prm_parent) {
    _TRACE_(prm_parent+"Åú"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving_since_onActive<<
                                                                           "/"<<
                                                                           _frame_of_behaving<<
                                                                           "/"<<
                                                                           _frame_of_life<<
                                                                           ","<<
                                                                           _was_initialize_flg<<
                                                                           ","<<
                                                                           _can_live_flg<<
                                                                           _is_active_flg<<
                                                                           ","<<
                                                                           _will_activate_after_flg<<
                                                                           "("<<_frame_of_life_when_activation<<")"<<
                                                                           _on_change_to_active_flg<<
                                                                           ","<<
                                                                           _will_inactivate_after_flg<<
                                                                           "("<<_frame_of_life_when_inactivation<<")"<<
                                                                           _on_change_to_inactive_flg<<
                                                                           ","<<
                                                                           _will_end_after_flg<<
                                                                           "("<<(_frame_of_life_when_end==MAXDWORD ? 0 : _frame_of_life_when_end)<<")"<<
                                                                           ","<<
                                                                           _was_paused_flg<<
                                                                           _was_paused_flg_in_next_frame<<
                                                                           _will_mv_first_in_next_frame_flg<<
                                                                           _will_mv_last_in_next_frame_flg
                                                                           );
    if (_pDirector) {
        _pDirector->dump(prm_parent + "\t\t\t\t\t\t\t\t");
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst) {
            while (true) {
                pScene_tmp->dump(prm_parent + "\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ¡ÇƒÇ¢Ç‹Ç∑");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

