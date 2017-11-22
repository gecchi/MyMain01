#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScene::GgafDxScene(const char* prm_name) : GgafMainScene(prm_name),
_pCurtain(new GgafDxAlphaCurtain(this)),
_pBgmPerformer(new GgafDxBgmPerformerForScene(this)) {
    _obj_class |= Obj_GgafDxScene;
    _class_name = "GgafDxScene";
    _scene_alpha = 1.0f;
    _scene_alpha_from_top = _scene_alpha;
}

void GgafDxScene::setSceneAlpha(float prm_scene_alpha) {
    _scene_alpha  = prm_scene_alpha;
    if (_scene_alpha > 1.0f) {
        _scene_alpha = 1.0f;
    } else if (_scene_alpha < 0.0f) {
        _scene_alpha = 0.0f;
    }
}
float GgafDxScene::getSceneAlpha() {
    return _scene_alpha;
}
void GgafDxScene::addSceneAlpha(float prm_scene_alpha) {
    setSceneAlpha(_scene_alpha+prm_scene_alpha);
}


void GgafDxScene::setSceneAlphaFromTop(float prm_scene_alpha_from_top) {
    _scene_alpha_from_top  = prm_scene_alpha_from_top;
    if (_scene_alpha_from_top > 1.0f) {
        _scene_alpha_from_top = 1.0f;
    } else if (_scene_alpha_from_top < 0.0f) {
        _scene_alpha_from_top = 0.0f;
    }
}
float GgafDxScene::getSceneAlphaFromTop() {
    return _scene_alpha_from_top;
}


void GgafDxScene::chengeCurtain(GgafDxSceneCurtain* prm_pCurtain_new) {
    if (prm_pCurtain_new) {
        delete _pCurtain;
        _pCurtain = prm_pCurtain_new;
    }
}

void GgafDxScene::callRecursive(void (GgafDxScene::*pFunc)()) {
    GgafScene* pElementTemp = getSubFirst();
    while (pElementTemp) {
        if (pElementTemp->instanceOf(Obj_GgafDxScene)) {
            GgafDxScene* p = (GgafDxScene*)pElementTemp;
            (p->*pFunc)(); //実行
        }
        if (pElementTemp->_is_last_flg) {
            break;
        } else {
            pElementTemp = pElementTemp->getNext();
        }
    }
}

void GgafDxScene::settleBehaviorEx() {
    //毎フレーム 実行される
    if (!_was_paused_flg && _can_live_flg) {
        if (_is_active_flg) {
            _pCurtain->behave(); //_scene_alphaが更新される
        }
        _pBgmPerformer->behave();
    }
    callRecursive(&GgafDxScene::settleBehaviorEx);
}


void GgafDxScene::settleBehavior() {
    if (getParent()->instanceOf(Obj_GgafDxSpacetime)) {
        //_once_in_n_time の影響を受けずに、
        //シーンだけ毎フレーム settleBehaviorEx() を実行させたい。
        settleBehaviorEx();
    }

    if (_is_next_frame) {
        GgafElement<GgafScene>::settleBehavior();
        _pSceneDirector->settleBehavior();
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

void GgafDxScene::fadeinScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pCurtain->open();
    } else {
        _pCurtain->openT(prm_frame_fade);
    }
}

void GgafDxScene::fadeoutScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pCurtain->close();
    } else {
        _pCurtain->closeT(prm_frame_fade);
    }
}

void GgafDxScene::fadeoutBgm(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pBgmPerformer->stop();
    } else {
        _pBgmPerformer->setDefaultFadeFrames(prm_frame_fade);
        _pBgmPerformer->fadeout_stop();
    }
}

void GgafDxScene::fadeoutBgmTree(int prm_frame_fade) {
    fadeoutBgm(prm_frame_fade);
    if (getSubFirst()) {
#ifdef MY_DEBUG
        if (getSubFirst()->instanceOf(Obj_GgafDxScene)) {
            //OK
        } else {
            _TRACE_("GgafDxScene::fadeoutBgmTree() サブシーンが、GgafDxScene に変換不可です。"
                    "this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName())<<" class="<<(getSubFirst()->_obj_class));
            throwGgafCriticalException("GgafDxScene::fadeoutBgmTree() サブシーンが、GgafDxScene に変換不可です。"
                    "this="<<getName()<<" getSubFirst()="<<(getSubFirst()->getName()) );
        }
#endif
        GgafDxScene* pScene = (GgafDxScene*)getSubFirst();
        while (true) {
            pScene->fadeoutBgmTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxScene::fadeoutBgmTree() "
                            "pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
                }
#endif
                pScene = (GgafDxScene*)(pScene->getNext());
            }
        }
    }
}

void GgafDxScene::fadeoutSceneWithBgm(int prm_frame_fade) {
    fadeoutScene(prm_frame_fade);
    fadeoutBgm(prm_frame_fade);
}

void GgafDxScene::fadeoutSceneWithBgmTree(int prm_frame_fade) {
    fadeoutScene(prm_frame_fade);
    fadeoutBgmTree( prm_frame_fade);
}
void GgafDxScene::onEnd() {
    _pBgmPerformer->stop();
}

GgafDxScene::~GgafDxScene() {
    delete _pCurtain;
    delete _pBgmPerformer;
}
