#ifndef GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#define GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"

namespace GgafDx {

class SkinAniMeshAllocHierarchy: public BoneAniMeshAllocHierarchy {
public:
    SkinAniMeshAllocHierarchy(void);
public:
    virtual ~SkinAniMeshAllocHierarchy(void);

protected:
    // メッシュコンテナ構造体を生成する
    virtual D3DXMESHCONTAINER* createNewMeshContainer();
    // メッシュデータを登録
    virtual void registerMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest);
};

}
#endif /*GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_*/
