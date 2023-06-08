#ifndef GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#define GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/Config.h"

namespace GgafDx {

/**
 * �����p�`�^���X�v���C�g�A�N�^�[ .
 * �|���S���Ƀe�N�X�`����\��t����<BR>
 * �����[���X�v���C�g�̃A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteActor : public FigureActor {

public:
    /** [r]���f������ */
    RegularPolygonSpriteModel* _pRegularPolygonSpriteModel;
    /** [r]�G�t�F�N�g���� */
    RegularPolygonSpriteEffect* const _pRegularPolygonSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

    /** �������`�悷�邩 */
    int _draw_fan_num;
    /** ���p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu */
    angle _circumference_begin_position;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".rsprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    RegularPolygonSpriteActor(const char* prm_name,
                              const char* prm_model,
                              const char* prm_effect_id,
                              const char* prm_technique,
                              CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

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

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~RegularPolygonSpriteActor();

};

}
#endif /*GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_*/
