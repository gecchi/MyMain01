#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchy.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAllocHierarchy::GgafDxAllocHierarchy() {
}

// デストラクタ
GgafDxAllocHierarchy::~GgafDxAllocHierarchy() {
    // 登録されたオブジェクトを全て削除する
    std::list<DeleterBase*>::iterator it = m_DelList.begin();
    for (; it != m_DelList.end(); ++it) {
        DeleterBase* p = (*it);
        delete p;
    }

    std::list<IUnknown*>::iterator comit = m_ReleaseList.begin();
    for (; comit != m_ReleaseList.end(); ++comit) {
        if (*comit) {
            (*comit)->Release();
        }
    }
}

// フレーム構造体を生成
D3DXFRAME* GgafDxAllocHierarchy::createNewFrame() {
    D3DXFRAME * tmp = NEW D3DXFRAME;
    ZeroMemory(tmp, sizeof(D3DXFRAME));
    addDelList( NEW Deleter<D3DXFRAME>(tmp) );
    return tmp;
}

// メッシュコンテナ構造体を生成
D3DXMESHCONTAINER *GgafDxAllocHierarchy::createNewMeshContainer() {
    D3DXMESHCONTAINER * tmp = NEW D3DXMESHCONTAINER;
    ZeroMemory(tmp, sizeof(D3DXMESHCONTAINER));
    addDelList( NEW Deleter<D3DXMESHCONTAINER>(tmp) );
    return tmp;
}

// 消去リストに登録
void GgafDxAllocHierarchy::addDelList(DeleterBase* ptr, bool isAry) {
    m_DelList.push_back(ptr);
}

// リリースリストに登録
void GgafDxAllocHierarchy::addReleaseList(IUnknown *comptr) {
    comptr->AddRef();
    m_ReleaseList.push_back(comptr);
}

// 文字列コピー関数
LPSTR GgafDxAllocHierarchy::copyStr(LPCSTR name) {
    if (!name)
        return nullptr;   // nullptrは文字数をカウントできない
    LPSTR
    Str = NEW
    char[strlen(name)+1];
    Str = strcpy(Str, name);
    addDelList( NEW Deleter<char>( Str, true ) );
    return Str;
}

// メッシュデータ登録
void GgafDxAllocHierarchy::registerMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
    pDest->Type = pSrc->Type;   // メッシュタイプ
    pDest->pMesh = pSrc->pMesh;// メッシュ（unionなのでどれでも一緒）
    addReleaseList( pDest->pMesh );// Releaseリストへ登録
}

// マテリアル登録
void GgafDxAllocHierarchy::registerMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
    // マテリアル配列の生成
    *ppDest = NEW D3DXMATERIAL[ num ];
    addDelList( NEW Deleter<D3DXMATERIAL>( *ppDest, true ) );

    DWORD i;
    for(i=0; i<num; i++) {
        (*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // マテリアル登録
        (*ppDest)[i].pTextureFilename = copyStr( pSrc[i].pTextureFilename );// テクスチャ名登録
    }
}

// エフェクト登録
void GgafDxAllocHierarchy::registerEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
    *ppDest = NEW D3DXEFFECTINSTANCE;
    addDelList( NEW Deleter<D3DXEFFECTINSTANCE>(*ppDest) );
    (*ppDest)->pEffectFilename = copyStr(pSrc->pEffectFilename);     // エフェクト名
    (*ppDest)->NumDefaults = pSrc->NumDefaults;// エフェクトデフォルト数
    (*ppDest)->pDefaults = NEW D3DXEFFECTDEFAULT[pSrc->NumDefaults];// エフェクトデフォルト配列生成
    addDelList( NEW Deleter<D3DXEFFECTDEFAULT>( (*ppDest)->pDefaults, true ) );

    // エフェクトデフォルトの登録
    D3DXEFFECTDEFAULT *pEDSrc = pSrc->pDefaults;// コピー元
    D3DXEFFECTDEFAULT *pEDDest = (*ppDest)->pDefaults;// コピー先
    unsigned int i=0;
    for(i = 0; i < pSrc->NumDefaults; i++) {
        pEDDest[i].pParamName = copyStr(pEDSrc[i].pParamName);              // パラメータ名
        DWORD NumBytes = pEDDest[i].NumBytes = pEDSrc[i].NumBytes;// パラメータサイズ
        pEDDest[i].Type = pEDSrc[i].Type;// パラメータタイプ
        if(pEDSrc[i].Type <= D3DXEDT_DWORD) {
            pEDDest[i].pValue = (void*)( NEW BYTE[ NumBytes ] );              // パラメータ配列生成
            memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
            addDelList( NEW Deleter<BYTE>( (BYTE*)(pEDDest[i].pValue), true ) );
        }
    }
}

// 隣接ポリゴン登録
void GgafDxAllocHierarchy::registerAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
    *Dest = NEW DWORD[ polynum * 3 ];   // 配列生成
    memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));// コピー
    addDelList( NEW Deleter<DWORD>( *Dest, true ) );
}

// スキン登録
void GgafDxAllocHierarchy::registerSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest) {
    if(!Src) return;   // スキンが無ければ何もしない
    *Dest = Src;// スキンをコピー
    addReleaseList( *Dest );// リリースリストに登録
}

// フレーム生成関数
HRESULT GgafDxAllocHierarchy::CreateFrame(THIS_
        LPCSTR Name,
        LPD3DXFRAME *ppNewFrame) {
    // フレームを新しく生成
    D3DXFRAME *pFrame = createNewFrame();
    pFrame->Name = copyStr( Name );
    *ppNewFrame = pFrame;

    return D3D_OK;
}

// メッシュコンテナ生成関数
HRESULT GgafDxAllocHierarchy::CreateMeshContainer(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer) {
    // メッシュコンテナオブジェクトの生成
    D3DXMESHCONTAINER *p = createNewMeshContainer();

    // 名前登録
    p->Name = copyStr( Name );

    // メッシュデータ登録
    registerMeshData( pMeshData, &p->MeshData );

    // マテリアル登録
    p->NumMaterials = NumMaterials;
    registerMaterial( pMaterials, NumMaterials, &p->pMaterials);

    // エフェクト登録
    registerEffect( pEffectInstances, &p->pEffects );

    // 隣接ポリゴン登録
    registerAdjacency( pAdjacency, pMeshData->pMesh->GetNumFaces(), &p->pAdjacency );

    // スキン登録
    registerSkin( pSkinInfo, &p->pSkinInfo );

    *ppNewMeshContainer = p;

    return D3D_OK;
}

// フレームを削除
HRESULT GgafDxAllocHierarchy::DestroyFrame(THIS_
        LPD3DXFRAME pFrameToFree) {
    // このクラスではデストラクタで削除されるので
    // この関数は使わない
    return D3D_OK;
}

// コンテナを削除
HRESULT GgafDxAllocHierarchy::DestroyMeshContainer(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree) {
    // このクラスではデストラクタで削除されるので
    // この関数は使わない
    return D3D_OK;
}
