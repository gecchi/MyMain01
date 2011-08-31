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
     * @param n 最大ステータス要素数。
     * @param prm_pFunc_reset ステータスリセットメソッド
     */
    GgafStatus(int n, GgafStatus* (*prm_pFunc_reset)(GgafStatus*) = NULL) {
        _len = n;
        _paValue = NEW VALUE[n];
        for (int i = 0; i < n; i++) {
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


    void set(int n, char val) {
        _paValue[n]._char_val = val;
    }

    void set(int n, int val) {
        _paValue[n]._int_val = val;
    }

    void set(int n, double val) {
        _paValue[n]._double_val = val;
    }

    void set(int n, void* p) {
        _paValue[n]._ptr = p;
    }

    char plus(int n, char val) {
        return _paValue[n]._char_val += val;
    }

    int plus(int n, int val) {
        return _paValue[n]._int_val += val;
    }

    double plus(int n, double val) {
        return _paValue[n]._double_val += val;
    }

    char minus(int n, char val) {
        return _paValue[n]._char_val -= val;
    }

    int minus(int n, int val) {
        return _paValue[n]._int_val -= val;
    }

    double minus(int n, double val) {
        return _paValue[n]._double_val -= val;
    }

    char mul(int n, char val) {
        return _paValue[n]._char_val *= val;
    }

    int mul(int n, int val) {
        return _paValue[n]._int_val *= val;
    }

    double mul(int n, double val) {
        return _paValue[n]._double_val *= val;
    }

    int get(int n) {
        return _paValue[n]._int_val;
    }

    int getChar(int n) {
        return _paValue[n]._char_val;
    }

    int getInt(int n) {
        return _paValue[n]._int_val;
    }

    double getDouble(int n) {
        return _paValue[n]._double_val;
    }

    void* getPtr(int n) {
        return _paValue[n]._ptr;
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
    }

};

}
#endif /*GGAFSTATUS_H_*/

