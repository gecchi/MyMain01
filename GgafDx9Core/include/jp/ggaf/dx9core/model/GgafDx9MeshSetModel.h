#ifndef GGAFDX9MESHSETMODEL_H_
#define GGAFDX9MESHSETMODEL_H_
namespace GgafDx9Core {

/**
 * メッシュモデルクラス(GgafDx9MeshActor用) .
 * GgafDx9MeshSetModel は独自にXファイルからモデルデータを読み込み、<BR>
 * オブジェクトを描画する機能を持った静的モデル用のクラスです。 <BR>
 * 読み込み時、モデルの頂点バッファを、複数個コピーして連結し、一つの頂点バッファとしてセットします。<BR>
 * 複数のオブジェクトを1回で描画し、高速化を目指すクラス。 <BR>
 * 編隊を組む敵や、弾、などに使用することを想定する。 <BR>
 * ＜長所＞  <BR>
 * ・GgafDx9MeshModel の長所と同じ長所。
 * ・複数オブジェクトを描画する場合は、GgafDx9MeshModel よりさらに高速描画。  <BR>
 * ＜短所＞  <BR>
 * ・GgafDx9MeshModel の短所と同じ短所。
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
class GgafDx9MeshSetModel : public GgafDx9Model {
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
        float x, y, z;    // 頂点座標
        float nx, ny, nz; // 法線
        float index;      // psizeではなくてはなくて頂点番号を埋め込む。シェーダー側で何セット目かを判断するために使用。
        DWORD color;      // 頂点の色（現在未使用）
        float tu, tv;     // テクスチャ座標

    };

    /** 前回表示の同時描画したセット数（キャラクタ数）*/
    static int _draw_set_num_LastDraw;
    /** 最大同時描画セット数（キャラクタ数）、現在は16キャラ同時描画可能 */
    int _set_num;

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ（８キャラ分） */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** インデックスバッファ（８キャラ分） */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;


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
    UINT* _pa_nMaterialListGrp;

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
    GgafDx9MeshSetModel(char* prm_model_name);

public:

    /**
     * GgafDx9MeshSetModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9MeshSetActor
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
    virtual ~GgafDx9MeshSetModel(); //デストラクタ
};

}
#endif /*GGAFDX9MESHSETMODEL_H_*/
