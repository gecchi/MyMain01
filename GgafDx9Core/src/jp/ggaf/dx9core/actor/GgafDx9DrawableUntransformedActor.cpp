#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
GgafDx9DrawableUntransformedActor::GgafDx9DrawableUntransformedActor(const char* prm_name,
                                                                     const char* prm_model,
                                                                     const char* prm_effect,
                                                                     const char* prm_technique,
                                                                     GgafDx9Checker* prm_pChecker) :
  GgafDx9UntransformedActor(prm_name, prm_pChecker) {
    _class_name = "GgafDx9DrawableUntransformedActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    //モデル取得
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //エフェクト取得
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
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
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
