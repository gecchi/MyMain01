#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;





//--------------------------------------------------------------------------------------
//階層割り当て：フレーム作成
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
    HRESULT hr = S_OK;
    D3DXFRAME_DERIVED *pFrame;//フレーム

    *ppNewFrame = NULL;

    pFrame = new D3DXFRAME_DERIVED;
    if (pFrame == NULL)//フレームが作成できなかったら
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }

    hr = AllocateName(Name, &pFrame->Name);//割り当て名を設定
    if (FAILED(hr)) goto e_Exit;

    //フレームの部品を初期化
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

    pFrame->pMeshContainer = NULL;
    pFrame->pFrameSibling = NULL;
    pFrame->pFrameFirstChild = NULL;

    *ppNewFrame = pFrame;
    pFrame = NULL;

    e_Exit: delete pFrame;
    return hr;
}

//--------------------------------------------------------------------------------------
//メッシュコンテナ作成
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(
        LPCSTR Name,//名前
        CONST D3DXMESHDATA *pMeshData,//メッシュデータ
        CONST D3DXMATERIAL *pMaterials,//マテリアル
        CONST D3DXEFFECTINSTANCE *pEffectInstances,//エフェクトの実体
        DWORD NumMaterials,//マテリアル数
        CONST DWORD *pAdjacency,//隣接関係
        LPD3DXSKININFO pSkinInfo,//スキン情報
        LPD3DXMESHCONTAINER *ppNewMeshContainer)//メッシュコンテナのポインタ
{
    HRESULT hr;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
    UINT NumFaces;//面の数
    UINT iMaterial;//マテリアルの数
    UINT iBone, cBones;//ボーンの数
    LPDIRECT3DDEVICE9 pd3dDevice = NULL;

    LPD3DXMESH pMesh = NULL;

    *ppNewMeshContainer = NULL;

    //パッチメッシュは扱えないので見つかったら終了
    if (pMeshData->Type != D3DXMESHTYPE_MESH)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    // メッシュポインタをメッシュデータ構造体から得る
    pMesh = pMeshData->pMesh;

    //FVFコンパチブルメッシュは扱えないので見つかったら終了
    if (pMesh->GetFVF() == 0)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    //D3DXMESHCONTAINERとしてリターンするためにオーバーロード状態の構造体を設定する
    pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
    if (pMeshContainer == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }
    memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

    //名前を設定する
    hr = AllocateName(Name, &pMeshContainer->Name);
    if (FAILED(hr))
    goto e_Exit;

    pMesh->GetDevice(&pd3dDevice);
    NumFaces = pMesh->GetNumFaces();

    //法線がメッシュにないなら、法線を設定する
    if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
    {
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        //メッシュのクローンを作って法線の場所を空ける
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(),
                pMesh->GetFVF() | D3DFVF_NORMAL,
                pd3dDevice, &pMeshContainer->MeshData.pMesh );
        if (FAILED(hr))
        goto e_Exit;

        //使用するメッシュコンテナからメッシュポインタを取り戻す
        //注意：それの参照がまだないので解放はしない
        pMesh = pMeshContainer->MeshData.pMesh;

        //メッシュポインタに法線を作る
        D3DXComputeNormals( pMesh, NULL );
    }
    else //法線が無ければ、ただメッシュにメッシュコンテナの参照をセットする
    {
        pMeshContainer->MeshData.pMesh = pMesh;
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        pMesh->AddRef();
    }

    //メモリを割り当てマテリアル情報を設定する
    //シェーダーの代わりにD3D9のマテリアルとテクスチャ
    pMeshContainer->NumMaterials = max(1, NumMaterials);
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
    pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
    pMeshContainer->pAdjacency = new DWORD[NumFaces*3];
    if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }

    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces*3);
    memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

    //マテリアルが設定されたらそれをコピーする
    if (NumMaterials > 0)
    {
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

        for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
        {
            if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
            {
                WCHAR str[MAX_PATH];

                MtoW( str,pMeshContainer->pMaterials[iMaterial].pTextureFilename, MAX_PATH );
                if( FAILED( D3DXCreateTextureFromFileW( pd3dDevice, str,
                                        &pMeshContainer->ppTextures[iMaterial] ) ) )
                pMeshContainer->ppTextures[iMaterial] = NULL;

                //ポインタをダイナミックメモリに確保しない事、テクスチャ名はNULLにする
                pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
            }
        }
    }
    else //もし、マテリアルが無かったらデフォルトの材質を
    {
        pMeshContainer->pMaterials[0].pTextureFilename = NULL;
        memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
    }

    //スキン情報があれば、ハードウェアスキニングのためにそれを使う
    if (pSkinInfo != NULL)
    {
        //まず最初にデータはスキン情報とメッシュに保存される
        pMeshContainer->pSkinInfo = pSkinInfo;
        pSkinInfo->AddRef();

        pMeshContainer->pOrigMesh = pMesh;
        pMesh->AddRef();

        //フィギュアスペースからボーンスペースへの頂点を移すためにオフセットマトリクスの配列が必要
        cBones = pSkinInfo->GetNumBones();
        pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
        if (pMeshContainer->pBoneOffsetMatrices == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto e_Exit;
        }

        //ここでボーンマトリクスを得て後で取得する必要を無くする
        for (iBone = 0; iBone < cBones; iBone++)
        {
            pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
        }

        //GenerateSkinnedMeshはハードウェアスキニングに最適なバージョンに変える
        hr = GenerateSkinnedMesh( pd3dDevice, pMeshContainer );
        if (FAILED(hr))
        goto e_Exit;
    }

    *ppNewMeshContainer = pMeshContainer;
    pMeshContainer = NULL;

    e_Exit:
    SAFE_RELEASE(pd3dDevice);

    //適当に割り当てられたデータをきれいにする
    if (pMeshContainer != NULL)
    {
        DestroyMeshContainer(pMeshContainer);
    }

    return hr;
}

//--------------------------------------------------------------------------------------
//フレーム削除
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree) {
    SAFE_DELETE_ARRAY(pFrameToFree->Name);
    SAFE_DELETE(pFrameToFree);
    return S_OK;
}

//--------------------------------------------------------------------------------------
//メッシュコンテナ削除
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase) {
    UINT iMaterial;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*) pMeshContainerBase;

    SAFE_DELETE_ARRAY(pMeshContainer->Name);
    SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
    SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
    SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);

    //割り当てられた全てのテクスチャを解放する
    if (pMeshContainer->ppTextures != NULL) {
        for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++) {
            SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
        }
    }

    SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
    SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);
    SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
    SAFE_RELEASE(pMeshContainer->pSkinInfo);
    SAFE_RELEASE(pMeshContainer->pOrigMesh);
    SAFE_DELETE(pMeshContainer);
    return S_OK;
}













GgafDx9AllocHierarchy::GgafDx9AllocHierarchy(void)
{
}


// デストラクタ
GgafDx9AllocHierarchy::~GgafDx9AllocHierarchy(void)
{
    // 登録されたオブジェクトを全て削除する
    list<deleterBase*>::iterator it = m_DelList.begin();
    for(; it!=m_DelList.end(); it++)
        delete[] (*it);

    list<IUnknown*>::iterator comit = m_ReleaseList.begin();
    for(; comit!=m_ReleaseList.end();comit++){
        if(*comit)
            (*comit)->Release();
    }
}


// フレーム構造体を生成
D3DXFRAME* GgafDx9AllocHierarchy::CreateNewFrame()
{
    D3DXFRAME* tmp = new D3DXFRAME;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    AddDelList( new deleter<D3DXFRAME>(tmp) );
    return tmp;
}


// メッシュコンテナ構造体を生成
D3DXMESHCONTAINER *GgafDx9AllocHierarchy::CreateNewMeshContainer()
{
    D3DXMESHCONTAINER* tmp = new D3DXMESHCONTAINER;
    ZeroMemory( tmp, sizeof(D3DXMESHCONTAINER) );
    AddDelList( new deleter<D3DXMESHCONTAINER>(tmp) );
    return tmp;
}


// 消去リストに登録
void GgafDx9AllocHierarchy::AddDelList( deleterBase* ptr, bool isAry )
{
    m_DelList.push_back( ptr );
}

// リリースリストに登録
void GgafDx9AllocHierarchy::AddReleaseList( IUnknown *comptr)
{
    comptr->AddRef();
    m_ReleaseList.push_back( comptr );
}


// 文字列コピー関数
LPSTR GgafDx9AllocHierarchy::CopyStr(LPCSTR name)
{
    if(!name) return NULL;   // NULLは文字数をカウントできない
    LPSTR Str = new char[strlen(name)+1];
    Str = strcpy(Str, name);
    AddDelList( new deleter<char>( Str, true ) );
    return Str;
}


// メッシュデータ登録
void GgafDx9AllocHierarchy::RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
    pDest->Type = pSrc->Type;   // メッシュタイプ
    pDest->pMesh = pSrc->pMesh;   // メッシュ（unionなのでどれでも一緒）
    AddReleaseList( pDest->pMesh );  // Releaseリストへ登録
}


// マテリアル登録
void GgafDx9AllocHierarchy::RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
    // マテリアル配列の生成
    *ppDest = new D3DXMATERIAL[ num ];
    AddDelList( new deleter<D3DXMATERIAL>( *ppDest, true ) );

    DWORD i;
    for(i=0; i<num; i++)
    {
        (*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // マテリアル登録
        (*ppDest)[i].pTextureFilename = CopyStr( pSrc[i].pTextureFilename );  // テクスチャ名登録
    }
}


// エフェクト登録
void GgafDx9AllocHierarchy::RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
    *ppDest = new D3DXEFFECTINSTANCE;
    AddDelList( new deleter<D3DXEFFECTINSTANCE>(*ppDest) );
    (*ppDest)->pEffectFilename = CopyStr(pSrc->pEffectFilename);     // エフェクト名
    (*ppDest)->NumDefaults = pSrc->NumDefaults;                      // エフェクトデフォルト数
    (*ppDest)->pDefaults = new D3DXEFFECTDEFAULT[pSrc->NumDefaults];  // エフェクトデフォルト配列生成
    AddDelList( new deleter<D3DXEFFECTDEFAULT>( (*ppDest)->pDefaults, true ) );

    // エフェクトデフォルトの登録
    D3DXEFFECTDEFAULT *pEDSrc  = pSrc->pDefaults;   // コピー元
    D3DXEFFECTDEFAULT *pEDDest = (*ppDest)->pDefaults; // コピー先
    unsigned int i=0;
    for(i=0; i<pSrc->NumDefaults; i++)
    {
       pEDDest[i].pParamName = CopyStr(pEDSrc[i].pParamName);				// パラメータ名
       DWORD NumBytes		 = pEDDest[i].NumBytes = pEDSrc[i].NumBytes;	// パラメータサイズ
       pEDDest[i].Type		 = pEDSrc[i].Type;								// パラメータタイプ
       if(pEDSrc[i].Type <= D3DXEDT_DWORD){
          pEDDest[i].pValue = (void*)( new BYTE[ NumBytes ] );              // パラメータ配列生成
          memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
          AddDelList( new deleter<void>( pEDDest[i].pValue, true ) );
       }
    }
}


// 隣接ポリゴン登録
void GgafDx9AllocHierarchy::RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
    *Dest = new DWORD[ polynum * 3 ];   // 配列生成
    memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));  // コピー
    AddDelList( new deleter<DWORD>( *Dest, true ) );
}


// スキン登録
void GgafDx9AllocHierarchy::RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest)
{
    if(!Src) return;   // スキンが無ければ何もしない
    *Dest = Src;               // スキンをコピー
//	(*Dest)->AddRef();         // 参照カウンタ増加
    AddReleaseList( *Dest );   // リリースリストに登録
}


// フレーム生成関数
HRESULT GgafDx9AllocHierarchy::CreateFrame(THIS_
   LPCSTR Name,
   LPD3DXFRAME *ppNewFrame)
{
    // フレームを新しく生成
    D3DXFRAME *pFrame = CreateNewFrame();
    pFrame->Name = CopyStr( Name );
    *ppNewFrame = pFrame;

    return D3D_OK;
}


// メッシュコンテナ生成関数
HRESULT GgafDx9AllocHierarchy::CreateMeshContainer(THIS_
   LPCSTR Name,
   CONST D3DXMESHDATA *pMeshData,
   CONST D3DXMATERIAL *pMaterials,
   CONST D3DXEFFECTINSTANCE *pEffectInstances,
   DWORD NumMaterials,
   CONST DWORD *pAdjacency,
   LPD3DXSKININFO pSkinInfo,
   LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
    // メッシュコンテナオブジェクトの生成
    D3DXMESHCONTAINER *p = CreateNewMeshContainer();

    // 名前登録
    p->Name = CopyStr( Name );

    // メッシュデータ登録
    RegistMeshData( pMeshData, &p->MeshData );

    // マテリアル登録
    p->NumMaterials = NumMaterials;
    RegistMaterial( pMaterials, NumMaterials, &p->pMaterials);

    // エフェクト登録
    RegistEffect( pEffectInstances, &p->pEffects );

    // 隣接ポリゴン登録
    RegistAdjacency( pAdjacency, pMeshData->pMesh->GetNumFaces(), &p->pAdjacency );

    // スキン登録
    RegistSkin( pSkinInfo, &p->pSkinInfo );

    *ppNewMeshContainer = p;

    return D3D_OK;
}


// フレームを削除
HRESULT GgafDx9AllocHierarchy::DestroyFrame(THIS_
   LPD3DXFRAME pFrameToFree)
{
    // このクラスではデストラクタで削除されるので
    // この関数は使わない
    return D3D_OK;
}


// コンテナを削除
HRESULT GgafDx9AllocHierarchy::DestroyMeshContainer(THIS_
   LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    // このクラスではデストラクタで削除されるので
    // この関数は使わない
    return D3D_OK;
}
