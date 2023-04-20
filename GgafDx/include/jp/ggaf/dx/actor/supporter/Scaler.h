#ifndef GGAF_DX_SCALER_H_
#define GGAF_DX_SCALER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

namespace GgafDx {

/**
 * �g��k���x���N���X.
 * GeometricActor �̃����o��<BR>
 * _sx, _sy, _sz  �E�E�E �A�N�^�[�̃X�P�[��<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �g��k��1.0�{�i�X�P�[�������j�́A�{�N���X�ł̃X�P�[���l1000�ɑ�������B
 * [���{��]     �� [�{�N���X�̃X�P�[���l]
 * ���{         �� 1000
 * 2.5�{�g��    �� 2500
 * �����̑傫�� �� 500
 * �k����80%    �� 800
 * �{�N���X�ł́A�X�P�[���ƃX�P�[�����O�Ƃ����P������̈Ӗ��Ŏg�p���Ă���ӏ�������B
 * �X�P�[���E�E�E���݁i�̃t���[���j�̊g��k����ԁA�X�P�[���l
 * �X�P�[�����O�E�E�E�t���[���Ԃ̊g��k����Ԃ̑J��
 * 2009/05/22 LocoVehicle ���番�������B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class Scaler : public GgafCore::ValueTransitioner<scale, 3 > {

public:
    /** [r]�ΏۃA�N�^�[ */
    GeometricActor* const _pActor;
    /** [r]�X�P�[���v���p�e�B�ւ̎Q�� */
    scale* _apActorScale[3];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    explicit Scaler(GeometricActor* prm_pActor);

    void reset() override;

    scale getValue(int idx) override;

    void setValue(int idx, scale value) override;

    virtual ~Scaler();
};

}
#endif /*GGAF_DX_SCALER_H_*/

