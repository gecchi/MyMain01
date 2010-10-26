#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Scene::GgafDx9Scene(const char* prm_name) : GgafMainScene(prm_name) {
    _obj_class |= Obj_GgafDx9Scene;
    _class_name = "GgafDx9Scene";
    _pAlphaCurtain = NEW GgafDx9AlphaCurtain(this);
    _pBgmPerformer = NEW GgafDx9BgmPerformer();
}

void GgafDx9Scene::processSettlementBehavior() {
    _pAlphaCurtain->behave();
    _pBgmPerformer->behave();
}

void GgafDx9Scene::fadeinSceneTree(int prm_frame_fade) {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (prm_frame_fade == 0) {
            _pAlphaCurtain->open(1.0);
        } else {
            _pAlphaCurtain->open(1.0 / prm_frame_fade);
        }
        if (getSubFirst() != NULL) {
#ifdef MY_DEBUG
            if (getSubFirst()->_obj_class & Obj_GgafDx9Scene) {
                //OK
            } else {
                throwGgafCriticalException("GgafDx9Scene::fadeinSceneTree() サブシーンが、GgafDx9Scene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
            }
#endif
            GgafDx9Scene* pScene = (GgafDx9Scene*)getSubFirst();
            while(true) {
                pScene->fadeinSceneTree(prm_frame_fade);
                if (pScene->isLast()) {
                    break;
                } else {
#ifdef MY_DEBUG
                    if (pScene->getNext()->_obj_class & Obj_GgafDx9Scene) {
                        //OK
                    } else {
                        throwGgafCriticalException("GgafDx9Scene::fadeinSceneTree() pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDx9Scene に変換不可です。this="<<getName());
                    }
#endif
                    pScene = (GgafDx9Scene*)(pScene->getNext());
                }
            }
        }
    }
}

void GgafDx9Scene::fadeinScene(int prm_frame_fade) {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (prm_frame_fade == 0) {
            _pAlphaCurtain->open(1.0);
        } else {
            _pAlphaCurtain->open(1.0 / prm_frame_fade);
        }
    }
}




void GgafDx9Scene::fadeoutSceneTree(int prm_frame_fade) {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (prm_frame_fade == 0) {
            _pAlphaCurtain->close(1.0);
        } else {
            _pAlphaCurtain->close(1.0 / prm_frame_fade);
        }
        if (getSubFirst() != NULL) {
#ifdef MY_DEBUG
            if (getSubFirst()->_obj_class & Obj_GgafDx9Scene) {
                //OK
            } else {
                _TRACE_("GgafDx9Scene::fadeoutSceneTree() サブシーンが、GgafDx9Scene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
                throwGgafCriticalException("GgafDx9Scene::fadeoutSceneTree() サブシーンが、GgafDx9Scene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
            }
#endif
            GgafDx9Scene* pScene = (GgafDx9Scene*)getSubFirst();
            while(true) {
                pScene->fadeoutSceneTree(prm_frame_fade);
                if (pScene->isLast()) {
                    break;
                } else {
#ifdef MY_DEBUG
                    if (pScene->getNext()->_obj_class & Obj_GgafDx9Scene) {
                        //OK
                    } else {
                        throwGgafCriticalException("GgafDx9Scene::fadeinSceneTree() pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDx9Scene に変換不可です。this="<<getName());
                    }
#endif
                    pScene = (GgafDx9Scene*)(pScene->getNext());
                }
            }
        }
    }
}

void GgafDx9Scene::fadeoutScene(int prm_frame_fade){
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (prm_frame_fade == 0) {
            _pAlphaCurtain->close(1.0);
        } else {
            _pAlphaCurtain->close(1.0 / prm_frame_fade);
        }
    }
}


GgafDx9Scene::~GgafDx9Scene() {
    DELETE_IMPOSSIBLE_NULL(_pAlphaCurtain);
    DELETE_IMPOSSIBLE_NULL(_pBgmPerformer);
}
