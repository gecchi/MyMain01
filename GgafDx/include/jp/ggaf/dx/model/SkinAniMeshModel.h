#ifndef GGAF_DX_SKINANIMESHMODEL_H_
#define GGAF_DX_SKINANIMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
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
        float bone_combi_index;      // psizeではなくてはなくてボーンコンビネーションのインデックス。paBoneCombination[n] の n
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標

        float infl_weight[4];     // 頂点重み(TODO:４でいいの？)
        byte  infl_bone_idx[4];
    };
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

//    struct BONE_CONBI_GRP {
//        DWORD bone_combi_index;
//
//
//        int infl_bone_idx_num;
//
//        float infl_weight[4];
//        byte  infl_bone_idx[4];
//    };
//    std::vector<BONE_CONBI_INFO> _vec_bone_combi_info;


    SkinAniMeshModel::VERTEX* _paVtxBuffer_data;
    WORD* _paIndexBuffer_data;
    /** インデックスバッファ番号に対応する頂点バッファのフレームメッシュ番号 */
    int* _paIndexBuffer_bone_combi_index;
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


    std::vector<DWORD> _infl_bone_idx_order;
    std::map<DWORD, DWORD> _map_infl_bone_idx_to_order;

    /** 総アニメーションセット数 */
    UINT _num_animation_set;
    /** AnimationSet から、AnimationSetインデックスが取得できるマップ */
    std::map<ID3DXAnimationSet*, UINT> _mapAnimationSet_AniSetindex;
    /** アニメーションセットインデックスから、AnimationのターゲットのBoneFrame の Nameの配列が取得できるマップ */
    std::map<UINT, std::vector<LPCSTR>> _mapAnimationSetIndex_AnimationTargetBoneFrameNames;
    /** [アニメーションセットインデックス][フレームインデックス] で アニメーションセットのアニメーション対象のフレームであるかどうかが返る */
    bool** _papaBool_AnimationSetIndex_BoneFrameIndex_is_act;

    int _anim_ticks_per_second;
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

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

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
