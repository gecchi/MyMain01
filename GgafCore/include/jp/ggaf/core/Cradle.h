#ifndef GGAF_CORE_CRADLE_H_
#define GGAF_CORE_CRADLE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include <string>
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafCore {

/**
 * ���i�C���X�^���X�j�̂�肩���N���X .
 * ��肩���ԍ�(_cradle_no) + ���\��l(_pReceiver) �Ŗ��͊Ǘ����ꃆ�j�[�N�ɂȂ�܂��B
 * �_�ɓn����肩����\�����N���X�ŁA ���i�C���X�^���X�j�P������ێ����܂��B<BR>
 * �܂���肩���I�u�W�F�N�g���m�ŘA�����X�g���쐬�ł��A���̃��X�g�͐_�����삷�邱�ƂɂȂ�܂��B<BR>
 * @version 1.00
 * @since 2007/12/17
 * @author Masatoshi Tsuge
 */
class Cradle : public Object {
    friend class God;

private:
    /** �]�񂾐l */
    Object* _pWisher;
    /** ���\��l(nullptr�̏ꍇ�́A����ł��󂯎���) */
    Object* _pReceiver;
    /** �]�񂾎��� */
    DWORD _time_of_wants;
    /** �j���J�n���� */
    DWORD _time_of_create_begin;
    /** �j���������� */
    DWORD _time_of_create_finish;
    /** ����̂�肩�� */
    Cradle* _pCradle_next;
    /** ��O�̂�肩�� */
    Cradle* _pCradle_prev;
    /** �擪�̂�肩���t���O */
    bool _is_first_cradle_flg;
    /** �Ō�̂�肩���t���O */
    bool _is_last_cradle_flg;
    /** �j�����\�b�h */
    Object* (*_pFunc)(void*, void*, void*);
    /** �j�����\�b�h�̃p�����[�^1 */
    void* _pArg1;
    /** �j�����\�b�h�̃p�����[�^2 */
    void* _pArg2;
    /** �j�����\�b�h�̃p�����[�^3 */
    void* _pArg3;

public:
    /** ��肩���ԍ� */
    uint64_t _cradle_no;
    /** �i����i0:������/1:�j����/2:�j���ς݁j */
    int _phase;
    /** ���ւ��`�̏� */
    Object* _pObject_creation;

public:
    Cradle(uint64_t prm_cradle_no);

    std::string getDebuginfo();

    virtual ~Cradle();
};

}
#endif /*GGAF_CORE_CRADLE_H_*/
