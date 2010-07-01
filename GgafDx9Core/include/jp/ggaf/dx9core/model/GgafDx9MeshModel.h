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
 *  ("Mesh"や"TextureFilename"等）は ハードコーディングされている。予測しない複雑なXファイルはまず読めない。<BR>
 * ・勝手に共有頂点の法線を平均化する <BR>
 * <BR>
 * 「その他注意点」<BR>
 * 頂点数を保証するため、法線が足りなくなってしまう場合がある。そこで共有頂点の法線は独自計算で平均化を行うことにしている。<BR>
 * もしエッジをクッキリ出したい場合は、Xファイル側で最初からちゃんと立方体ならば頂点を32個書けばよい。<BR>
 * また、法線の無いXファイルでも頂点インデックスから自動で法線を計算し生成する。<BR>
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

//「経緯メモ（というかグチ）」
//D3DXLoadMeshFromX で読み込むと思った通りの頂点数にならない。増えたり場合によっては減ったりするのである。
//例えば三角形ポリゴンでの立方体の場合、頂点は8個、面は12個（よって頂点インデックス12）、法線ベクトルも12個（よって法線インデックス12) となるが、
//このようなXファイルを作って D3DXLoadMeshFromX で読み込むと、勝手に頂点数が増えてしまうことで悩んでいた。
//これは、DirectXは頂点に法線を持つため、頂点が8個では法線が足りなくなってしまうためで、
//親切にも D3DXLoadMeshFromX 内部では、面と面の陰影をつけるため（エッジをクッキリ見せるため）に法線が頂点より優先されて、
//頂点の隣接する面の数（法線数）分、頂点を増やす、という処理が内部で行われるのであろう。立方体の場合は頂点が24個になってしまう。
//しかし、シェーダーでのモーフ時や、複数オブジェクトをDrawIndexedPrimitiveでわけて表示する時等、
//勝手に頂点の数が変わってしまうのは致命的であることが解るようになった。
//「Xファイルから、思った通りの頂点数で頂点バッファを作りたい」と考え試行錯誤した。
//D3DXLoadMeshFromX の頂点が増えるロジック（頂点分割や最適化）の解説はあれど、完全な仕様は公開されていない（と思う）。
//D3DXLoadMeshFromX のソースコードさえあれば全て解決するのだが、これも公開されて無い。
//試行錯誤している間に、DirectX10からは D3DXLoadMeshFromX が無くなるという新事実も知ってしまう。
//そんなわけで、内部で何やってるか90%ぐらい理解できるが、完璧にはわからない D3DXLoadMeshFromX はやっぱり使えない事になり、
//シェーダーを使うには独自にXファイルを読み込むしかないのか・・・めんどくさいなぁ、という結論に行きついた。
//てか、むしろXファイルじゃなくてもいいし、FBXとか良さそうなどと考えたが、D3DXLoadMeshFromX が使えないと決断するまでの期間が
//非常に長かったお陰で、Xファイルマスターになっていた。ということで、せっかくなのでXファイルを無理やり読むことにした。
//とりあえず、メタセコイア、3DSMAXのエクスポートするXファイル形式の静的モデルが読み込めれば良い、という設計で本クラスを作成。
//そして Paul さんのサンプルコードを発見する。
//「Loading and displaying .X files without DirectX」だと！。なんてドンピシャなトピックなんだ。というわけで流用させていただいた。
//しかしこのサンプル、結構バグが潜んでいて大変だった。でも０から作るよりは遥かにマシで、勉強にもなったので良しとしよう。
//このあたりの事は、他の人達はいったいどうやってるのだろうか・・・・


