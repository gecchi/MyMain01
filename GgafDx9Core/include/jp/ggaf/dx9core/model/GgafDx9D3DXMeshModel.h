#ifndef GGAFDX9D3DXMESHMODEL_H_
#define GGAFDX9D3DXMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9D3DXActor用モデルクラス.(現在未使用？)
 * GgafDx9D3DXMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 */
class GgafDx9D3DXMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    LPD3DXMESH _pID3DXMesh;
    /** テクスチャ配列(インスタンスはテクスチャ毎、モデルとは別管理） */
    GgafDx9TextureConnection** _papTextureCon;
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
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9D3DXMeshModelManagerである<BR>
     */
    virtual ~GgafDx9D3DXMeshModel(); //デストラクタ

};

}
#endif /*GGAFDX9D3DXMESHMODEL_H_*/
