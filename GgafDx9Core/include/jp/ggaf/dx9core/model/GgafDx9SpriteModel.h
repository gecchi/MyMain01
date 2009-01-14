#ifndef GGAFDX9SPRITEMODEL_H_
#define GGAFDX9SPRITEMODEL_H_

class GgafDx9SpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
	struct VERTEX{
		float x, y, z;    // 頂点座標
		float nx, ny, nz; // 法線
		DWORD color;      // 頂点の色
		float tu, tv;     // テクスチャ座標
	};
	/** VERTEXのFVF */
	static DWORD FVF;
	/** マテリアル */
	D3DMATERIAL9* 		_pD3DMaterial9;
	/** テクスチャ(アニメーションパターン） */
	LPDIRECT3DTEXTURE9 _pID3DTexture9;
	/** 矩形の頂点合計のサイズ */
	UINT _iSize_Vertecs;
	/** 1頂点のサイズ */
	UINT _iSize_Vertec_unit;
	/** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
	GgafDx9RectUV*  _paRectUV;


	/** 頂点バッファへのポインタ */
	LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;

	/** 前回表示のUV */
	GgafDx9RectUV*  _pRectUV_drawlast;

	//bool _isChangedAlpha;

public:
	/** 全アニメパターン数(0～) */
	int _iAnimationPatternNo_Max;
	float  _fSize_SpriteModelWidthPx;
	float  _fSize_SpriteModelHeightPx;
	int    _iRowNum_TextureSplit;
	int    _iColNum_TextureSplit;
	//int	   _iChangeVertexAlpha;

	/**
	 * コンストラクタ<BR>
	 * @param prm_spritemodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 */
	GgafDx9SpriteModel(string prm_spritemodel_name);

	/**
	 * GgafDx9SpriteModelオブジェクトの描画<BR>
	 * @param	prm_pActor_Target 描画するGgafDx9SpriteActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();

	void changeVertexAlpha(int prm_iVertexAlpha);

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9SpriteModelManagerである<BR>
	 */
	virtual ~GgafDx9SpriteModel();		//デストラクタ

};

#endif /*GGAFDX9SPRITEMODEL_H_*/
