#ifndef GGAFDX9MORPHMESHMODEL_H_
#define GGAFDX9MORPHMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9MorphMeshModel用のモデルクラス.
 * GgafDx9MorphMeshModel は GgafDx9MeshModel の描画する機能に加え、モーフアニメーション機能を有するモデルです。<BR>
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
class GgafDx9MorphMeshModel : public GgafDx9Model {
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
    GgafDx9MorphMeshModel(char* prm_model_name);

public:

    /**
     * GgafDx9MorphMeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9MorphMeshModel
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9MorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9MORPHMESHMODEL_H_*/
