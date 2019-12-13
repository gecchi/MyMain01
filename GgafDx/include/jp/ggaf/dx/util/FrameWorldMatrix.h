#ifndef GGAF_DX_FRAMEWORLDMATRIX_H_
#define GGAF_DX_FRAMEWORLDMATRIX_H_
#include "GgafDxCommonHeader.h"

#include <map>
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class FrameWorldMatrix : public D3DXFRAME {
public:
    /** フレームツリーを直列化した際の要素番号 */
    UINT _frame_index; //WorldMatStack の _prevTransformationMatrixList の要素番号と一致させる必要がある
    /** 描画時、計算後のワールド変換行列が格納される */
    D3DXMATRIX _world_trans_matrix;
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIX_H_*/
