#ifndef GGAFDXCORE_GGAFDXMORPHER_H_
#define GGAFDXCORE_GGAFDXMORPHER_H_
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * ���[�t�B���O�x���N���X .
 * GgafDxMorphMeshActor �̃����o��<BR>
 * �d�� _weight[] <BR>
 * ���ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 * �� _weight[] �́A[0]�͖��g�p�A[1]�`[n]�����[�t�^�[�Q�b�g1�`n�̏d�� <BR>
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker �����ʉ�����B
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDxMorpher : public GgafCore::GgafValueTransitioner<float, (MAX_MORPH_TARGET+1) > {

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxMorphMeshActor* const _pActor;

    GgafDxMorpherHelperA* _pHlprA;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor);

    GgafDxMorpherHelperA* hlprA();

    void reset() override;
    float getValue(int idx) override;
    void setValue(int idx, float value) override;

    void behave(int s = 0, int n = (MAX_MORPH_TARGET+1)) override;

    virtual ~GgafDxMorpher();
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHER_H_*/

