#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScene::GgafDxScene(const char* prm_name) : GgafMainScene(prm_name) {
    _obj_class |= Obj_GgafDxScene;
    _class_name = "GgafDxScene";
    _pAlphaCurtain = NEW GgafDxAlphaCurtain(this);
    _pBgmPerformer = NEW GgafDxBgmPerformer();
}

void GgafDxScene::processSettlementBehavior() {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _pAlphaCurtain->behave();
    }
    _pBgmPerformer->behave();
}

void GgafDxScene::fadeinSceneTree(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->open();
    } else {
        _pAlphaCurtain->open(1.0 / prm_frame_fade);
    }
    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->_obj_class & Obj_GgafDxScene) {
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
                if (pScene->getNext()->_obj_class & Obj_GgafDxScene) {
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
        _pAlphaCurtain->open(1.0 / prm_frame_fade);
    }
}


void GgafDxScene::fadeoutSceneTree(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->close();
    } else {
        _pAlphaCurtain->close(1.0 / prm_frame_fade);
    }
    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->_obj_class & Obj_GgafDxScene) {
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
                if (pScene->getNext()->_obj_class & Obj_GgafDxScene) {
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

void GgafDxScene::fadeoutScene(int prm_frame_fade){
    if (prm_frame_fade == 0) {
        _pAlphaCurtain->close();
    } else {
        _pAlphaCurtain->close(1.0 / prm_frame_fade);
    }
}



GgafDxScene::~GgafDxScene() {
    DELETE_IMPOSSIBLE_NULL(_pAlphaCurtain);
    DELETE_IMPOSSIBLE_NULL(_pBgmPerformer);
}
