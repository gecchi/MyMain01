#ifndef GGAFDX9D3DXANIMESHMODEL_H_
#define GGAFDX9D3DXANIMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9D3DXActor用モデルクラス.(現在未使用？)
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
    ID3DXAnimationController* _pAC;
    FLOAT _Ang;


    GgafDx9WorldMatStack WTMStack;
    /** D3DXLoadMeshFromXのオプション */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @param prm_dwOptions D3DXLoadMeshFromXのオプション
     * @return
     */
    GgafDx9D3DXAniMeshModel(char* prm_model);

    /**
     * GgafDx9D3DXAniMeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9D3DXAniMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9D3DXAniMeshModelManagerである<BR>
     */
    virtual ~GgafDx9D3DXAniMeshModel(); //デストラクタ

};

}
#endif /*GGAFDX9D3DXANIMESHMODEL_H_*/
