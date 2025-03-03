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
        DWORD bone_num = pSkinInfo->GetNumBones();
        // 描画頂点に関係するボーンの数 ＝ ボーンオフセット行列の数
        pNewMC->_dwBoneOffsetMatrixNum = bone_num;
        //_TRACE_("pSkinInfo->GetNumBones() = "<<bone_num);
        pNewMC->_paBoneOffsetMatrix = new D3DXMATRIX[bone_num];
        for (DWORD i =  0; i < bone_num; i++) {
            // オフセット行列をコピーする
            memcpy(&pNewMC->_paBoneOffsetMatrix[i], pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DXMATRIX));
        }
        //_TRACE_("ボーンオフセット行列をコピーしますた");

        // メッシュデータ登録
        pNewMC->MeshData.Type = pMeshData->Type;   // メッシュタイプ
        //メッシュデータを最適化する
        //・頂点、描画面を並べ替えて最適化
        //・ボーンの影響をうける範囲ごとに、メッシュをサブセットに分割
        //・頂点情報にブレンド加重値を付与
        //・ボーンに合わせて頂点を移動
//        DWORD Options = D3DXMESH_SYSTEMMEM|D3DXMESHOPT_VERTEXCACHE;
        LPD3DXBUFFER pVertexRemap;
        hr = pNewMC->pSkinInfo->ConvertToBlendedMesh(
          pMeshData->pMesh,                  //[in] LPD3DXMESH pMesh, 入力メッシュ
          NULL,                              //[in] DWORD Options,          未使用？
          pAdjacency,                        //[in] CONST LPDWORD pAdjacencyIn, 入力メッシュ隣接面情報（配列？）
          pNewMC->pAdjacency,                //[out]LPDWORD pAdjacencyOut,     出力メッシュ隣接面情報
          NULL,                 //[out]DWORD *pFaceRemap,         面をどう並べ替えたかの情報、不要時NULL
          &(pVertexRemap),                 //[out]LPD3DXBUFFER *ppVertexRemap, 頂点をどう並べ替えたかの情報、不要時NULL
          &(pNewMC->_dwMaxInfleNum),         //[out]DWORD *pMaxFaceInfl, 一つの頂点に影響を与えるボーンの数の最大値
          &(pNewMC->_dwBoneCombNum),         //[out]DWORD *pNumBoneCombinations, ボーンコンビネーションの数
          &(pNewMC->_pBoneCombinationTable), //[out]LPD3DXBUFFER *ppBoneCombinationTable, ボーンコンビネーション情報、ボーンと頂点の対応表配列
          &(pNewMC->MeshData.pMesh)          //[out]LPD3DXMESH *ppMesh 出力メッシュ情報、処理済みのメッシュが返ってくる
        );
        checkDxException(hr, D3D_OK, "ConvertToBlendedMeshに失敗しました。");
        //Remap処理、ターゲットの頂点バッファが外部的に順番変更された場合は、このメソッドを呼び出す必要があります。
        DWORD* d = (DWORD*)pVertexRemap->GetBufferPointer();
        pNewMC->pSkinInfo->Remap(pNewMC->MeshData.pMesh->GetNumVertices(),d);
        pVertexRemap->Release();

        // ConvertToBlenderMesh関数で戻ってくる ID3DXBuffer には、
        // D3DXBONECOMBINATION構造体が　NumBoneCombinations 個入っている。
    } else {
        //throwCriticalException("SkinAniMeshAllocHierarchy::CreateMeshContainer()  pSkinInfo 情報がありません");
        _TRACE_("【警告】SkinAniMeshAllocHierarchy::CreateMeshContainer()  pSkinInfo 情報がありません。 pNewMC->Name="<<pNewMC->Name);
        pNewMC->pSkinInfo = nullptr;
        pNewMC->_dwBoneOffsetMatrixNum = 0;
        pNewMC->_paBoneOffsetMatrix = nullptr;
        pNewMC->_dwMaxInfleNum = 0;
        pNewMC->_dwBoneCombNum = 0;
        pNewMC->_pBoneCombinationTable = nullptr;
        BoneAniMeshAllocHierarchy::createNewMeshContainer(); //今のところ変更なし
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
    //親クラスメンバ(BoneAniMeshFrame)初期化
    tmp->_frame_index = MAXDWORD; // 0 が有効なインデックスなので 0 で初期化したくなかった
    D3DXMatrixIdentity(&(tmp->_world_trans_matrix)); //とりあえず単位行列
    //拡張分の初期化
    tmp->_bone_id = MAXDWORD;
    D3DXMatrixIdentity(&(tmp->_bone_offset_matrix));
    D3DXMatrixIdentity(&(tmp->_combined_matrix));
    return tmp;
}

D3DXMESHCONTAINER* SkinAniMeshAllocHierarchy::createNewMeshContainer() {
    SkinAniMeshContainer* tmp = NEW SkinAniMeshContainer();
    ZeroMemory(tmp, sizeof(D3DXMESHCONTAINER));
    //拡張分の初期化
    tmp->_dwMaxInfleNum = 0;    // ボーン最大影響数
    tmp->_dwBoneCombNum = 0;    // ボーンコンビネーション数
    tmp->_pBoneCombinationTable = nullptr;  // ボーンコンビネーション構造体配列へのポインタ

    tmp->_dwBoneOffsetMatrixNum = UINT_MAX;
    tmp->_paBoneOffsetMatrix = nullptr;
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

    D3DXMATRIX* paBoneOffsetMatrix = p->_paBoneOffsetMatrix;
    GGAF_DELETEARR_NULLABLE(pBoneCombinationTable);

    delete p;
    return D3D_OK;
}
