#ifndef GGAFLIB_FIXEDFONTSPRITEACTOR_H_
#define GGAFLIB_FIXEDFONTSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dxcore/actor/GgafDxMassSpriteActor.h"
#include "interface/IFixedFont.hpp"

namespace GgafLib {

/**
 * 固定幅文字表示 .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FixedFontSpriteActor : public GgafDxCore::GgafDxMassSpriteActor , public IFixedFont<FixedFontSpriteActor> {

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float local_x, local_y;     // : TEXCOORD5  ローカル座標オフセット
        float offset_u, offset_v;   // : TEXCOORD6  テクスチャオフセット
        float r, g, b, a;           // : TEXCOORD7  マテリアルカラー
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);
public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;
    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;
    virtual void setAlign(GgafDxAlign prm_align) override;
    virtual void setValign(GgafDxValign prm_valign) override;
public:
    FixedFontSpriteActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual ~FixedFontSpriteActor();

};

}
#endif /*GGAFLIB_FIXEDFONTSPRITEACTOR_H_*/
