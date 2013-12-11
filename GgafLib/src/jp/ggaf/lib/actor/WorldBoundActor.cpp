#include "stdafx.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDxWorldBoundActor(prm_name,
                              prm_model,
                              "WorldBoundEffect",
                              "WorldBoundTechnique",
                              nullptr,
                              nullptr) {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND);

    setZEnable(false);        //Zバッファは考慮無し
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void WorldBoundActor::initialize() {
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //世界境界球半径
    dxcoord dxmodel_r = 1.0f; //WorldBoundActorのモデルは半径DIRECTX距離1の球である事前提
    _sx = _sy = _sz = R_SC(dxworld_r/dxmodel_r)*0.989;
}


void WorldBoundActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・８分木登録
    //・視錐台からの距離計算
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    positionAs(P_CAM);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScRxRzRyMv(this, _matWorld); //ワールド変換
}
//void WorldBoundActor::processPreDraw() {
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

WorldBoundActor::~WorldBoundActor() {
}
