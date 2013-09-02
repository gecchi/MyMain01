#ifndef GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_
#define GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

//注意：このクラスは現在未使用です。削除予定。
//     固定機能パイプライン時に頂点書き換えのため作成したが、
//     現在は全てプログラマブルシェーダーであるため、もう使わない。
/**
 * メッシュアクター.
 * GgafDxDrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * GgafDxD3DXMeshActor との違いは、頂点バッファに直接アクセスをことに考慮して、<BR>
 * D3DXMESH_DYNAMIC オプションを使用しているところだけです。<BR>
 * 頂点をロックする場合はGgafDxD3DXMeshActorではなく、こちらを継承してください。<BR>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class GgafDxDynaD3DXMeshActor : public GgafDxDrawableActor {

public:
    static DWORD FVF;
    GgafDxD3DXMeshModel* _pD3DXMeshModel;
    /** エフェクト資源 */
    GgafDxMeshEffect* _pMeshEffect;

public:
    GgafDxDynaD3DXMeshActor(const char* prm_name,
                             const char* prm_model_id,
                             const char* prm_effect_id,
                             const char* prm_technique,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual ~GgafDxDynaD3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_*/
