#ifndef GGAF_DX_BONEANIMESHFRAME_H_
#define GGAF_DX_BONEANIMESHFRAME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class BoneAniMeshFrame : public D3DXFRAME {
public:
    /** フレームツリーを直列化した際の要素番号 */
    DWORD _frame_index; //BoneAniMeshWorldMatStack の _prevTransformationMatrixList の要素番号と一致させる必要がある
    /** 描画時、計算後のワールド変換行列が格納される */
    D3DXMATRIX _world_trans_matrix;
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIX_H_*/
