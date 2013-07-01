#include "stdafx.h"
#include "jp/ggaf/lib/actor/SpriteMeshWorldBoundActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

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
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);
}

void SpriteMeshWorldBoundActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・８分木登録
    //・視錐台からの距離計算
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    positionAs(P_CAM);
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    UTIL::setWorldMatrix_ScMv(this, _matWorld); //ワールド変換
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
    GGAF_DELETE(_pScaler);
}
