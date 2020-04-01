#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"

#include "jp/ggaf/dx/util/SkinAniMeshContainer.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"
#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

SkinAniMeshAllocHierarchy::SkinAniMeshAllocHierarchy() : BoneAniMeshAllocHierarchy() {
}

SkinAniMeshAllocHierarchy::~SkinAniMeshAllocHierarchy() {
}

// ���b�V���R���e�i�����֐�
HRESULT SkinAniMeshAllocHierarchy::CreateMeshContainer(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer) {
    // ���b�V���R���e�i�I�u�W�F�N�g�̐���
    SkinAniMeshContainer* pNewMC = (SkinAniMeshContainer*)createNewMeshContainer();
    HRESULT hr;

    // ���O�o�^
    pNewMC->Name = copyStr( Name );
    // �אڃ|���S�����i�[�̂��߂̃o�b�t�@�m��
    DWORD polynum = pMeshData->pMesh->GetNumFaces();
    pNewMC->pAdjacency = NEW DWORD[ polynum * 3 ];   // �z�񐶐�
    memset(pNewMC->pAdjacency, 0, polynum * 3 * sizeof(DWORD)); // �R�s�[

    // �X�L���o�^
    if(pSkinInfo) {
        pNewMC->pSkinInfo = pSkinInfo;// �X�L�����R�s�[
        pNewMC->pSkinInfo->AddRef();
        DWORD bone_num = pSkinInfo->GetNumBones();
        // �`�撸�_�Ɋ֌W����{�[���̐� �� �{�[���I�t�Z�b�g�s��̐�
        pNewMC->_dwBoneOffsetMatrixNum = bone_num;
        _TRACE_("pSkinInfo->GetNumBones() = "<<bone_num);
        pNewMC->_paBoneOffsetMatrix = new D3DXMATRIX[bone_num];
        for (DWORD i =  0; i < bone_num; i++) {
            // �I�t�Z�b�g�s����R�s�[����
            memcpy(&pNewMC->_paBoneOffsetMatrix[i], pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DXMATRIX));
        }
        _TRACE_("�{�[���I�t�Z�b�g�s����R�s�[���܂���");

        // ���b�V���f�[�^�o�^
        pNewMC->MeshData.Type = pMeshData->Type;   // ���b�V���^�C�v
        //���b�V���f�[�^���œK������
        //�E���_�A�`��ʂ���בւ��čœK��
        //�E�{�[���̉e����������͈͂��ƂɁA���b�V�����T�u�Z�b�g�ɕ���
        //�E���_���Ƀu�����h���d�l��t�^
        //�E�{�[���ɍ��킹�Ē��_���ړ�
//        DWORD Options = D3DXMESH_SYSTEMMEM|D3DXMESHOPT_VERTEXCACHE;
        LPD3DXBUFFER pVertexRemap;
        hr = pNewMC->pSkinInfo->ConvertToBlendedMesh(
          pMeshData->pMesh,                  //[in] LPD3DXMESH pMesh, ���̓��b�V��
          NULL,                              //[in] DWORD Options,          ���g�p�H
          pAdjacency,                        //[in] CONST LPDWORD pAdjacencyIn, ���̓��b�V���אږʏ��i�z��H�j
          pNewMC->pAdjacency,                //[out]LPDWORD pAdjacencyOut,     �o�̓��b�V���אږʏ��
          NULL,                 //[out]DWORD *pFaceRemap,         �ʂ��ǂ����בւ������̏��A�s�v��NULL
          &(pVertexRemap),                 //[out]LPD3DXBUFFER *ppVertexRemap, ���_���ǂ����בւ������̏��A�s�v��NULL
          &(pNewMC->_dwMaxInfleNum),         //[out]DWORD *pMaxFaceInfl, ��̒��_�ɉe����^����{�[���̐��̍ő�l
          &(pNewMC->_dwBoneCombNum),         //[out]DWORD *pNumBoneCombinations, �{�[���R���r�l�[�V�����̐�
          &(pNewMC->_pBoneCombinationTable), //[out]LPD3DXBUFFER *ppBoneCombinationTable, �{�[���R���r�l�[�V�������A�{�[���ƒ��_�̑Ή��\�z��
          &(pNewMC->MeshData.pMesh)          //[out]LPD3DXMESH *ppMesh �o�̓��b�V�����A�����ς݂̃��b�V�����Ԃ��Ă���
        );
        checkDxException(hr, D3D_OK, "ConvertToBlendedMesh�Ɏ��s���܂����B");
        //Remap�����A�^�[�Q�b�g�̒��_�o�b�t�@���O���I�ɏ��ԕύX���ꂽ�ꍇ�́A���̃��\�b�h���Ăяo���K�v������܂��B
        DWORD* d = (DWORD*)pVertexRemap->GetBufferPointer();
        pNewMC->pSkinInfo->Remap(pNewMC->MeshData.pMesh->GetNumVertices(),d);
        pVertexRemap->Release();

        // ConvertToBlenderMesh�֐��Ŗ߂��Ă��� ID3DXBuffer �ɂ́A
        // D3DXBONECOMBINATION�\���̂��@NumBoneCombinations �����Ă���B
    } else {
        //throwCriticalException("SkinAniMeshAllocHierarchy::CreateMeshContainer()  pSkinInfo ��񂪂���܂���");
        _TRACE_("���x����SkinAniMeshAllocHierarchy::CreateMeshContainer()  pSkinInfo ��񂪂���܂���B pNewMC->Name="<<pNewMC->Name);
        pNewMC->pSkinInfo = nullptr;
        pNewMC->_dwBoneOffsetMatrixNum = 0;
        pNewMC->_paBoneOffsetMatrix = nullptr;
        pNewMC->_dwMaxInfleNum = 0;
        pNewMC->_dwBoneCombNum = 0;
        pNewMC->_pBoneCombinationTable = nullptr;
        BoneAniMeshAllocHierarchy::createNewMeshContainer(); //���̂Ƃ���ύX�Ȃ�
    }

    // �}�e���A���o�^
    pNewMC->NumMaterials = NumMaterials;
    registerMaterial( pMaterials, NumMaterials, &pNewMC->pMaterials);
    // �G�t�F�N�g�o�^
    registerEffect( pEffectInstances, &pNewMC->pEffects );

    *ppNewMeshContainer = pNewMC;

    return D3D_OK;
}

D3DXFRAME* SkinAniMeshAllocHierarchy::createNewFrame() {
    SkinAniMeshFrame* tmp = NEW SkinAniMeshFrame;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //�e�N���X�����o(BoneAniMeshFrame)������
    tmp->_frame_index = MAXDWORD; // 0 ���L���ȃC���f�b�N�X�Ȃ̂� 0 �ŏ������������Ȃ�����
    D3DXMatrixIsIdentity(&(tmp->_world_trans_matrix)); //�Ƃ肠�����P�ʍs��
    //�g�����̏�����
    tmp->_bone_id = MAXDWORD;
    D3DXMatrixIsIdentity(&(tmp->_bone_offset_matrix));
    D3DXMatrixIsIdentity(&(tmp->_combined_matrix));
    return tmp;
}

D3DXMESHCONTAINER* SkinAniMeshAllocHierarchy::createNewMeshContainer() {
    SkinAniMeshContainer* tmp = NEW SkinAniMeshContainer();
    ZeroMemory(tmp, sizeof(D3DXMESHCONTAINER));
    //�g�����̏�����
    tmp->_dwMaxInfleNum = 0;    // �{�[���ő�e����
    tmp->_dwBoneCombNum = 0;    // �{�[���R���r�l�[�V������
    tmp->_pBoneCombinationTable = nullptr;  // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^

    tmp->_dwBoneOffsetMatrixNum = UINT_MAX;
    tmp->_paBoneOffsetMatrix = nullptr;
    return tmp;
}

// �R���e�i���폜
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

    // �G�t�F�N�g
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

    //�����ǉ��A���̑��͓���
    ID3DXBuffer* pBoneCombinationTable = p->_pBoneCombinationTable;
    GGAF_RELEASE_NULLABLE(pBoneCombinationTable);

    D3DXMATRIX* paBoneOffsetMatrix = p->_paBoneOffsetMatrix;
    GGAF_DELETEARR_NULLABLE(pBoneCombinationTable);

    delete p;
    return D3D_OK;
}
