#ifndef GGAFCORE_GGAFSTATUS_H_
#define GGAFCORE_GGAFSTATUS_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * ステースクラス.
 * 何らかの値のセットを表現します。
 * @version 1.00
 * @since 2009/07/22 誕生日
 * @author Masatoshi Tsuge
 */
class GgafStatus : public GgafObject {

    /**
     * ステータス値を表す .
     */
    union VALUE {
      uint64_t _v;
      int _int_val;
      unsigned int _uint_val;
      double _double_val;
      void* _ptr;
    };

public:
    /** ステータス数 */
    int _len;
    /** ステータス値配列 */
    VALUE* _paValue;

    /** リセットメソッド */
    GgafStatus* (*_pFunc_reset)(GgafStatus*);

public:
    /**
     * ステータスセットを作成 .
     * リセットメソッドを実行しステータス初期化を行います。
     * @param prm_max_status_kind 最大ステータス要素数。
     * @param prm_pFunc_reset ステータスリセットメソッド
     */
    GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*) = nullptr);

    inline void set(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._int_val = val;
    }

    inline void set(const int prm_status_kind, const unsigned int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._uint_val = val;
    }

    inline void set(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._double_val = val;
    }

    inline void set(const int prm_status_kind, void* p) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._ptr = p;
    }

    inline int plus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._int_val += val;
    }

    inline double plus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._double_val += val;
    }

    inline int minus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._int_val -= val;
    }

    inline double minus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._double_val -= val;
    }

    inline int mul(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._int_val *= val;
    }

    inline double mul(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        return _paValue[prm_status_kind]._double_val *= val;
    }

    inline int get(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("＜警告＞配列要素数オーバー。意図していますか？");
            return 0;
        } else {
            return _paValue[prm_status_kind]._int_val;
        }
    }

    inline int getInt(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("＜警告＞配列要素数オーバー。意図していますか？");
            return 0;
        } else {
            return _paValue[prm_status_kind]._int_val;
        }
    }

    inline unsigned int getUint(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("＜警告＞配列要素数オーバー。意図していますか？");
            return 0;
        } else {
            return _paValue[prm_status_kind]._uint_val;
        }
    }

    inline double getDouble(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("＜警告＞配列要素数オーバー。意図していますか？");
            return 0.0;
        } else {
            return _paValue[prm_status_kind]._double_val;
        }
    }

    inline void* getPtr(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("＜警告＞配列要素数オーバー。意図していますか？");
            return nullptr;
        } else {
            return _paValue[prm_status_kind]._ptr;
        }
    }

    /**
     * ステータスをリセットします。
     * @return
     */
    GgafStatus* reset() {
        if (_pFunc_reset) {
            return (*_pFunc_reset)(this);
        } else {
            throwGgafCriticalException("リセット用メソッドがnullptrです。");
        }
    }

    ~GgafStatus();

};

}
#endif /*GGAFCORE_GGAFSTATUS_H_*/

