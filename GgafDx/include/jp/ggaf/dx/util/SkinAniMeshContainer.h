#ifndef GGAF_DX_SKINANIMESHCONTAINER_H_
#define GGAF_DX_SKINANIMESHCONTAINER_H_
#include "GgafDxCommonHeader.h"

#include <map>

namespace GgafDx {

/**
 * ワールド変換行列付きフレーム構造体
 */
class SkinAniMeshContainer : public D3DXMESHCONTAINER {
public:
    DWORD dwMaxInfleNum;            // ボーン最大影響数
    DWORD dwBoneCombNum;            // ボーンコンビネーション数
    D3DXBONECOMBINATION *pBoneComb;  // ボーンコンビネーション構造体配列へのポインタ
};

}
#endif /*GGAF_DX_SKINANIMESHCONTAINER_H_*/
