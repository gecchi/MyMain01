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


    virtual void set(int n, char val) {
        _paValue[n]._char_val = val;
    }

    virtual void set(int n, int val) {
        _paValue[n]._int_val = val;
    }

    virtual void set(int n, double val) {
        _paValue[n]._double_val = val;
    }

    virtual char plus(int n, char val) {
        return _paValue[n]._char_val += val;
    }

    virtual int plus(int n, int val) {
        return _paValue[n]._int_val += val;
    }

    virtual double plus(int n, double val) {
        return _paValue[n]._double_val += val;
    }

    virtual char minus(int n, char val) {
        return _paValue[n]._char_val += val;
    }

    virtual int minus(int n, int val) {
        return _paValue[n]._int_val += val;
    }

    virtual double minus(int n, double val) {
        return _paValue[n]._double_val += val;
    }

    virtual char mul(int n, char val) {
        return _paValue[n]._char_val *= val;
    }

    virtual int mul(int n, int val) {
        return _paValue[n]._int_val *= val;
    }

    virtual double mul(int n, double val) {
        return _paValue[n]._double_val *= val;
    }

    virtual int get(int n) {
        return _paValue[n]._int_val;
    }

    virtual int getChar(int n) {
        return _paValue[n]._char_val;
    }

    virtual int getInt(int n) {
        return _paValue[n]._int_val;
    }

    virtual double getDouble(int n) {
        return _paValue[n]._double_val;
    }

    virtual ~GgafStatus() {
        delete[] _paValue;
    }

};

}
#endif /*GGAFSTATUS_H_*/

