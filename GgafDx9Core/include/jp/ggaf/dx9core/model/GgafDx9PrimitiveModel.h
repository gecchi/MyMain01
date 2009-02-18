#ifndef GGAFDX9PRIMITIVEMODEL_H_
#define GGAFDX9PRIMITIVEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PrimitiveActor用のモデルクラス.
 * GgafDx9PrimitiveModel は D3DXLoadMeshFromX を使用せず、独自にXファイルからモデルデータを読み込み設定する。<BR>
 * ＜注意＞<BR>
 * ・Faceは、3角形しか駄目。（D3DXLoadMeshFromX は 3角形 or 4角形をサポート）<BR>
 * ・UV座標について、頂点数と一致しなくても、とりあえず順番に設定する。データーが無いUV座標は(0,0)に設定される。<BR>
 * ・法線について、Faceの3頂点に同じ値を設定。共有頂点の場合、後に設定された法線で上書きれる。<BR>
 *   TODO:法線の向きは平均化は、したいのですがまだしてない。いつかする！<BR>
 * ・GgafDx9PrimitiveModelは頂点インデックスの最適化しないを行なわない、行なわないのが売りでもある。<BR>
 *   そのため、描画時は、Xファイルから読み込んだマテリアルリストの順番通りに描画する。<BR>
 *   これは、DrawIndexedPrimitive は、マテリアルリストのマテリアル番号が切り替わるたびに発生することを意味し、<BR>
 *   マテリアルリストのバラけ具合によっては、D3DXLoadMeshFromX よりパフォーマンスが落ちる。<BR>
 *   例えば、Xファイルのマテリアルリストが {0,0,1,1,0,1} な場合、マテリアル数が2つでも、描画は4回実行することになる。<BR>
 * ＜使い所＞<BR>
 * ・不完全と解っているXファイルを、あえて読みたい場合。（データローダーで使う場合）<BR>
 * ・Xファイル頂点情報等が、D3DXLoadMeshFromXの最適化によって、増えたり減ったり移動されたりして欲しくない場合。<BR>
 * ・シェーダーにパラメータを渡したい、あとから頂点をいじりたい場合等、ID3DXMesh からいちいち探すのが面倒だ。<BR>
 */
class GgafDx9PrimitiveModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:

    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

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
    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9_default;
    INDEXPARAM* _paIndexParam;
    /** テクスチャ配列(インスタンスはテクスチャ毎、モデルとは別管理） */
    GgafDx9TextureConnection** _papTextureCon;

    UINT _size_vertecs;
    /** 1頂点のサイズ */
    UINT _size_vertec_unit;
    /** 1頂点のサイズ */
    DWORD _dwNumMaterials;
    UINT _pFaceMaterials;

    VERTEX* _paVtxBuffer_org;
    WORD* _paIdxBuffer_org;

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
