#ifndef GGAFCORE_GGAFCRADLE_H_
#define GGAFCORE_GGAFCRADLE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
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
class GgafCradle : public GgafObject {
    friend class GgafGod;

private:
    /** �]�񂾐l */
    GgafObject* _pWisher;
    /** ���\��l(nullptr�̏ꍇ�́A����ł��󂯎���) */
    GgafObject* _pReceiver;
    /** �]�񂾎��� */
    DWORD _time_of_wants;
    /** �j���J�n���� */
    DWORD _time_of_create_begin;
    /** �j���������� */
    DWORD _time_of_create_finish;
    /** ����̂�肩�� */
    GgafCradle* _pCradle_next;
    /** ��O�̂�肩�� */
    GgafCradle* _pCradle_prev;
    /** �擪�̂�肩���t���O */
    bool _is_first_cradle_flg;
    /** �Ō�̂�肩���t���O */
    bool _is_last_cradle_flg;
    /** �j�����\�b�h */
    GgafObject* (*_pFunc)(void*, void*, void*);
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
    int _progress;
    /** ���ւ��`�̏� */
    GgafObject* _pObject_creation;

public:
    GgafCradle(uint64_t prm_cradle_no);

    std::string getDebuginfo();

    virtual ~GgafCradle();
};

}
#endif /*GGAFCORE_GGAFCRADLE_H_*/
