#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9WorldMatStack::GgafDx9WorldMatStack(void)
{
}

GgafDx9WorldMatStack::~GgafDx9WorldMatStack(void)
{
}



// ���[���h�ϊ��s��̐ݒ�
void GgafDx9WorldMatStack::SetWorldMatrix( D3DXMATRIX* worldmat )
{
	m_WorldTransMatrix = *worldmat;
}


void GgafDx9WorldMatStack::UpdateFrame( D3DXFRAME_WORLD* frame )
{

  _TRACE_("GgafDx9WorldMatStack::UpdateFrame!!");
  // �X�^�b�N�̏�����
   while(!m_MatrixStack.empty())
      m_MatrixStack.pop();

   // �`��t���[�����X�g�̏�����
   m_DrawFrameList.clear();

   // ���[���h�ϊ��s����X�^�b�N�ɐς�
   m_MatrixStack.push( &m_WorldTransMatrix );

   // ���[�g�t���[�����烏�[���h�ϊ��s���A���v�Z
   CalcFrameWorldMatrix( frame );
}


void GgafDx9WorldMatStack::CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame )
{
    _TRACE_("GgafDx9WorldMatStack::CalcFrameWorldMatrix!!!!");
   // ���݂̃X�^�b�N�̐擪�ɂ��郏�[���h�ϊ��s����Q��
   D3DXMATRIX *pStackMat = m_MatrixStack.top();

   // �����̃t���[���ɑΉ����郏�[���h�ϊ��s����v�Z
   D3DXMatrixMultiply( &frame->WorldTransMatrix, &frame->TransformationMatrix, pStackMat );

   // �t���[���Ƀ��b�V���R���e�i������΁A���̃t���[�������X�g�ɒǉ�����
   if( frame->pMeshContainer != NULL ) {
       _TRACE_("�t���[���Ƀ��b�V���R���e�i������΁A���̃t���[�������X�g�ɒǉ�");
      m_DrawFrameList.push_back( frame );
   }

   // �q�t���[��������΃X�^�b�N��ς�ŁA�q�t���[���̃��[���h�ϊ����W�̌v�Z��
   if( frame->pFrameFirstChild != NULL ){
      _TRACE_("�q�t���[���ւ�����");
      m_MatrixStack.push( &frame->WorldTransMatrix );
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameFirstChild );
      _TRACE_("�������Ă��܂���");
      m_MatrixStack.pop();    // �q�t���[���������I������̂ŃX�^�b�N��1�O��
   }

   // �Z��t���[��������΁u���݂́v�X�^�b�N�𗘗p
   if( frame->pFrameSibling != NULL){
       _TRACE_("�Z��t���[���ւ����܂�");
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameSibling );
   }
}


// �`�惊�X�g���擾
list< D3DXFRAME_WORLD*> *GgafDx9WorldMatStack::GetDrawList()
{
	return &m_DrawFrameList;
}
