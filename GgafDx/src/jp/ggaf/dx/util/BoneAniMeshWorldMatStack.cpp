#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
using namespace GgafDx;

BoneAniMeshWorldMatStack::BoneAniMeshWorldMatStack() : GgafCore::Object() {
//    _pModel_MapBoneFrameIndex_ActAnimationSetIndexList = nullptr;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _as0_index = -1;
    _as1_index = -1;
    _prevTransformationMatrixList.clear();
}

BoneAniMeshWorldMatStack::~BoneAniMeshWorldMatStack(void) {
}

void BoneAniMeshWorldMatStack::registerFrameTransformationMatrix(BoneAniMeshFrame* pFrame) {
    _prevTransformationMatrixList.push_back(pFrame->TransformationMatrix);
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        registerFrameTransformationMatrix((BoneAniMeshFrame*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        registerFrameTransformationMatrix((BoneAniMeshFrame*)pFrame->pFrameSibling);
    }
}
// ���[���h�ϊ��s��̐ݒ�
void BoneAniMeshWorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    _actor_world_trans_matrix = *worldmat;
}

void BoneAniMeshWorldMatStack::UpdateFrame(BoneAniMeshFrame* prm_frame_root, int prm_as0_index, int prm_as1_index, bool** prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
#ifdef MY_DEBUG
    if (_prevTransformationMatrixList.size() == 0) {
        throwCriticalException("BoneAniMeshWorldMatStack::UpdateFrame() �����s�O��registerFrameTransformationMatrix() �Ńt���[���o�^���ĉ������B");
    }
#endif
    // �X�^�b�N�̏�����
    while (!_stack_matrix.empty())
        _stack_matrix.pop();

    // ���[���h�ϊ��s����X�^�b�N�ɐς�
    _stack_matrix.push(&_actor_world_trans_matrix);
    _as0_index = prm_as0_index;
    _as1_index = prm_as1_index;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
    // ���[�g�t���[�����烏�[���h�ϊ��s���A���v�Z
    if (_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
        CalcBoneAniMeshFrame(prm_frame_root);
    } else {
        m_DrawFrameList.clear();  //�폜�\��
        CalcBoneAniMeshFrame_old(prm_frame_root);  //�폜�\��
    }
}

void BoneAniMeshWorldMatStack::CalcBoneAniMeshFrame_old(BoneAniMeshFrame* prm_pBoneFrame) {
     //�폜�\��
    // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
    D3DXMATRIX *pStackMat = _stack_matrix.top();

    D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);

    if (prm_pBoneFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        m_DrawFrameList.push_back(prm_pBoneFrame);
    }

    // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
    if (prm_pBoneFrame->pFrameFirstChild) {
        _stack_matrix.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcBoneAniMeshFrame_old((BoneAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // �q�t���[���������I������̂ŃX�^�b�N��1�O��
    }

    // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
    if (prm_pBoneFrame->pFrameSibling) {
        //_TRACE_("�Z��t���[���ւ����܂�");
        CalcBoneAniMeshFrame_old((BoneAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

void BoneAniMeshWorldMatStack::CalcBoneAniMeshFrame(BoneAniMeshFrame* prm_pBoneFrame) {
    // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
    D3DXMATRIX *pStackMat = _stack_matrix.top();

    //���̃t���[��(frame_world)���A�A�j���[�V�����ΏۂȂ̂�����
    bool is_target_frame = false;
    LPSTR born_frame_name = prm_pBoneFrame->Name;
    if (born_frame_name) {
        if (_as0_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as0_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true; //���̃t���[���́A�g���b�N0�̃A�j���[�V�����Z�b�g�̃A�j���[�V�����Ώۂł���
        } else if (_as1_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as1_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true; //���̃t���[���́A�g���b�N1�̃A�j���[�V�����Z�b�g�̃A�j���[�V�����Ώۂł���
        }
    }

    if (is_target_frame) {
        //�A�j���[�V�����Ώۂ̃t���[���ł���ꍇ�A
        //�A�j���[�V�����R���g���[���[�� pAc->AdvanceTime(0, nullptr) �ɂ�胂�f���̃t���[���� TransformationMatrix ���X�V����Ă���̂ŁA
        //�����(prm_pBoneFrame->TransformationMatrix) ���g�p���ă��[���h�ϊ�
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
        //TransformationMatrix ��ۑ�
        _prevTransformationMatrixList[prm_pBoneFrame->_frame_index]  = prm_pBoneFrame->TransformationMatrix;
    } else {
        //�A�j���[�V�����Ώۂ̃t���[���łȂ�
        //�A�j���[�V�����R���g���[���[�� pAc->AdvanceTime(0, nullptr) �ł��A���f���̃t���[���� TransformationMatrix ���e������Ȃ��̂ŁA
        //�ȑO�̉����̃A�j���[�V�������̍s�񂪎c���Ă��܂��Ă���B����Ă���(prm_pBoneFrame->TransformationMatrix) �͎g�p���Ȃ��B
        //�O��ۑ��� TransformationMatrix �g�p���ă��[���h�ϊ�����B�܂肱�̃{�[���͑O��ƕς�炸��~��ԁB
        D3DXMATRIX* pMatrix = &(_prevTransformationMatrixList[prm_pBoneFrame->_frame_index]); //�O��ۑ��ς݂�TransformationMatrix
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), pMatrix, pStackMat);
    }

    // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
    if (prm_pBoneFrame->pFrameFirstChild) {
        _stack_matrix.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcBoneAniMeshFrame((BoneAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // �q�t���[���������I������̂ŃX�^�b�N��1�O��
    }

    // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
    if (prm_pBoneFrame->pFrameSibling) {
        CalcBoneAniMeshFrame((BoneAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

