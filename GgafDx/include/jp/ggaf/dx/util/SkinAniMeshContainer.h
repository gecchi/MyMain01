#ifndef GGAF_DX_SKINANIMESHCONTAINER_H_
#define GGAF_DX_SKINANIMESHCONTAINER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/BoneAniMeshContainer.h"

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class SkinAniMeshContainer : public BoneAniMeshContainer {
public:
    DWORD _dwMaxInfleNum;            // ボーン最大影響数
    DWORD _dwBoneCombNum;            // ボーンコンビネーション数
    ID3DXBuffer* _pBoneCombinationTable;
//    D3DXBONECOMBINATION* _pBoneComb; // ボーンコンビネーション構造体配列へのポインタ
    DWORD _dwBoneOffsetMatrixNum;
    D3DXMATRIX* _paBoneOffsetMatrix;
};

}
#endif /*GGAF_DX_SKINANIMESHCONTAINER_H_*/
