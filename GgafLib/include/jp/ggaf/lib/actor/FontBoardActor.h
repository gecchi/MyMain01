#ifndef GGAFLIB_FONTBOARDACTOR_H_
#define GGAFLIB_FONTBOARDACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"
#include "interface/ICharacterChip.hpp"

namespace GgafLib {

/**
 * å≈íËïùï∂éöï\é¶ .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public GgafDxCore::GgafDxMassBoardActor , public ICharacterChip<FontBoardActor> {

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;         // : TEXCOORD1
        float offset_u, offset_v, alpha;   // : TEXCOORD2
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);
public:
    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;
    virtual void setAlign(GgafDxAlign prm_align) override;
    virtual void setValign(GgafDxValign prm_valign) override;
public:
    FontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~FontBoardActor();

};

}
#endif /*GGAFLIB_FONTBOARDACTOR_H_*/
