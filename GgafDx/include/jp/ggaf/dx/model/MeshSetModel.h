#ifndef GGAF_DX_MESHSETMODEL_H_
#define GGAF_DX_MESHSETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * メッシュモデルクラス(MeshActor用) .
 * MeshSetModel は独自にXファイルからモデルデータを読み込み、<BR>
 * オブジェクトを描画する機能を持った静的モデル用のクラスです。 <BR>
 * 読み込み時、モデルの頂点バッファを、複数個コピーして連結し、一つの頂点バッファとしてセットします。<BR>
 * 同一モデルの複数のオブジェクトを1回で描画し、高速化を目指すクラス。 <BR>
 * 編隊を組む敵や、弾、などに使用することを想定する。 <BR>
 * ＜長所＞  <BR>
 * ・MeshModel の長所と同じ長所。
 * ・複数オブジェクトを描画する場合は、MeshModel よりさらに高速描画。  <BR>
 * ＜短所＞  <BR>
 * ・MeshModel の短所と同じ短所。
 * ・描画キャラ分の頂点のコピー連結して頂点バッファに持つため、1キャラクタの頂点数が、 65536/同時描画数 個<BR>
 *  を超えると駄目である。<BR>
 * ・さらに、マテリアルは1種類が望ましい。これは全体で1種類ではなく、<BR>
 *  各キャラごとにそれぞれマテリアル色が1種類しか割り当てれないという意味。しかし、テクスチャは全体で1種類しか駄目。<BR>
 *  ※複数マテリアルのXファイルを指定してもエラーにはならないが、複数マテリアルの場合、マテリアル毎にシェーダーのレジスタを更新
 *  （CommitChangesが発生）してしまうため、オブジェクトそれぞれ描画していることになり、やや高速化の意味が薄くなる。<BR>
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class MeshSetModel : public Model {
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

    struct VERTEX : public Model::VERTEX_POS_NOMAL {
        float index;      // psizeではなくてはなくて頂点番号として使用。シェーダー側で何セット目かを判断するために使用。
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ（ｎキャラ分） */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** インデックスバッファ（ｎキャラ分） */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;


    /** １頂点のサイズ */
    UINT _size_vertex_unit;
    /** 基本モデル（１キャラ分）頂点サイズ計 */
    UINT _size_vertices;
    /** 基本モデル（１キャラ分）頂点数 */
    UINT _nVertices;
    /** 基本モデル（１キャラ分）の面の数 */
    UINT _nFaces;

    INDEXPARAM** _papaIndexParam;

    /** マテリアルリストの連続で同一のマテリアル番号の塊（グループ）が幾つあるか */
    UINT* _paUint_material_list_grp_num;

    VERTEX* _paVtxBuffer_data;
    bool _is_65535;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

    /** Paulさんモデル */
    Frm::Model3D* _pModel3D;
    /** Paulさんメッシュ */
    Frm::Mesh* _pMeshesFront;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    MeshSetModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~MeshSetModel(); //デストラクタ
};

}
#endif /*GGAF_DX_MESHSETMODEL_H_*/
