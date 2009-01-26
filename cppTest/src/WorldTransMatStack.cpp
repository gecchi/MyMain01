#include "WorldTransMatStack.h"

CWorldTransMatStack::CWorldTransMatStack(void)
{
}

CWorldTransMatStack::~CWorldTransMatStack(void)
{
}



// ワールド変換行列の設定
void CWorldTransMatStack::SetWorldMatrix( D3DXMATRIX* worldmat )
{
	m_WorldTransMatrix = *worldmat;
}


void CWorldTransMatStack::UpdateFrame( D3DXFRAME_WORLD* frame )
{
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


void CWorldTransMatStack::CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame )
{
   // 現在のスタックの先頭にあるワールド変換行列を参照
   D3DXMATRIX *pStackMat = m_MatrixStack.top();

   // 引数のフレームに対応するワールド変換行列を計算
   D3DXMatrixMultiply( &frame->WorldTransMatrix, &frame->TransformationMatrix, pStackMat );

   // フレームにメッシュコンテナがあれば、このフレームをリストに追加する
   if( frame->pMeshContainer != NULL )
      m_DrawFrameList.push_back( frame );

   // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
   if( frame->pFrameFirstChild != NULL ){
      m_MatrixStack.push( &frame->WorldTransMatrix );
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameFirstChild );
      m_MatrixStack.pop();    // 子フレームがもう終わったのでスタックを1つ外す
   }

   // 兄弟フレームがあれば「現在の」スタックを利用
   if( frame->pFrameSibling != NULL){
      CalcFrameWorldMatrix( (D3DXFRAME_WORLD*)frame->pFrameSibling );
   }
}


// 描画リストを取得
list< D3DXFRAME_WORLD*> *CWorldTransMatStack::GetDrawList()
{
	return &m_DrawFrameList;
}
