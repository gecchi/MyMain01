#ifndef GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_
#define GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"

namespace GgafDxCore {

/**
 * GgafDxD3DXActor用モデルクラス.(未使用、自前のアニメーションフレームで解決。addSubGroupAsFk()で事足りる)
 * GgafDxD3DXAniMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み設定する。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    GgafDxAllocHierarchyWorldFrame* _pAH;
    D3DXFRAME_WORLD* _pFR;
    ID3DXAnimationController* _pAcBase;
    int _anim_ticks_per_second;
    /** 60フレーム(1秒)で1ループする場合の1フレーム辺りの時間 */
//    double _advance_time_per_frame0;//60フレーム(1秒)で1ループすることを標準設定とする。

    GgafDxWorldMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromXのオプション */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @return
     */
    GgafDxD3DXAniMeshModel(char* prm_model);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

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
     * deleteするのはGgafDxD3DXAniMeshModelManagerである<BR>
     */
    virtual ~GgafDxD3DXAniMeshModel(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_*/
