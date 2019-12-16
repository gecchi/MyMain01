#include "jp/ggaf/dx/util/WorldMatStack.h"
#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
using namespace GgafDx;

WorldMatStack::WorldMatStack() : GgafCore::Object() {
//    _pModel_MapBoneFrameIndex_ActAnimationSetIndexList = nullptr;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _as0_index = -1;
    _as1_index = -1;
    _prevTransformationMatrixList.clear();
}

WorldMatStack::~WorldMatStack(void) {
}

void WorldMatStack::registerFrameTransformationMatrix(FrameWorldMatrix* pFrame) {
    _prevTransformationMatrixList.push_back(pFrame->TransformationMatrix);
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        registerFrameTransformationMatrix((FrameWorldMatrix*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        registerFrameTransformationMatrix((FrameWorldMatrix*)pFrame->pFrameSibling);
    }
}
// ���[���h�ϊ��s��̐ݒ�
void WorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    _actor_world_trans_matrix = *worldmat;
}

void WorldMatStack::UpdateFrame(FrameWorldMatrix* prm_frame_world, int prm_as0_index, int prm_as1_index) {

    // �X�^�b�N�̏�����
    while (!m_MatrixStack.empty())
        m_MatrixStack.pop();

//    // �`��t���[�����X�g�̏�����
//    _vecDrawBoneFrame.clear();

    // ���[���h�ϊ��s����X�^�b�N�ɐς�
    m_MatrixStack.push(&_actor_world_trans_matrix);
    _as0_index = prm_as0_index;
    _as1_index = prm_as1_index;
    // ���[�g�t���[�����烏�[���h�ϊ��s���A���v�Z
    CalcFrameWorldMatrix(prm_frame_world);
}

void WorldMatStack::CalcFrameWorldMatrix(FrameWorldMatrix* prm_pBoneFrame) {
    // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
    D3DXMATRIX *pStackMat = m_MatrixStack.top();

    //���̃t���[��(frame_world)���A�A�j���[�V�����ΏۂȂ̂�����
    //�A�j���[�V�����Ώۂ̃t���[���́Aframe_world->TransformationMatrix ��ϊ��s��Ƃ��Ďg�p����B
    //�A�j���[�V�����Ώۂł͂Ȃ��̃t���[���������ꍇ�A�A�N�^�[���Ƃɕێ����Ă���O��̕ϊ��s����g�p����B
    bool is_target_frame = false;
    LPSTR born_frame_name = prm_pBoneFrame->Name;
    if (born_frame_name) {
        if (_as0_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as0_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true;

        } else if (_as1_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as1_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true;
        }
    }

    if (is_target_frame) {
        //�A�j���[�V�����Ώۂ̃t���[���ł���
        _prevTransformationMatrixList[prm_pBoneFrame->_frame_index]  = prm_pBoneFrame->TransformationMatrix; //TransformationMatrix �ۑ�
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
    } else {
        D3DXMATRIX* pMatrix = &(_prevTransformationMatrixList[prm_pBoneFrame->_frame_index]);
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), pMatrix, pStackMat);
    }

    // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
    if (prm_pBoneFrame->pFrameFirstChild) {
        m_MatrixStack.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcFrameWorldMatrix((FrameWorldMatrix*)prm_pBoneFrame->pFrameFirstChild);
        m_MatrixStack.pop(); // �q�t���[���������I������̂ŃX�^�b�N��1�O��
    }

    // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
    if (prm_pBoneFrame->pFrameSibling) {
        //_TRACE_("�Z��t���[���ւ����܂�");
        CalcFrameWorldMatrix((FrameWorldMatrix*)prm_pBoneFrame->pFrameSibling);
    }
}

