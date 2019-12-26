#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"

#include "jp/ggaf/dx/util/SkinAniMeshContainer.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"
#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

SkinAniMeshAllocHierarchy::SkinAniMeshAllocHierarchy() : BoneAniMeshAllocHierarchy() {
}

SkinAniMeshAllocHierarchy::~SkinAniMeshAllocHierarchy() {
}

// メッシュコンテナ生成関数
HRESULT SkinAniMeshAllocHierarchy::CreateMeshContainer(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer) {
    // メッシュコンテナオブジェクトの生成
    SkinAniMeshContainer* pNewMC = (SkinAniMeshContainer*)createNewMeshContainer();
    HRESULT hr;

    // 名前登録
    pNewMC->Name = copyStr( Name );
    // 隣接ポリゴン情報格納のためのバッファ確保
    DWORD polynum = pMeshData->pMesh->GetNumFaces();
    pNewMC->pAdjacency = NEW DWORD[ polynum * 3 ];   // 配列生成
    memset(pNewMC->pAdjacency, 0, polynum * 3 * sizeof(DWORD)); // コピー

    // スキン登録
    if(pSkinInfo) {
        pNewMC->pSkinInfo = pSkinInfo;// スキンをコピー
        pNewMC->pSkinInfo->AddRef();

        // メッシュデータ登録
        pNewMC->MeshData.Type = pMeshData->Type;   // メッシュタイプ
        //メッシュデータを最適化する
        //・頂点、描画面を並べ替えて最適化
        //・ボーンの影響をうける範囲ごとに、メッシュをサブセットに分割
        //・頂点情報にブレンド加重値を付与
        //・ボーンに合わせて頂点を移動
        DWORD Options = D3DXMESH_MANAGED|D3DXMESHOPT_VERTEXCACHE;
        hr = pNewMC->pSkinInfo->ConvertToBlendedMesh(
          pMeshData->pMesh,                  //[in] LPD3DXMESH pMesh, 入力メッシュ
          Options,                           //[in] DWORD Options,          未使用？
          pAdjacency,                        //[in] CONST LPDWORD pAdjacencyIn, 入力メッシュ隣接面情報（配列？）
          pNewMC->pAdjacency,                //[out]LPDWORD pAdjacencyOut,     出力メッシュ隣接面情報
          NULL,                 //[out]DWORD *pFaceRemap,         面をどう並べ替えたかの情報、不要時NULL
          NULL,              //[out]LPD3DXBUFFER *ppVertexRemap, 頂点をどう並べ替えたかの情報、不要時NULL
          &(pNewMC->_dwMaxInfleNum),         //[out]DWORD *pMaxFaceInfl, 一つの頂点に影響を与えるボーンの数の最大値
          &(pNewMC->_dwBoneCombNum),         //[out]DWORD *pNumBoneCombinations, ボーンコンビネーションの数
          &(pNewMC->_pBoneCombinationTable), //[out]LPD3DXBUFFER *ppBoneCombinationTable, ボーンコンビネーション情報、ボーンと頂点の対応表配列
          &(pNewMC->MeshData.pMesh)          //[out]LPD3DXMESH *ppMesh 出力メッシュ情報、処理済みのメッシュが返ってくる
        );
        // ConvertToBlenderMesh関数で戻ってくる ID3DXBuffer には、
        // D3DXBONECOMBINATION構造体が　NumBoneCombinations 個入っている。
    } else {
        throwCriticalException("SkinAniMeshAllocHierarchy::CreateMeshContainer()  pSkinInfo 情報がありません");
    }

    // マテリアル登録
    pNewMC->NumMaterials = NumMaterials;
    registerMaterial( pMaterials, NumMaterials, &pNewMC->pMaterials);
    // エフェクト登録
    registerEffect( pEffectInstances, &pNewMC->pEffects );

    *ppNewMeshContainer = pNewMC;

    return D3D_OK;
}

D3DXFRAME* SkinAniMeshAllocHierarchy::createNewFrame() {
    SkinAniMeshFrame* tmp = NEW SkinAniMeshFrame;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //拡張分の初期化
    tmp->_frame_index = UINT_MAX; // 0 が有効なインデックスなので 0 で初期化したくなかった
    D3DXMatrixIsIdentity(&(tmp->_world_trans_matrix)); //とりあえず単位行列
    D3DXMatrixIsIdentity(&(tmp->_bone_offset_matrix));
    D3DXMatrixIsIdentity(&(tmp->_conbined_matrix));
    return tmp;
}

D3DXMESHCONTAINER* SkinAniMeshAllocHierarchy::createNewMeshContainer() {
    SkinAniMeshContainer* tmp = NEW SkinAniMeshContainer();
    ZeroMemory(tmp, sizeof(D3DXMESHCONTAINER));
    //拡張分の初期化
    tmp->_dwMaxInfleNum = 0;    // ボーン最大影響数
    tmp->_dwBoneCombNum = 0;    // ボーンコンビネーション数
    tmp->_pBoneCombinationTable = nullptr;  // ボーンコンビネーション構造体配列へのポインタ
    return tmp;
}

// コンテナを削除
HRESULT SkinAniMeshAllocHierarchy::DestroyMeshContainer(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree) {
    SkinAniMeshContainer* p = (SkinAniMeshContainer*)pMeshContainerToFree;

    delete[] p->Name;
    ID3DXMesh* pMesh = p->MeshData.pMesh;
    GGAF_RELEASE_NULLABLE(pMesh);

    for(unsigned int i=0; i < p->NumMaterials; i++){
        delete[] p->pMaterials[i].pTextureFilename;
    }
    delete[] p->pMaterials;

    // エフェクト
    for(int i = 0; i < p->pEffects->NumDefaults; i++) {
        delete[] p->pEffects->pDefaults[i].pParamName;
        delete[] p->pEffects->pDefaults[i].pValue;
    }

    delete[] p->pEffects->pEffectFilename;
    delete[] p->pEffects->pDefaults;
    delete p->pEffects;

    delete[] p->pAdjacency;
    LPD3DXSKININFO pSkinInfo = p->pSkinInfo;
    GGAF_RELEASE_NULLABLE(pSkinInfo);

    //これを追加、その他は同じ
    ID3DXBuffer* pBoneCombinationTable = p->_pBoneCombinationTable;
    GGAF_RELEASE_NULLABLE(pBoneCombinationTable);

    delete p;
    return D3D_OK;
}
