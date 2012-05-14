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
    struct VALUE {
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

    /**
     * ステータスセットを作成 .
     * リセットメソッドを実行しステータス初期化を行います。
     * @param prm_max_status_kind 最大ステータス要素数。
     * @param prm_pFunc_reset ステータスリセットメソッド
     */
    GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*) = NULL) {
        _len = prm_max_status_kind;
        _paValue = new VALUE[prm_max_status_kind];
        for (int i = 0; i < prm_max_status_kind; i++) {
            _paValue[i]._double_val = 0;
            _paValue[i]._int_val = 0;
            _paValue[i]._char_val = 0;
            _paValue[i]._ptr = NULL;
        }
        _pFunc_reset = prm_pFunc_reset;
        if (_pFunc_reset) {
            (*_pFunc_reset)(this);
        }
    }

    void set(int prm_status_kind, char val) {
        _paValue[prm_status_kind]._char_val = val;
    }

    void set(int prm_status_kind, int val) {
        _paValue[prm_status_kind]._int_val = val;
    }

    void set(int prm_status_kind, double val) {
        _paValue[prm_status_kind]._double_val = val;
    }

    void set(int prm_status_kind, void* p) {
        _paValue[prm_status_kind]._ptr = p;
    }

    char plus(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val += val;
    }

    int plus(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val += val;
    }

    double plus(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val += val;
    }

    char minus(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val -= val;
    }

    int minus(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val -= val;
    }

    double minus(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val -= val;
    }

    char mul(int prm_status_kind, char val) {
        return _paValue[prm_status_kind]._char_val *= val;
    }

    int mul(int prm_status_kind, int val) {
        return _paValue[prm_status_kind]._int_val *= val;
    }

    double mul(int prm_status_kind, double val) {
        return _paValue[prm_status_kind]._double_val *= val;
    }

    int get(int prm_status_kind) {
        return _paValue[prm_status_kind]._int_val;
    }

    int getChar(int prm_status_kind) {
        return _paValue[prm_status_kind]._char_val;
    }

    int getInt(int prm_status_kind) {
        return _paValue[prm_status_kind]._int_val;
    }

    double getDouble(int prm_status_kind) {
        return _paValue[prm_status_kind]._double_val;
    }

    void* getPtr(int prm_status_kind) {
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
            throwGgafCriticalException("GgafStatus::reset() リセット用メソッドがNULLです。");
        }
    }

    ~GgafStatus() {
        delete[] _paValue;
        //DELETEARR_IMPOSSIBLE_NULL(_paValue);
    }

};

}
#endif /*GGAFSTATUS_H_*/

