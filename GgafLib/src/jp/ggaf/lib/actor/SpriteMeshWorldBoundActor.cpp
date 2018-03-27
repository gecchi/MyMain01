#include "jp/ggaf/lib/actor/SpriteMeshWorldBoundActor.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

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
    changeEffectTechnique("NoLight"); //NoLightでベタ塗りテクニック
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_SP_BACK(1));
}

void SpriteMeshWorldBoundActor::processSettlementBehavior() {
    DefaultCamera* pCam = pGOD->getSpacetime()->getCamera();
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・八分木登録
    //・視錐台からの距離計算
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    setPositionAt(pCam);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScMv(this, _matWorld); //ワールド変換
}
//void SpriteMeshWorldBoundActor::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //次の処理を無視しています
//    //・段階レンダリングの深度計算
//    //・一時テクニック考慮
//    //GgafDxFigureActor::processPreDraw() と同期を取る事！
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //モデル作成時の初期処理
//        _pModel->_is_init_model = true;
//    }
//    GgafDxSpacetime::registerFigureActor(REGULAR_RENDER_DEPTH_INDEXS_NUM,this); //最深部
//}

SpriteMeshWorldBoundActor::~SpriteMeshWorldBoundActor() {
}

