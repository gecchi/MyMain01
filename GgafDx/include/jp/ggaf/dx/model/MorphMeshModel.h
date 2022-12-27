#ifndef GGAF_DX_MORPHMESHMODEL_H_
#define GGAF_DX_MORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * MorphMeshModel用のモデルクラス.
 * MorphMeshModel は MeshModel の描画する機能に加え、モーフアニメーション機能を有するモデルです。<BR>
 * <b>引数のモデル名 ( prm_model_id ) の与えかたと読み込まれるXファイルについて</b><BR>
 * ＜例＞<BR>
 * <table border=1>
 * <tr>
 * <th>prm_model_id</th>
 * <th>プライマリメッシュ Xファイル</th>
 * <th>モーフターゲット Xファイル</th>
 * </tr>
 * <tr>
 * <td>"M,ball_0"</td>
 * <td>ball_0.x</td>
 * <td>無し</td>
 * </tr>
 * <tr>
 * <td>"M,ball_1"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x</td>
 * </tr>
 * <tr>
 * <td>"M,ball_2"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x, ball_2.x</td>
 * </tr>
 * <tr>
 * <td>"M,ball_6"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x, ball_2.x, ball_3.x,・・・ball_6.x</td>
 * </tr>
 * </table>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MorphMeshModel : public Model {
    friend class ModelManager;

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
    struct VERTEX_PRIMARY : public Model::VERTEX_POS_NOMAL {
        DWORD color;      // 頂点の色（現在未使用）
        float tu, tv;     // テクスチャ座標
    };

    /** モーフターゲットメッシュの頂点フォーマット定義 */
    struct VERTEX_MORPH : public Model::VERTEX_POS_NOMAL {
    };

    /** モーフターゲット数 */
    int _morph_target_num;
    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** 頂点バッファ（プライマリ） */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer_primary;
    /** 頂点バッファの配列（要素数＝モーフターゲット数） */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9_morph;

    /** インデックスバッファ（プライマリのみ） */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;

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
    UINT _material_list_grp_num;

    /** 頂点バッファの写しコピーの頂点配列（プライマリ） */
    VERTEX_PRIMARY* _paVtxBuffer_data_primary;
    /** 頂点バッファの写しコピーの頂点配列のモーフターゲット数配列 */
    VERTEX_MORPH**  _papaVtxBuffer_data_morph;
    /** インデックスバッファの写しコピー（プライマリのみ） */
    bool _is_65535;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

    /** Paulさんモデル（要素数＝プライマリ＋モーフターゲット数） */
    Frm::Model3D** _papModel3D;
    /** Paulさんメッシュ（要素数＝プライマリ＋モーフターゲット数） */
    Frm::Mesh** _papMeshesFront;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id モデル定義の識別名
     */
    MorphMeshModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~MorphMeshModel(); //デストラクタ
};

}
#endif /*GGAF_DX_MORPHMESHMODEL_H_*/
