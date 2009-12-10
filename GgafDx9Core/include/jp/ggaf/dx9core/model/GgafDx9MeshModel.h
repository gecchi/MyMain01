#ifndef GGAFDX9MESHMODEL_H_
#define GGAFDX9MESHMODEL_H_
namespace GgafDx9Core {


// このクラスは Paul Coppens さんの作成された、Xファイルを読み込むサンプル
// を元に、独自に修正（やデバッグ）したクラスを使用しています。
// ありがとう Paul。
//
// 【対象】
// Frm 名前空間のクラス
//
// 【Loading and displaying .X files without DirectX 】
// http://www.gamedev.net/reference/programming/features/xfilepc/
//
//                                         2009/03/06 Masatoshi Tsuge

/**
 * メッシュモデルクラス(GgafDx9MeshActor用).
 * GgafDx9MeshModel は独自にXファイルからモデルデータを読み込み、<BR>
 * オブジェクトを描画する機能を持った静的モデル用のクラスです。 <BR>
 * ＜長所＞  <BR>
 * ・GgafDx9D3DXMeshModel より読み込みが高速。  <BR>
 * ・Xファイルに複数メッシュ登録されている場合、これを連結して一つの頂点バッファ、インデックスバッファと扱うため  <BR>
 *  描画が GgafDx9D3DXMeshModel より高速  <BR>
 * ・勝手に共有頂点の法線を平均化する機能つき  <BR>
 * ＜短所＞  <BR>
 * ・D3DXLoadMeshFromXを使用しておらず、Xファイルの template 宣言は見ていないため、データ構造名  <BR>
 *  ("Mesh"や"TextureFilename"等）は ハードコーディングされている。  <BR>
 *  予測しない複雑なXファイルはうまく読め無い場合があるだろう。  <BR>
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshModel : public GgafDx9Model {
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
        DWORD color; // 頂点の色（現在未使用）
        float tu, tv; // テクスチャ座標
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;

    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;

    UINT _nMaterialListGrp;

    VERTEX* _paVtxBuffer_org;
    WORD* _paIdxBuffer_org;

    /** Paulさんモデル */
    Frm::Model3D* _pModel3D;
    /** Paulさんメッシュ */
    Frm::Mesh* _pMeshesFront;




    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9MeshModel(char* prm_model_name);

public:

    /**
     * GgafDx9MeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9MeshActor
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
    virtual ~GgafDx9MeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9MESHMODEL_H_*/
