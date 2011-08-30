#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDx9WorldBoundActor(prm_name,
                               prm_model,
                               "WorldBoundEffect",
                               "WorldBoundTechnique",
                               NULL,
                               NULL) {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    _pScaler = NEW GgafDx9Scaler(this);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);
}

void WorldBoundActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・８分木登録
    //・視錐台からの距離計算
    //GgafDx9GeometricActor::processSettlementBehavior() と同期を取る事！
    locateAs(P_CAM);
    _fX = App2Dx(_X);
    _fY = App2Dx(_Y);
    _fZ = App2Dx(_Z);
    GgafDx9Util::setWorldMatrix_ScRxRzRyMv(this, _matWorld); //ワールド変換
}
//void WorldBoundActor::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //次の処理を無視しています
//    //・段階レンダリングの深度計算
//    //・一時テクニック考慮
//    //GgafDx9DrawableActor::processPreDraw() と同期を取る事！
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //モデル作成時の初期処理
//        _pModel->_is_init_model = true;
//    }
//    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL,this); //最深部
//}

WorldBoundActor::~WorldBoundActor() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
