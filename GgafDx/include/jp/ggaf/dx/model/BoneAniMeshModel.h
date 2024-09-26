#ifndef GGAF_DX_BONEANIMESHMODEL_H_
#define GGAF_DX_BONEANIMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。appendChildAsFk()で事足りる)
 * BoneAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class BoneAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** 頂点のFVF */
    static DWORD FVF;
    struct VERTEX : public Model::VERTEX_POS_NOMAL {
        float index;      // psizeではなくてはなくて頂点番号として使用。何フレーム目かするために使用。
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標
    };
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    BoneAniMeshModel::VERTEX* _paVtxBuffer_data;
    D3DFORMAT _indexBuffer_fmt;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;
    /** インデックスバッファ番号に対応する頂点バッファのフレームメッシュ番号 */
    int* _paIndexBuffer_frame_no;
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
    /** BoneAniMeshFrame取り扱いAllocateHierarchyクラス */
    BoneAniMeshAllocHierarchy* _pAllocHierarchy;
    /** ワールド変換行列付きフレーム構造体のルート */
    BoneAniMeshFrame* _pFrameRoot;
    /** アニメーションコントローラ、Actor生成時にはこれが clone されてActorに保持されることになる */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot を巡ってフレームを直列化したもの、要素番号はフレームインデックスと呼称する  */
    std::vector<BoneAniMeshFrame*> _vecAllBoneFrame;
    /** _pFrameRoot を巡ってメッシュコンテナがある描画対象フレームを直列化したもの、要素番号はただの連番  */
    std::vector<BoneAniMeshFrame*> _vecDrawBoneFrame;


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
     * @param prm_model モデルの識別名。".modelx"を追加するとモデル定義ファイル名になる。
     * @return
     */
    BoneAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** フレームを巡って情報取得 */
    void setFrameInfo(BoneAniMeshFrame* prm_pFrame);
    /** setFrameInfo(BoneAniMeshFrame*) で使用される、frame_indexの通し番号 */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはBoneAniMeshModelManagerである<BR>
     */
    virtual ~BoneAniMeshModel();

};

}
#endif /*GGAF_DX_BONEANIMESHMODEL_H_*/
