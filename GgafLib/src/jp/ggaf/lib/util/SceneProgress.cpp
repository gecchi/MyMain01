#include "jp/ggaf/lib/util/SceneProgress.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafLib;

SceneProgress::SceneProgress(DefaultScene* prm_pScene)  : GgafCore::Progress(&(prm_pScene->_frame_of_behaving)) {
    _pScene = prm_pScene;
    _progress_next_promise = 0;
    _count_next_promise = 0;
}

void SceneProgress::relateChildScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstChildSceneName) {
    relateChildScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getChildByName(prm_FirstChildSceneName)));
}

void SceneProgress::relateChildScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstChildScene) {
    DefaultScene* pChild = prm_pFirstChildScene;
    int num = 1;
    _TRACE_(FUNC_NAME<<" シーン("<<_pScene->getName()<<")は、SceneProgressの進捗番号と子シーンを関連付けて操作します。対応は以下の通り。");
    for (progress prog = prm_FirstProgress; prog <= prm_EndProgress; prog++, num++) {
        _mapProg2Scene[prog] = pChild;
        if (pChild->isLast() && prog < prm_EndProgress) {
            throwCriticalException("_pScene("<<_pScene->getName()<<")の"
                                       "子シーン("<<prm_pFirstChildScene->getName()<<")から数えての子シーンの数が足りません(子シーンが一周しました)。\n"
                                       "進捗番号数は "<<prm_FirstProgress<<"～"<<prm_EndProgress<<" の "<<(prm_EndProgress-prm_FirstProgress)<<" 個に対し、\n"
                                       "子シーン数は "<<prm_pFirstChildScene->getName()<<"～"<<pChild->getName()<<" の "<<num<<"個でした。");
        }
        _TRACE_("   進捗番号:"<<prog<<" ==> シーン:"<<pChild->getName()<<"");
        pChild = (DefaultScene*)(pChild->getNext());
    }
}

void SceneProgress::changeWithSceneFadein(progress prm_progress, frame prm_fade_in ) {
    _TRACE_("SceneProgress::changeWithSceneFadein("<<prm_progress<<","<<prm_fade_in<<")  進捗シーン:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
                _TRACE_("＜警告＞SceneProgress::changeWithSceneFadein シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移先進捗(prm_progress="<<prm_progress<<") だった為、activate() ができませんでした。");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinScene(prm_fade_in);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFlipping(progress prm_progress) {
    _TRACE_("SceneProgress::changeWithSceneFlipping("<<prm_progress<<")  進捗シーン:"<<get()<<"->"<<prm_progress<<" ");

    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFlipping シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移元進捗(get()="<<get()<<")だった為、inactivate() ができませんでした。");
    } else {
        _mapProg2Scene[get()]->fadeoutBgmTree(0);
        _mapProg2Scene[get()]->inactivate();
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFlipping シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移先進捗(prm_progress="<<prm_progress<<") だった為、activate() ができませんでした。");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinScene(0);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames) {
    _TRACE_("SceneProgress::changeWithSceneCrossfading("<<prm_progress<<","<<prm_cross_fade_frames<<")  進捗シーン:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移元進捗(get()="<<get()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_cross_fade_frames); //フェード完了後、非活動に
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移先進捗(prm_progress="<<prm_progress<<") だった為、activate() ができませんでした。");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);
        _mapProg2Scene[prm_progress]->fadeinScene(prm_cross_fade_frames);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out, frame prm_fade_in) {
    _TRACE_("SceneProgress::changeWithSceneFadeoutFadein("<<prm_progress<<","<<prm_fade_out<<","<<prm_fade_in<<")  進捗シーン:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移元進捗(get()="<<get()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_out);
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移先進捗(prm_progress="<<prm_progress<<") だった為、activateDelay() ができませんでした。");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activateDelay(prm_fade_out);   //活動予約
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);    //
        _mapProg2Scene[prm_progress]->fadeinScene(prm_fade_in);  //activateDelay なので、prm_fade_out フレーム後にフェードインする。
    }
    changeDelay(prm_progress, prm_fade_out); //進捗変更予約
}

void SceneProgress::changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames) {
    _TRACE_("SceneProgress::changeWithSceneOverlapping("<<prm_progress<<","<<prm_overlapping_frames<<")  進捗シーン:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移元進捗(get()="<<get()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapProg2Scene[get()]->inactivateDelay(prm_overlapping_frames);
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("＜警告＞SceneProgress::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")で、"
            "子シーンと関連付けされていない遷移先進捗(prm_progress="<<prm_progress<<") だった為、activate() ができませんでした。");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    }
    change(prm_progress);
}


DefaultScene* SceneProgress::getGazedScene() {
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        return nullptr;
    } else {
        return (_mapProg2Scene[get()]);
    }
}

DefaultScene* SceneProgress::getScene(progress prm_progress) {
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        return nullptr;
    } else {
        return (_mapProg2Scene[prm_progress]);
    }
}

void SceneProgress::change(progress prm_progress) {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //遷移先予約が、今回のchangeと同じ遷移先ならいいが
        //異なる場合は、前回のシーンの活動予約を取り消す。
        if (prm_progress == _progress_next_promise) {
            //遷移先シーンが同じ、
            //_progress+1 のシーンは 即activate()で、既存activateDelay()を上書きするのでOK
        } else {
            //_progress_next_promiseの activateDelay() を取り消す。
            if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
                _TRACE_("＜情報＞SceneProgress::change("<<prm_progress<<")  シーン("<<_pScene->getName()<<")で、"
                    "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                    "活動予約を取り消しの措置は行いません。");
            } else {
                _TRACE_("＜情報＞SceneProgress::change("<<prm_progress<<")  シーン("<<_pScene->getName()<<")で、"
                    "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在し、関連シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")が、"
                    "既に activateDelay() されています。しかし、本 change() を優先し、シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"の activateDelay() を取り消しました。");
                _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Progress::change(prm_progress);
}

void SceneProgress::changeNothing() {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //_progress_next_promiseの activateDelay() を取り消す。
        if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
            _TRACE_("＜情報＞SceneProgress::changeNothing() シーン("<<_pScene->getName()<<")で、"
                "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                "活動予約を取り消しの措置は行いません。");
        } else {
            _TRACE_("＜情報＞SceneProgress::changeNothing()  シーン("<<_pScene->getName()<<")で、"
                "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在し、関連シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")が、"
                "既に activateDelay() されています。しかし、本 changeNothing() を優先し、シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"の activateDelay() を取り消しました。");
            _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Progress::changeNothing();
}

void SceneProgress::changeNext() {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //遷移先予約が、今回のchangeと同じならいいが
        //異なる場合は、シーンの活動予約を取り消す。
        if (_progress+1 == _progress_next_promise) {
            //遷移先シーンが同じ、
            //_progress+1 のシーンは 即activate()で、既存activateDelay()を上書きするのでOK
        } else {
            //_progress_next_promiseの activateDelay() を取り消す。
            if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
                _TRACE_("＜情報＞SceneProgress::changeNext() _progress+1="<<(_progress+1)<<" シーン("<<_pScene->getName()<<")で、"
                "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                "活動予約を取り消しの措置は行いません。");
            } else {
                _TRACE_("＜情報＞SceneProgress::changeNext() _progress+1="<<(_progress+1)<<" シーン("<<_pScene->getName()<<")で、"
                "遷移先予約進捗(_progress_next_promise="<<_progress_next_promise<<")が存在し、関連シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")が、"
                "既に activateDelay() されています。しかし、本 changeNext() を優先し、シーン("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"の activateDelay() を取り消しました。");
                _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Progress::changeNext();
}

void SceneProgress::changeDelay(progress prm_progress, frame prm_delay) {
    _progress_next_promise = prm_progress;
    _count_next_promise = (*_p_frame_counter) + prm_delay;
}

void SceneProgress::update() {
    if (_count_next_promise > 0) {
        if ((*_p_frame_counter) == _count_next_promise) {
            change(_progress_next_promise);
            _progress_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafCore::Progress::update();
}

SceneProgress::~SceneProgress() {
}
