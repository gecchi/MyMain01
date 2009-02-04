#ifndef GGAFDX9PLATEACTORD_H_
#define GGAFDX9PLATEACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター.
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです<BR>
 */
class GgafDx9PlateActor : public GgafDx9TransformedActor {
private:

	struct VERTEX{
		float x, y, z;    // 頂点座標
		float rhw;
		D3DCOLOR color;
		float tu, tv;     // テクスチャ座標
	};

	/** 内部アニメパターン用カウンター */
	int _iCounter_PatternNo;
	/** 内部アニメフレーム用カウンタ */
	int _iCounter_AnimationFrame;

public:
	/** モデルオブジェクトへのポインタ */
	GgafDx9ModelLead* _pModelLead;
	GgafDx9PlateModel* _pPlateModel;
	/** キャラ全体のα */
	float _fAlpha;

	/** 矩形の頂点情報 */
	VERTEX* _paVertex;
	/** 矩形の頂点合計のサイズ */
	UINT _iSize_Vertecs;
	/** 1頂点のサイズ */
	UINT _iSize_Vertec_unit;

	/** アニメパターン番号の上限番号 */
	int _iPatternNo_Top;
	/** 現在表示中のアニメパターン番号 */
	int _iPatternNo_Bottom;
	/** 現在表示中のアニメパターン番号 */
	int _iPatternNo_Active;


	GgafDx9PlateActor(char* prm_name, char* prm_spritemodel_name);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual void setPatternNo(int prm_iPlateNo);

	void setAlpha(float prm_fAlpha) {
		_fAlpha = prm_fAlpha;
	}

	float getAlpha() {
		return _fAlpha;
	}

	virtual ~GgafDx9PlateActor();		//デストラクタ

	//virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};


}
#endif /*GGAFDX9PLATEACTORD_H_*/
