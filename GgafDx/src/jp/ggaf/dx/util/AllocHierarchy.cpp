#include "jp/ggaf/dx/util/AllocHierarchy.h"


using namespace GgafDx;

AllocHierarchy::AllocHierarchy() : ID3DXAllocateHierarchy()  {
}

// �f�X�g���N�^
AllocHierarchy::~AllocHierarchy() {
    // �o�^���ꂽ�I�u�W�F�N�g��S�č폜����
//    std::list<DeleterBase*>::iterator it = m_DelList.begin();
//    for (; it != m_DelList.end(); ++it) {
//        DeleterBase* p = (*it);
//        delete p;
//    }
//
//    std::list<IUnknown*>::iterator comit = m_ReleaseList.begin();
//    for (; comit != m_ReleaseList.end(); ++comit) {
//        if (*comit) {
//            (*comit)->Release();
//        }
//    }
}

// �t���[���\���̂𐶐�
D3DXFRAME* AllocHierarchy::createNewFrame() {
    D3DXFRAME * tmp = NEW D3DXFRAME;
    ZeroMemory(tmp, sizeof(D3DXFRAME));
//    addDelList( NEW Deleter<D3DXFRAME>(tmp) );
    return tmp;
}

// ���b�V���R���e�i�\���̂𐶐�
D3DXMESHCONTAINER *AllocHierarchy::createNewMeshContainer() {
    D3DXMESHCONTAINER * tmp = NEW D3DXMESHCONTAINER;
    ZeroMemory(tmp, sizeof(D3DXMESHCONTAINER));
//    addDelList( NEW Deleter<D3DXMESHCONTAINER>(tmp) );
    return tmp;
}

// �������X�g�ɓo�^
//void AllocHierarchy::addDelList(DeleterBase* ptr, bool isAry) {
//    m_DelList.push_back(ptr);
//}

//// �����[�X���X�g�ɓo�^
//void AllocHierarchy::addReleaseList(IUnknown *comptr) {
//    comptr->AddRef();
//    m_ReleaseList.push_back(comptr);
//}

// ������R�s�[�֐�
LPSTR AllocHierarchy::copyStr(LPCSTR name) {
    if (!name) {
        return nullptr;   // nullptr�͕��������J�E���g�ł��Ȃ�
    }
    LPSTR Str = NEW char[strlen(name)+1];
    Str = strcpy(Str, name);
//    addDelList( NEW Deleter<char>( Str, true ) );
    return Str;
}

//// ���b�V���f�[�^�o�^
//void AllocHierarchy::registerMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
//{
//    pDest->Type = pSrc->Type;   // ���b�V���^�C�v
//    pDest->pMesh = pSrc->pMesh;// ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
////    addReleaseList( pDest->pMesh );// Release���X�g�֓o�^
//    (pDest->pMesh)->AddRef(); //COM�I�u�W�F�N�g�𕡐������̂ŎQ�Ƃ��{�P
//}

// �}�e���A���o�^
void AllocHierarchy::registerMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
    // �}�e���A���z��̐���
    *ppDest = NEW D3DXMATERIAL[ num ];
//    addDelList( NEW Deleter<D3DXMATERIAL>( *ppDest, true ) );

    for (DWORD i = 0; i < num; i++) {
        (*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // �}�e���A���o�^
        (*ppDest)[i].pTextureFilename = copyStr( pSrc[i].pTextureFilename );// �e�N�X�`�����o�^
    }
}

// �G�t�F�N�g�o�^
void AllocHierarchy::registerEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
    *ppDest = NEW D3DXEFFECTINSTANCE;
//    addDelList( NEW Deleter<D3DXEFFECTINSTANCE>(*ppDest) );
    (*ppDest)->pEffectFilename = copyStr(pSrc->pEffectFilename);     // �G�t�F�N�g��
    (*ppDest)->NumDefaults = pSrc->NumDefaults;// �G�t�F�N�g�f�t�H���g��
    (*ppDest)->pDefaults = NEW D3DXEFFECTDEFAULT[pSrc->NumDefaults];// �G�t�F�N�g�f�t�H���g�z�񐶐�
//    addDelList( NEW Deleter<D3DXEFFECTDEFAULT>( (*ppDest)->pDefaults, true ) );

    // �G�t�F�N�g�f�t�H���g�̓o�^
    D3DXEFFECTDEFAULT *pEDSrc = pSrc->pDefaults;// �R�s�[��
    D3DXEFFECTDEFAULT *pEDDest = (*ppDest)->pDefaults;// �R�s�[��
    unsigned int i=0;
    for (i = 0; i < pSrc->NumDefaults; i++) {
        pEDDest[i].pParamName = copyStr(pEDSrc[i].pParamName);              // �p�����[�^��
        DWORD NumBytes = pEDDest[i].NumBytes = pEDSrc[i].NumBytes;// �p�����[�^�T�C�Y
        pEDDest[i].Type = pEDSrc[i].Type;// �p�����[�^�^�C�v
        if(pEDSrc[i].Type <= D3DXEDT_DWORD) {
            pEDDest[i].pValue = (void*)( NEW BYTE[ NumBytes ] );              // �p�����[�^�z�񐶐�
            memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
//            addDelList( NEW Deleter<BYTE>( (BYTE*)(pEDDest[i].pValue), true ) );
        }
    }
}

//// �אڃ|���S���o�^
//void AllocHierarchy::registerAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
//{
//    *Dest = NEW DWORD[ polynum * 3 ];   // �z�񐶐�
//    memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));// �R�s�[
////    addDelList( NEW Deleter<DWORD>( *Dest, true ) );
//}
//
//// �X�L���o�^
//void AllocHierarchy::registerSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest) {
//    if(!Src) return;   // �X�L����������Ή������Ȃ�
//    *Dest = Src;// �X�L�����R�s�[
////    addReleaseList( *Dest );// �����[�X���X�g�ɓo�^
//    (*Dest)->AddRef();
//}

// �t���[�������֐�
HRESULT AllocHierarchy::CreateFrame(THIS_
        LPCSTR Name,
        LPD3DXFRAME *ppNewFrame) {
    // �t���[����V��������
    D3DXFRAME *pFrame = createNewFrame();
    pFrame->Name = copyStr( Name );
    *ppNewFrame = pFrame;

    return D3D_OK;
}

// ���b�V���R���e�i�����֐�
HRESULT AllocHierarchy::CreateMeshContainer(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer) {
    // ���b�V���R���e�i�I�u�W�F�N�g�̐���
    D3DXMESHCONTAINER *p = createNewMeshContainer();

    // ���O�o�^
    p->Name = copyStr( Name );

    // ���b�V���f�[�^�o�^
    p->MeshData.Type = pMeshData->Type;   // ���b�V���^�C�v
    p->MeshData.pMesh = pMeshData->pMesh;// ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
    p->MeshData.pMesh->AddRef(); //COM�I�u�W�F�N�g�𕡐������̂ŎQ�Ƃ��{�P

    // �אڃ|���S���o�^
    DWORD polynum = pMeshData->pMesh->GetNumFaces();
    p->pAdjacency = NEW DWORD[ polynum * 3 ];   // �z�񐶐�
    memcpy( p->pAdjacency, pAdjacency, polynum * 3 * sizeof(DWORD));// �R�s�[

    // �X�L���o�^
    if (pSkinInfo) {
        p->pSkinInfo = pSkinInfo;// �X�L�����R�s�[
        p->pSkinInfo->AddRef();
    }

    // �}�e���A���o�^
    p->NumMaterials = NumMaterials;
    registerMaterial( pMaterials, NumMaterials, &p->pMaterials);
    // �G�t�F�N�g�o�^
    registerEffect( pEffectInstances, &p->pEffects );

    *ppNewMeshContainer = p;

    return D3D_OK;
}

// �t���[�����폜
HRESULT AllocHierarchy::DestroyFrame(THIS_
        LPD3DXFRAME pFrameToFree) {
    if(pFrameToFree->Name) {
        delete[] pFrameToFree->Name;
    }
    if(pFrameToFree->pMeshContainer) {
        DestroyMeshContainer(pFrameToFree->pMeshContainer);
    }
    if(pFrameToFree->pFrameSibling) {
        DestroyFrame(pFrameToFree->pFrameSibling);
    }
    if(pFrameToFree->pFrameFirstChild) {
        DestroyFrame(pFrameToFree->pFrameFirstChild);
    }
    delete pFrameToFree;
    return D3D_OK;
}

// �R���e�i���폜
HRESULT AllocHierarchy::DestroyMeshContainer(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree) {
    D3DXMESHCONTAINER *p = pMeshContainerToFree;   // �����̂�
    delete[] p->Name;
    ID3DXMesh* pMesh = p->MeshData.pMesh;
    GGAF_RELEASE_NULLABLE(pMesh);

    for(unsigned int i=0; i < p->NumMaterials; i++){
        delete[] p->pMaterials[i].pTextureFilename;
    }
    delete[] p->pMaterials;

    // �G�t�F�N�g
    for(int i = 0; i < (int)(p->pEffects->NumDefaults); i++) {
        delete[] p->pEffects->pDefaults[i].pParamName;
        BYTE* paByte = (BYTE*)(p->pEffects->pDefaults[i].pValue);
        delete[] paByte;
    }
    delete[] p->pEffects->pEffectFilename;
    delete[] p->pEffects->pDefaults;
    delete p->pEffects;

    delete[] p->pAdjacency;
    LPD3DXSKININFO pSkinInfo = p->pSkinInfo;
    GGAF_RELEASE_NULLABLE(pSkinInfo);
    delete p;
    return D3D_OK;
}
