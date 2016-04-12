#include "jp/ggaf/core/scene/GgafScene.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/GgafFactory.h"

using namespace GgafCore;

GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    _class_name = "GgafScene";
    _obj_class |= Obj_GgafScene;

    _pSceneDirector = NEW GgafSceneDirector(this);
    _once_in_n_time = 1;
#ifdef MY_DEBUG
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
#else

#endif
}

GgafScene::~GgafScene() {
    if (GgafFactory::_is_working_flg) {
        GgafFactory::removeOrder(this); //自身が注文しっぱなしの商品を掃除
    } else {
        //アプリ終了処理時のため、工場ももれなく掃除されるため考慮不要
    }
#ifdef MY_DEBUG
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
#else
    //OutputDebugStringA("*");
#endif
    GGAF_DELETE_NULLABLE(_pSceneDirector);
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
//    _TRACE_("GgafScene::nextFrame() "<<this<<" ★"<<NODE_INFO<<DUMP_FLGS);
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
//        _TRACE_("nextFrame OK _once_in_n_time="<<_once_in_n_time<<" P_GOD->_frame_of_God="<<P_GOD->_frame_of_God);
        GgafElement<GgafScene>::nextFrame();
        if(_pSceneDirector) {
            _pSceneDirector->nextFrame();
        }
    }
//    } else {
//		isActive()?
//        //isActiveInTheTree() を成立させるため、配下の全てのシーンと、
//        //それぞれのシーン所属アクター全てに
//        //_last_frame_of_god = P_GOD->_frame_of_God;
//        //のみを実行する。
//        update_last_frame_of_god();
//    }
}
//void GgafScene::update_last_frame_of_god() {
//    GgafElement<GgafScene>::update_last_frame_of_god();
//    _pSceneDirector->update_last_frame_of_god();
//}


void GgafScene::behave() {
//    _TRACE_("GgafScene::behave() "<<this<<" ★"<<NODE_INFO<<DUMP_FLGS);
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
//        _TRACE_("behave OK _once_in_n_time="<<_once_in_n_time<<" P_GOD->_frame_of_God="<<P_GOD->_frame_of_God);
        GgafElement<GgafScene>::behave();
        _pSceneDirector->behave();
    }
}

void GgafScene::settleBehavior() {
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::settleBehavior();
        _pSceneDirector->settleBehavior();
    }
}

void GgafScene::judge() {
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::judge();
        _pSceneDirector->judge();
    }
}

void GgafScene::preDraw() {
    GgafElement<GgafScene>::preDraw();
    _pSceneDirector->preDraw();
}

void GgafScene::draw() {
    GgafElement<GgafScene>::draw();
    _pSceneDirector->draw();
}

void GgafScene::afterDraw() {
    GgafElement<GgafScene>::afterDraw();
    _pSceneDirector->afterDraw();
}

void GgafScene::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventLowerTree(prm_no, prm_pSource);
    _pSceneDirector->throwEventLowerTree(prm_no, prm_pSource);
}

void GgafScene::throwEventLowerTree(hashval prm_no) {
    GgafElement<GgafScene>::throwEventLowerTree(prm_no);
    _pSceneDirector->throwEventLowerTree(prm_no);
}

void GgafScene::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventUpperTree(prm_no, prm_pSource);
}

void GgafScene::throwEventUpperTree(hashval prm_no) {
    GgafElement<GgafScene>::throwEventUpperTree(prm_no);
}

void GgafScene::doFinally() {
    if (_once_in_n_time == 1 || P_GOD->_frame_of_God % _once_in_n_time == 0) {
        GgafElement<GgafScene>::doFinally();
        _pSceneDirector->doFinally();
    }
}

void GgafScene::activateTree() {
    GgafElement<GgafScene>::activateTree();
    _pSceneDirector->activateTree();
}

void GgafScene::activateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::activateDelay(prm_offset_frames);
    _pSceneDirector->activateDelay(prm_offset_frames);
}

void GgafScene::activate() {
    GgafElement<GgafScene>::activate();
    _pSceneDirector->activate();
}

void GgafScene::activateTreeImmed() {
    GgafElement<GgafScene>::activateTreeImmed();
    _pSceneDirector->activateTreeImmed();
}

void GgafScene::activateImmed() {
    GgafElement<GgafScene>::activateImmed();
    _pSceneDirector->activateImmed();
}

void GgafScene::inactivateTree() {
    GgafElement<GgafScene>::inactivateTree();
    _pSceneDirector->inactivateTree();
}

void GgafScene::inactivateDelay(frame prm_offset_frames) {
    GgafElement<GgafScene>::inactivateDelay(prm_offset_frames);
    _pSceneDirector->inactivateDelay(prm_offset_frames);
}

void GgafScene::inactivate() {
    GgafElement<GgafScene>::inactivate();
    _pSceneDirector->inactivate();
}

void GgafScene::inactivateTreeImmed() {
    GgafElement<GgafScene>::inactivateTreeImmed();
    _pSceneDirector->inactivateTreeImmed();
}

void GgafScene::inactivateImmed() {
    GgafElement<GgafScene>::inactivateImmed();
    _pSceneDirector->inactivate();
}

void GgafScene::pauseTree() {
    GgafElement<GgafScene>::pauseTree();
    _pSceneDirector->pauseTree();
}

void GgafScene::pause() {
    GgafElement<GgafScene>::pause();
    _pSceneDirector->pause();
}

void GgafScene::pauseTreeImmed() {
    GgafElement<GgafScene>::pauseTreeImmed();
    _pSceneDirector->pauseTreeImmed();
}

void GgafScene::pauseImmed() {
    GgafElement<GgafScene>::pauseImmed();
    _pSceneDirector->pauseImmed();
}

void GgafScene::unpauseTree() {
    GgafElement<GgafScene>::unpauseTree();
    _pSceneDirector->unpauseTree();
}

void GgafScene::unpause() {
    GgafElement<GgafScene>::unpause();
    _pSceneDirector->unpause();
}

void GgafScene::unpauseTreeImmed() {
    GgafElement<GgafScene>::unpauseTreeImmed();
    _pSceneDirector->unpauseTreeImmed();
}

void GgafScene::unpauseImmed() {
    GgafElement<GgafScene>::unpauseImmed();
    _pSceneDirector->unpauseImmed();
}

void GgafScene::executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    GgafElement<GgafScene>::executeFuncLowerTree(pFunc, prm1, prm2);
    _pSceneDirector->executeFuncLowerTree(pFunc, prm1, prm2);
}

void GgafScene::reset() {
    GgafElement<GgafScene>::reset();
    _pSceneDirector->reset();
}

void GgafScene::resetTree() {
    GgafElement<GgafScene>::resetTree();
    _pSceneDirector->resetTree();
}

void GgafScene::end(frame prm_offset_frames) {
    _pSceneDirector->end(prm_offset_frames);
    if (prm_offset_frames > 3) {
        GgafElement<GgafScene>::end(prm_offset_frames-2);
    } else {
        GgafElement<GgafScene>::end(prm_offset_frames);
    }
    //この順番は重要。逆にするとゴミ箱の解放時に不正ポインタになりうるため。
}

void GgafScene::sayonara(frame prm_offset_frames) {
    _pSceneDirector->sayonara(prm_offset_frames);
    if (prm_offset_frames > 3) {
        GgafElement<GgafScene>::end(prm_offset_frames-2);
    } else {
        GgafElement<GgafScene>::end(prm_offset_frames);
    }

    GgafScene* pScene = _pSubFirst;
    while (pScene) {
        pScene->sayonara(prm_offset_frames);
        if (pScene->_is_last_flg) {
            break;
        } else {
            pScene = pScene->_pNext;
        }
    }
}

void GgafScene::clean(int prm_num_cleaning) {
    if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
        return;
    }
    if (_pSceneDirector) {
        _pSceneDirector->clean(prm_num_cleaning);
        if (_pSceneDirector->_pSubFirst == nullptr) {
            GGAF_DELETE(_pSceneDirector);
        }
    } else {
        GgafElement<GgafScene>::clean(prm_num_cleaning);
    }
}

GgafGod* GgafScene::askGod() {
    if (_pGod == nullptr) {
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

void GgafScene::dump() {
    _TRACE_("●"<<NODE_INFO<<DUMP_FLGS);
    if (_pSceneDirector) {
        _pSceneDirector->dump();
        GgafScene* pScene_tmp = _pSubFirst;
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

void GgafScene::dump(std::string prm_parent) {
    _TRACE_(prm_parent+"●"<<NODE_INFO<<DUMP_FLGS);
    if (_pSceneDirector) {
        _pSceneDirector->dump(prm_parent + "\t\t\t\t\t\t\t\t");
        GgafScene* pScene_tmp = _pSubFirst;
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

