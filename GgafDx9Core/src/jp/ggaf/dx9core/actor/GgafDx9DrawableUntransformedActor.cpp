#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableUntransformedActor::GgafDx9DrawableUntransformedActor(const char* prm_name, GgafDx9Checker* prm_pChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pChecker) {
    _class_name = "GgafDx9DrawableUntransformedActor";
    _fAlpha = 1.0f;
}


void GgafDx9DrawableUntransformedActor::processDrawPrior() {
    //TODO:要検証
    if (_is_active_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            //＜メモ＞
            //透明の場合は、Z軸値で遠くから描画するように設定。
            //_Z が カメラ位置 ～ カメラ + 1000*MAX_DRAW_DEPTH_LEVEL の間であれば MAX_DRAW_DEPTH_LEVELで
            //段階レンダリングをすることとする。
            //粗さは 1000。←この範囲のZは同一深度となる。
            //TODO: カメラが動きZ座標で深度が決まらない場合波状する。正しくはカメラ座標からの距離でソートすべき。・・・その内やろう。
            GgafDx9Universe::setDrawDepthLevel(
              (_Z-(GgafDx9Universe::_pCamera->_pVecCamFromPoint->z*LEN_UNIT*PX_UNIT)) / 1000,
              this
            );
        } else {
            //不透明の場合は初めに描画するように設定。
            //レンダリング時最遠から描画するので、深度レベルはMAX
            GgafDx9Universe::setDrawDepthMaxLevel(this);
        }
    }
}




GgafDx9DrawableUntransformedActor::~GgafDx9DrawableUntransformedActor() {
}
