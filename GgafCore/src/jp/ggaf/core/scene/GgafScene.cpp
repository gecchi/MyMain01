#include "stdafx.h"
using namespace std;

using namespace GgafCore;


GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _obj_class = Obj_GgafScene;

    _pDirector = NEW GgafDirector(this);
    _once_in_n_time = 1;
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
void GgafScene::setRunFrameOnce(int prm_once_in_n_time) {
    if (prm_once_in_n_time <= 1) {
        _once_in_n_time = 1;
    } else {
        _once_in_n_time = prm_once_in_n_time;
    }
}

void GgafScene::addRunFrameOnce(int prm_once_in_n_time) {
    if ((int)_once_in_n_time + prm_once_in_n_time <= 1) {
        _once_in_n_time = 1;
    } else {
        _once_in_n_time += prm_once_in_n_time;
    }
}

void GgafScene::addSubLast(GgafScene* prm_pScene) {
//    prm_pScene->_once_in_n_time = _once_in_n_time;
    GgafElement<GgafScene>::addSubLast(prm_pScene);
}

void GgafScene::nextFrame() {
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::nextFrame();
        _pDirector->nextFrame();
    }
    else {
        //isActiveInTheWorld() を成立させるため、配下の全てのシーンと、
        //それぞれのシーン所属アクター全てに
        //_last_frame_of_god = P_GOD->_frame_of_God;
        //のみを実行する。
        update_last_frame_of_god();
    }
}
void GgafScene::update_last_frame_of_god() {
    GgafElement<GgafScene>::update_last_frame_of_god();
    _pDirector->update_last_frame_of_god();
}


void GgafScene::behave() {
    TRACE("GgafScene::behave() " << getName());
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::behave();
        _pDirector->behave();
    }
}

void GgafScene::settleBehavior() {
    TRACE("GgafScene::settleBehavior() " << getName());
    GgafElement<GgafScene>::settleBehavior();
    _pDirector->settleBehavior();
}

void GgafScene::judge() {
    TRACE("GgafScene::judge() " << getName());
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::judge();
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
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::doFinally();
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
    //この順番は重要。逆にするとゴミ箱の解放時に不正ポインタになりうるため。
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

GgafGod* GgafScene::askGod() {
    if (_pGod == NULL) {
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

void GgafScene::dump() {
    _TRACE_("●"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving_since_onActive<<
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
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLっています");
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
    _TRACE_(prm_parent+"●"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving_since_onActive<<
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
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLっています");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

