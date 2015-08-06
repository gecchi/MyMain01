#ifndef GGAFDXCORE_GGAFDXD3DXMESHACTOR_H_
#define GGAFDXCORE_GGAFDXD3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * DirectXメッシュアクター.
 * GgafDxFigureActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXMeshActor : public GgafDxFigureActor {

public:
    static DWORD FVF;
    /** [r]モデル */
    GgafDxD3DXMeshModel* _pD3DXMeshModel;
    /** [r]エフェクト資源 */
    GgafDxMeshEffect* _pMeshEffect;

public:
    GgafDxD3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    /**
     * GgafDxD3DXMeshActorを描画 .
     */
    virtual void processDraw() override;

    virtual ~GgafDxD3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXD3DXMESHACTOR_H_*/
