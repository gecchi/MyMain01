#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//GgafGroupActor* GgafScene::_apGroupActor01[MAX_GROUPACTOR_PER_SCENE];
//GgafGroupActor* GgafScene::_apGroupActor02[MAX_GROUPACTOR_PER_SCENE];

GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _scene_class = Obj_GgafScene;

    _pLordActor = NEW GgafLordActor(this);
    _progress = -1;
    _progress_prev = -2;
    DWORD x = UINT_MAX/2;
    for (int i = 0; i < 100; i++) {
        _aFrame_ProgressChange[i] = x; //有りえないフレームなら良い
    }
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

void GgafScene::settleBehavior() {
    TRACE("GgafScene::settleBehavior() " << getName());
    GgafElement<GgafScene>::settleBehavior();
    _pLordActor->settleBehavior();
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

void GgafScene::end(DWORD prm_frame_offset) {
    GgafElement<GgafScene>::end(prm_frame_offset);
    _pLordActor->end(prm_frame_offset);
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
//        if (pGroupActor != NULL) {
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
//        if (pScene->_pSubFirst != NULL) {
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
    _TRACE_("●"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_flg<<"("<<_frame_of_life_when_activation<<")");
    if (_pLordActor) {
        _pLordActor->dump();
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst != NULL) {
            while (true) {
                pScene_tmp->dump("\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLにっています");
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
    _TRACE_(prm_parent+"●"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_flg<<"("<<_frame_of_life_when_activation<<")");
    if (_pLordActor) {
        _pLordActor->dump(prm_parent + "\t\t\t\t\t\t\t\t");
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst != NULL) {
            while (true) {
                pScene_tmp->dump(prm_parent + "\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLにっています");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

