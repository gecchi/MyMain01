#include "jp/ggaf/dx/util/WorldMatStack.h"
#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"

using namespace GgafDx;

WorldMatStack::WorldMatStack(void) : GgafCore::Object() {
}

WorldMatStack::~WorldMatStack(void) {
}

// ���[���h�ϊ��s��̐ݒ�
void WorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    m_WorldTransMatrix = *worldmat;
}

void WorldMatStack::UpdateFrame(FrameWorldMatrix* frame_world) {
    // �X�^�b�N�̏�����
    while (!m_MatrixStack.empty())
        m_MatrixStack.pop();

    // �`��t���[�����X�g�̏�����
    m_DrawFrameList.clear();

    // ���[���h�ϊ��s����X�^�b�N�ɐς�
    m_MatrixStack.push(&m_WorldTransMatrix);

    // ���[�g�t���[�����烏�[���h�ϊ��s���A���v�Z
    CalcFrameWorldMatrix(frame_world);
}

void WorldMatStack::CalcFrameWorldMatrix(FrameWorldMatrix* frame_world) {
    // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
    D3DXMATRIX *pStackMat = m_MatrixStack.top();

    D3DXMatrixMultiply(&(frame_world->WorldTransMatrix), &(frame_world->TransformationMatrix), pStackMat);

    if (frame_world->pMeshContainer) {
        //_TRACE_("�t���[���Ƀ��b�V���R���e�i������");
        // �����̃t���[���ɑΉ����郏�[���h�ϊ��s����v�Z
        m_DrawFrameList.push_back(frame_world);
    }


//    // �t���[���Ƀ��b�V���R���e�i������΁A���̃t���[�������X�g�ɒǉ�����
//    if (frame_world->pMeshContainer) {
//        _TRACE_("�t���[���Ƀ��b�V���R���e�i������");
//        // �����̃t���[���ɑΉ����郏�[���h�ϊ��s����v�Z
//        D3DXMatrixMultiply(&frame_world->WorldTransMatrix, &frame_world->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame_world);
//    } else {
//        D3DXMatrixMultiply(&frame_world->WorldTransMatrix, &frame_world->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame_world);
//    }

    // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
    if (frame_world->pFrameFirstChild) {
        m_MatrixStack.push(&(frame_world->WorldTransMatrix));
        CalcFrameWorldMatrix((FrameWorldMatrix*)frame_world->pFrameFirstChild);
        m_MatrixStack.pop(); // �q�t���[���������I������̂ŃX�^�b�N��1�O��
    }

    // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
    if (frame_world->pFrameSibling) {
        //_TRACE_("�Z��t���[���ւ����܂�");
        CalcFrameWorldMatrix((FrameWorldMatrix*)frame_world->pFrameSibling);
    }
}

// �`�惊�X�g���擾
std::list<FrameWorldMatrix*> *WorldMatStack::GetDrawList() {
    return &m_DrawFrameList;
}
