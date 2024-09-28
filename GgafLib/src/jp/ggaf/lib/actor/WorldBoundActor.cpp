#include "jp/ggaf/lib/actor/WorldBoundActor.h"

#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

using namespace GgafLib;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDx::WorldBoundActor(prm_name,
                              prm_model,
                              "WorldBoundEffect",
                              "WorldBoundTechnique") {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    setHitAble(false);
    setZEnableDraw(false);   //Zバッファは考慮無し
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setSpecialRenderDepthFar(0); //特別な最背面レンダリング（一番最初に描画）
    setFaceAngZero();
}

void WorldBoundActor::initialize() {
    DefaultCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    setPositionAt(pCam);
    dxcoord world_r = pCam->getZFar(); //世界境界球半径
    dxcoord world_bound_model_r = 1.0f; //WorldBound001のモデルは半径DIRECTX距離1の球である
    setScaleR((world_r*0.989)/world_bound_model_r);
}


void WorldBoundActor::processSettlementBehavior() {
    DefaultCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    //画面外判定無しに伴ない処理簡略化。
    //次の処理を無視しています
    //・自身がボーン時の考慮
    //・八分木登録
    //・視錐台からの距離計算
    //GeometricActor::processSettlementBehavior() と同期を取る事！
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
//    //FigureActor::processPreDraw() と同期を取る事！
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //モデル作成時の初期処理
//        _pModel->_is_init_model = true;
//    }
//    GgafDx::Spacetime::registerDrawActor(CONFIG::RENDER_DEPTH_INDEXS_NUM,this); //最深部
//}

WorldBoundActor::~WorldBoundActor() {
}
