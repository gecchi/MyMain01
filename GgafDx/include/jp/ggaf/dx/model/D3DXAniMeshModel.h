#ifndef GGAF_DX_D3DXANIMESHMODEL_H_
#define GGAF_DX_D3DXANIMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

#include "jp/ggaf/dx/util/WorldMatStack.h"

namespace GgafDx {

/**
 * D3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。appendGroupChildAsFk()で事足りる)
 * D3DXAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    AllocHierarchyWorldFrame* _pAllocHierarchy;
    FrameWorldMatrix* _pFrameRoot;
    ID3DXAnimationController* _pAniControllerBase;
    int _anim_ticks_per_second;
    /** 60フレーム(1秒)で1ループする場合の1フレーム辺りの時間 */
//    double _advance_time_per_frame0;//60フレーム(1秒)で1ループすることを標準設定とする。

//    WorldMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromXのオプション */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @return
     */
    D3DXAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    void getDrawFrameList(std::list<FrameWorldMatrix*>* pList, FrameWorldMatrix* frame);

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
     * deleteするのはD3DXAniMeshModelManagerである<BR>
     */
    virtual ~D3DXAniMeshModel(); //デストラクタ

};

}
#endif /*GGAF_DX_D3DXANIMESHMODEL_H_*/
