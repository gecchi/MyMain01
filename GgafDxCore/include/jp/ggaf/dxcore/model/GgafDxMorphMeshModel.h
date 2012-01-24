#ifndef GGAFDXMORPHMESHMODEL_H_
#define GGAFDXMORPHMESHMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxMorphMeshModel用のモデルクラス.
 * GgafDxMorphMeshModel は GgafDxMeshModel の描画する機能に加え、モーフアニメーション機能を有するモデルです。<BR>
 * <b>引数のモデル名 ( prm_model_name ) の与えかたと読み込まれるXファイルについて</b><BR>
 * ＜例＞<BR>
 * <table border=1>
 * <tr>
 * <th>prm_model_name</th>
 * <th>プライマリメッシュ Xファイル</th>
 * <th>モーフターゲット Xファイル</th>
 * </tr>
 * <tr>
 * <td>"M/0/ball"</td>
 * <td>ball_0.x</td>
 * <td>無し</td>
 * </tr>
 * <tr>
 * <td>"M/1/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x</td>
 * </tr>
 * <tr>
 * <td>"M/2/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x</td>
 * </tr>
 * <tr>
 * <td>"M/3/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x<BR>ball_3.x</td>
 * </tr>
 * <tr>
 * <td>"M/6/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x<BR>ball_3.x<BR>・・・<BR>ball_6.x</td>
 * </tr>
 * </table>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

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

    /** プライマリメッシュの頂点フォーマット定義 */
    struct VERTEX_PRIMARY {
        float x, y, z;    // 頂点座標
        float nx, ny, nz; // 法線
        DWORD color;      // 頂点の色（現在未使用）
        float tu, tv;     // テクスチャ座標
    };

    /** モーフターゲットメッシュの頂点フォーマット定義 */
    struct VERTEX_MORPH {
        float x, y, z;    // 頂点座標
        float nx, ny, nz; // 法線
    };

    /** モーフターゲット数 */
    int _morph_target_num;
    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pIDirect3DVertexDeclaration9;
    /** 頂点バッファ（プライマリ） */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_primary;
    /** 頂点バッファの配列（要素数＝モーフターゲット数） */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9_morph;

    /** インデックスバッファ（プライマリのみ） */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;


    /** 頂点のサイズ（プライマリ） */
    UINT _size_vertices_primary;
    /** 1頂点のサイズ（プライマリ） */
    UINT _size_vertex_unit_primary;
    /** 頂点のサイズ（モーフターゲット） */
    UINT _size_vertices_morph;
    /** 1頂点のサイズ（モーフターゲット） */
    UINT _size_vertex_unit_morph;

    /** DrawIndexedPrimitive描画パラメーター（プライマリのみ） */
    INDEXPARAM* _paIndexParam;
    /** マテリアル種類数（プライマリのみ） */
    UINT _nMaterialListGrp;

    /** 頂点バッファの写しコピーの頂点配列（プライマリ） */
    VERTEX_PRIMARY* _paVtxBuffer_org_primary;
    /** 頂点バッファの写しコピーの頂点配列のモーフターゲット数配列 */
    VERTEX_MORPH**  _papaVtxBuffer_org_morph;
    /** インデックスバッファの写しコピー（プライマリのみ） */
    WORD* _paIdxBuffer_org;

    /** Paulさんモデル（要素数＝プライマリ＋モーフターゲット数） */
    Frm::Model3D** _papModel3D;
    /** Paulさんメッシュ（要素数＝プライマリ＋モーフターゲット数） */
    Frm::Mesh** _papMeshesFront;

    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名
     */
    GgafDxMorphMeshModel(char* prm_model_name);

public:

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXMORPHMESHMODEL_H_*/
