#include "stdafx.h"

using namespace GgafCore;


GgafScene::GgafScene(const char* prm_name) : GgafElement<GgafScene> (prm_name) {
    TRACE("GgafScene::GgafScene() " << prm_name);
    _class_name = "GgafScene";
    _obj_class |= Obj_GgafScene;

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
    GGAF_DELETE_NULLABLE(_pDirector);
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
//    _pDirector->update_last_frame_of_god();
//}


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

void GgafScene::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    GgafElement<GgafScene>::throwEventLowerTree(prm_no, prm_pSource);
    _pDirector->throwEventLowerTree(prm_no, prm_pSource);
}

void GgafScene::throwEventLowerTree(hashval prm_no) {
    GgafElement<GgafScene>::throwEventLowerTree(prm_no);
    _pDirector->throwEventLowerTree(prm_no);
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

void GgafScene::activateTreeImmed() {
    GgafElement<GgafScene>::activateTreeImmed();
    _pDirector->activateTreeImmed();
}

void GgafScene::activateImmed() {
    GgafElement<GgafScene>::activateImmed();
    _pDirector->activateImmed();
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

void GgafScene::inactivateTreeImmed() {
    GgafElement<GgafScene>::inactivateTreeImmed();
    _pDirector->inactivateTreeImmed();
}

void GgafScene::inactivateImmed() {
    GgafElement<GgafScene>::inactivateImmed();
    _pDirector->inactivateImmed();
}

void GgafScene::pauseTree() {
    GgafElement<GgafScene>::pauseTree();
    _pDirector->pauseTree();
}

void GgafScene::pause() {
    GgafElement<GgafScene>::pause();
    _pDirector->pause();
}

void GgafScene::pauseTreeImmed() {
    GgafElement<GgafScene>::pauseTreeImmed();
    _pDirector->pauseTreeImmed();
}

void GgafScene::pauseImmed() {
    GgafElement<GgafScene>::pauseImmed();
    _pDirector->pauseImmed();
}

void GgafScene::unpauseTree() {
    GgafElement<GgafScene>::unpauseTree();
    _pDirector->unpauseTree();
}

void GgafScene::unpause() {
    GgafElement<GgafScene>::unpause();
    _pDirector->unpause();
}

void GgafScene::unpauseTreeImmed() {
    GgafElement<GgafScene>::unpauseTreeImmed();
    _pDirector->unpauseTreeImmed();
}

void GgafScene::unpauseImmed() {
    GgafElement<GgafScene>::unpauseImmed();
    _pDirector->unpauseImmed();
}

void GgafScene::executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    GgafElement<GgafScene>::executeFuncLowerTree(pFunc, prm1, prm2);
    _pDirector->executeFuncLowerTree(pFunc, prm1, prm2);
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
    if (prm_offset_frames > 3) {
        GgafElement<GgafScene>::end(prm_offset_frames-2);
    } else {
        GgafElement<GgafScene>::end(prm_offset_frames);
    }
    //この順番は重要。逆にするとゴミ箱の解放時に不正ポインタになりうるため。
}

void GgafScene::sayonara(frame prm_offset_frames) {
    _pDirector->sayonara(prm_offset_frames);
    if (prm_offset_frames > 3) {
        GgafElement<GgafScene>::end(prm_offset_frames-2);
    } else {
        GgafElement<GgafScene>::end(prm_offset_frames);
    }

    GgafScene* pScene;
    if (_pSubFirst) {
        pScene = _pSubFirst;
        while (true) {
            pScene->sayonara(prm_offset_frames);
            if (pScene->_is_last_flg) {
                break;
            } else {
                pScene = pScene->_pNext;
            }
        }
    }
}

void GgafScene::clean(int prm_num_cleaning) {
    if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
        return;
    }
    if (_pDirector) {
        _pDirector->clean(prm_num_cleaning);
        if (_pDirector->_pSubFirst == nullptr) {
            GGAF_DELETE(_pDirector);
        }
    } else {
        GgafElement<GgafScene>::clean(prm_num_cleaning);
    }
}

GgafDirector* GgafScene::getDirector() {
    return _pDirector;
}

GgafGod* GgafScene::askGod() {
    if (_pGod == nullptr) {
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

void GgafScene::dump() {
    _TRACE_("●"<<_class_name<<"("<<this<<")["<<getName()<<"]"<<DUMP_FLGS);
    if (_pDirector) {
        _pDirector->dump();
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst) {
            while (true) {
                pScene_tmp->dump("\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrっています");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

void GgafScene::dump(std::string prm_parent) {
    _TRACE_(prm_parent+"●"<<_class_name<<"("<<this<<")["<<getName()<<"]"<<DUMP_FLGS);
    if (_pDirector) {
        _pDirector->dump(prm_parent + "\t\t\t\t\t\t\t\t");
        GgafScene* pScene_tmp = _pSubFirst;
        if (_pSubFirst) {
            while (true) {
                pScene_tmp->dump(prm_parent + "\t");
                if (pScene_tmp->_pNext) {
                    pScene_tmp = pScene_tmp->_pNext;
                } else {
                    _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrっています");
                    break;
                }
                if (pScene_tmp->_is_first_flg) {
                    break;
                }
            }
        }
    }
}

