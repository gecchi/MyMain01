#ifndef GGAFCORE_GGAFSTATUS_H_
#define GGAFCORE_GGAFSTATUS_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * �X�e�[�X�N���X.
 * ���炩�̒l�̃Z�b�g��\�����܂��B
 * @version 1.00
 * @since 2009/07/22 �a����
 * @author Masatoshi Tsuge
 */
class GgafStatus : public GgafObject {

    /**
     * �X�e�[�^�X�l��\�� .
     */
    union VALUE {
      uint64_t _v;
      int _int_val;
      unsigned int _uint_val;
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
    GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*) = nullptr);

    inline void set(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._int_val = val;
    }

    inline void set(const int prm_status_kind, const unsigned int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._uint_val = val;
    }

    inline void set(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._double_val = val;
    }

    inline void set(const int prm_status_kind, void* p) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        _paValue[prm_status_kind]._ptr = p;
    }

    inline int plus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._int_val += val;
    }

    inline double plus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._double_val += val;
    }

    inline int minus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._int_val -= val;
    }

    inline double minus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._double_val -= val;
    }

    inline int mul(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._int_val *= val;
    }

    inline double mul(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_len < prm_status_kind) {
            throwGgafCriticalException("�z��v�f���I�[�o�[");
        }
#endif
        return _paValue[prm_status_kind]._double_val *= val;
    }

    inline int get(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("���x�����z��v�f���I�[�o�[�B�Ӑ}���Ă��܂����H");
            return 0;
        } else {
            return _paValue[prm_status_kind]._int_val;
        }
    }

    inline int getInt(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("���x�����z��v�f���I�[�o�[�B�Ӑ}���Ă��܂����H");
            return 0;
        } else {
            return _paValue[prm_status_kind]._int_val;
        }
    }

    inline unsigned int getUint(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("���x�����z��v�f���I�[�o�[�B�Ӑ}���Ă��܂����H");
            return 0;
        } else {
            return _paValue[prm_status_kind]._uint_val;
        }
    }

    inline double getDouble(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("���x�����z��v�f���I�[�o�[�B�Ӑ}���Ă��܂����H");
            return 0.0;
        } else {
            return _paValue[prm_status_kind]._double_val;
        }
    }

    inline void* getPtr(const int prm_status_kind) const {
        if (_len < prm_status_kind) {
            _TRACE_("���x�����z��v�f���I�[�o�[�B�Ӑ}���Ă��܂����H");
            return nullptr;
        } else {
            return _paValue[prm_status_kind]._ptr;
        }
    }

    /**
     * �X�e�[�^�X�����Z�b�g���܂��B
     * @return
     */
    GgafStatus* reset() {
        if (_pFunc_reset) {
            return (*_pFunc_reset)(this);
        } else {
            throwGgafCriticalException("���Z�b�g�p���\�b�h��nullptr�ł��B");
        }
    }

    ~GgafStatus();

};

}
#endif /*GGAFCORE_GGAFSTATUS_H_*/

