#ifndef GGAFSTATUS_H_
#define GGAFSTATUS_H_
namespace GgafCore {

/**
 * ステースクラス.
 * @version 1.00
 * @since 2009/07/22 誕生日
 * @author Masatoshi Tsuge
 */
class GgafStatus {

    union VALUE {
      char _char_val;
      int _int_val;
      double _double_val;
    };

public:
    int _len;
    VALUE* _paValue;

    GgafStatus(int n) {
        _len = n;
        _paValue = NEW VALUE[n];
        ZeroMemory(_paValue, sizeof(VALUE)*_len);
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

