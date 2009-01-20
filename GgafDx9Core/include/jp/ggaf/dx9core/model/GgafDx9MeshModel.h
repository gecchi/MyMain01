#ifndef GGAFDX9MESHMODEL_H_
#define GGAFDX9MESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用モデルクラス.
 */
class GgafDx9MeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
	/** メッシュ(ID3DXMeshインターフェイスへのポインタ） */
	LPD3DXMESH			_pID3DXMesh;
	/** マテリアル(D3DMATERIAL9構造体を要素とする配列の先頭アドレスを指すポインタ） */
	D3DMATERIAL9* 		_paD3DMaterial9;
	/** テクスチャ(IDirect3DTexture9インターフェイスへのポインタを要素とする配列の先頭アドレスを指すポインタ） */
	LPDIRECT3DTEXTURE9* _papID3DTexture9;
	/** D3DXLoadMeshFromXのオプション */
	DWORD _dwOptions;

	/** メッシュに含まれる各面の隣接面を格納するポインタ */
//	LPD3DXBUFFER	_pAdjacency;
	/** マテリアル数(=メッシュ数) */
	DWORD               _dwNumMaterials;

public:
	/**
	 * コンストラクタ<BR>
	 * @param prm_meshmodel_name モデルの識別名。".x"を追加すると定義Xファイル名になる。
	 * @param prm_dwOptions D3DXLoadMeshFromXのオプション
	 * @return
	 */
	GgafDx9MeshModel(std::string prm_meshmodel_name, DWORD prm_dwOptions);

	/**
	 * GgafDx9MeshModelオブジェクトの描画<BR>
	 * @param	prm_pActor_Target 描画するGgafDx9MeshActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();

	void setAlpha(float prm_fAlpha);

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9MeshModelManagerである<BR>
	 */
	virtual ~GgafDx9MeshModel();		//デストラクタ

};


}
#endif /*GGAFDX9MESHMODEL_H_*/
