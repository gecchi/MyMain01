#ifndef GGAFDX9MORPHTWOMESHMODEL_H_
#define GGAFDX9MORPHTWOMESHMODEL_H_
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
 * GgafDx9MorphTwoMeshModel用のモデルクラス.
 * GgafDx9MorphTwoMeshModel は D3DXLoadMeshFromX を使用せず、Xファイルからのモデルデータを保持、描画するクラスです。<BR>
 * <B>＜留意＞</B><BR>
 * ・アニメーションは読み込まれません。静的モデルです。(TODO:いつかスキンメッシュもする)<BR>
 * ・Faceは、3角形しか駄目です。（D3DXLoadMeshFromX は 3角形 or 4角形をサポート）<BR>
 * ・UV座標について、頂点数と一致しなくても、とりあえず順番に設定する。データーが無いUV座標は(0,0)に設定される。<BR>
 * ・共有頂点法線は、独自計算で平均化される。
 *   計算方法は、共有頂点から伸びる各Faceの「成す角」／「全Faceの成す角合計の」によって法線の掛ける割合が決まる。<BR>
 * ・GgafDx9MorphTwoMeshModelは並べ替えによるインデックスの最適化しないを行なわない。行なわないのが売りでもある。<BR>
 *   そのため、描画時は、Xファイルから読み込んだマテリアルリストの順番通りに描画する。<BR>
 *   Xファイルのマテリアルリストのバラけ具合によっては、D3DXLoadMeshFromX よりパフォーマンスが落ちるやもしれない。<BR>
 *   例えば、Xファイルのマテリアルリストが {0,0,1,1,2,0,1} な場合、マテリアル数が3つでも、描画は5回実行することになる。<BR>
 * ・void GgafDx9ModelManager::restoreMeshModel(GgafDx9MorphTwoMeshModel* prm_pPrimModel) で実際の設定を行なっています。<BR>
 * <B>＜使い所＞</B><BR>
 * ・単純な分、基本的に D3DXLoadMeshFromX → drawSubset(n) より描画は高速。<BR>
 * ・ロジックで頂点をいじりたい場合等、D3DXLoadMeshFromX により最適化されたかもしれない ID3DXMesh から、
 *   所望の頂点を割り出すのがしんどい場合。<BR>
 * ・不完全と解っているXファイルを、あえて読みたい場合。（データローダー的な意味で使う場合）<BR>
 */
class GgafDx9MorphTwoMeshModel : public GgafDx9Model {
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
        DWORD color; // 頂点の色
        float tu, tv; // テクスチャ座標
    };


    /** 頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pIDirect3DVertexDeclaration9;

    /** 頂点バッファ（２個） */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9;
    /** インデックスバッファ（共有・１つ目優先） */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** マテリアル配列（共有・１つ目優先） */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** テクスチャ配列(インスタンスはテクスチャ毎、モデルとは別管理。共有・１つ目優先） */
    GgafDx9TextureConnection** _papTextureCon;

    UINT _size_vertecs;
    /** 1頂点のサイズ */
    UINT _size_vertec_unit;
    /** 1頂点のサイズ */
    DWORD _dwNumMaterials;

    /** 描画時パラメーター（共有・１つ目優先） */
    INDEXPARAM* _paIndexParam;

    UINT _nMaterialListGrp;

    /** 頂点バッファの写しコピー（２個） */
    VERTEX** _papaVtxBuffer_org;
    /** インデックスバッファの写しコピー（共有・１つ目優先） */
    WORD* _paIdxBuffer_org;

    /** Paulさんモデル（２個） */
    Frm::Model3D** _papModel3D;
    /** Paulさんメッシュ（２個） */
    Frm::Mesh** _papMeshesFront;




    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9MorphTwoMeshModel(char* prm_model_name);

public:

    /**
     * GgafDx9MorphTwoMeshModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9MorphTwoMeshModel
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
    virtual ~GgafDx9MorphTwoMeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9MORPHTWOMESHMODEL_H_*/
