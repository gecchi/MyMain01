#ifndef GGAFDX9PLATEMODEL_H_
#define GGAFDX9PLATEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PlateActor用モデルクラス.
 */
class GgafDx9PlateModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9PlateActor;
protected:
    /**
     * コンストラクタ<BR>
     * @param prm_platemodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9PlateModel(char* prm_platemodel_name);

public:

    /** VERTEXのFVF */
    static DWORD FVF;

    /** テクスチャ(アニメーションパターン） */
    GgafDx9TextureConnection* _pTexture;

    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;

    /** 前回表示のUV */
    GgafDx9RectUV* _pRectUV_drawlast;

    /** 全アニメパターン数 */
    int _iPatternNo_Max;
    float _fSize_PlateModelWidth;
    float _fSize_PlateModelHeight;
    int _iRowNum_TextureSplit;
    int _iColNum_TextureSplit;

    /**
     * GgafDx9PlateModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9PlateActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9PlateModelManagerである<BR>
     */
    virtual ~GgafDx9PlateModel(); //デストラクタ

};

}
#endif /*GGAFDX9PLATEMODEL_H_*/
