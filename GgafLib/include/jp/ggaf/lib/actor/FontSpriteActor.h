#ifndef GGAF_LIB_FONTSPRITEACTOR_H_
#define GGAF_LIB_FONTSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/dx/actor/MassSpriteActor.h"
#include "interface/ICharacterChip.hpp"

namespace GgafLib {

/**
 * �����L�����N�^�X�v���C�g�\�� .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontSpriteActor : public GgafDx::MassSpriteActor , public ICharacterChip<FontSpriteActor, 256, 1024> {

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
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);
public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;
    Align _align;
    Valign _valign;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);
public:
    FontSpriteActor(const char* prm_name, const char* prm_model_id);

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

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual ~FontSpriteActor();

};

}
#endif /*GGAF_LIB_FIXEDFONTSPRITEACTOR_H_*/
