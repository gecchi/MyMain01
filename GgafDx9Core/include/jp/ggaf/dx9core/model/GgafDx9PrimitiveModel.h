#ifndef GGAFDX9PRIMITIVEMODEL_H_
#define GGAFDX9PRIMITIVEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PrimitiveActor用モデルクラス.
 */
class GgafDx9PrimitiveModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z; // 頂点座標
        float nx, ny, nz; // 法線
        DWORD color; // 頂点の色
        float tu, tv; // テクスチャ座標
    };

    /** VERTEXのFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** マテリアル */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** テクスチャ(アニメーションパターン） */
    GgafDx9TextureConnection* _pTextureCon;


    UINT _size_vertecs;
    /** 1頂点のサイズ */
    UINT _size_vertec_unit;

    VERTEX* _paVtxBuffer_org;
    WORD _paIdxBuffer_org;

    Frm::Model3D* _pModel3D;
    Frm::Mesh* _pMeshesFront;




    /**
     * コンストラクタ<BR>
     * @param prm_spritemodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9PrimitiveModel(char* prm_spritemodel_name);

public:

    /**
     * GgafDx9PrimitiveModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9PrimitiveActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9PrimitiveModel(); //デストラクタ
};

}
#endif /*GGAFDX9PRIMITIVEMODEL_H_*/
