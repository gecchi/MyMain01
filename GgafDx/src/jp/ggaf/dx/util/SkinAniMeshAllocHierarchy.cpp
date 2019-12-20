#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/SkinAniMeshContainer.h"
using namespace GgafDx;

SkinAniMeshAllocHierarchy::SkinAniMeshAllocHierarchy(void)
{
}

SkinAniMeshAllocHierarchy::~SkinAniMeshAllocHierarchy(void)
{
}

void SkinAniMeshAllocHierarchy::registerMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest) {
    pDest->Type = pSrc->Type;   // メッシュタイプ
    pDest->pMesh = pSrc->pMesh;// メッシュ（unionなのでどれでも一緒）
    //最適化するのでAddRefを除去
//    (pDest->pMesh)->AddRef();
}

D3DXMESHCONTAINER* SkinAniMeshAllocHierarchy::createNewMeshContainer() {
    SkinAniMeshContainer* tmp = NEW SkinAniMeshContainer();
    ZeroMemory(tmp, sizeof(SkinAniMeshContainer));
    //	下記の独自追加した分も ZeroMemory されるので注意
//    DWORD dwMaxInfleNum;            // ボーン最大影響数
//    DWORD dwBoneCombNum;            // ボーンコンビネーション数
//    D3DXBONECOMBINATION *pBoneComb;  // ボーンコンビネーション構造体配列へのポインタ

    return tmp;
}

