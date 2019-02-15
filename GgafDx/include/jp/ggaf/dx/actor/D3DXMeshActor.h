#ifndef GGAF_DX_D3DXMESHACTOR_H_
#define GGAF_DX_D3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * DirectXメッシュアクター.
 * FigureActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class D3DXMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** [r]モデル */
    D3DXMeshModel* _pD3DXMeshModel;
    /** [r]エフェクト資源 */
    MeshEffect* _pMeshEffect;

public:
    D3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         Checker* prm_pChecker);

    /**
     * D3DXMeshActorを描画 .
     */
    virtual void processDraw() override;

    virtual ~D3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_D3DXMESHACTOR_H_*/
