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
    };

public:
    /** ステータス数 */
    int _len;
    /** ステータス値配列 */
    VALUE* _paValue;

    /**
     * ステータスセットを作成 .
     * @param n 最大ステータス要素数。
     * @return
     */
    GgafStatus(int n) {
        _len = n;
        _paValue = NEW VALUE[n];
        for (int i = 0; i < n; i++) {
            _paValue[i]._double_val = 0;
            _paValue[i]._int_val = 0;
            _paValue[i]._char_val = 0;
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

    ~GgafStatus() {
        delete[] _paValue;
    }

};

}
#endif /*GGAFSTATUS_H_*/

