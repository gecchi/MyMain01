#ifndef GGAFSTATUS_H_
#define GGAFSTATUS_H_
namespace GgafCore {


class GgafStatus {


public:
    int _len;
    int* _pa_val;

    GgafStatus(int n) {
        _len = n;
        _pa_val = NEW int[n];
        for (int i  = 0; i < n; i++) {
            _pa_val[i] = 0;
        }
    }

    virtual int get(int n);

    virtual void set(int n, int val);

    virtual ~GgafStatus() {
        delete[] _pa_val;
    }

};

}
#endif /*GGAFSTATUS_H_*/

