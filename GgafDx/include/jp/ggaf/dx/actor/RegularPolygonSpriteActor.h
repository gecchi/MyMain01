#ifndef GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#define GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * �����p�`�^���X�v���C�g�A�N�^�[ .
 * FigureActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteActor : public FigureActor {

public:
    /** [r]���f������ */
    RegularPolygonSpriteModel* const _pRegularPolygonSpriteModel;
    /** [r]�G�t�F�N�g���� */
    RegularPolygonSpriteEffect* const _pRegularPolygonSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

    float _far_rate;

    Align _align;

    Valign _valign;
    /** �������`�悷�邩 */
    int _draw_fan_num;
    /** ���p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu */
    angle _circumference_begin_position;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    RegularPolygonSpriteActor(const char* prm_name,
                              const char* prm_model,
                              const char* prm_effect_id,
                              const char* prm_technique,
                              Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~RegularPolygonSpriteActor();

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

//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    /**
     * �`�悷��FAN(��^)�̖������擾
     * @return �`�悷��FAN(��^)�̖���
     */
    int getDrawFanNum() {
        return _draw_fan_num;
    }

    /**
     * �`�悷��FAN(��^)�̖������w�肷�� .
     * @param prm_draw_fan_num �`�悷��FAN(��^)�̖���
     */
    void setDrawFanNum(int prm_draw_fan_num) {
        _draw_fan_num = prm_draw_fan_num;
    }

    /**
     * ���p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu��ݒ肷�� .
     * @param prm_ang �ŏ��̒��_�̊p�x�ʒu
     */
    void setBeginAngPos(angle prm_ang) {
        _circumference_begin_position = prm_ang;
    }

    /**
     * ���݂̑��p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu���擾
     * @return �ŏ��̒��_�̊p�x�ʒu
     */
    angle getBeginAngPos() {
        return _circumference_begin_position;
    }
};

}
#endif /*GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_*/
