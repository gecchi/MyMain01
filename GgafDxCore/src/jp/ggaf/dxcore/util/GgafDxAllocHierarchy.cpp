#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;



GgafDxAllocHierarchy::GgafDxAllocHierarchy(void)
{
}


// �f�X�g���N�^
GgafDxAllocHierarchy::~GgafDxAllocHierarchy(void)
{
    // �o�^���ꂽ�I�u�W�F�N�g��S�č폜����
    list<deleterBase*>::iterator it = m_DelList.begin();
    for(; it!=m_DelList.end(); it++) {
        deleterBase* p = (*it);
        delete p;
    }

    list<IUnknown*>::iterator comit = m_ReleaseList.begin();
    for(; comit!=m_ReleaseList.end();comit++){
        if(*comit)
            (*comit)->Release();
    }
}


// �t���[���\���̂𐶐�
D3DXFRAME* GgafDxAllocHierarchy::CreateNewFrame()
{
    D3DXFRAME* tmp = NEW D3DXFRAME;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    AddDelList( NEW deleter<D3DXFRAME>(tmp) );
    return tmp;
}


// ���b�V���R���e�i�\���̂𐶐�
D3DXMESHCONTAINER *GgafDxAllocHierarchy::CreateNewMeshContainer()
{
    D3DXMESHCONTAINER* tmp = NEW D3DXMESHCONTAINER;
    ZeroMemory( tmp, sizeof(D3DXMESHCONTAINER) );
    AddDelList( NEW deleter<D3DXMESHCONTAINER>(tmp) );
    return tmp;
}


// �������X�g�ɓo�^
void GgafDxAllocHierarchy::AddDelList( deleterBase* ptr, bool isAry )
{
    m_DelList.push_back( ptr );
}

// �����[�X���X�g�ɓo�^
void GgafDxAllocHierarchy::AddReleaseList( IUnknown *comptr)
{
    comptr->AddRef();
    m_ReleaseList.push_back( comptr );
}


// ������R�s�[�֐�
LPSTR GgafDxAllocHierarchy::CopyStr(LPCSTR name)
{
    if(!name) return NULL;   // NULL�͕��������J�E���g�ł��Ȃ�
    LPSTR Str = NEW char[strlen(name)+1];
    Str = strcpy(Str, name);
    AddDelList( NEW deleter<char>( Str, true ) );
    return Str;
}


// ���b�V���f�[�^�o�^
void GgafDxAllocHierarchy::RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
    pDest->Type = pSrc->Type;   // ���b�V���^�C�v
    pDest->pMesh = pSrc->pMesh;   // ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
    AddReleaseList( pDest->pMesh );  // Release���X�g�֓o�^
}


// �}�e���A���o�^
void GgafDxAllocHierarchy::RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
    // �}�e���A���z��̐���
    *ppDest = NEW D3DXMATERIAL[ num ];
    AddDelList( NEW deleter<D3DXMATERIAL>( *ppDest, true ) );

    DWORD i;
    for(i=0; i<num; i++)
    {
        (*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // �}�e���A���o�^
        (*ppDest)[i].pTextureFilename = CopyStr( pSrc[i].pTextureFilename );  // �e�N�X�`�����o�^
    }
}


// �G�t�F�N�g�o�^
void GgafDxAllocHierarchy::RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
    *ppDest = NEW D3DXEFFECTINSTANCE;
    AddDelList( NEW deleter<D3DXEFFECTINSTANCE>(*ppDest) );
    (*ppDest)->pEffectFilename = CopyStr(pSrc->pEffectFilename);     // �G�t�F�N�g��
    (*ppDest)->NumDefaults = pSrc->NumDefaults;                      // �G�t�F�N�g�f�t�H���g��
    (*ppDest)->pDefaults = NEW D3DXEFFECTDEFAULT[pSrc->NumDefaults];  // �G�t�F�N�g�f�t�H���g�z�񐶐�
    AddDelList( NEW deleter<D3DXEFFECTDEFAULT>( (*ppDest)->pDefaults, true ) );

    // �G�t�F�N�g�f�t�H���g�̓o�^
    D3DXEFFECTDEFAULT *pEDSrc  = pSrc->pDefaults;   // �R�s�[��
    D3DXEFFECTDEFAULT *pEDDest = (*ppDest)->pDefaults; // �R�s�[��
    unsigned int i=0;
    for(i=0; i<pSrc->NumDefaults; i++)
    {
       pEDDest[i].pParamName = CopyStr(pEDSrc[i].pParamName);				// �p�����[�^��
       DWORD NumBytes		 = pEDDest[i].NumBytes = pEDSrc[i].NumBytes;	// �p�����[�^�T�C�Y
       pEDDest[i].Type		 = pEDSrc[i].Type;								// �p�����[�^�^�C�v
       if(pEDSrc[i].Type <= D3DXEDT_DWORD){
          pEDDest[i].pValue = (void*)( NEW BYTE[ NumBytes ] );              // �p�����[�^�z�񐶐�
          memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
          AddDelList( NEW deleter<BYTE>( (BYTE*)(pEDDest[i].pValue), true ) );
       }
    }
}


// �אڃ|���S���o�^
void GgafDxAllocHierarchy::RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
    *Dest = NEW DWORD[ polynum * 3 ];   // �z�񐶐�
    memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));  // �R�s�[
    AddDelList( NEW deleter<DWORD>( *Dest, true ) );
}


// �X�L���o�^
void GgafDxAllocHierarchy::RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest)
{
    if(!Src) return;   // �X�L����������Ή������Ȃ�
    *Dest = Src;               // �X�L�����R�s�[
//	(*Dest)->AddRef();         // �Q�ƃJ�E���^����
    AddReleaseList( *Dest );   // �����[�X���X�g�ɓo�^
}


// �t���[�������֐�
HRESULT GgafDxAllocHierarchy::CreateFrame(THIS_
   LPCSTR Name,
   LPD3DXFRAME *ppNewFrame)
{
    // �t���[����V��������
    D3DXFRAME *pFrame = CreateNewFrame();
    pFrame->Name = CopyStr( Name );
    *ppNewFrame = pFrame;

    return D3D_OK;
}


// ���b�V���R���e�i�����֐�
HRESULT GgafDxAllocHierarchy::CreateMeshContainer(THIS_
   LPCSTR Name,
   CONST D3DXMESHDATA *pMeshData,
   CONST D3DXMATERIAL *pMaterials,
   CONST D3DXEFFECTINSTANCE *pEffectInstances,
   DWORD NumMaterials,
   CONST DWORD *pAdjacency,
   LPD3DXSKININFO pSkinInfo,
   LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
    // ���b�V���R���e�i�I�u�W�F�N�g�̐���
    D3DXMESHCONTAINER *p = CreateNewMeshContainer();

    // ���O�o�^
    p->Name = CopyStr( Name );

    // ���b�V���f�[�^�o�^
    RegistMeshData( pMeshData, &p->MeshData );

    // �}�e���A���o�^
    p->NumMaterials = NumMaterials;
    RegistMaterial( pMaterials, NumMaterials, &p->pMaterials);

    // �G�t�F�N�g�o�^
    RegistEffect( pEffectInstances, &p->pEffects );

    // �אڃ|���S���o�^
    RegistAdjacency( pAdjacency, pMeshData->pMesh->GetNumFaces(), &p->pAdjacency );

    // �X�L���o�^
    RegistSkin( pSkinInfo, &p->pSkinInfo );

    *ppNewMeshContainer = p;

    return D3D_OK;
}


// �t���[�����폜
HRESULT GgafDxAllocHierarchy::DestroyFrame(THIS_
   LPD3DXFRAME pFrameToFree)
{
    // ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
    // ���̊֐��͎g��Ȃ�
    return D3D_OK;
}


// �R���e�i���폜
HRESULT GgafDxAllocHierarchy::DestroyMeshContainer(THIS_
   LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    // ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
    // ���̊֐��͎g��Ȃ�
    return D3D_OK;
}
