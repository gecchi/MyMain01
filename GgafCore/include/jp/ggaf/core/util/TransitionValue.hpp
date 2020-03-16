#ifndef GGAF_CORE_TRANSITIONVALUE_H_
#define GGAF_CORE_TRANSITIONVALUE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * �l�̑J�ڃw���p�[ .
 * �I�ɔO��̋��ʉ��B
 * @tparam VAL_TYPE �J�ڒl�̃f�[�^�^
 * @tparam N �C���f�b�N�X(����)�̐�
 * @version 1.00
 * @since 2014/02/19
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class TransitionValue : public ValueTransitioner<VAL_TYPE, 1> {
public:
    VAL_TYPE _value;
public:
    /**
     * �R���X�g���N�^<BR>
     */
    TransitionValue() : ValueTransitioner<VAL_TYPE, 1>() {
        _value = (VAL_TYPE)0;
    }

    /**
     * �l���擾����i�v�����j .
     * @param idx �C���f�b�N�X
     * @return �l
     */
    virtual VAL_TYPE getValue(int idx) override {
        return _value;
    }

    virtual VAL_TYPE getValue() {
        return _value;
    }

    /**
     * �l��ݒ肷��i�v�����j .
     * @param idx �C���f�b�N�X
     * @param value �l
     */
    virtual void setValue(int idx, VAL_TYPE value) override {
        _value = value;
    }

    virtual void setValue(VAL_TYPE value) {
        _value = value;
    }

public:

    virtual ~TransitionValue() {
    }
};

}

#endif /*GGAF_CORE_TRANSITIONVALUE_H_*/

