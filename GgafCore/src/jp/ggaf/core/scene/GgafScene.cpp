#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//GgafGroupActor* GgafScene::_apGroupActor01[MAX_GROUPACTOR_PER_SCENE];
//GgafGroupActor* GgafScene::_apGroupActor02[MAX_GROUPACTOR_PER_SCENE];

GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _obj_class = Obj_GgafScene;

    _pLordActor = NEW GgafLordActor(this);
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
    OutputDebugStringA("*\n");
#endif
    DELETE_POSSIBLE_NULL(_pLordActor);
}

void GgafScene::nextFrame() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        TRACE("GgafScene::nextFrame() " << getName());
        GgafElement<GgafScene>::nextFrame();
        _pLordActor->nextFrame();
    }
}

void GgafScene::behave() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        TRACE("GgafScene::behave() " << getName());
        GgafElement<GgafScene>::behave();
        _pLordActor->behave();
    }
}

void GgafScene::settleBehavior() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        TRACE("GgafScene::settleBehavior() " << getName());
        GgafElement<GgafScene>::settleBehavior();
        _pLordActor->settleBehavior();
    }
}

void GgafScene::judge() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        TRACE("GgafScene::judge() " << getName());
        GgafElement<GgafScene>::judge();
        _pLordActor->judge();
    }
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

void GgafScene::throwEventToLowerTree(UINT32 prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventToLowerTree(prm_no, prm_pSource);
    _pLordActor->throwEventToLowerTree(prm_no, prm_pSource);
}

void GgafScene::throwEventToUpperTree(UINT32 prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventToUpperTree(prm_no, prm_pSource);
}


void GgafScene::doFinally() {
    if (_n_once == 1 || getParent()->getBehaveingFrame() % _n_once == 0) {
        GgafElement<GgafScene>::doFinally();
        _pLordActor->doFinally();
    }
}

void GgafScene::activateTree() {
    GgafElement<GgafScene>::activateTree();
    _pLordActor->activateTree();
}

void GgafScene::activateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::activateDelay(prm_offset_frames);
    _pLordActor->activateDelay(prm_offset_frames);
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

void GgafScene::inactivateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::inactivateDelay(prm_offset_frames);
    _pLordActor->inactivateDelay(prm_offset_frames);
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

void GgafScene::executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    GgafElement<GgafScene>::executeFuncToLowerTree(pFunc, prm1, prm2);
    _pLordActor->executeFuncToLowerTree(pFunc, prm1, prm2);
}

void GgafScene::reset() {
    GgafElement<GgafScene>::reset();
    _pLordActor->reset();

}
void GgafScene::resetTree() {
    GgafElement<GgafScene>::resetTree();
    _pLordActor->resetTree();
}


void GgafScene::end(frame prm_offset_frames) {
    _pLordActor->end(prm_offset_frames);
    GgafElement<GgafScene>::end(prm_offset_frames);
    //Ç±ÇÃèáî‘ÇÕèdóvÅBãtÇ…Ç∑ÇÈÇ∆ÉSÉ~î†ÇÃâï˙éûÇ…ïsê≥É|ÉCÉìÉ^Ç…Ç»ÇËÇ§ÇÈÇΩÇﬂÅB
}

void GgafScene::clean(int prm_num_cleaning) {
    if (_pLordActor) {
        _pLordActor->clean(prm_num_cleaning);
        if (_pLordActor->_pSubFirst == NULL) {
            DELETE_IMPOSSIBLE_NULL(_pLordActor);
        }
    } else {
        GgafElement<GgafScene>::clean(prm_num_cleaning);
    }
}

GgafLordActor* GgafScene::getLordActor() {
    return _pLordActor;
}

//void GgafScene::executeHitChkGroupActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02) {
//    static GgafScene* pScene;
//    pScene = this;
//    static GgafGroupActor* pGroupActor;
//    pGroupActor = NULL;
//    static int index01, index02;
//    index01 = 0;
//    index02 = 0;
//
//    do {
//        pGroupActor = (GgafGroupActor*)(pScene->getLordActor()->_pSubFirst);
//        if (pGroupActor) {
//            do {
//                if ((pGroupActor->_kind & prm_actorkindmask01) > 0) {
//                    _apGroupActor01[index01] = pGroupActor;
//                    index01++;
//                }
//                if ((pGroupActor->_kind & prm_actorkindmask02) > 0) {
//                    _apGroupActor02[index02] = pGroupActor;
//                    index02++;
//                }
//                if (pGroupActor->_is_last_flg) {
//                    break;
//                } else {
//                    pGroupActor = (GgafGroupActor*)(pGroupActor->_pNext);
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
//            if (_apGroupActor01[i] == _apGroupActor02[j]) {
//                _apGroupActor01[i]->executeHitChk_RoundRobin2(_apGroupActor02[j]);
//            } else {
//                _apGroupActor01[i]->executeHitChk_RoundRobin(_apGroupActor02[j]);
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
    if (_pLordActor) {
        _pLordActor->dump();
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
    if (_pLordActor) {
        _pLordActor->dump(prm_parent + "\t\t\t\t\t\t\t\t");
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

