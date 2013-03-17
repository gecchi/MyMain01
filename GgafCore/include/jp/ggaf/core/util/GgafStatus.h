#ifndef GGAFSTATUS_H_
#define GGAFSTATUS_H_
namespace GgafCore {

/**
 * ステースクラス.
 * 何らかの値のセットを表現します。
 * @version 1.00
 * @since 2009/07/22 誕生日
 * @author Masatoshi Tsuge
 */
class GgafStatus {

    /**
     * ステータス値を表す .
     * 型は char, int, doubleのいずれか。
     */
    union VALUE {
      char _char_val;
      int _int_val;
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
    GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*) = nullptr) {
        _len = prm_max_status_kind;
        _paValue = new VALUE[_len];
        for (int i = 0; i < _len; i++) {
            _paValue[i]._double_val = 0;
            _paValue[i]._int_val = 0;
            _paValue[i]._char_val = 0;
            _paValue[i]._ptr = nullptr;
        }
        _pFunc_reset = prm_pFunc_reset;
        if (_pFunc_reset) {
            (*_pFunc_reset)(this); //リセットメソッドを実行して初期化
        }
    }

    inline void set(int prm_status_kind, char val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._char_val = val;
    }

    inline void set(int prm_status_kind, int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._int_val = val;
    }

    inline void set(int prm_status_kind, double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._double_val = val;
    }

    inline void set(int prm_status_kind, void* p) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("配列要素数オーバー");
        }
#endif
        _paValue[prm_status_kind]._ptr = p;
    }

    inline char plus(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val += val;
    }

    inline int plus(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val += val;
    }

    inline double plus(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val += val;
    }

    inline char minus(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val -= val;
    }

    inline int minus(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val -= val;
    }

    inline double minus(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val -= val;
    }

    inline char mul(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val *= val;
    }

    inline int mul(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val *= val;
    }

    inline double mul(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val *= val;
    }

    inline int get(int prm_status_kind) {
        return _paValue[prm_status_kind]._int_val;
    }

    inline int getChar(int prm_status_kind) {
        return _paValue[prm_status_kind]._char_val;
    }

    inline int getInt(int prm_status_kind) {
        return _paValue[prm_status_kind]._int_val;
    }

    inline double getDouble(int prm_status_kind) {
        return _paValue[prm_status_kind]._double_val;
    }

    inline void* getPtr(int prm_status_kind) {
        return _paValue[prm_status_kind]._ptr;
    }

    /**
     * ステータスをリセットします。
     * @return
     */
    GgafStatus* reset() {
        if (_pFunc_reset) {
            return (*_pFunc_reset)(this);
        } else {
            throwGgafCriticalException("GgafStatus::reset() リセット用メソッドがnullptrです。");
        }
    }

    ~GgafStatus() {
        delete[] _paValue;
        //GGAF_DELETEARR(_paValue);
    }

};

}
#endif /*GGAFSTATUS_H_*/

