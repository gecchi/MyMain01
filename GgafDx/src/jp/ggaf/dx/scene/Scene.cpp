#include "jp/ggaf/dx/scene/Scene.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/scene/supporter/AlphaCurtain.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"


using namespace GgafDx;

Scene::Scene(const char* prm_name, GgafCore::SceneChief* prm_pSceneChief) : GgafCore::MainScene(prm_name, prm_pSceneChief),
_pCurtain(new AlphaCurtain(this)),
_pConductor(new BgmConductor()) {
    _obj_class |= Obj_GgafDx_Scene;
    _class_name = "Scene";
    _scene_alpha = 1.0f;
    _scene_alpha_from_top = _scene_alpha;
}

void Scene::setSceneAlpha(float prm_scene_alpha) {
    _scene_alpha  = prm_scene_alpha;
    if (_scene_alpha > 1.0f) {
        _scene_alpha = 1.0f;
    } else if (_scene_alpha < 0.0f) {
        _scene_alpha = 0.0f;
    }
}
float Scene::getSceneAlpha() {
    return _scene_alpha;
}
void Scene::addSceneAlpha(float prm_scene_alpha) {
    setSceneAlpha(_scene_alpha+prm_scene_alpha);
}


void Scene::setSceneAlphaFromTop(float prm_scene_alpha_from_top) {
    _scene_alpha_from_top  = prm_scene_alpha_from_top;
    if (_scene_alpha_from_top > 1.0f) {
        _scene_alpha_from_top = 1.0f;
    } else if (_scene_alpha_from_top < 0.0f) {
        _scene_alpha_from_top = 0.0f;
    }
}
float Scene::getSceneAlphaFromTop() {
    return _scene_alpha_from_top;
}


void Scene::chengeCurtain(SceneCurtain* prm_pCurtain_new) {
    if (prm_pCurtain_new) {
        delete _pCurtain;
        _pCurtain = prm_pCurtain_new;
    }
}

void Scene::processSettlementBehavior() {
    GgafCore::MainScene::processSettlementBehavior();
    if (!_was_paused_flg) {
        _pCurtain->behave();
        _pConductor->behave();
    }
}

void Scene::pause() {
    _TRACE_("Scene::pause() シーン"<<getName()<<"("<<this<<")の BGMを一時停止 pause() します。");
    _pConductor->pause();
    GgafCore::MainScene::pause();
}

void Scene::unpause() {
    _TRACE_("Scene::unpause() シーン"<<getName()<<"("<<this<<")の BGMを一時停止解除 unpause() します。");
    _pConductor->unpause();
    GgafCore::MainScene::unpause();
}

void Scene::fadeinScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pCurtain->open();
    } else {
        _pCurtain->openT(prm_frame_fade);
    }
}

void Scene::fadeoutScene(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pCurtain->close();
    } else {
        _pCurtain->closeT(prm_frame_fade);
    }
}

void Scene::fadeoutBgm(int prm_frame_fade) {
    if (prm_frame_fade == 0) {
        _pConductor->stop();
    } else {
        _pConductor->fadeoutStopAll(prm_frame_fade);
    }
}

void Scene::fadeoutBgmTree(int prm_frame_fade) {
    fadeoutBgm(prm_frame_fade);
    if (getChildFirst()) {
#ifdef MY_DEBUG
        if (getChildFirst()->instanceOf(Obj_GgafDx_Scene)) {
            //OK
        } else {
            _TRACE_("Scene::fadeoutBgmTree() 子シーンが、Scene に変換不可です。"
                    "this="<<getName()<<" getChildFirst()="<<(getChildFirst()->getName())<<" class="<<(getChildFirst()->_obj_class));
            throwCriticalException("Scene::fadeoutBgmTree() 子シーンが、Scene に変換不可です。"
                    "this="<<getName()<<" getChildFirst()="<<(getChildFirst()->getName()) );
        }
#endif
        Scene* pScene = (Scene*)getChildFirst();
        while (true) {
            pScene->fadeoutBgmTree(prm_frame_fade);
            if (pScene->isLast()) {
                break;
            } else {
#ifdef MY_DEBUG
                if (pScene->getNext()->instanceOf(Obj_GgafDx_Scene)) {
                    //OK
                } else {
                    throwCriticalException("Scene::fadeoutBgmTree() "
                            "pScene["<<(pScene->getName())<<"->getNext()["<<(pScene->getNext()->getName())<<"]が、Scene に変換不可です。this="<<getName());
                }
#endif
                pScene = (Scene*)(pScene->getNext());
            }
        }
    }
}

void Scene::fadeoutSceneWithBgm(int prm_frame_fade) {
    fadeoutScene(prm_frame_fade);
    fadeoutBgm(prm_frame_fade);
}

void Scene::fadeoutSceneWithBgmTree(int prm_frame_fade) {
    fadeoutScene(prm_frame_fade);
    fadeoutBgmTree( prm_frame_fade);
}
void Scene::onEnd() {
    _pConductor->stop();
}

Scene::~Scene() {
    delete _pCurtain;
    delete _pConductor;
}
