#ifndef GGAF_DX_SKINANIMESHMODEL_H_
#define GGAF_DX_SKINANIMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。appendGroupChildAsFk()で事足りる)
 * SkinAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class SkinAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** 頂点のFVF */
    struct VERTEX : public Model::VERTEX_3D_BASE {
//        float bone_combi_index;      // psizeではなくてはなくてボーンコンビネーションのインデックス。paBoneCombination[n] の n
        float bone_combi_grp_index;
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標

        float infl_weight[4];     // 頂点重み(TODO:４でいいの？)
        byte  infl_bone_id[4];     //ボーンID
        byte  infl_bone_id_order[4]; //ボーンIDの通し番号
    };
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    class BoneConbi {
    public:
        DWORD vertex_start;
        DWORD vertex_count;
        BoneConbi() {
            vertex_start = 0;
            vertex_count = 0;
        }
    };
    /** ボーンコンビネーション毎の情報。添え字はボーンコンビネーションインデックス */
    std::vector<BoneConbi> _vec_bone_combi_info;

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
//        D3DXMATRIX* _ap_draw_combined_matrix[8];
        BoneConbiGrp() {
            bone_combi_start_index = 0;
            bone_combi_count = 0;
            grp_vertex_start = 0;
            grp_vertex_start = 0;
        }
    };
    std::vector<BoneConbiGrp> _vec_bone_combi_grp_info;

    SkinAniMeshModel::VERTEX* _paVtxBuffer_data;
    WORD* _paIndexBuffer_data;
    /** インデックスバッファ番号に対応する頂点バッファのフレームメッシュ番号 */
//    int* _paIndexBuffer_bone_combi_index;
    /** インデックスバッファ番号に対応する頂点バッファの bone_combi_grp_index */
    int* _paIndexBuffer_bone_combi_grp_index;
    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** 頂点バッファ（全フレームのメッシュ分） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** インデックスバッファ（全フレームのメッシュ分）  */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
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

//    struct BoneCombinationGrp {
//        std::vector<DWORD> vecInflBoneId;
//
//
//    };
//    std::vector<BoneCombinationGrp> _vecBoneCombinationGrp;

    //要素番号はbone_id_order、値は bone_id の配列。bone_id_order から bone_idを得るのに使用
    //std::vector<DWORD> _vec_infl_bone_id_order;
    //bone_id から、bone_id_order を得るMAP
    //std::map<DWORD, DWORD> _map_infl_bone_id_to_order;
    /** 描画時の最終的な変換行列（通し時） */
    //D3DXMATRIX* _ap_draw_combined_matrix[SkinAniMeshModel_MAX_BONE_WORLD_MATRIX];
    /** 一回の描画でセットできる変換行列数 */
    int _draw_combined_matrix_set_num;

    /** 総アニメーションセット数 */
    UINT _num_animation_set;
    /** AnimationSet から、AnimationSetインデックスが取得できるマップ */
    std::map<ID3DXAnimationSet*, UINT> _mapAnimationSet_AniSetindex;
    /** アニメーションセットインデックスから、AnimationのターゲットのBoneFrame の Nameの配列が取得できるマップ */
    std::map<UINT, std::vector<LPCSTR>> _mapAnimationSetIndex_AnimationTargetBoneFrameNames;
    /** [アニメーションセットインデックス][フレームインデックス] で アニメーションセットのアニメーション対象のフレームであるかどうかが返る */
    bool** _papaBool_AnimationSetIndex_BoneFrameIndex_is_act;

//    int _anim_ticks_per_second;
    /** 60フレーム(1秒)で1ループする場合の1フレーム辺りの時間 */
//    double _advance_time_per_frame0;//60フレーム(1秒)で1ループすることを標準設定とする。

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @return
     */
    SkinAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

//    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** フレームを巡って情報取得 */
    void setFrameInfo(SkinAniMeshFrame* prm_pFrame);
    /** setFrameInfo(SkinAniMeshFrame*) で使用される、frame_indexの通し番号 */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはSkinAniMeshModelManagerである<BR>
     */
    virtual ~SkinAniMeshModel(); //デストラクタ

};

}
#endif /*GGAF_DX_SKINANIMESHMODEL_H_*/
