#ifndef GGAF_DX_SKINANIMESHMODEL_H_
#define GGAF_DX_SKINANIMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。appendChildAsFk()で事足りる)
 * SkinAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class SkinAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** 頂点のFVF */
    struct VERTEX : public Model::VERTEX_POS_NOMAL {
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標
        float infl_weight[4];     // 頂点重み(TODO:４でいいの？)
        byte  infl_bone_id_order[4]; //ボーンIDの通し番号
    };
    /**
     * 頂点バッファの補足情報 .
     */
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    /**
     * 一括描画単位のボーンコンビネーショングループ .
     */
    class BoneConbiGrp {
    public:
        /** グループの最初のボーンコンビネーションインデックス */
        int bone_combi_start_index;
        /** グループの bone_combi_start_index 空のボーンコンビネーションインデックス数 */
        int bone_combi_count;
        /** グループの頂点バッファ開始インデックス */
        DWORD grp_vertex_start;
        /** グループの grp_vertex_start からの頂点バッファ数 */
        DWORD grp_vertex_count;

        std::vector<DWORD> vec_infl_bone_id_order; //ユニークなvec_cb_idx_orderが挿入されていく
        std::vector<DWORD> vec_cb_idx_order;       //vec_infl_bone_id_order が挿入された時の

        //bone_id から、bone_id_order を得るMAP
        std::map<DWORD, DWORD> map_infl_bone_id_to_order;
        /** 描画時の最終的な変換行列（通し時） */
        BoneConbiGrp() {
            bone_combi_start_index = 0;
            bone_combi_count = 0;
            grp_vertex_start = 0;
            grp_vertex_count = 0;
        }
    };
    std::vector<BoneConbiGrp> _vec_bone_combi_grp_info;

    SkinAniMeshModel::VERTEX* _paVtxBuffer_data;
    D3DFORMAT _indexBuffer_fmt;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** 頂点バッファ（全フレームのメッシュ分） */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** インデックスバッファ（全フレームのメッシュ分）  */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** モデル頂点数 */
    UINT _nVertices;
    /** モデル面の数 */
    UINT _nFaces;
    /** １頂点のサイズ */
    UINT _size_vertex_unit;
    /** モデル頂点サイズ計 */
    UINT _size_vertices;
    int _index_param_num;
    INDEXPARAM* _paIndexParam;
    /** SkinAniMeshFrame取り扱いAllocateHierarchyクラス */
    SkinAniMeshAllocHierarchy* _pAllocHierarchy;
    /** ワールド変換行列付きフレーム構造体のルート */
    SkinAniMeshFrame* _pFrameRoot;
    /** アニメーションコントローラ、Actor生成時にはこれが clone されてActorに保持されることになる */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot を巡ってフレームを直列化したもの、要素番号はフレームインデックスと呼称する  */
    std::vector<SkinAniMeshFrame*> _vecAllBoneFrame;
    /** _pFrameRoot を巡って描画対象があるフレームを直列化したもの、要素番号はただの連番  */
    std::vector<SkinAniMeshFrame*> _vecDrawBoneFrame;


    std::vector<SkinAniMeshFrame*> _vecBoneIdFrame;

    /** 一回の描画でセットできる変換行列数 */
    int _draw_combined_matrix_set_num;

    /** 総アニメーションセット数 */
    UINT _num_animation_set;
    /** AnimationSet から、AnimationSetインデックスが取得できるマップ */
    std::map<ID3DXAnimationSet*, UINT> _mapAnimationSet_AniSetindex;
    /** [アニメーションセットインデックス][フレームインデックス] で アニメーションセットのアニメーション対象のフレームであるかどうかが返る */
    bool** _papaBool_AnimationSetIndex_BoneFrameIndex_is_act;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".modelx"を追加するとモデル定義ファイル名になる。
     * @return
     */
    SkinAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    /** フレームを巡って情報取得 */
    void setFrameInfo(SkinAniMeshFrame* prm_pFrame);

    void setAnimationFrameIndex();

    /** setFrameInfo(SkinAniMeshFrame*) で使用される、frame_indexの通し番号 */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはSkinAniMeshModelManagerである<BR>
     */
    virtual ~SkinAniMeshModel();

};

}
#endif /*GGAF_DX_SKINANIMESHMODEL_H_*/
