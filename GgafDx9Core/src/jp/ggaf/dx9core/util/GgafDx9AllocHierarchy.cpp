#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;





//--------------------------------------------------------------------------------------
//�K�w���蓖�āF�t���[���쐬
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
    HRESULT hr = S_OK;
    D3DXFRAME_DERIVED *pFrame;//�t���[��

    *ppNewFrame = NULL;

    pFrame = new D3DXFRAME_DERIVED;
    if (pFrame == NULL)//�t���[�����쐬�ł��Ȃ�������
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }

    hr = AllocateName(Name, &pFrame->Name);//���蓖�Ė���ݒ�
    if (FAILED(hr)) goto e_Exit;

    //�t���[���̕��i��������
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
//���b�V���R���e�i�쐬
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(
        LPCSTR Name,//���O
        CONST D3DXMESHDATA *pMeshData,//���b�V���f�[�^
        CONST D3DXMATERIAL *pMaterials,//�}�e���A��
        CONST D3DXEFFECTINSTANCE *pEffectInstances,//�G�t�F�N�g�̎���
        DWORD NumMaterials,//�}�e���A����
        CONST DWORD *pAdjacency,//�אڊ֌W
        LPD3DXSKININFO pSkinInfo,//�X�L�����
        LPD3DXMESHCONTAINER *ppNewMeshContainer)//���b�V���R���e�i�̃|�C���^
{
    HRESULT hr;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
    UINT NumFaces;//�ʂ̐�
    UINT iMaterial;//�}�e���A���̐�
    UINT iBone, cBones;//�{�[���̐�
    LPDIRECT3DDEVICE9 pd3dDevice = NULL;

    LPD3DXMESH pMesh = NULL;

    *ppNewMeshContainer = NULL;

    //�p�b�`���b�V���͈����Ȃ��̂Ō���������I��
    if (pMeshData->Type != D3DXMESHTYPE_MESH)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    // ���b�V���|�C���^�����b�V���f�[�^�\���̂��瓾��
    pMesh = pMeshData->pMesh;

    //FVF�R���p�`�u�����b�V���͈����Ȃ��̂Ō���������I��
    if (pMesh->GetFVF() == 0)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    //D3DXMESHCONTAINER�Ƃ��ă��^�[�����邽�߂ɃI�[�o�[���[�h��Ԃ̍\���̂�ݒ肷��
    pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
    if (pMeshContainer == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }
    memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

    //���O��ݒ肷��
    hr = AllocateName(Name, &pMeshContainer->Name);
    if (FAILED(hr))
    goto e_Exit;

    pMesh->GetDevice(&pd3dDevice);
    NumFaces = pMesh->GetNumFaces();

    //�@�������b�V���ɂȂ��Ȃ�A�@����ݒ肷��
    if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
    {
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        //���b�V���̃N���[��������Ė@���̏ꏊ���󂯂�
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(),
                pMesh->GetFVF() | D3DFVF_NORMAL,
                pd3dDevice, &pMeshContainer->MeshData.pMesh );
        if (FAILED(hr))
        goto e_Exit;

        //�g�p���郁�b�V���R���e�i���烁�b�V���|�C���^�����߂�
        //���ӁF����̎Q�Ƃ��܂��Ȃ��̂ŉ���͂��Ȃ�
        pMesh = pMeshContainer->MeshData.pMesh;

        //���b�V���|�C���^�ɖ@�������
        D3DXComputeNormals( pMesh, NULL );
    }
    else //�@����������΁A�������b�V���Ƀ��b�V���R���e�i�̎Q�Ƃ��Z�b�g����
    {
        pMeshContainer->MeshData.pMesh = pMesh;
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        pMesh->AddRef();
    }

    //�����������蓖�ă}�e���A������ݒ肷��
    //�V�F�[�_�[�̑����D3D9�̃}�e���A���ƃe�N�X�`��
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

    //�}�e���A�����ݒ肳�ꂽ�炻����R�s�[����
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

                //�|�C���^���_�C�i�~�b�N�������Ɋm�ۂ��Ȃ����A�e�N�X�`������NULL�ɂ���
                pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
            }
        }
    }
    else //�����A�}�e���A��������������f�t�H���g�̍ގ���
    {
        pMeshContainer->pMaterials[0].pTextureFilename = NULL;
        memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
    }

    //�X�L����񂪂���΁A�n�[�h�E�F�A�X�L�j���O�̂��߂ɂ�����g��
    if (pSkinInfo != NULL)
    {
        //�܂��ŏ��Ƀf�[�^�̓X�L�����ƃ��b�V���ɕۑ������
        pMeshContainer->pSkinInfo = pSkinInfo;
        pSkinInfo->AddRef();

        pMeshContainer->pOrigMesh = pMesh;
        pMesh->AddRef();

        //�t�B�M���A�X�y�[�X����{�[���X�y�[�X�ւ̒��_���ڂ����߂ɃI�t�Z�b�g�}�g���N�X�̔z�񂪕K�v
        cBones = pSkinInfo->GetNumBones();
        pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
        if (pMeshContainer->pBoneOffsetMatrices == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto e_Exit;
        }

        //�����Ń{�[���}�g���N�X�𓾂Č�Ŏ擾����K�v�𖳂�����
        for (iBone = 0; iBone < cBones; iBone++)
        {
            pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
        }

        //GenerateSkinnedMesh�̓n�[�h�E�F�A�X�L�j���O�ɍœK�ȃo�[�W�����ɕς���
        hr = GenerateSkinnedMesh( pd3dDevice, pMeshContainer );
        if (FAILED(hr))
        goto e_Exit;
    }

    *ppNewMeshContainer = pMeshContainer;
    pMeshContainer = NULL;

    e_Exit:
    SAFE_RELEASE(pd3dDevice);

    //�K���Ɋ��蓖�Ă�ꂽ�f�[�^�����ꂢ�ɂ���
    if (pMeshContainer != NULL)
    {
        DestroyMeshContainer(pMeshContainer);
    }

    return hr;
}

//--------------------------------------------------------------------------------------
//�t���[���폜
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree) {
    SAFE_DELETE_ARRAY(pFrameToFree->Name);
    SAFE_DELETE(pFrameToFree);
    return S_OK;
}

//--------------------------------------------------------------------------------------
//���b�V���R���e�i�폜
//--------------------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase) {
    UINT iMaterial;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*) pMeshContainerBase;

    SAFE_DELETE_ARRAY(pMeshContainer->Name);
    SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
    SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
    SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);

    //���蓖�Ă�ꂽ�S�Ẵe�N�X�`�����������
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


// �f�X�g���N�^
GgafDx9AllocHierarchy::~GgafDx9AllocHierarchy(void)
{
    // �o�^���ꂽ�I�u�W�F�N�g��S�č폜����
    list<deleterBase*>::iterator it = m_DelList.begin();
    for(; it!=m_DelList.end(); it++)
        delete[] (*it);

    list<IUnknown*>::iterator comit = m_ReleaseList.begin();
    for(; comit!=m_ReleaseList.end();comit++){
        if(*comit)
            (*comit)->Release();
    }
}


// �t���[���\���̂𐶐�
D3DXFRAME* GgafDx9AllocHierarchy::CreateNewFrame()
{
    D3DXFRAME* tmp = new D3DXFRAME;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    AddDelList( new deleter<D3DXFRAME>(tmp) );
    return tmp;
}


// ���b�V���R���e�i�\���̂𐶐�
D3DXMESHCONTAINER *GgafDx9AllocHierarchy::CreateNewMeshContainer()
{
    D3DXMESHCONTAINER* tmp = new D3DXMESHCONTAINER;
    ZeroMemory( tmp, sizeof(D3DXMESHCONTAINER) );
    AddDelList( new deleter<D3DXMESHCONTAINER>(tmp) );
    return tmp;
}


// �������X�g�ɓo�^
void GgafDx9AllocHierarchy::AddDelList( deleterBase* ptr, bool isAry )
{
    m_DelList.push_back( ptr );
}

// �����[�X���X�g�ɓo�^
void GgafDx9AllocHierarchy::AddReleaseList( IUnknown *comptr)
{
    comptr->AddRef();
    m_ReleaseList.push_back( comptr );
}


// ������R�s�[�֐�
LPSTR GgafDx9AllocHierarchy::CopyStr(LPCSTR name)
{
    if(!name) return NULL;   // NULL�͕��������J�E���g�ł��Ȃ�
    LPSTR Str = new char[strlen(name)+1];
    Str = strcpy(Str, name);
    AddDelList( new deleter<char>( Str, true ) );
    return Str;
}


// ���b�V���f�[�^�o�^
void GgafDx9AllocHierarchy::RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
    pDest->Type = pSrc->Type;   // ���b�V���^�C�v
    pDest->pMesh = pSrc->pMesh;   // ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
    AddReleaseList( pDest->pMesh );  // Release���X�g�֓o�^
}


// �}�e���A���o�^
void GgafDx9AllocHierarchy::RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
    // �}�e���A���z��̐���
    *ppDest = new D3DXMATERIAL[ num ];
    AddDelList( new deleter<D3DXMATERIAL>( *ppDest, true ) );

    DWORD i;
    for(i=0; i<num; i++)
    {
        (*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // �}�e���A���o�^
        (*ppDest)[i].pTextureFilename = CopyStr( pSrc[i].pTextureFilename );  // �e�N�X�`�����o�^
    }
}


// �G�t�F�N�g�o�^
void GgafDx9AllocHierarchy::RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
    *ppDest = new D3DXEFFECTINSTANCE;
    AddDelList( new deleter<D3DXEFFECTINSTANCE>(*ppDest) );
    (*ppDest)->pEffectFilename = CopyStr(pSrc->pEffectFilename);     // �G�t�F�N�g��
    (*ppDest)->NumDefaults = pSrc->NumDefaults;                      // �G�t�F�N�g�f�t�H���g��
    (*ppDest)->pDefaults = new D3DXEFFECTDEFAULT[pSrc->NumDefaults];  // �G�t�F�N�g�f�t�H���g�z�񐶐�
    AddDelList( new deleter<D3DXEFFECTDEFAULT>( (*ppDest)->pDefaults, true ) );

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
          pEDDest[i].pValue = (void*)( new BYTE[ NumBytes ] );              // �p�����[�^�z�񐶐�
          memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
          AddDelList( new deleter<void>( pEDDest[i].pValue, true ) );
       }
    }
}


// �אڃ|���S���o�^
void GgafDx9AllocHierarchy::RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
    *Dest = new DWORD[ polynum * 3 ];   // �z�񐶐�
    memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));  // �R�s�[
    AddDelList( new deleter<DWORD>( *Dest, true ) );
}


// �X�L���o�^
void GgafDx9AllocHierarchy::RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest)
{
    if(!Src) return;   // �X�L����������Ή������Ȃ�
    *Dest = Src;               // �X�L�����R�s�[
//	(*Dest)->AddRef();         // �Q�ƃJ�E���^����
    AddReleaseList( *Dest );   // �����[�X���X�g�ɓo�^
}


// �t���[�������֐�
HRESULT GgafDx9AllocHierarchy::CreateFrame(THIS_
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
HRESULT GgafDx9AllocHierarchy::DestroyFrame(THIS_
   LPD3DXFRAME pFrameToFree)
{
    // ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
    // ���̊֐��͎g��Ȃ�
    return D3D_OK;
}


// �R���e�i���폜
HRESULT GgafDx9AllocHierarchy::DestroyMeshContainer(THIS_
   LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    // ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
    // ���̊֐��͎g��Ȃ�
    return D3D_OK;
}
