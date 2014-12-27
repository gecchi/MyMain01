#ifndef GGAFDXCORE_GGAFDXSPRITESETACTOR_H_
#define GGAFDXCORE_GGAFDXSPRITESETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[.
 * GgafDxDrawableActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A���������`��ɍœK�����ꂽ�A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetActor : public GgafDxDrawableActor {
private:
    void setMaterialColor(float r, float g, float b) override {
        throwGgafCriticalException("GgafDxSpriteSetActor::setMaterialColor �͎g�p�s�ł��B(1)");
    }
    void setMaterialColor(const GgafCore::GgafRgb* prm_rgb) override {
        throwGgafCriticalException("GgafDxSpriteSetActor::setMaterialColor �͎g�p�s�ł��B(2)");
    }
    void resetMaterialColor() override {
        throwGgafCriticalException("GgafDxSpriteSetActor::resetMaterialColor �͎g�p�s�ł��B");
    }

public:
    /** [r]���f������ */
    GgafDxSpriteSetModel* const _pSpriteSetModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxSpriteSetEffect* const _pSpriteSetEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* const _pUvFlipper;

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
    GgafDxSpriteSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteSetActor();

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXSPRITESETACTOR_H_*/
