#ifndef GGAFDXCORE_GGAFDXMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

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
 * メッシュモデルクラス(GgafDxMeshActor用).
 * GgafDxMeshModel は独自にXファイルからモデルデータを読み込み、<BR>
 * オブジェクトを描画する機能を持った静的モデル用のクラスです。 <BR>
 * <b>＜長所＞</b>  <BR>
 * ・Xファイルの頂点数を保証。 <BR>
 * ・GgafDxD3DXMeshModel より読み込みが高速（templateとか見てない）。 <BR>
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
class GgafDxMeshModel : public GgafDxModel {
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

    struct VERTEX : public GgafDxModel::VERTEX_3D_BASE {
        DWORD color; // 頂点の色（現在未使用）
        float tu, tv; // テクスチャ座標
        float tan_x, tan_y, tan_z; //
        float bin_x, bin_y, bin_z;
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

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

    WORD* _paIndexBuffer_data;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMESHMODEL_H_*/

