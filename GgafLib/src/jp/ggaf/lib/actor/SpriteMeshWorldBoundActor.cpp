#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshWorldBoundActor::SpriteMeshWorldBoundActor(const char* prm_name,
                                                     const char* prm_model,
                                                     GgafStatus* prm_pStat) :
        GgafDxSpriteMeshActor(prm_name,
                               prm_model,
                               prm_pStat,
                               nullptr) {

    _class_name = "SpriteMeshWorldBoundActor";
    _pScaler = NEW GgafDxScaler(this);
    changeEffectTechnique("NoLight"); //NoLightでベタ塗りテクニック
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_ScMv); //拡大×平行移動のみ
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);
}

void SpriteMeshWorldBoundActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・８分木登録
    //・視錐台からの距離計算
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    locateWith(P_CAM);
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //ワールド変換
}
//void SpriteMeshWorldBoundActor::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //次の処理を無視しています
//    //・段階レンダリングの深度計算
//    //・一時テクニック考慮
//    //GgafDxDrawableActor::processPreDraw() と同期を取る事！
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //モデル作成時の初期処理
//        _pModel->_is_init_model = true;
//    }
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL,this); //最深部
//}

SpriteMeshWorldBoundActor::~SpriteMeshWorldBoundActor() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
