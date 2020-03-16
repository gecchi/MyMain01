#ifndef GGAF_CORE_TRANSITIONVALUE_H_
#define GGAF_CORE_TRANSITIONVALUE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * 値の遷移ヘルパー .
 * 終に念願の共通化。
 * @tparam VAL_TYPE 遷移値のデータ型
 * @tparam N インデックス(軸等)の数
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
     * コンストラクタ<BR>
     */
    TransitionValue() : ValueTransitioner<VAL_TYPE, 1>() {
        _value = (VAL_TYPE)0;
    }

    /**
     * 値を取得する（要実装） .
     * @param idx インデックス
     * @return 値
     */
    virtual VAL_TYPE getValue(int idx) override {
        return _value;
    }

    virtual VAL_TYPE getValue() {
        return _value;
    }

    /**
     * 値を設定する（要実装） .
     * @param idx インデックス
     * @param value 値
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

