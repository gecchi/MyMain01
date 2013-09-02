#ifndef GGAFDXCORE_GGAFDXSPRITEACTORD_H_
#define GGAFDXCORE_GGAFDXSPRITEACTORD_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDxGeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteActor : public GgafDxDrawableActor {

public:
    /** [r]���f������ */
    GgafDxSpriteModel* _pSpriteModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxSpriteEffect* _pSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;

    float _far_rate;

    GgafDxAlign _align;
    GgafDxValign _valign;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxSpriteActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteActor();

    /**
     * �����̍��W�ł������\�� .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_MIDDLE);
};

}
#endif /*GGAFDXCORE_GGAFDXSPRITEACTORD_H_*/
