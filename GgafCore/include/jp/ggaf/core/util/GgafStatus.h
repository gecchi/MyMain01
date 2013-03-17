#ifndef GGAFSTATUS_H_
#define GGAFSTATUS_H_
namespace GgafCore {

/**
 * �X�e�[�X�N���X.
 * ���炩�̒l�̃Z�b�g��\�����܂��B
 * @version 1.00
 * @since 2009/07/22 �a����
 * @author Masatoshi Tsuge
 */
class GgafStatus {

    /**
     * �X�e�[�^�X�l��\�� .
     * �^�� char, int, double�̂����ꂩ�B
     */
    union VALUE {
      char _char_val;
      int _int_val;
      double _double_val;
      void* _ptr;
    };

public:
    /** �X�e�[�^�X�� */
    int _len;
    /** �X�e�[�^�X�l�z�� */
    VALUE* _paValue;

    /** ���Z�b�g���\�b�h */
    GgafStatus* (*_pFunc_reset)(GgafStatus*);

public:
    /**
     * �X�e�[�^�X�Z�b�g���쐬 .
     * ���Z�b�g���\�b�h�����s���X�e�[�^�X���������s���܂��B
     * @param prm_max_status_kind �ő�X�e�[�^�X�v�f���B
     * @param prm_pFunc_reset �X�e�[�^�X���Z�b�g���\�b�h
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
            (*_pFunc_reset)(this); //���Z�b�g���\�b�h�����s���ď�����
        }
    }

    inline void set(int prm_status_kind, char val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._char_val = val;
    }

    inline void set(int prm_status_kind, int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._int_val = val;
    }

    inline void set(int prm_status_kind, double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._double_val = val;
    }

    inline void set(int prm_status_kind, void* p) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
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
     * �X�e�[�^�X�����Z�b�g���܂��B
     * @return
     */
    GgafStatus* reset() {
        if (_pFunc_reset) {
            return (*_pFunc_reset)(this);
        } else {
            throwGgafCriticalException("GgafStatus::reset() ���Z�b�g�p���\�b�h��nullptr�ł��B");
        }
    }

    ~GgafStatus() {
        delete[] _paValue;
        //GGAF_DELETEARR(_paValue);
    }

};

}
#endif /*GGAFSTATUS_H_*/

