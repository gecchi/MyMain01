#ifndef GGAFDX9MESHMODEL_H_
#define GGAFDX9MESHMODEL_H_
namespace GgafDx9Core {


// 本プログラムは Paul Coppens さんの作成された、Xファイルを読み込むサンプル
// を元に、独自に改良修正（やデバッグ）したクラスを使用しています。
// ありがとう Paulさん。
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
 * <b>＜長所＞</b>  <BR>
 * ・Xファイルの頂点数を保証。 <BR>
 * ・GgafDx9D3DXMeshModel より読み込みが高速（templateとか見てない）。 <BR>
 * ・Xファイルに複数メッシュ登録されている場合、これを連結して一つの頂点バッファ、インデックスバッファと扱うため
 *   描画がより高速になる。 <BR>
 * <b>＜短所＞</b> <BR>
 * ・D3DXLoadMeshFromXを使用しておらず、Xファイルの template 宣言は見ていないため、データ構造名のヘッダ名
 *  ("Mesh"や"TextureFilename"等）は ハードコーディングされている。メタセコア、3DSMAX等のXファイルのエクスポートを
 *  読み込めれば良いという設計で、予測しない複雑なXファイルはまず読めない。<BR>
 * ・勝手に共有頂点の法線を平均化する <BR>
 * <BR>
 * <b>「経緯」</b><BR>
 * 例えば立方体の場合、普通は、頂点は8個、法線ベクトル6個、頂点インデックス32、法線インデックス32となるが、
 * このようなXファイルを D3DXLoadMeshFromXで読み込むと、勝手に頂点が増える。<BR>
 * これは親切にも、エッジをクッキリ見せるために法線が優先されて処理されるためだと思う。<BR>
 * しかし、シェーダーでモーフ時や、複数オブジェクトをDrawIndexedPrimitiveでわけて表示する時等、
 * 勝手に頂点の数が変わってしまうのは致命的な場合がある。<BR>
 * 「Xファイルに書いた通りの頂点で頂点バッファを作りたい」<BR>
 * 頂点が増える条件は想像できるが、頂点の分割や最適化アルゴリズムの詳細な仕様が探しても無い（と思う）。<BR>
 * D3DXLoadMeshFromXのソースコードさえあれば解決だが、そんなの公開されて無い。<BR>
 * そんなわけで、D3DXLoadMeshFromXは使えないという結論になり、独自にXファイルを読み込むようにした。<BR>
 * 使えないと決断するまで非常長かった。お陰でXファイルマスターになりました。<BR>
 * 頂点数を保証するため、法線が足りなくなってしまう場合がある。そこで共有頂点の法線は平均化を行うことにしている。<BR>
 * もしエッジをクッキリ出したい場合は、Xファイル側で最初からちゃんと立方体ならば頂点を32個書けばよい。<BR>
 * また、法線の無いXファイルでも頂点インデックスから自動で法線を計算し生成する。<BR>
 *
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
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    virtual void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9MeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9MESHMODEL_H_*/
