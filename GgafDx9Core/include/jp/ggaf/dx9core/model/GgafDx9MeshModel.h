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
 * GgafDx9MeshActor用のモデルクラス.
 * GgafDx9MeshModel は D3DXLoadMeshFromX を使用せず、Xファイルからのモデルデータを保持、描画するクラスです。<BR>
 * <B>＜色々留意＞</B><BR>
 * ・アニメーションは読み込まれません。静的モデルです。<BR>
 * ・Face（面）は、3角形しか駄目です。（ちなみにD3DXLoadMeshFromX は 3角形 or 4角形をサポート）<BR>
 * ・UV座標について、頂点数と一致しなくても、とりあえず順番に設定する。データーが無いUV座標は(0,0)で埋まる。<BR>
 * ・共有頂点法線は、独自計算で平均化される（これがやりたかっただけかもしれない）。 計算方法は、
 *  「共有頂点から伸びる各Faceの成す角」／「共有頂点に接する全Faceの成す角合計」によって各Faceの法線の掛ける割合を決定、合算、正規化する。<BR>
 * ・GgafDx9MeshModelは並べ替えによるインデックスの最適化しないを行なわない。行なわないのが売りでもある。<BR>
 *   そのため、描画時は、Xファイルから読み込んだマテリアルリストの順番通りに描画する。マテリアルでグループしたXファイルは自分で作る。<BR>
 *   （※Xファイルのマテリアルリストのバラけ具合によっては、D3DXLoadMeshFromX よりパフォーマンスが落ちるやもしれない。<BR>
 *     例えば、Xファイルのマテリアルリストが {0,0,1,1,2,0,1} な場合、マテリアル数が3つでも、描画は5回実行することになる。）<BR>
 * ・void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pPrimModel) で実際の初期設定を行なっている。<BR>
 * <B>＜想定する使い所＞</B><BR>
 * ・単純な分、基本的に D3DXLoadMeshFromX → drawSubset(n) より描画は高速なはず。<BR>
 * ・ロジックで頂点をいじりたい場合等、 ID3DXMesh から所望の頂点を割り出すのがめんどくさい場合。<BR>
 * ・不完全と解っているXファイルを、あえて読みたい場合。<BR>
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
