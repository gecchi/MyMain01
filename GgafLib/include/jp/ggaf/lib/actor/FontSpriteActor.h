#ifndef GGAF_LIB_FONTSPRITEACTOR_H_
#define GGAF_LIB_FONTSPRITEACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

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
    WorldCollisionChecker* _pWorldCollisionChecker;
    Align _align;
    Valign _valign;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);
public:
    FontSpriteActor(const char* prm_name, const char* prm_model);

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    /**
     * ���f���������P�������Ēǉ�����B .
     * ���߂Ė{���\�b�h�����s����ƁA�������X�g�ɕێ�����A���̃��f���������L���ɂȂ�܂��B
     * �Q��ڈȍ~�̎��s�́A�����������f��������������X�g�̖����ɒǉ����܂��B�i�L���ɂȂ�܂���j
     * @param prm_model ���f����`��
     */
    virtual void addModel(const char* prm_model) override;

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~FontSpriteActor();

};

}
#endif /*GGAF_LIB_FIXEDFONTSPRITEACTOR_H_*/
