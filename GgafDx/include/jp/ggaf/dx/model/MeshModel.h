#ifndef GGAF_DX_MESHMODEL_H_
#define GGAF_DX_MESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

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
 * メッシュモデルクラス(MeshActor用).
 * MeshModel は独自にXファイルからモデルデータを読み込み、<BR>
 * オブジェクトを描画する機能を持った静的モデル用のクラスです。 <BR>
 * <b>＜長所＞</b>  <BR>
 * ・Xファイルの頂点数を保証。 <BR>
 * ・D3DXMeshModel より読み込みが高速（templateとか見てない）。 <BR>
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
class MeshModel : public Model {
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
        DWORD color; // 頂点の色（現在未使用）
        float tu, tv; // テクスチャ座標
        float tan_x, tan_y, tan_z; // 接ベクトル(u方向単位ベクトル、バンプマッピング時に使用) (ローカル座標系)
        float bin_x, bin_y, bin_z; // 従法線ベクトル(v方向単位ベクトル、バンプマッピング時に使用) (ローカル座標系)
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;

    /** モデル頂点数 */
    UINT _nVertices;
    /** モデル面の数 */
    UINT _nFaces;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** モデル頂点サイズ計 */
    UINT _size_vertices;


    INDEXPARAM* _paIndexParam;

    UINT _material_list_grp_num;

    VERTEX* _paVtxBuffer_data;

    bool _is_65535;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".modelx"を追加するとモデル定義ファイル名になる。
     */
    MeshModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;
//DEBUG
    void dispFrame(Frm::Bone* pBone, int dep = 0);

    /**
     * デストラクタ<BR>
     */
    virtual ~MeshModel();
};

}
#endif /*GGAF_DX_MESHMODEL_H_*/

