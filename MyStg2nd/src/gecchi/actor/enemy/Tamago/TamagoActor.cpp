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
    _SX = _SY = _SZ = 200;
    LPD3DXANIMATIONSET pAnimationSet0;
    _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0番のアニメーションセット
    _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0番のアニメーションセットをトラック0番にセット（デフォルトでこうなるはず）
    _pAc->ResetTime();//グローバル時間を0にする
    _pAc->SetTrackPosition(0,0);//トラック0(=ID0番)のローカル時間を0にする
    _pAc->AdvanceTime(0,NULL);//それを反映させる。
    double time_set0 =  pAnimationSet0->GetPeriod(); //ID0番(=トラック0)のアニメーションセットの開始～終了までの時間
    _advanceTimePerFrame0 = time_set0 / 60.0 ; //トラック0番のアニメーションを60分割時間を求める、つまり１ループ1フレームにするための時間
    _pAc->SetTrackSpeed(0, 0.5f);  //トラック0(=ID0番)のスピードを設定。
                                  //1.0で1ループ60フレーム
                                  //0.5で1ループ60*2フレーム
                                  //0.1で1ループ60*10フレームになるはず
}

void TamagoActor::processBehavior() {

}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
