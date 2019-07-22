#include "jp/ggaf/core/scene/Scene.h"

#include "jp/ggaf/core/God.h"
#include "jp/ggaf/core/actor/SceneMediator.h"

using namespace GgafCore;

Scene::Scene(const char* prm_name, SceneMediator* prm_pSceneMediator) : Element<Scene> (prm_name) {
    _class_name = "Scene";
    _obj_class |= Obj_ggaf_Scene;
    if (prm_pSceneMediator) {
        _pSceneMediator = prm_pSceneMediator;
    } else {
        _pSceneMediator =  NEW SceneMediator(this);
    }
#ifdef MY_DEBUG
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
#else

#endif
}

Scene::~Scene() {
    if (pGOD->_is_loving_flg) {
        pGOD->pardon(this); //自身が望んだ命を破棄
    } else {
        //アプリ終了処理時のため、愛ももれなく掃除されるため考慮不要
    }
#ifdef MY_DEBUG
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
#else
    //OutputDebugStringA("*");
#endif
    GGAF_DELETE_NULLABLE(_pSceneMediator);
}

void Scene::appendChild(Scene* prm_pScene) {
    Element<Scene>::appendChild(prm_pScene);
}

void Scene::nextFrame() {
    Element<Scene>::nextFrame();
    frame f = _pSceneMediator->_frame_of_life;
    if (_is_active_in_the_tree_flg ||
        f <= _pSceneMediator->_frame_of_life_when_activation ||
        f <= _pSceneMediator->_frame_of_life_when_inactivation ||
        f <= _pSceneMediator->_frame_of_life_when_end)
    {
        _pSceneMediator->nextFrame();
    }
}

void Scene::behave() {
    Element<Scene>::behave();
    _pSceneMediator->behave();
}

void Scene::settleBehavior() {
    Element<Scene>::settleBehavior();
    _pSceneMediator->settleBehavior();
}

void Scene::preJudge() {
    Element<Scene>::preJudge();
    _pSceneMediator->preJudge();
}

void Scene::judge() {
    Element<Scene>::judge();
    _pSceneMediator->judge();
}

void Scene::preDraw() {
    Element<Scene>::preDraw();
    _pSceneMediator->preDraw();
}

void Scene::draw() {
    Element<Scene>::draw();
    _pSceneMediator->draw();
}

void Scene::afterDraw() {
    Element<Scene>::afterDraw();
    _pSceneMediator->afterDraw();
}

void Scene::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    Element<Scene>::throwEventLowerTree(prm_no, prm_pSource);
    _pSceneMediator->throwEventLowerTree(prm_no, prm_pSource);
}

void Scene::throwEventLowerTree(hashval prm_no) {
    Element<Scene>::throwEventLowerTree(prm_no);
    _pSceneMediator->throwEventLowerTree(prm_no);
}

void Scene::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    Element<Scene>::throwEventUpperTree(prm_no, prm_pSource);
}

void Scene::throwEventUpperTree(hashval prm_no) {
    Element<Scene>::throwEventUpperTree(prm_no);
}

void Scene::doFinally() {
    //doFinally()は_once_in_n_timeの影響を受けない。
    //必ず毎フレーム実行したい処理はprocessFinal()に書くことができることとする。
    Element<Scene>::doFinally();
    _pSceneMediator->doFinally();
}

void Scene::activateTree() {
    Element<Scene>::activateTree();
    _pSceneMediator->activateTree();
}

void Scene::activateDelay(frame prm_offset_frames) {
    Element<Scene>::activateDelay(prm_offset_frames);
    _pSceneMediator->activateDelay(prm_offset_frames);
}

void Scene::activate() {
    Element<Scene>::activate();
    _pSceneMediator->activate();
}

void Scene::activateTreeImmed() {
    Element<Scene>::activateTreeImmed();
    _pSceneMediator->activateTreeImmed();
}

void Scene::activateImmed() {
    Element<Scene>::activateImmed();
    _pSceneMediator->activateImmed();
}

void Scene::inactivateTree() {
    Element<Scene>::inactivateTree();
    _pSceneMediator->inactivateTree();
}

void Scene::inactivateDelay(frame prm_offset_frames) {
    Element<Scene>::inactivateDelay(prm_offset_frames);
    _pSceneMediator->inactivateDelay(prm_offset_frames);
}

void Scene::inactivate() {
    Element<Scene>::inactivate();
    _pSceneMediator->inactivate();
}

void Scene::inactivateTreeImmed() {
    Element<Scene>::inactivateTreeImmed();
    _pSceneMediator->inactivateTreeImmed();
}

void Scene::inactivateImmed() {
    Element<Scene>::inactivateImmed();
    _pSceneMediator->inactivate();
}

void Scene::pauseTree() {
    Element<Scene>::pauseTree();
    _pSceneMediator->pauseTree();
}

void Scene::pause() {
    Element<Scene>::pause();
    _pSceneMediator->pause();
}

void Scene::unpauseTree() {
    Element<Scene>::unpauseTree();
    _pSceneMediator->unpauseTree();
}

void Scene::unpause() {
    Element<Scene>::unpause();
    _pSceneMediator->unpause();
}

void Scene::executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
    Element<Scene>::executeFuncLowerTree(pFunc, prm1, prm2, prm3);
    _pSceneMediator->executeFuncLowerTree(pFunc, prm1, prm2, prm3);
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
    _pSceneMediator->reset();
}

void Scene::resetTree() {
    Element<Scene>::resetTree();
    _pSceneMediator->resetTree();
}

void Scene::end(frame prm_offset_frames) {
    _pSceneMediator->end(prm_offset_frames);
    if (prm_offset_frames > 3) {
        Element<Scene>::end(prm_offset_frames-2);
    } else {
        Element<Scene>::end(prm_offset_frames);
    }
    //この順番は重要。逆にするとゴミ箱の解放時に不正ポインタになりうるため。
}

void Scene::sayonara(frame prm_offset_frames) {
    _pSceneMediator->sayonara(prm_offset_frames);
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
    if (_pSceneMediator) {
        _pSceneMediator->clean(prm_num_cleaning);
        if (_pSceneMediator->_pChildFirst == nullptr) {
            GGAF_DELETE(_pSceneMediator);
        }
    } else {
        Element<Scene>::clean(prm_num_cleaning);
    }
}

God* Scene::askGod() {
    if (_pGod == nullptr) {
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

void Scene::dump() {
    _TRACE_("●"<<NODE_INFO<<DUMP_FLGS);
    if (_pSceneMediator) {
        _pSceneMediator->dump();
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
    _TRACE_(prm_parent+"●"<<NODE_INFO<<DUMP_FLGS);
    if (_pSceneMediator) {
        _pSceneMediator->dump(prm_parent + "\t\t\t\t\t\t\t\t");
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

