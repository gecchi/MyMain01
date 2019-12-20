#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"


using namespace GgafDx;

BoneAniMeshAllocHierarchy::BoneAniMeshAllocHierarchy(void)
{
}

BoneAniMeshAllocHierarchy::~BoneAniMeshAllocHierarchy(void)
{
}


// ワールド変換行列付きのフレーム構造体を生成
D3DXFRAME* BoneAniMeshAllocHierarchy::createNewFrame()
{
    BoneAniMeshFrame* tmp = NEW BoneAniMeshFrame;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //	下記の独自追加した分は ZeroMemory しないで自分で初期化
    //    /** フレームツリーを直列化した際の要素番号 */
    //    UINT _frame_index; //BoneAniMeshWorldMatStack の _prevTransformationMatrixList の要素番号と一致させる必要がある
    //    /** 描画時、計算後のワールド変換行列が格納される */
    //    D3DXMATRIX _world_trans_matrix;

    return tmp;
}
