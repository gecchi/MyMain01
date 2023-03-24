#include "jp/ggaf/lib/util/ScenePhase.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafLib;

ScenePhase::ScenePhase(DefaultScene* prm_pScene)  : GgafCore::Phase(&(prm_pScene->_frame_of_behaving)) {
    _pScene = prm_pScene;
    _phase_no_next_promise = 0;
    _count_next_promise = 0;
}

void ScenePhase::relateChildScene(int prm_FirstPhase, int prm_EndPhase, const char* prm_FirstChildSceneName) {
    relateChildScene(prm_FirstPhase, prm_EndPhase, (DefaultScene*)(_pScene->getChildByName(prm_FirstChildSceneName)));
}

void ScenePhase::relateChildScene(int prm_FirstPhase, int prm_EndPhase, DefaultScene* prm_pFirstChildScene) {
    DefaultScene* pChild = prm_pFirstChildScene;
    int num = 1;
    _TRACE_(FUNC_NAME<<" シーン("<<_pScene->getName()<<")は、ScenePhaseのフェーズ番号と子シーンを関連付けて操作します。対応は以下の通り。");
    for (int phs = prm_FirstPhase; phs <= prm_EndPhase; phs++, num++) {
        _mapPhase2Scene[phs] = pChild;
        if (pChild->isLast() && phs < prm_EndPhase) {
            throwCriticalException("_pScene("<<_pScene->getName()<<")の"
                                   "子シーン("<<prm_pFirstChildScene->getName()<<")から数えての子シーンの数が足りません(子シーンが一周しました)。\n"
                                   "フェーズ番号数は "<<prm_FirstPhase<<"～"<<prm_EndPhase<<" の "<<(prm_EndPhase-prm_FirstPhase)<<" 個に対し、\n"
                                   "子シーン数は "<<prm_pFirstChildScene->getName()<<"～"<<pChild->getName()<<" の "<<num<<"個でした。");
        }
        _TRACE_("   フェーズ番号:"<<phs<<" ==> シーン:"<<pChild->getName()<<"");
        pChild = (DefaultScene*)(pChild->getNext());
    }
}

void ScenePhase::changeWithSceneFadein(int prm_phase_no, frame prm_fade_in ) {
    _TRACE_("ScenePhase::changeWithSceneFadein("<<prm_phase_no<<","<<prm_fade_in<<")  シーンフェーズ:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneFadein シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移先フェーズ(prm_phase_no="<<prm_phase_no<<") だった為、activate() ができませんでした。");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_fade_in);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneFlipping(int prm_phase_no) {
    _TRACE_("ScenePhase::changeWithSceneFlipping("<<prm_phase_no<<")  シーンフェーズ:"<<getCurrent()<<"->"<<prm_phase_no<<" ");

    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneFlipping シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移元フェーズ(get()="<<getCurrent()<<")だった為、inactivate() ができませんでした。");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutBgmTree(0);
        _mapPhase2Scene[getCurrent()]->inactivate();
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneFlipping シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移先フェーズ(prm_phase_no="<<prm_phase_no<<") だった為、activate() ができませんでした。");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeinScene(0);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneCrossfading(int prm_phase_no, frame prm_cross_fade_frames) {
    _TRACE_("ScenePhase::changeWithSceneCrossfading("<<prm_phase_no<<","<<prm_cross_fade_frames<<")  シーンフェーズ:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移元フェーズ(get()="<<getCurrent()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_cross_fade_frames); //フェード完了後、非活動に
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneCrossfading シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移先フェーズ(prm_phase_no="<<prm_phase_no<<") だった為、activate() ができませんでした。");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeoutSceneWithBgmTree(0);
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_cross_fade_frames);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneFadeoutFadein(int prm_phase_no, frame prm_fade_out, frame prm_fade_in) {
    _TRACE_("ScenePhase::changeWithSceneFadeoutFadein("<<prm_phase_no<<","<<prm_fade_out<<","<<prm_fade_in<<")  シーンフェーズ:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移元フェーズ(get()="<<getCurrent()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_fade_out);
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneFadeoutFadein シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移先フェーズ(prm_phase_no="<<prm_phase_no<<") だった為、activateDelay() ができませんでした。");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activateDelay(prm_fade_out);   //活動予約
        _mapPhase2Scene[prm_phase_no]->fadeoutSceneWithBgmTree(0);    //
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_fade_in);  //activateDelay なので、prm_fade_out フレーム後にフェードインする。
    }
    changeDelay(prm_phase_no, prm_fade_out); //フェーズ変更予約
}

void ScenePhase::changeWithSceneOverlapping(int prm_phase_no, frame prm_overlapping_frames) {
    _TRACE_("ScenePhase::changeWithSceneOverlapping("<<prm_phase_no<<","<<prm_overlapping_frames<<")  シーンフェーズ:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移元フェーズ(get()="<<getCurrent()<<")だった為、inactivateDelay() ができませんでした。");
    } else {
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_overlapping_frames);
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("【警告】ScenePhase::changeWithSceneOverlapping シーン("<<_pScene->getName()<<")で、"
                "子シーンと関連付けされていない遷移先フェーズ(prm_phase_no="<<prm_phase_no<<") だった為、activate() ができませんでした。");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
    }
    change(prm_phase_no);
}


DefaultScene* ScenePhase::getGazedScene() {
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[getCurrent()]);
    }
}

DefaultScene* ScenePhase::getRelationScene(int prm_phase_no) {
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[prm_phase_no]);
    }
}

void ScenePhase::change(int prm_phase_no) {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //遷移先予約が、今回のchangeと同じ遷移先ならいいが
        //異なる場合は、前回のシーンの活動予約を取り消す。
        if (prm_phase_no == _phase_no_next_promise) {
            //遷移先シーンが同じ、
            //_phase_no+1 のシーンは 即activate()で、既存activateDelay()を上書きするのでOK
        } else {
            //_phase_no_next_promiseの activateDelay() を取り消す。
            if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("【情報】ScenePhase::change("<<prm_phase_no<<")  シーン("<<_pScene->getName()<<")で、"
                        "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                        "活動予約を取り消しの措置は行いません。");
            } else {
                _TRACE_("【情報】ScenePhase::change("<<prm_phase_no<<")  シーン("<<_pScene->getName()<<")で、"
                        "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在し、関連シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")が、"
                        "既に activateDelay() されています。しかし、本 change() を優先し、シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"の activateDelay() を取り消しました。");
                _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::change(prm_phase_no);
}

void ScenePhase::changeNothing() {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //_phase_no_next_promiseの activateDelay() を取り消す。
        if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
            _TRACE_("【情報】ScenePhase::changeNothing() シーン("<<_pScene->getName()<<")で、"
                    "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                    "活動予約を取り消しの措置は行いません。");
        } else {
            _TRACE_("【情報】ScenePhase::changeNothing()  シーン("<<_pScene->getName()<<")で、"
                    "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在し、関連シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")が、"
                    "既に activateDelay() されています。しかし、本 changeNothing() を優先し、シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"の activateDelay() を取り消しました。");
            _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNothing();
}

void ScenePhase::changeNext() {
    if (_count_next_promise > 0) {
        //遷移先予約がすでにあった場合とりけす
        //遷移先予約が、今回のchangeと同じならいいが
        //異なる場合は、シーンの活動予約を取り消す。
        if (_phase_no+1 == _phase_no_next_promise) {
            //遷移先シーンが同じ、
            //_phase_no+1 のシーンは 即activate()で、既存activateDelay()を上書きするのでOK
        } else {
            //_phase_no_next_promiseの activateDelay() を取り消す。
            if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("【情報】ScenePhase::changeNext() _phase_no+1="<<(_phase_no+1)<<" シーン("<<_pScene->getName()<<")で、"
                        "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在しましたが、子シーンと関連付けされていないため、"
                        "活動予約を取り消しの措置は行いません。");
            } else {
                _TRACE_("【情報】ScenePhase::changeNext() _phase_no+1="<<(_phase_no+1)<<" シーン("<<_pScene->getName()<<")で、"
                        "遷移先予約フェーズ(_phase_no_next_promise="<<_phase_no_next_promise<<")が存在し、関連シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")が、"
                        "既に activateDelay() されています。しかし、本 changeNext() を優先し、シーン("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"の activateDelay() を取り消しました。");
                _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNext();
}

void ScenePhase::changeDelay(int prm_phase_no, frame prm_delay) {
    _phase_no_next_promise = prm_phase_no;
    _count_next_promise = (*_p_frame_counter) + prm_delay;
}

void ScenePhase::update() {
    if (_count_next_promise > 0) {
        if ((*_p_frame_counter) == _count_next_promise) {
            change(_phase_no_next_promise);
            _phase_no_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafCore::Phase::update();
}

ScenePhase::~ScenePhase() {
}
