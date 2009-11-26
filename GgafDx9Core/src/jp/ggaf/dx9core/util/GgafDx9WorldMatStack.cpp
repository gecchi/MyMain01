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



// ワールド変換行列の設定
void GgafDx9WorldMatStack::SetWorldMatrix( D3DXMATRIX* worldmat )
{
	m_WorldTransMatrix = *worldmat;
}


void GgafDx9WorldMatStack::UpdateFrame( D3DXFRAME_WORLD* frame )
{

  _TRACE_("GgafDx9WorldMatStack::UpdateFrame!!");
  // スタックの初期化
   while(!m_MatrixStack.empty())
      m_MatrixStack.pop();

   // 描画フレームリストの初期化
   m_DrawFrameList.clear();

   // ワールド変換行列をスタックに積む
   m_MatrixStack.push( &m_WorldTransMatrix );

   // ルートフレームからワールド変換行列を連続計算
   CalcFrameWorldMatrix( frame );
}


void GgafDx9WorldMatStack::CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame )
{
    _TRACE_("GgafDx9WorldMatStack::CalcFrameWorldMatrix!!!!");
   // 現在のスタックの先頭にあるワールド変換行列を参照
   D3DXMATRIX *pStackMat = m_MatrixStack.top();

   // 引数のフレームに対応するワールド変換行列を計算
   D3DXMatrixMultiply( &frame->WorldTransMatrix, &frame->TransformationMatrix, pStackMat );

   // フレームにメッシュコンテナがあれば、このフレームをリストに追加する
   if( frame->pMeshContainer != NULL ) {
       _TRACE_("フレームにメッシュコンテナがあれば、このフレームをリストに追加");
      m_DrawFrameList.push_back( frame );
   }

   // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
   if( frame->pFrameFirstChild != NULL ){
      _TRACE_("子フレームへもぐる");
      m_MatrixStack.push( &frame->WorldTransMatrix );
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameFirstChild );
      _TRACE_("かえってきました");
      m_MatrixStack.pop();    // 子フレームがもう終わったのでスタックを1つ外す
   }

   // 兄弟フレームがあれば「現在の」スタックを利用
   if( frame->pFrameSibling != NULL){
       _TRACE_("兄弟フレームへいきます");
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameSibling );
   }
}


// 描画リストを取得
list< D3DXFRAME_WORLD*> *GgafDx9WorldMatStack::GetDrawList()
{
	return &m_DrawFrameList;
}
