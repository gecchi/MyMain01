#ifndef GGAF_CORE_STATUS_H_
#define GGAF_CORE_STATUS_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include <vector>
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * �X�e�[�X�N���X.
 * ���炩�̒l�̃Z�b�g��\�����܂��B
 * @version 1.00
 * @since 2009/07/22 �a����
 * @author Masatoshi Tsuge
 */
class Status : public Object {

    /**
     * �X�e�[�^�X�l .
     */
    union VALUE {
      uint64_t _v;
      int _int_val;
      unsigned int _uint_val;
      double _double_val;
      bool _bool_val;
      void* _ptr;
    };

public:
    /** �X�e�[�^�X�l���X�g */
    std::vector<VALUE> _value;

    /** ���Z�b�g���\�b�h */
    Status* (*_pFunc_reset)(Status*);

    bool _has_been_reset;

public:
    /**
     * �X�e�[�^�X�Z�b�g���쐬 .
     * ���Z�b�g���\�b�h�����s���X�e�[�^�X���������s���܂��B
     * @param prm_pFunc_reset �X�e�[�^�X���Z�b�g���\�b�h
     */
    Status(Status* (*prm_pFunc_reset)(Status*) = nullptr);

    inline void set(const int prm_status_kind, const int val) {
        if (_value.size() <= (size_t)(prm_status_kind)) {
            _value.resize((size_t)prm_status_kind+1);
        }
        _value[prm_status_kind]._int_val = val;
    }

    inline void set(const int prm_status_kind, const unsigned int val) {
        if (_value.size() <= (size_t)(prm_status_kind)) {
            _value.resize((size_t)prm_status_kind);
        }
        _value[prm_status_kind]._uint_val = val;
    }

    inline void set(const int prm_status_kind, const double val) {
        if (_value.size() <= (size_t)(prm_status_kind)) {
            _value.resize((size_t)prm_status_kind+1);
        }
        _value[prm_status_kind]._double_val = val;
    }

    inline void set(const int prm_status_kind, bool val) {
        if (_value.size() <= (size_t)(prm_status_kind)) {
            _value.resize((size_t)prm_status_kind+1);
        }
        _value[prm_status_kind]._bool_val = val;
    }

    inline void set(const int prm_status_kind, void* p) {
        if (_value.size() <= (size_t)(prm_status_kind)) {
            _value.resize((size_t)prm_status_kind+1);
        }
        _value[prm_status_kind]._ptr = p;
    }

    inline int plus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._int_val += val);
    }

    inline double plus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._double_val += val);
    }

    inline int minus(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._int_val -= val);
    }

    inline double minus(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._double_val -= val);
    }

    inline int mul(const int prm_status_kind, const int val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._int_val *= val);
    }

    inline double mul(const int prm_status_kind, const double val) {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return (_value[prm_status_kind]._double_val *= val);
    }

    inline int get(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._int_val;
    }

    inline int getInt(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._int_val;
    }

    inline unsigned int getUint(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._uint_val;
    }

    inline double getDouble(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._double_val;
    }

    inline double getBool(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._bool_val;
    }

    inline void* getPtr(const int prm_status_kind) const {
#ifdef MY_DEBUG
        if (_value.size() <= (size_t)(prm_status_kind)) {
            throwCriticalException("�v�f�I�[�o�[�Aprm_status_kind="<<prm_status_kind);
        }
#endif
        return _value[prm_status_kind]._ptr;
    }

    /**
     * ���Z�b�g�֐���ݒ肵�ăX�e�[�^�X�����Z�b�g���܂��B
     * @return
     */
    inline void reset(Status* (*prm_pFunc_reset)(Status*)) {
       _pFunc_reset = prm_pFunc_reset;
       reset();
    }
    inline void reset(void* prm_pFunc_reset) {
        _pFunc_reset = (Status* (*)(Status*))prm_pFunc_reset;
        reset();
    }
    /**
     * �O��g�p�̃��Z�b�g�֐����g�p���ăX�e�[�^�X�����Z�b�g���܂��B
     * @return
     */
    void reset() {
        if (_pFunc_reset) {
            (*_pFunc_reset)(this);
            _has_been_reset = true;
        } else {
#ifdef MY_DEBUG
            throwCriticalException("���Z�b�g�p���\�b�h��nullptr�ł��B");
#endif
        }
    }

    bool hasBeenReset() {
        return _has_been_reset;
    }

    ~Status();

};

}
#endif /*GGAF_CORE_STATUS_H_*/

