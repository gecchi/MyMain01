#ifndef GGAFDXCORE_GGAFDXSCALER_H_
#define GGAFDXCORE_GGAFDXSCALER_H_
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

using GgafCore::GgafValueTransitioner;

namespace GgafDxCore {

/**
 * �g��k���x���N���X.
 * GgafDxGeometricActor �̃����o��<BR>
 * _sx , _sy, _sz  �E�E�E �A�N�^�[�̃X�P�[��<BR>
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
 * 2009/05/22 GgafDxKuroko ���番�������B
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker �����ʉ�����B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxScaler : public GgafValueTransitioner<scale, 3 > {

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxGeometricActor* const _pActor;
    scale* _apActorScale[3];
public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDxScaler(GgafDxGeometricActor* prm_pActor);

    virtual scale getValue(int idx) override;
    virtual void setValue(int idx, scale value) override;

    virtual ~GgafDxScaler();
};

}
#endif /*GGAFDXCORE_GGAFDXSCALER_H_*/

