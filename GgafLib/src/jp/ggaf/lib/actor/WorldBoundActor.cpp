#include "jp/ggaf/lib/actor/WorldBoundActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


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
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_WORLDBOUND);

    setZEnableDraw(false);        //Zバッファは考慮無し
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
}

void WorldBoundActor::initialize() {
    DefaultCamera* pCam = P_GOD->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //世界境界球半径
    dxcoord world_bound_model_r = 1.0f; //WorldBound001のモデルは半径DIRECTX距離1の球である
    setScaleR((world_r*0.989)/world_bound_model_r);
}


void WorldBoundActor::processSettlementBehavior() {
    DefaultCamera* pCam = P_GOD->getSpacetime()->getCamera();
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
    UTIL::setWorldMatrix_ScRxRzRyMv(this, _matWorld); //ワールド変換
}
//void WorldBoundActor::processPreDraw() {
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

WorldBoundActor::~WorldBoundActor() {
}
