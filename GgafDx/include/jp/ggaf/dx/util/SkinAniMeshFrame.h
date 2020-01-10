#ifndef GGAF_DX_SKINANIMESHFRAME_H_
#define GGAF_DX_SKINANIMESHFRAME_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class SkinAniMeshFrame : public BoneAniMeshFrame {
public:
    D3DXMATRIX _bone_offset_matrix;    // ボーンオフセット行列
    D3DXMATRIX _combined_matrix;  // 合成行列
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIXEX_H_*/
