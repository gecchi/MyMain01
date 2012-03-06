#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;



SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
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

void SceneProgress::changeWithScene_Flipping(progress prm_progress) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Flipping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Flipping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithScene_Crossfading(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneTree(prm_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Crossfading シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Crossfading シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithScene_FadeoutFadin(progress prm_progress, frame prm_fade_frames) {
}

void SceneProgress::changeWithScene_Overlapping(progress prm_progress, frame prm_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivateDelay(prm_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Overlapping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithScene_Overlapping シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}



DefaultScene* SceneProgress::getGazeScene() {
    return (_mapProg2Scene[get()]);
}

DefaultScene* SceneProgress::getScene(progress prm_progress) {
    return (_mapProg2Scene[prm_progress]);
}

SceneProgress::~SceneProgress() {
}
