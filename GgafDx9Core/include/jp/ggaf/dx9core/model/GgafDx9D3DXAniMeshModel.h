#ifndef GGAFDX9D3DXANIMESHMODEL_H_
#define GGAFDX9D3DXANIMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。addSubBone()で事足りる)
 * GgafDx9D3DXAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    GgafDx9AllocHierarchyWorldFrame* _pAH;
    D3DXFRAME_WORLD* _pFR;
    ID3DXAnimationController* _pAcBase;
    FLOAT _Ang;
    int _anim_ticks_per_second;
    /** 60フレーム(1秒)で1ループする場合の1フレーム辺りの時間 */
//    double _advance_time_per_frame0;//60フレーム(1秒)で1ループすることを標準設定とする。

    GgafDx9WorldBoundMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromXのオプション */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @return
     */
    GgafDx9D3DXAniMeshModel(char* prm_model);

    /**
     * GgafDx9D3DXAniMeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9D3DXAniMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;



    void putMat(D3DXMATRIX* pMat) {
        _TRACE_( pMat->_11<<", "<< pMat->_12<<", "<< pMat->_13<<", "<< pMat->_14);
        _TRACE_( pMat->_21<<", "<< pMat->_22<<", "<< pMat->_23<<", "<< pMat->_24);
        _TRACE_( pMat->_31<<", "<< pMat->_32<<", "<< pMat->_33<<", "<< pMat->_34);
        _TRACE_( pMat->_41<<", "<< pMat->_42<<", "<< pMat->_43<<", "<< pMat->_44);
    };

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9D3DXAniMeshModelManagerである<BR>
     */
    virtual ~GgafDx9D3DXAniMeshModel(); //デストラクタ

};

}
#endif /*GGAFDX9D3DXANIMESHMODEL_H_*/
