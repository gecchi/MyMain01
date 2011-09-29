#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxWorldMatStack::GgafDxWorldMatStack(void) {
}

GgafDxWorldMatStack::~GgafDxWorldMatStack(void) {
}

// ���[���h�ϊ��s��̐ݒ�
void GgafDxWorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    m_WorldTransMatrix = *worldmat;
}

void GgafDxWorldMatStack::UpdateFrame(D3DXFRAME_WORLD* frame) {
    // �X�^�b�N�̏�����
    while (!m_MatrixStack.empty())
        m_MatrixStack.pop();

    // �`��t���[�����X�g�̏�����
    m_DrawFrameList.clear();

    // ���[���h�ϊ��s����X�^�b�N�ɐς�
    m_MatrixStack.push(&m_WorldTransMatrix);

    // ���[�g�t���[�����烏�[���h�ϊ��s���A���v�Z
    CalcFrameWorldMatrix(frame);
}

void GgafDxWorldMatStack::CalcFrameWorldMatrix(D3DXFRAME_WORLD* frame) {
    // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
    D3DXMATRIX *pStackMat = m_MatrixStack.top();

    D3DXMatrixMultiply(&(frame->WorldTransMatrix), &(frame->TransformationMatrix), pStackMat);

    if (frame->pMeshContainer) {
        //_TRACE_("�t���[���Ƀ��b�V���R���e�i������");
        // �����̃t���[���ɑΉ����郏�[���h�ϊ��s����v�Z
        m_DrawFrameList.push_back(frame);
    }


//    // �t���[���Ƀ��b�V���R���e�i������΁A���̃t���[�������X�g�ɒǉ�����
//    if (frame->pMeshContainer) {
//        _TRACE_("�t���[���Ƀ��b�V���R���e�i������");
//        // �����̃t���[���ɑΉ����郏�[���h�ϊ��s����v�Z
//        D3DXMatrixMultiply(&frame->WorldTransMatrix, &frame->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame);
//    } else {
//        D3DXMatrixMultiply(&frame->WorldTransMatrix, &frame->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame);
//    }

    // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
    if (frame->pFrameFirstChild) {
        m_MatrixStack.push(&(frame->WorldTransMatrix));
        CalcFrameWorldMatrix((D3DXFRAME_WORLD*)frame->pFrameFirstChild);
        m_MatrixStack.pop(); // �q�t���[���������I������̂ŃX�^�b�N��1�O��
    }

    // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
    if (frame->pFrameSibling) {
        //_TRACE_("�Z��t���[���ւ����܂�");
        CalcFrameWorldMatrix((D3DXFRAME_WORLD*)frame->pFrameSibling);
    }
}

// �`�惊�X�g���擾
list<D3DXFRAME_WORLD*> *GgafDxWorldMatStack::GetDrawList() {
    return &m_DrawFrameList;
}
