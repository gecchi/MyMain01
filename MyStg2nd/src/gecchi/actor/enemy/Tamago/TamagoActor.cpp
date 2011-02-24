#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "anibox") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(4000);
//    HRESULT hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    _last_time =  pAnimationSet0->GetPeriod();
//    hr = _pAc->SetTrackEnable(0, TRUE);//トラック有効
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackPosition(0,_last_time);//トラック0(=ID0番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
}

void TamagoActor::processBehavior() {
    if (GgafDx9Input::isPushedDownKey(DIK_0)) {
        _pPuppeteer->play(0, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_9)) {
        _pPuppeteer->play(1, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_8)) {
        _pPuppeteer->play(2, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_7)) {
        _pPuppeteer->play(3, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_6)) {
        _pPuppeteer->play(4, LOOP_MOTION_LINER);
    }

//    _TRACE_("GgafDx9Input::isBeingPressedKey(DIK_E)="<<(GgafDx9Input::isBeingPressedKey(DIK_E)));
    if (GgafDx9Input::isPushedDownKey(DIK_E)) {
        _pPuppeteer->stop();
//        _TRACE_("GgafDx9Input::isPushedDownKey(DIK_E)!!!!!!");
//        HRESULT hr;
//        LPD3DXANIMATIONSET pAnimationSet;
//        HRESULT hr = _pAc->GetAnimationSet(1, &pAnimationSet); //ID1番のアニメーションセット取得
//        checkDxException(hr, D3D_OK, "失敗しました。");
//        hr = _pAc->SetTrackAnimationSet(0, pAnimationSet);//ID1番のアニメーションセットをトラック0番にセット
//        checkDxException(hr, D3D_OK, "失敗しました。");
//        HRESULT hr = _pAc->SetTrackEnable(0, TRUE);//トラック有効
//        checkDxException(hr, D3D_OK, "失敗しました。");
    }

    if (GgafDx9Input::isPushedDownKey(DIK_R)) {
        _TRACE_("GgafDx9Input::isPushedDownKey(DIK_R)!!!!!!");
        _pPuppeteer->play();
//        HRESULT hr = _pAc->SetTrackEnable(0, FALSE);//トラック無効
//        checkDxException(hr, D3D_OK, "失敗しました。");
//    } else {
//        HRESULT hr = _pAc->SetTrackPosition(0,_last_time);//トラック0(=ID0番)のローカル時間を0にする
//        checkDxException(hr, D3D_OK, "失敗しました。");
//        _last_time -= (1.0/60.0);
    }

    _pPuppeteer->behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
