#include "jp/ggaf/core/scene/Scene.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/core/actor/SceneChief.h"

using namespace GgafCore;

Scene::Scene(const char* prm_name, SceneChief* prm_pSceneChief) : Element<Scene> (prm_name) {
    _class_name = "Scene";
    _obj_class |= Obj_ggaf_Scene;
    if (prm_pSceneChief) {
        _pSceneChief = prm_pSceneChief;
    } else {
        _pSceneChief =  NEW SceneChief(this);
    }

    _was_paused_flg = false;
    _was_paused_flg_in_next_frame = false;
#ifdef MY_DEBUG
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
#else

#endif
}

Scene::~Scene() {
    if (pCARETAKER->_is_loving_flg) {
        pCARETAKER->repent(this); //自身が望んだ命を破棄
    } else {
        //アプリ終了処理時のため、愛ももれなく掃除されるため考慮不要
    }
#ifdef MY_DEBUG
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
#else
    //OutputDebugStringA("*");
#endif
    GGAF_DELETE_NULLABLE(_pSceneChief);
}

void Scene::appendChild(Scene* prm_pScene) {
    Element<Scene>::appendChild(prm_pScene);
}

void Scene::nextFrame() {
    Element<Scene>::nextFrame();
    frame f = _pSceneChief->_frame_of_life;
    if (_is_active_in_the_tree_flg ||
        f <= _pSceneChief->_frame_of_life_when_activation ||
        f <= _pSceneChief->_frame_of_life_when_inactivation ||
        f <= _pSceneChief->_frame_of_life_when_end)
    {
        if (!_was_paused_flg) {
            _pSceneChief->nextFrame();
        }
    }
}

void Scene::processNextFrame() {
    _was_paused_flg = _was_paused_flg_in_next_frame;
    if (!_was_paused_flg) {
        Element<Scene>::processNextFrame();
    }
}

void Scene::behave() {
    if (!_was_paused_flg) {
        Element<Scene>::behave();
        _pSceneChief->behave();
    }
}

void Scene::settleBehavior() {
    if (!_was_paused_flg) {
        Element<Scene>::settleBehavior();
        _pSceneChief->settleBehavior();
    }
}

void Scene::judge() {
    if (!_was_paused_flg) {
        Element<Scene>::judge();
        _pSceneChief->judge();
    }
}
void Scene::preDraw() {
    Element<Scene>::preDraw();
    _pSceneChief->preDraw();
}

void Scene::draw() {
    Element<Scene>::draw();
    _pSceneChief->draw();
}

void Scene::afterDraw() {
    Element<Scene>::afterDraw();
    _pSceneChief->afterDraw();
}

void Scene::throwEventLowerTree(eventval prm_event_val, void* prm_pSource) {
    Element<Scene>::throwEventLowerTree(prm_event_val, prm_pSource);
    _pSceneChief->throwEventLowerTree(prm_event_val, prm_pSource);
}

void Scene::throwEventLowerTree(eventval prm_event_val) {
    Element<Scene>::throwEventLowerTree(prm_event_val);
    _pSceneChief->throwEventLowerTree(prm_event_val);
}

void Scene::throwEventUpperTree(eventval prm_event_val, void* prm_pSource) {
    Element<Scene>::throwEventUpperTree(prm_event_val, prm_pSource);
}

void Scene::throwEventUpperTree(eventval prm_event_val) {
    Element<Scene>::throwEventUpperTree(prm_event_val);
}

void Scene::doFinally() {
    if (!_was_paused_flg) {
        Element<Scene>::doFinally();
        _pSceneChief->doFinally();
    }
}

void Scene::activateTree() {
    Element<Scene>::activateTree();
    _pSceneChief->activateTree();
}

void Scene::activateDelay(frame prm_offset_frames) {
    Element<Scene>::activateDelay(prm_offset_frames);
    _pSceneChief->activateDelay(prm_offset_frames);
}

void Scene::activate() {
    Element<Scene>::activate();
    _pSceneChief->activate();
}

void Scene::activateTreeImmed() {
    Element<Scene>::activateTreeImmed();
    _pSceneChief->activateTreeImmed();
}

void Scene::activateImmed() {
    Element<Scene>::activateImmed();
    _pSceneChief->activateImmed();
}

void Scene::inactivateTree() {
    Element<Scene>::inactivateTree();
    _pSceneChief->inactivateTree();
}

void Scene::inactivateDelay(frame prm_offset_frames) {
    Element<Scene>::inactivateDelay(prm_offset_frames);
    _pSceneChief->inactivateDelay(prm_offset_frames);
}

void Scene::inactivate() {
    Element<Scene>::inactivate();
    _pSceneChief->inactivate();
}

void Scene::inactivateTreeImmed() {
    Element<Scene>::inactivateTreeImmed();
    _pSceneChief->inactivateTreeImmed();
}

void Scene::inactivateImmed() {
    Element<Scene>::inactivateImmed();
    _pSceneChief->inactivate();
}

void Scene::executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
    Element<Scene>::executeFuncLowerTree(pFunc, prm1, prm2, prm3);
    _pSceneChief->executeFuncLowerTree(pFunc, prm1, prm2, prm3);
}

void Scene::executeFuncLowerSceneTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
    if (_can_live_flg && _is_active_flg) {
        pFunc(this, prm1, prm2, prm3);
        Scene* pScene = _pChildFirst;
        while (pScene) {
            pScene->executeFuncLowerSceneTree(pFunc, prm1, prm2, prm3);
            if (pScene->_is_last_flg) {
                break;
            } else {
                pScene = pScene->_pNext;
            }
        }
    }
}

void Scene::reset() {
    Element<Scene>::reset();
    _pSceneChief->reset();
}

void Scene::resetTree() {
    Element<Scene>::resetTree();
    _pSceneChief->resetTree();
}

void Scene::end(frame prm_offset_frames) {
    _pSceneChief->end(prm_offset_frames);
    if (prm_offset_frames > 3) {
        Element<Scene>::end(prm_offset_frames-2);
    } else {
        Element<Scene>::end(prm_offset_frames);
    }
    //この順番は重要。逆にするとゴミ箱の解放時に不正ポインタになりうるため。
}

void Scene::sayonara(frame prm_offset_frames) {
    _pSceneChief->sayonara(prm_offset_frames);
    if (prm_offset_frames > 3) {
        Element<Scene>::end(prm_offset_frames-2);
    } else {
        Element<Scene>::end(prm_offset_frames);
    }
    Scene* pScene = _pChildFirst;
    while (pScene) {
        pScene->sayonara(prm_offset_frames);
        if (pScene->_is_last_flg) {
            break;
        } else {
            pScene = pScene->_pNext;
        }
    }
}

void Scene::clean(int prm_num_cleaning) {
    if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
        return;
    }
    if (_pSceneChief) {
        _pSceneChief->clean(prm_num_cleaning);
        if (_pSceneChief->_pChildFirst == nullptr) {
            GGAF_DELETE(_pSceneChief);
        }
    } else {
        Element<Scene>::clean(prm_num_cleaning);
    }
}

Caretaker* Scene::askCaretaker() {
    if (_pCaretaker == nullptr) {
        _pCaretaker = getParent()->askCaretaker();
    }
    return _pCaretaker;
}

void Scene::dump() {
    _TRACE_("●"<<NODE_INFO<< DUMP_FLGS_SCENE);
    if (_pSceneChief) {
        _pSceneChief->dump();
        Scene* pScene_tmp = _pChildFirst;
        while (pScene_tmp) {
            pScene_tmp->dump("\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<NODE_INFO<<" のnextがnullptrっています");
                break;
            }
            if (pScene_tmp->_is_first_flg) {
                break;
            }
        }
    }
}

void Scene::dump(std::string prm_parent) {
    _TRACE_(prm_parent+"●"<<NODE_INFO<<DUMP_FLGS_SCENE);
    if (_pSceneChief) {
        _pSceneChief->dump(prm_parent + "\t\t\t\t\t\t\t\t");
        Scene* pScene_tmp = _pChildFirst;
        while (pScene_tmp) {
            pScene_tmp->dump(prm_parent + "\t");
            if (pScene_tmp->_pNext) {
                pScene_tmp = pScene_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<NODE_INFO<<" のnextがnullptrっています");
                break;
            }
            if (pScene_tmp->_is_first_flg) {
                break;
            }
        }
    }
}

