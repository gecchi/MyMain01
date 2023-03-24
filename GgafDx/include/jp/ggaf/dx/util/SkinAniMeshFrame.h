#ifndef GGAF_DX_SKINANIMESHFRAME_H_
#define GGAF_DX_SKINANIMESHFRAME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class SkinAniMeshFrame : public BoneAniMeshFrame {
public:
    DWORD _bone_id;
    /** ボーンオフセット行列 */
    D3DXMATRIX _bone_offset_matrix; //ローカル頂点をボーン空間の座標に変換する行列
                                    //考え方：boneanimesh のXファイルのメッシュは、skinメッシュ頂点にボーンオフセット行列を掛けたもの（ではないか？）
    D3DXMATRIX _combined_matrix;  // 合成行列
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIXEX_H_*/
