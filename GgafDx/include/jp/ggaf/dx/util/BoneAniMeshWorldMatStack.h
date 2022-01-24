#ifndef GGAF_DX_BONEANIMESHWORLDMATSTACK_H_
#define GGAF_DX_BONEANIMESHWORLDMATSTACK_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <list>
#include <stack>
#include <vector>
#include <map>

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 *
 */
class BoneAniMeshWorldMatStack : public GgafCore::Object {
public:
    D3DXMATRIX _actor_world_trans_matrix;
    std::stack<D3DXMATRIX*> _stack_matrix;
    std::list<BoneAniMeshFrame*> m_DrawFrameList; //D3DXAniMeshActor�ێ��p�A�폜�\��

    /** �O�񃏁[���h�ϊ��̌v�Z�Ɏg�p���ꂽ�t���[���̕ϊ��s��̕ۑ� */
    std::vector<D3DXMATRIX> _prevTransformationMatrixList;
    /** [�A�j���[�V�����Z�b�g�C���f�b�N�X][�t���[���C���f�b�N�X] �� �A�j���[�V�����Ώۂ��ǂ��� �̏��z�� */
    bool** _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
    int _as0_index;
    int _as1_index;
public:
    BoneAniMeshWorldMatStack();
    virtual ~BoneAniMeshWorldMatStack();
    virtual void registerFrameTransformationMatrix(BoneAniMeshFrame* pFrame);
    virtual void SetWorldMatrix( D3DXMATRIX* worldmat );

    /**
     * �A�N�^�[�̃��[���h�ϊ����s�� .
     * @param prm_pMatBaseTransformMatrix ���f���x�[�X�ϊ��s��
     * @param prm_frame_root �A�j���[�V�����{�[���t���[���̃��[�g
     * @param prm_as0_index �g���b�N0�ɐݒ肳��Ă���A�j���[�V�����Z�b�g�C���f�b�N�X
     * @param prm_as1_index �g���b�N0�ɐݒ肳��Ă���A�j���[�V�����Z�b�g�C���f�b�N�X
     * @param prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act
     */
    virtual void UpdateFrame(D3DXMATRIX* prm_pMatBaseTransformMatrix, BoneAniMeshFrame* prm_frame_root, int prm_as0_index = -1, int prm_as1_index = -1,
           bool** prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr);

    //D3DXAniMeshActor�ێ��p�A�폜�\��
    std::list< BoneAniMeshFrame*> *GetDrawList() {
        return &m_DrawFrameList;
    }
public:
   /**
    * �t���[�����[���h�s��Z�o�ċA�֐� .
    * @param frame_world �{�[���t���[��
    */
    void CalcBoneAniMeshFrame(BoneAniMeshFrame* frame_world);
    void CalcBoneAniMeshFrame_old(BoneAniMeshFrame* frame_world);   //D3DXAniMeshActor�ێ��p�A�폜�\��
};

}

#endif /*GGAF_DX_BONEANIMESHWORLDMATSTACK_H_*/
