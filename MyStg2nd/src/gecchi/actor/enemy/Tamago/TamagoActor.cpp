#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(100);
    HRESULT hr;
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());

    LPD3DXANIMATIONSET pAnimationSet0;
    hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0番のアニメーションセット取得
    checkDxException(hr, D3D_OK, "失敗しました。");
//    LPD3DXANIMATIONSET pAnimationSet1;
//    hr = _pAc->GetAnimationSet(1, &pAnimationSet1); //ID1番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    LPD3DXANIMATIONSET pAnimationSet2;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet2); //ID2番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");

    hr = _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0番のアニメーションセットをトラック0番にセット（デフォルトでこうなるはず）
    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackAnimationSet(1, pAnimationSet1);//ID1番のアニメーションセットをトラック1番にセット（デフォルトでこうなるはず）
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackAnimationSet(2, pAnimationSet2);//ID2番のアニメーションセットをトラック2番にセット（デフォルトでこうなるはず）
//    checkDxException(hr, D3D_OK, "失敗しました。");

    hr = _pAc->ResetTime();//グローバル時間を0にする
    checkDxException(hr, D3D_OK, "失敗しました。");

//    hr = _pAc->SetTrackPosition(0,0);//トラック0(=ID0番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackPosition(1,0);//トラック1(=ID1番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackPosition(2,0);//トラック2(=ID2番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");

//    hr = _pAc->SetTrackEnable(0,TRUE );//トラック0(=ID0番)を有効
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackEnable(1,TRUE );//トラック1(=ID1番)を有効
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackEnable(2,TRUE );//トラック2(=ID2番)を有効
//    checkDxException(hr, D3D_OK, "失敗しました。");

//    hr = _pAc->SetTrackWeight(0, 1.00);
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackWeight(1, 1.00);
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackWeight(2, 1.00);
//    checkDxException(hr, D3D_OK, "失敗しました。");

//    hr = _pAc->AdvanceTime(0,NULL);//0秒進める（それを反映させる）。
//    checkDxException(hr, D3D_OK, "失敗しました。");

    //ID0番(=トラック0)のアニメーションセットの開始～終了までの時間(秒)
//    _advanceTimePerFrame =  pAnimationSet0->GetPeriod()/60.0;
//    double time_period0 = pAnimationSet0->GetPeriod();  //・pD3DXAniMeshModel->_anim_ticks_per_second = 4800fps の場合
                                                        //    1 ループ 4800 フレームアニメーションならば 1.0 (秒)を得る    (60/4800)
                                                        //    1 ループ 4800*2 フレームアニメーションならば 2.0 (秒)を得る
                                                        //・pD3DXAniMeshModel->_anim_ticks_per_second = 60fps の場合
                                                        //    1 ループ 60 フレームアニメーションならば 1.0 (秒)を得る
                                                        //    1 ループ 120 フレームアニメーションならば 2.0 (秒)を得る
//    _TRACE_("time_period0="<<time_period0);
//    double time_set0 = time_period0 / (60.0 / _pD3DXAniMeshModel->_anim_ticks_per_second); //そのアニメーションにかかる秒数
    //ID0番(=トラック0)の SetTrackSpeed が 1.0 固定ならば advanceTimePerFrame は time_period0 / (time_set0 * 60.0)
//    _advanceTimePerFrame0 = time_set0 / time_set0*60.0 ; //トラック0番のアニメーションを60分割時間を求める、つまり１ループ1秒にするための時間
//    hr = _pAc->SetTrackSpeed(0, 1.0f);  //トラック0(=ID0番)のスピードを設定。
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackSpeed(1, 1.0f);
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackSpeed(2, 1.0f);
//    checkDxException(hr, D3D_OK, "失敗しました。");
    _track0time = 0;
}

void TamagoActor::processBehavior() {
//    setCoordinateBy(P_MYSHIP);
    //ここをなんとかしる！
    _track0time += _advanceTimePerFrame;
    HRESULT hr = _pAc->SetTrackPosition(0,_track0time);//トラック0(=ID0番)のローカル時間を0にする
    checkDxException(hr, D3D_OK, "失敗しました。");

    hr = _pAc->AdvanceTime(_advanceTimePerFrame, NULL );
    checkDxException(hr, D3D_OK, "失敗しました。");
}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
