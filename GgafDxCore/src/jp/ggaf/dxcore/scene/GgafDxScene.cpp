#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScene::GgafDxScene(const char* prm_name) : GgafMainScene(prm_name) {
    _obj_class |= Obj_GgafDxScene;
    _class_name = "GgafDxScene";
    _pAlphaCurtain = NEW GgafDxAlphaCurtain(this);
    _pBgmPerformer = NEW GgafDxBgmPerformerForScene(this);
    _master_alpha = 1.0f;
}

void GgafDxScene::processSettlementBehavior() {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _pAlphaCurtain->behave(); //_master_alphaが更新される
    }
    _pBgmPerformer->behave();
    if (_was_paused_flg_in_next_frame) {
        _pBgmPerformer->pause();
    } else {
        _pBgmPerformer->unpause();
    }
}

void GgafDxScene::fadeinSceneTree(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->open();
    } else {
        _pAlphaCurtain->open(_pAlphaCurtain->_range_alpha / prm_frame_fade);
    }
    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->instanceOf(Obj_GgafDxScene)) {
            //OK
        } else {
            throwGgafCriticalException("GgafDxScene::fadeinSceneTree() サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while(true) {
            pScene->fadeinSceneTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxScene::fadeinSceneTree() pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
                }
#endif
                pScene = (GgafDxScene*)(pScene->getNext());
            }
        }
    }
}

void GgafDxScene::fadeinScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->open();
    } else {
        _pAlphaCurtain->open(_pAlphaCurtain->_range_alpha / prm_frame_fade);
    }
}


void GgafDxScene::fadeoutSceneTree(int prm_frame_fade) {
    fadeoutScene(prm_frame_fade);

    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->instanceOf(Obj_GgafDxScene)) {
            //OK
        } else {
            _TRACE_("GgafDxScene::fadeoutSceneTree() サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
            throwGgafCriticalException("GgafDxScene::fadeoutSceneTree() サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while(true) {
            pScene->fadeoutSceneTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxScene::fadeinSceneTree() pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
                }
#endif
                pScene = (GgafDxScene*)(pScene->getNext());
            }
        }
    }
}

void GgafDxScene::fadeoutScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->close();
    } else {
        _pAlphaCurtain->close(_pAlphaCurtain->_range_alpha / prm_frame_fade);
    }
}

void GgafDxScene::fadeoutSceneWithBgm(int prm_frame_fade){
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->close();
        _pBgmPerformer->stop();
    } else {
        _pAlphaCurtain->close(_pAlphaCurtain->_range_alpha / prm_frame_fade);
        _pBgmPerformer->setDefaultFadeFrames(prm_frame_fade);
        _pBgmPerformer->fadeout_stop();
    }
}

void GgafDxScene::fadeoutSceneWithBgmTree(int prm_frame_fade) {
    fadeoutSceneWithBgm(prm_frame_fade);

    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->instanceOf(Obj_GgafDxScene)) {
            //OK
        } else {
            _TRACE_("GgafDxScene::fadeoutSceneTree() サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
            throwGgafCriticalException("GgafDxScene::fadeoutSceneTree() サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while(true) {
            pScene->fadeoutSceneWithBgmTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxScene::fadeinSceneTree() pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
                }
#endif
                pScene = (GgafDxScene*)(pScene->getNext());
            }
        }
    }

}

GgafDxScene::~GgafDxScene() {
    GGAF_DELETE(_pAlphaCurtain);
    GGAF_DELETE(_pBgmPerformer);
}
