#ifndef GGAF_DX_ANIMESHMODELL_H_
#define GGAF_DX_ANIMESHMODELL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。appendGroupChildAsFk()で事足りる)
 * AniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class AniMeshModel : public Model {
    friend class ModelManager;

public:
    /** 頂点のFVF */
    static DWORD FVF;
    struct VERTEX : public Model::VERTEX_3D_BASE {
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

    AniMeshModel::VERTEX* _paVtxBuffer_data;
    WORD* _paIndexBuffer_data;
    /** インデックスバッファ番号に対応する頂点バッファのフレームメッシュ番号 */
    int* _paIndexBuffer_frame_no;
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
    /** FrameWorldMatrix取り扱いAllocateHierarchyクラス */
    AllocHierarchyWorldFrame* _pAllocHierarchy;
    /** ワールド変換行列付きフレーム構造体のルート */
    FrameWorldMatrix* _pFrameRoot;
    /** アニメーションコントローラ、Actor生成時にはこれが clone されてActorに保持されることになる */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot を巡ってフレームを直列化したもの、要素番号はフレームインデックスと呼称する  */
    std::vector<FrameWorldMatrix*> _vecAllBoneFrame;
    /** _pFrameRoot を巡ってメッシュコンテナがある描画対象フレームを直列化したもの、要素番号はただの連番  */
    std::vector<FrameWorldMatrix*> _vecDrawBoneFrame;


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
    AniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** フレームを巡って情報取得 */
    void setFrameInfo(FrameWorldMatrix* prm_pFrame);
    /** setFrameInfo(FrameWorldMatrix*) で使用される、frame_indexの通し番号 */
    UINT _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    void putMat(D3DXMATRIX* pMat) {
        _TRACE_( pMat->_11<<", "<< pMat->_12<<", "<< pMat->_13<<", "<< pMat->_14);
        _TRACE_( pMat->_21<<", "<< pMat->_22<<", "<< pMat->_23<<", "<< pMat->_24);
        _TRACE_( pMat->_31<<", "<< pMat->_32<<", "<< pMat->_33<<", "<< pMat->_34);
        _TRACE_( pMat->_41<<", "<< pMat->_42<<", "<< pMat->_43<<", "<< pMat->_44);
    };

    /**
     * デストラクタ<BR>
     * deleteするのはAniMeshModelManagerである<BR>
     */
    virtual ~AniMeshModel(); //デストラクタ

};

}
#endif /*GGAF_DX_ANIMESHMODELL_H_*/
