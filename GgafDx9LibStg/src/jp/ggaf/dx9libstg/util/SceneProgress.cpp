#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;



SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
}
void SceneProgress::affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName) {
    affectSubScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getSubByName(prm_FirstSubSceneName)));
}
void SceneProgress::affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene) {
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
    //    _mapSubScene[GAMESCENE_PROG_PRE_TITLE] = NEW GamePreTitleScene("PreGameTitle");
    //    _mapSubScene[GAMESCENE_PROG_TITLE]     = NEW GameTitleScene("GameTitle");
    //    _mapSubScene[GAMESCENE_PROG_DEMO]      = NEW GameDemoScene("GameDemo");
    //    _mapSubScene[GAMESCENE_PROG_BEGINNING] = NEW GameBeginningScene("GameBeginning");
    //    _mapSubScene[GAMESCENE_PROG_MAIN]      = NEW GameMainScene("GameMain");
    //    _mapSubScene[GAMESCENE_PROG_ENDING]    = NEW GameEndingScene("GameEnding");
    //    _mapSubScene[GAMESCENE_PROG_GAME_OVER] = NEW GameOverScene("GameOver");
}

void SceneProgress::changeWithFlippingSubScene(progress prm_progress) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithFlippingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithFlippingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithCrossfadingSubScene(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneTree(prm_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithFlippingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithFlippingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithOverlappingSubScene(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithOverlappingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンのため無視しました。get()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    } else {
        _TRACE_("＜警告＞SceneProgress::changeWithOverlappingSubScene シーン("<<_pScene->getName()<<")に未エントリーの進捗シーンため無視しました。prm_progress="<<prm_progress);
    }
    change(prm_progress);
}



DefaultScene* SceneProgress::getSubScene() {
    return (_mapProg2Scene[get()]);
}
SceneProgress::~SceneProgress() {
}
