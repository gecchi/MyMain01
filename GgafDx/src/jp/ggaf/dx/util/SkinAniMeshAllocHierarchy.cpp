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
    pDest->Type = pSrc->Type;   // ���b�V���^�C�v
    pDest->pMesh = pSrc->pMesh;// ���b�V���iunion�Ȃ̂łǂ�ł��ꏏ�j
    //�œK������̂�AddRef������
//    (pDest->pMesh)->AddRef();
}

D3DXMESHCONTAINER* SkinAniMeshAllocHierarchy::createNewMeshContainer() {
    SkinAniMeshContainer* tmp = NEW SkinAniMeshContainer();
    ZeroMemory(tmp, sizeof(SkinAniMeshContainer));
    //	���L�̓Ǝ��ǉ��������� ZeroMemory �����̂Œ���
//    DWORD dwMaxInfleNum;            // �{�[���ő�e����
//    DWORD dwBoneCombNum;            // �{�[���R���r�l�[�V������
//    D3DXBONECOMBINATION *pBoneComb;  // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^

    return tmp;
}

