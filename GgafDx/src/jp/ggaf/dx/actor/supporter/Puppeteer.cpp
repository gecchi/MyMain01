#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"

using namespace GgafDx;


Puppeteer::Performance::Performance() {
    _pAnimationSet = nullptr;
    _animation_set_index = 0;
//    _local_time._t_value = 0.0;
    _target_loop        = -1;
    _loop_count         = 0;
    _period             = 1.0;
//    _weight._t_value = 1.0;
    _method             = NO_CHENGE;
    _p1 = 0.0;
    _p2 = 1.0;
}
void Puppeteer::Performance::setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index) {
    _pAnimationSet = prm_pAnimationSet;
    _animation_set_index = prm_animation_set_index;
    _period = _pAnimationSet->GetPeriod();
}
Puppeteer::Performance::~Performance() {
}


//26693083 <DEBUG> [0] Enable=1
//26693083 <DEBUG> [0] Position=0
//26693083 <DEBUG> [0] Speed=1
//26693083 <DEBUG> [0] Weight=1
//26693083 <DEBUG> [0] Priority=0
//26693083 <DEBUG> [1] Enable=0
//26693083 <DEBUG> [1] Position=0
//26693083 <DEBUG> [1] Speed=0
//26693083 <DEBUG> [1] Weight=0
//26693083 <DEBUG> [1] Priority=0
Puppeteer::Puppeteer(ID3DXAnimationController* prm_pAc_cloned,
                     double prm_ani_time_delta) : GgafCore::Object() {
    _paPerformances = nullptr;
    _pAc = prm_pAc_cloned;
    _advance_time = 0.0;
//    _TRACE_("Puppeteer::Puppeteer!!!!");
//    D3DXTRACK_DESC TD;   // トラックの能力
//    for (int tno = 0; tno < 2; tno++) {
//        prm_pAc_cloned->GetTrackDesc(tno, &TD);
//        _TRACE_("["<<tno<<"] Enable="<<TD.Enable);
//        _TRACE_("["<<tno<<"] Position="<<TD.Position);
//        _TRACE_("["<<tno<<"] Speed="<<TD.Speed);
//        _TRACE_("["<<tno<<"] Weight="<<TD.Weight);
//        _TRACE_("["<<tno<<"] Priority="<<TD.Priority);
//    }
    HRESULT hr;
    //グローバル時間を0にする
    hr = _pAc->ResetTime();
    checkDxException(hr, D3D_OK, "失敗しました。");

    _ani_time_delta =  prm_ani_time_delta; //デフォルトはとりあえずマルペケ参考値 4800フレームを1秒
    _pStickMain = NEW Stick;
    _pStickSub = NEW Stick;
    _apStick[0] = _pStickMain;
    _apStick[1] = _pStickSub;

    _num_perform = _pAc->GetMaxNumAnimationSets();
#ifdef MY_DEBUG
    if (_num_perform == 0) {
        throwCriticalException("Puppeteer アニメーションセットが一つもありません。");
    }
    if (_pAc->GetMaxNumTracks() < 2) {
        throwCriticalException("Puppeteer アニメーショントラックが少なくとも2つ必要です。ご使用のビデオカードではトラック機能がありません。");
    }
#endif
    //int x = 'o'  ^0^  -~-  -0-  ~-~  +0+  0-0  *0*  0*0;
    UINT max_num_tracks = _pAc->GetMaxNumTracks();
    for (UINT tno = 0; tno < max_num_tracks; tno++) {
        hr = _pAc->SetTrackEnable(tno, FALSE);
    }

    //モーション情報初期化
    _paPerformances = NEW Performance[_num_perform];
    for (UINT i = 0; i < _num_perform; i++) {
        LPD3DXANIMATIONSET pAnimationSet;
        hr = _pAc->GetAnimationSet(i, &(pAnimationSet)); //アニメーションセット保持
        checkDxException(hr, D3D_OK, "失敗しました。");
        _paPerformances[i].setAnimationSet(pAnimationSet, i);
    }

    //Stick初期化(トラック初期設定)
    _pStickMain->_tno = 0;
//    _pStickMain->_pPerformance = &(_paPerformances[0]);
    _pStickMain->_pPerformance = nullptr;
    _pStickMain->_weight.setRange(0.000001, 1.0);
    _pStickMain->_weight._t_value = 1.0;

    _pStickSub->_tno = 1;
    _pStickSub->_pPerformance = nullptr;
    _pStickSub->_weight.setRange(0.000001, 1.0);
    _pStickSub->_weight._t_value = 0.0;

    //反映
    ID3DXAnimationController* pAc = _pAc;
    for (UINT hand = 0; hand < 2; hand++) {
        UINT tno = _apStick[hand]->_tno;
        Performance* p = _apStick[hand]->_pPerformance;
        if (p) {
            hr = pAc->SetTrackEnable(tno, TRUE);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackAnimationSet(tno, p->_pAnimationSet);
            checkDxException(hr, D3D_OK, "失敗しました。");
            _paAs[tno] = p->_pAnimationSet;
        } else {
            hr = pAc->SetTrackEnable(tno, FALSE);
            checkDxException(hr, D3D_OK, "失敗しました。");
            _paAs[tno] = nullptr;
        }
    }

}


void Puppeteer::play(UINT prm_performance_no) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    _pStickMain->_pPerformance = p;
    UINT main_tno = _pStickMain->_tno;
    _pStickMain->_weight._t_value = 1.0;
    _pStickMain->_weight.stop();

    HRESULT hr;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackAnimationSet(main_tno, _pStickMain->_pPerformance->_pAnimationSet); _paAs[main_tno] = _pStickMain->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(main_tno, 1.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(main_tno, 0.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");

    UINT sub_tno = _pStickSub->_tno;
    _pStickSub->_weight._t_value = 0.0;
    _pStickSub->_weight.stop();
    hr = _pAc->SetTrackEnable(sub_tno, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");
}
void Puppeteer::switchTo(UINT prm_performance_no, frame prm_switch_frames) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    if (_pStickMain->_pPerformance == p) {
        _TRACE_("Puppeteer::switchTo() prm_performance_no="<<prm_performance_no<<" は既にアニメーション中の為無視されました。");
        return;
    }

    _pStickSub->_pPerformance = p;
    _pStickSub->_weight._t_value = 0.0;
    _pStickSub->_weight.transitionLinearToTop(prm_switch_frames);
    UINT sub_tno = _pStickSub->_tno;
    HRESULT hr;
    hr = _pAc->SetTrackEnable(sub_tno, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackAnimationSet(sub_tno, _pStickSub->_pPerformance->_pAnimationSet); _paAs[sub_tno] = _pStickSub->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(sub_tno, 1.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(sub_tno, 0.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");


    _pStickMain->_weight.transitionLinearToBottom(prm_switch_frames);
    UINT main_tno = _pStickMain->_tno;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(main_tno,_pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");


    //MainとSubを交換
    Stick* pWk = _pStickMain;
    _pStickMain = _pStickSub;
    _pStickSub = pWk;

}
void Puppeteer::playPartly2(UINT prm_performance_no, int prm_loop) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    if (_pStickMain->_pPerformance == p) {
        _TRACE_("Puppeteer::switchTo() prm_performance_no="<<prm_performance_no<<" は既にアニメーション中の為無視されました。");
        return;
    }
    Puppeteer::playPartly(prm_performance_no, p->_period*prm_loop / _ani_time_delta);
}
void Puppeteer::playPartly(UINT prm_performance_no, frame prm_spend_frames) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    if (_pStickMain->_pPerformance == p) {
        _TRACE_("Puppeteer::switchTo() prm_performance_no="<<prm_performance_no<<" は既にアニメーション中の為無視されました。");
        return;
    }

    _pStickSub->_pPerformance = p;
    _pStickSub->_weight._t_value = 0.0;
    _pStickSub->_weight.beat(prm_spend_frames, prm_spend_frames*0.2, prm_spend_frames*0.6, prm_spend_frames*0.2, 1.0);
    UINT sub_tno = _pStickSub->_tno;
    HRESULT hr;
    hr = _pAc->SetTrackEnable(sub_tno, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackAnimationSet(sub_tno, _pStickSub->_pPerformance->_pAnimationSet); _paAs[sub_tno] = _pStickSub->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(sub_tno, 1.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(sub_tno, 0.0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");

    _pStickMain->_weight.rbeat(prm_spend_frames, prm_spend_frames*0.2, prm_spend_frames*0.6, prm_spend_frames*0.2, 1.0);
    UINT main_tno = _pStickMain->_tno;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(main_tno,_pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "失敗しました。");
}

void Puppeteer::behave() {

    HRESULT hr;
    UINT main_tno = _pStickMain->_tno;
    if (_pStickMain->_weight.isTransitioning()) {
        _pStickMain->_weight.behave();
        hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
        checkDxException(hr, D3D_OK, "失敗しました。");
//        _TRACE_("_pStickMain tno="<<main_tno<<" _weight="<<_pStickMain->_weight._t_value);
    }

    UINT sub_tno = _pStickSub->_tno;
    if (_pStickSub->_weight.isTransitioning()) {
        _pStickSub->_weight.behave();
        hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
        checkDxException(hr, D3D_OK, "失敗しました。");
//        _TRACE_("_pStickSub  tno="<<sub_tno<<" _weight="<<_pStickSub->_weight._t_value);
    } else {
        hr = _pAc->SetTrackEnable(sub_tno, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }
    _advance_time += _ani_time_delta;
}

void Puppeteer::stop() {
//    for (UINT hand = 0; hand < 2; hand++) {
//        Performance* p = _apStick[hand]->_pPerformance;
//        if (p) {
//            p->_method = NO_CHENGE;
//        }
//    }
}

void Puppeteer::updateAnimationTrack() {
    HRESULT hr;
    hr = _pAc->AdvanceTime(_advance_time, nullptr);
    checkDxException(hr, D3D_OK, "失敗しました。");
    _advance_time = 0;
}


Puppeteer::~Puppeteer() {
    GGAF_DELETE(_pStickMain);
    GGAF_DELETE(_pStickSub);
    GGAF_DELETEARR(_paPerformances);
}
