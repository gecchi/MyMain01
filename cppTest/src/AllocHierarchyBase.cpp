#include "AllocHierarchyBase.h"

// v1.01
// �E�X�L���o�^����AddRef���Ă΂�Ă��鎖�ɂ�郊�[�N�����P


CAllocHierarchyBase::CAllocHierarchyBase(void)
{
}


// �f�X�g���N�^
CAllocHierarchyBase::~CAllocHierarchyBase(void)
{
	// �o�^���ꂽ�I�u�W�F�N�g��S�č폜����
	list<void*>::iterator it = m_DelList.begin();
	for(; it!=m_DelList.end(); it++)
		delete[] (*it);

	list<IUnknown*>::iterator comit = m_ReleaseList.begin();
	for(; comit!=m_ReleaseList.end();comit++){
		if(*comit)
			(*comit)->Release();
	}
}


// �t���[���\���̂𐶐�
D3DXFRAME* CAllocHierarchyBase::CreateNewFrame()
{
	D3DXFRAME* tmp = new D3DXFRAME;
	ZeroMemory( tmp, sizeof(D3DXFRAME) );
	AddDelList( tmp );
	return tmp;
}


// ���b�V���R���e�i�\���̂𐶐�
D3DXMESHCONTAINER *CAllocHierarchyBase::CreateNewMeshContainer()
{
	D3DXMESHCONTAINER* tmp = new D3DXMESHCONTAINER;
	ZeroMemory( tmp, sizeof(D3DXMESHCONTAINER) );
	AddDelList( tmp );
	return tmp;
}


// �������X�g�ɓo�^
void CAllocHierarchyBase::AddDelList( void* ptr )
{
	m_DelList.push_back( ptr );
}

// �����[�X���X�g�ɓo�^
void CAllocHierarchyBase::AddReleaseList( IUnknown *comptr)
{
	comptr->AddRef();
	m_ReleaseList.push_back( comptr );
}


// ������R�s�[�֐�
LPSTR CAllocHierarchyBase::CopyStr(LPCSTR name)
{
	if(!name) return NULL;   // NULL�͕��������J�E���g�ł��Ȃ�
	LPSTR Str = new char[strlen(name)+1];
	//strcpy_s(Str, strlen(name)+1, name);
	strcpy(Str, name);
	AddDelList( Str );
	return Str;
}


// ���b�V���f�[�^�o�^
void CAllocHierarchyBase::RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
	pDest->Type = pSrc->Type;   // ���b�V���^�C�v
	pDest->pMesh = pSrc->pMesh;   // ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
	AddReleaseList( pDest->pMesh );  // Release���X�g�֓o�^
}


// �}�e���A���o�^
void CAllocHierarchyBase::RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
	// �}�e���A���z��̐���
	*ppDest = new D3DXMATERIAL[ num ];
	AddDelList( *ppDest );

	DWORD i;
	for(i=0; i<num; i++)
	{
		(*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // �}�e���A���o�^
		(*ppDest)[i].pTextureFilename = CopyStr( pSrc[i].pTextureFilename );  // �e�N�X�`�����o�^
	}
}


// �G�t�F�N�g�o�^
void CAllocHierarchyBase::RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
	*ppDest = new D3DXEFFECTINSTANCE;
	AddDelList( *ppDest );
	(*ppDest)->pEffectFilename = CopyStr(pSrc->pEffectFilename);     // �G�t�F�N�g��
	(*ppDest)->NumDefaults = pSrc->NumDefaults;                      // �G�t�F�N�g�f�t�H���g��
	(*ppDest)->pDefaults = new D3DXEFFECTDEFAULT[pSrc->NumDefaults];  // �G�t�F�N�g�f�t�H���g�z�񐶐�
	AddDelList( (*ppDest)->pDefaults );

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
		  AddDelList( pEDDest[i].pValue );
	   }
	}
}


// �אڃ|���S���o�^
void CAllocHierarchyBase::RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
	*Dest = new DWORD[ polynum * 3 ];   // �z�񐶐�
	memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));  // �R�s�[
	AddDelList( *Dest );
}


// �X�L���o�^
void CAllocHierarchyBase::RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest)
{
	if(!Src) return;   // �X�L����������Ή������Ȃ�
	*Dest = Src;               // �X�L�����R�s�[
//	(*Dest)->AddRef();         // �Q�ƃJ�E���^����
	AddReleaseList( *Dest );   // �����[�X���X�g�ɓo�^
}


// �t���[�������֐�
HRESULT CAllocHierarchyBase::CreateFrame(THIS_
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
HRESULT CAllocHierarchyBase::CreateMeshContainer(THIS_
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
HRESULT CAllocHierarchyBase::DestroyFrame(THIS_
   LPD3DXFRAME pFrameToFree)
{
	// ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
	// ���̊֐��͎g��Ȃ�
	return D3D_OK;
}


// �R���e�i���폜
HRESULT CAllocHierarchyBase::DestroyMeshContainer(THIS_
   LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	// ���̃N���X�ł̓f�X�g���N�^�ō폜�����̂�
	// ���̊֐��͎g��Ȃ�
	return D3D_OK;
}
