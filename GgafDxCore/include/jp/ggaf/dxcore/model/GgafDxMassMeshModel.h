#ifndef GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"


#define MAX_INSTACE 256
namespace GgafDxCore {

/**
 * Massメッシュモデルクラス(GgafDxMeshActor用) .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:

    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標
    };

    class VERTEX_instancedata {
    public:
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float r, g, b, a;           // : TEXCOORD5  マテリアルカラー
    };

    /** 頂点のFVF */
//    static DWORD FVF;
    /** 頂点バッファ（モデル） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** 頂点バッファ（インスタンス：ワールド変換行列情報、マテリアルカラー情報） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pIDirect3DVertexDeclaration9;

    /** １頂点のサイズ（モデル） */
    UINT _size_vertex_unit_model;
    /** １頂点のサイズ（インスタンス） */
    UINT _size_vertex_unit_instacedata;
    /** １モデル頂点サイズ計 */
    UINT _size_vertices_model;
    /** モデル頂点数 */
    UINT _nVertices;
    /** モデル面の数 */
    UINT _nFaces;

    /** マテリアルリストの連続で同一のマテリアル番号の塊（グループ）が幾つあるか */
    UINT* _paUint_material_list_grp_num;

    VERTEX_model* _paVtxBuffer_org_model;

    VERTEX_instancedata _aInstancedata[MAX_INSTACE];

    WORD* _paIdxBuffer_org;

    /** Paulさんモデル */
    Frm::Model3D* _pModel3D;
    /** Paulさんメッシュ */
    Frm::Mesh* _pMeshesFront;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
