#ifndef GGAFDXCORE_GGAFDXMORPHER_H_
#define GGAFDXCORE_GGAFDXMORPHER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

template<class T>
class GgafDxMorpherAssistantA;

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
template<class T>
class GgafDxMorpher : public GgafCore::GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) > {

private:
    /** [r]���[�t�@�[�̏���A */
    GgafDxMorpherAssistantA<T>* _pAsstMv;

public:
    /** [r]�ΏۃA�N�^�[ */
    T* _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_pActor �K�pActor
     */
    explicit GgafDxMorpher(T* prm_pActor);

    /**
     * ���[�t�@�[�̏���A(�Ȃ߂炩���[�t)���擾 .
     * @return ���[�t�@�[�̏���A
     */
    GgafDxMorpherAssistantA<T>* asst();

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void behave(int s = 1, int n = MAX_MORPH_TARGET) override;

    virtual ~GgafDxMorpher();
};

template<class T>
GgafDxMorpher<T>::GgafDxMorpher(T* prm_pActor) : GgafCore::GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >(),
_pActor(prm_pActor) {
    _pAsstMv = nullptr;
    setRange(0.0f, 1.0f);
}

template<class T>
GgafDxMorpherAssistantA<T>* GgafDxMorpher<T>::asst() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW GgafDxMorpherAssistantA<T>(this);
}

template<class T>
void GgafDxMorpher<T>::reset() {
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::reset();
    setRange(0.0f, 1.0f);
}

template<class T>
float GgafDxMorpher<T>::getValue(int idx) {
    return _pActor->_weight[idx];
}

template<class T>
void GgafDxMorpher<T>::setValue(int idx, float value) {
    _pActor->_weight[idx] = value;
}

template<class T>
void GgafDxMorpher<T>::behave(int s, int n) {
    if (_pAsstMv) {
        _pAsstMv->behave();
    }
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::behave(1, _pActor->_morph_target_num);
}

template<class T>
GgafDxMorpher<T>::~GgafDxMorpher() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
}


}
#endif /*GGAFDXCORE_GGAFDXMORPHER_H_*/

