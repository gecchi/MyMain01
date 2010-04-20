#ifndef GGAFDX9D3DXMESHMODEL_H_
#define GGAFDX9D3DXMESHMODEL_H_
namespace GgafDx9Core {

/**
 * メッシュモデルクラス(GgafDx9D3DXActor用).
 * GgafDx9D3DXMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み、<BR>
 * 描画する機能を持った静的モデル用のクラスです。
 * ＜長所＞
 * ・D3DXLoadMeshFromX を使用して読み込むため、複雑なXファイルでも問題なく読みこみ描画できる。
 * ＜短所＞
 * ・他のモデルクラス郡に比べて、描画の最適化という面では劣る。読み込んで DrawSubset() するだけ。
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    LPD3DXMESH _pID3DXMesh;
    /** D3DXLoadMeshFromXのオプション */
    DWORD _dwOptions;

    /** メッシュに含まれる各面の隣接面を格納するポインタ */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @param prm_dwOptions D3DXLoadMeshFromXのオプション
     * @return
     */
    GgafDx9D3DXMeshModel(char* prm_model, DWORD prm_dwOptions);

    /**
     * GgafDx9D3DXMeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9D3DXMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    virtual void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9D3DXMeshModelManagerである<BR>
     */
    virtual ~GgafDx9D3DXMeshModel(); //デストラクタ

};

}
#endif /*GGAFDX9D3DXMESHMODEL_H_*/
