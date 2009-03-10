#ifndef GGAFDX9BOARDMODEL_H_
#define GGAFDX9BOARDMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardActor用モデルクラス.
 */
class GgafDx9BoardModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9BoardActor;
protected:
    /**
     * コンストラクタ<BR>
     * @param prm_platemodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9BoardModel(char* prm_platemodel_name);

public:

    /** VERTEXのFVF */
    static DWORD FVF;

    /** テクスチャ(アニメーションパターン） */
    GgafDx9TextureConnection* _pTextureCon;

    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;

    /** 前回表示のUV */
    GgafDx9RectUV* _pRectUV_drawlast;

    /** 全アニメパターン数 */
    int _pattno_max;
    float _fSize_BoardModelWidth;
    float _fSize_BoardModelHeight;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9BoardModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9BoardActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9BoardModelManagerである<BR>
     */
    virtual ~GgafDx9BoardModel(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDMODEL_H_*/
