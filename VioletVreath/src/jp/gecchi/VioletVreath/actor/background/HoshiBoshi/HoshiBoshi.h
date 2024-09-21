#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/dx/actor/PointSpriteActor.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

//#define RENDER_DEPTH_INDEX_HOSHIBOSHI (RENDER_DEPTH_INDEX_WORLDBOUND-1)

/**
 * ���X�|�C���g�X�v���C�g��� .
 * ���X�̒��_(�X�v���C�g)���W�Q�́AXYZ�����W -1.0�`1.0 �͈͓��ɏW�񂵂č쐬����Ă��邱�Ƃ��O��B<BR>
 * X���AY���AZ���ړ������Ă��A���X�̒��_(�X�v���C�g)���W�̓��[�e�[�g�����A�X�N���[�����Ă��悤�Ɍ�������ʂ��o��<br>
 * �܂��A��A�N�^�[(���@��)�̎���Ő��������炩�ɔ�\��������ʂ��o���B<br>
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDx::PointSpriteActor {

public:
    float far_rate_;

    coord space_distance_;

    GgafDx::GeometricActor* pCriteria_;

    static coord CAM_ZF_;

public:
    HoshiBoshi(const char* prm_name, const char* prm_model);

    static bool initStatic(HoshiBoshi* prm_pHoshiBoshi);

    /**
     * ���X�̍L����̊g��{����ݒ� .
     * ���X��DIRECTX����-1.0�`1.0�i-10px�`10px)�Ɏ��܂��Ă���O��ŁA
     * 1.0��ݒ肷��ƁA���݂̃J�������猩����ŉ��̋���(zf) ���g�p���A -zf �` zf ����ӂ̒����Ƃ��闧���̂ɁA
     * ���f���̐��X�̒��_(�X�v���C�g)���W�Q�̍��W�͈�(XYZ�����W -1.0�`1.0�j�ƈ�v������B
     * @param prm_far_rate �L����̊g��{��
     */
    void setFarRate(float prm_far_rate);

    inline float getFarRate() {
        return far_rate_;
    }
    /**
     * ��A�N�^�[��ݒ� .
     * �ݒ肳�ꂽ�A�N�^�[�̎���́A���X�͊��炩�ɔ�\���i�A���t�@�œ����j�ƂȂ�B
     * @param prm_pCriteria ��A�N�^�[
     */
    void setCriteriaActor(GgafDx::GeometricActor* prm_pCriteria);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual int isOutOfView() override;

    virtual bool isOutOfSpacetime() const override;



    virtual ~HoshiBoshi();



    static void setWorldMatrix_HoshiBoshi(const GgafDx::GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI_H_*/

