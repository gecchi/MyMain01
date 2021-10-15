#ifndef GGAF_DX_TEXTUREBLINKER_H_
#define GGAF_DX_TEXTUREBLINKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/TransitionValue.hpp"

namespace GgafDx {

/**
 * ����J���[�_�Ŏx���N���X.
 * Model �̃����o�� _power_blink <BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �ŏI�I�Ƀs�N�Z���V�F�[�_�[�ŐF(float4)�ɏ悸��l�ƂȂ�B
 * �F���x 1.0 �͐F���x�����A
 * �F���x 2.0 �͐F���x�Q�{�B���邭�Ȃ�B
 * �F���x 0.5 �͐F���x1/�Q�{�B�Â��Ȃ�B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class TextureBlinker : public GgafCore::TransitionValue<float, 1 > {

public:
    /** �ΏۃA�N�^�[ */
    Model* const _pModel;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pModel  �K�p�Ώۂ�Model
     */
    TextureBlinker(Model* prm_pModel);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~TextureBlinker();
};

}
#endif /*GGAF_DX_TEXTUREBLINKER_H_*/

