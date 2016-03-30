#ifndef GGAFLIB_FIXEDFONTSPRITEACTOR_H_
#define GGAFLIB_FIXEDFONTSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dxcore/actor/GgafDxMassSpriteActor.h"
#include "interface/IFixedFont.hpp"

namespace GgafLib {

/**
 * �Œ蕝�����\�� .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FixedFontSpriteActor : public GgafDxCore::GgafDxMassSpriteActor , public IFixedFont<FixedFontSpriteActor> {

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float local_x, local_y;     // : TEXCOORD5  ���[�J�����W�I�t�Z�b�g
        float offset_u, offset_v;   // : TEXCOORD6  �e�N�X�`���I�t�Z�b�g
        float r, g, b, a;           // : TEXCOORD7  �}�e���A���J���[
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);
public:
    /** �Փ˔���x���I�u�W�F�N�g */
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
