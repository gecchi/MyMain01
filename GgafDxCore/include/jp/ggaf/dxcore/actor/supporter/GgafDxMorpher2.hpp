#ifndef GGAFDXCORE_GGAFDXMORPHER2_H_
#define GGAFDXCORE_GGAFDXMORPHER2_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

template<class T>
class GgafDxMorpher2AssistantA;

/**
 * モーフィング支援クラス .
 * GgafDxMorphMeshActor のメンバの<BR>
 * 重み _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * 尚 _weight[] は、[0]は未使用、[1]～[n]がモーフターゲット1～nの重み <BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafDxMorpher2 : public GgafCore::GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) > {

private:
    /** [r]モーファーの助手A */
    GgafDxMorpher2AssistantA<T>* _pAsstMv;

public:
    /** [r]対象アクター */
    T* _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_pActor 適用Actor
     */
    explicit GgafDxMorpher2(T* prm_pActor);

    /**
     * モーファーの助手A(なめらかモーフ)を取得 .
     * @return モーファーの助手A
     */
    GgafDxMorpher2AssistantA<T>* asst();

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void behave(int s = 1, int n = MAX_MORPH_TARGET) override;

    virtual ~GgafDxMorpher2();
};

template<class T>
GgafDxMorpher2<T>::GgafDxMorpher2(T* prm_pActor) : GgafCore::GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >(),
_pActor(prm_pActor) {
    _pAsstMv = nullptr;
    setRange(0.0f, 1.0f);
}

template<class T>
GgafDxMorpher2AssistantA<T>* GgafDxMorpher2<T>::asst() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW GgafDxMorpher2AssistantA<T>(this);
}

template<class T>
void GgafDxMorpher2<T>::reset() {
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::reset();
    setRange(0.0f, 1.0f);
}

template<class T>
float GgafDxMorpher2<T>::getValue(int idx) {
    return _pActor->_weight[idx];
}

template<class T>
void GgafDxMorpher2<T>::setValue(int idx, float value) {
    _pActor->_weight[idx] = value;
}

template<class T>
void GgafDxMorpher2<T>::behave(int s, int n) {
    if (_pAsstMv) {
        _pAsstMv->behave();
    }
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::behave(1, _pActor->_morph_target_num);
}

template<class T>
GgafDxMorpher2<T>::~GgafDxMorpher2() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
}


}
#endif /*GGAFDXCORE_GGAFDXMORPHER2_H_*/

