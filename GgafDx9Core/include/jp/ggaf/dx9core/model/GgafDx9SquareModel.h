#ifndef GGAFDX9SQUAREMODEL_H_
#define GGAFDX9SQUAREMODEL_H_
namespace GgafDx9Core {


class GgafDx9SquareModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
	struct VERTEX{
		float x, y, z;    // 頂点座標
		float nx, ny, nz; // 法線
		DWORD color;      // 頂点の色
//		float tu, tv;     // テクスチャ座標
	};
	/** VERTEXのFVF */
	static DWORD FVF;
	/** マテリアル */
	D3DMATERIAL9* 		_pD3DMaterial9;
//	/** テクスチャ(アニメーションパターン） */
//	LPDIRECT3DTEXTURE9 _pID3DTexture9;
	/** 矩形の頂点合計のサイズ */
	UINT _iSize_Vertecs;
	/** 1頂点のサイズ */
	UINT _iSize_Vertec_unit;
//	/** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
//	GgafDx9RectUV*  _paRectUV;


	/** 頂点バッファへのポインタ */
	LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;


public:
	/** 全アニメパターン数 */
//	int _iAnimationPatternNo_Max;
//	float  _fSize_SquareModelWidth;
//	float  _fSize_SquareModelHeight;
//	int    _iRowNum_TextureSplit;
//	int    _iColNum_TextureSplit;

	/**
	 * コンストラクタ<BR>
	 * @param prm_squaremodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 */
	GgafDx9SquareModel(string prm_squaremodel_name);

	/**
	 * GgafDx9SquareModelオブジェクトの描画<BR>
	 * @param	prm_pActor_Target 描画するGgafDx9SquareActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();
	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9SquareModelManagerである<BR>
	 */
	virtual ~GgafDx9SquareModel();		//デストラクタ

};


}
#endif /*GGAFDX9SQUAREMODEL_H_*/
