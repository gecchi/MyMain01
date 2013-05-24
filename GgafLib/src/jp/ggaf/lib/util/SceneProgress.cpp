#include "stdafx.h"
#include "jp/ggaf/lib/util/SceneProgress.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
    _progress_next_promise = 0;
    _count_next_promise = 0;
}
void SceneProgress::relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName) {
    relatSubScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getSubByName(prm_FirstSubSceneName)));
}
void SceneProgress::relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene) {
    DefaultScene* pSub = prm_pFirstSubScene;
    int num_progress = _pScene->_pProg->_num_progress;
    int num = 1;
    for (progress prog = prm_FirstProgress; prog <= prm_EndProgress; prog++, num++) {
        _mapProg2Scene[prog] = pSub;
        if (pSub->isLast() && prog < prm_EndProgress) {
            throwGgafCriticalException("SceneProgress::SceneProgress _pScene("<<_pScene->getName()<<")の"<<
                                       "サブシーン("<<prm_pFirstSubScene->getName()<<")から数えてのサブシーンの数が足りません(サブシーンが一周しました)。\n"<<
                                       "進捗番号数は "<<prm_FirstProgress<<"～"<<prm_EndProgress<<" の "<<(prm_EndProgress-prm_FirstProgress)<<" 個に対し、\n"<<
                                       "サブシーン数は "<<prm_pFirstSubScene->getName()<<"～"<<pSub->getName()<<" の "<<num<<"個でした。");
        }
        pSub = (DefaultScene*)(pSub->getNext());

    }
}

void SceneProgress::changeWithScene(progress prm_progress) {
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFlipping(progress prm_progress) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFlipping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFlipping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_cross_fade_frames); //フェード完了後、非活動に
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_cross_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out, frame prm_fade_in) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_out);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activateDelay(prm_fade_out); //活動予約
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);    //
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_in);  //activateDelay なので、prm_fade_out フレーム後にフェードインする。
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    changeDelay(prm_progress, prm_fade_out); //進捗変更予約
}

void SceneProgress::changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivateDelay(prm_overlapping_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}



DefaultScene* SceneProgress::getGazedScene() {
    return (_mapProg2Scene[get()]);
}

DefaultScene* SceneProgress::getScene(progress prm_progress) {
    return (_mapProg2Scene[prm_progress]);
}

void SceneProgress::changeDelay(progress prm_progress, frame prm_delay) {
    _progress_next_promise = prm_progress;
    _count_next_promise = (*_pFrame_counter) + prm_delay;
}

void SceneProgress::update() {
    if (_count_next_promise > 0) {
        if ((*_pFrame_counter) == _count_next_promise) {
            change(_progress_next_promise);
            _progress_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafProgress::update();
}

SceneProgress::~SceneProgress() {
}
