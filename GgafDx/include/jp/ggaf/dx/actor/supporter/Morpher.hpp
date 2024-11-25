#ifndef GGAF_DX_MORPHER_H_
#define GGAF_DX_MORPHER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

namespace GgafDx {

template<class T>
class MorpherAssistant;

/**
 * モーフィング支援クラス .
 * MorphMeshActor のメンバの<BR>
 * 重み _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * 尚 _weight[] は、[0]は未使用、[1]～[n]がモーフターゲット1～nの重み <BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
template<class T>
class Morpher : public GgafCore::ValueTransitioner<float, (MAX_MORPH_TARGET+1) > {

private:
    /** [r]モーファーの助手 */
    MorpherAssistant<T>* _pAsstMph;

public:
    /** [r]対象アクター */
    T* _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_pActor 適用Actor
     */
    explicit Morpher(T* prm_pActor);

    /**
     * モーファーの助手(なめらかモーフ)を取得 .
     * @return モーファーの助手
     */
    MorpherAssistant<T>* asst();

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void behave(int s = 1, int n = MAX_MORPH_TARGET) override;

    virtual ~Morpher();
};

template<class T>
Morpher<T>::Morpher(T* prm_pActor) : GgafCore::ValueTransitioner<float, (MAX_MORPH_TARGET+1) >(),
_pActor(prm_pActor) {
    _pAsstMph = nullptr;
    setRange(0.0f, 1.0f);
}

template<class T>
MorpherAssistant<T>* Morpher<T>::asst() {
    return _pAsstMph ? _pAsstMph : _pAsstMph = NEW MorpherAssistant<T>(this);
}

template<class T>
void Morpher<T>::reset() {
    GgafCore::ValueTransitioner<float, (MAX_MORPH_TARGET+1) >::reset();
    setRange(0.0f, 1.0f);
}

template<class T>
float Morpher<T>::getValue(int idx) {
    return _pActor->_weight[idx];
}

template<class T>
void Morpher<T>::setValue(int idx, float value) {
    _pActor->_weight[idx] = value;
}

template<class T>
void Morpher<T>::behave(int s, int n) {
    if (_pAsstMph) {
        _pAsstMph->behave();
    }
    GgafCore::ValueTransitioner<float, (MAX_MORPH_TARGET+1) >::behave(1, _pActor->_morph_target_num);
}

template<class T>
Morpher<T>::~Morpher() {
    GGAF_DELETE_NULLABLE(_pAsstMph);
}


}
#endif /*GGAF_DX_MORPHER_H_*/

