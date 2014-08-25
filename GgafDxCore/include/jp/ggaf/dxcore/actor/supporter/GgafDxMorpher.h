#ifndef GGAFDXCORE_GGAFDXMORPHER_H_
#define GGAFDXCORE_GGAFDXMORPHER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * ���[�t�B���O�x���N���X .
 * GgafDxMorphMeshActor �̃����o��<BR>
 * �d�� _weight[] <BR>
 * ���ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 * �� _weight[] �́A[0]�͖��g�p�A[1]�`[n]�����[�t�^�[�Q�b�g1�`n�̏d�� <BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDxMorpher : public GgafCore::GgafValueTransitioner<float, (MAX_MORPH_TARGET+1) > {

private:
    /** [r]���[�t�@�[�̏���A */
    GgafDxMorpherAssistantA* _pAsstA;

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxMorphMeshActor* const _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_pActor �K�pActor
     */
    explicit GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor);

    /**
     * ���[�t�@�[�̏���A(�Ȃ߂炩���[�t)���擾 .
     * @return ���[�t�@�[�̏���A
     */
    GgafDxMorpherAssistantA* asst();

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void behave(int s = 1, int n = MAX_MORPH_TARGET) override;

    virtual ~GgafDxMorpher();
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHER_H_*/

