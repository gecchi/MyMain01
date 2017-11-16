#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScene::GgafDxScene(const char* prm_name) : GgafMainScene(prm_name),
_pAlphaCurtain(new GgafDxAlphaCurtain(this)),
_pBgmPerformer(new GgafDxBgmPerformerForScene(this)) {
    _obj_class |= Obj_GgafDxScene;
    _class_name = "GgafDxScene";

    _master_alpha = 1.0f;
}

void GgafDxScene::processSettlementBehavior() {
    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _pAlphaCurtain->behave(); //_master_alphaが更新される
        _pBgmPerformer->behave();
    }
}

void GgafDxScene::pauseTree() {
    if (_can_live_flg) {
        _TRACE_("GgafDxScene::pauseTree() シーン"<<getName()<<"("<<this<<")の BGMを一時停止 pause() します。");
        _pBgmPerformer->pause();
    }
    GgafElement<GgafScene>::pauseTree();
    _pSceneDirector->pauseTree();
}

void GgafDxScene::pause() {
    if (_can_live_flg) {
        _TRACE_("GgafDxScene::pause() シーン"<<getName()<<"("<<this<<")の BGMを一時停止 pause() します。");
        _pBgmPerformer->pause();
    }
    GgafElement<GgafScene>::pause();
    _pSceneDirector->pause();
}

void GgafDxScene::unpauseTree() {
    if (_can_live_flg) {
        _TRACE_("GgafDxScene::unpauseTree() シーン"<<getName()<<"("<<this<<")の BGMを一時停止解除 unpause() します。");
        _pBgmPerformer->unpause();
    }
    GgafElement<GgafScene>::unpauseTree();
    _pSceneDirector->unpauseTree();
}

void GgafDxScene::unpause() {
    if (_can_live_flg) {
        _TRACE_("GgafDxScene::unpause() シーン"<<getName()<<"("<<this<<")の BGMを一時停止解除 unpause() します。");
        _pBgmPerformer->unpause();
    }
    GgafElement<GgafScene>::unpause();
    _pSceneDirector->unpause();
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
            throwGgafCriticalException("サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while (true) {
            pScene->fadeinSceneTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
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
            _TRACE_("サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
            throwGgafCriticalException("サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while (true) {
            pScene->fadeoutSceneTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
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

void GgafDxScene::fadeoutSceneWithBgm(int prm_frame_fade) {
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
            _TRACE_("サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
            throwGgafCriticalException("サブシーンが、GgafDxScene に変換不可です。this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while (true) {
            pScene->fadeoutSceneWithBgmTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
                }
#endif
                pScene = (GgafDxScene*)(pScene->getNext());
            }
        }
    }

}

GgafDxScene::~GgafDxScene() {
    delete _pAlphaCurtain;
    delete _pBgmPerformer;
}
