#ifndef GGAFDX9MESHSETMODEL_H_
#define GGAFDX9MESHSETMODEL_H_
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
 * GgafDx9MeshSetActor用のモデルクラス.
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
    /** 最大同時描画セット数（キャラクタ数）、現在は８キャラ同時描画可能 */
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
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9MeshSetModel(); //デストラクタ
};

}
#endif /*GGAFDX9MESHSETMODEL_H_*/
