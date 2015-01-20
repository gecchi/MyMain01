#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

namespace VioletVreath {

/**
 * ���X�|�C���g�X�v���C�g��� .
 * ���X�̒��_(�X�v���C�g)���W�Q�́AXYZ�����W -1.0�`1.0 �͈͓��ɏW�񂵂č쐬����Ă��邱�Ƃ��O��B<BR>
 * X���AY���AZ���ړ������Ă��A���X�̒��_(�X�v���C�g)���W�̓��[�e�[�g�����A�X�N���[�����Ă��悤�Ɍ�������ʂ��o��<br>
 * �܂��A��A�N�^�[(���@��)�̎���Ő��������炩�ɔ�\��������ʂ��o���B<br>
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDxCore::GgafDxPointSpriteActor {

public:


    float far_rate_;
    coord space_distance_;
    GgafDxCore::GgafDxGeometricActor* pCriteria_;

    static D3DXHANDLE h_fX_MyShip_;
    static D3DXHANDLE h_fY_MyShip_;
    static D3DXHANDLE h_fZ_MyShip_;
    static D3DXHANDLE h_far_rate_;
    static coord CAM_ZF_;

    static bool is_init_;

public:
    HoshiBoshi(const char* prm_name, const char* prm_model_id);

    /**
     * ���X�̍L����̊g��{����ݒ� .
     * 1.0��ݒ肷��ƁA���݂̃J�������猩����͈�(XYZ�����W -zf �` zf)���A
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
    void setCriteriaActor(GgafDxCore::GgafDxGeometricActor* prm_pCriteria);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() const override;



    virtual ~HoshiBoshi();



    static void setWorldMatrix_HoshiBoshi(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI_H_*/

