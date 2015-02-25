#ifndef GGAFCORE_GGAFORDER_H_
#define GGAFCORE_GGAFORDER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include <windows.h>

namespace GgafCore {

/**
 * ���i�i�C���X�^���X�j�̒����N���X .
 * ��������ID(_order_id) + ���\��l(_pReceiver) �ŏ��i�͊Ǘ����ꃆ�j�[�N�ɂȂ�܂��B
 * �H��(GgafFactory)�ɓn��������\�����N���X�ŁA ���i�i�C���X�^���X�j�P������ێ����܂��B<BR>
 * �܂������I�u�W�F�N�g���m�ŘA�����X�g���쐬�ł��A���̃��X�g�͍H��(GgafFactory)�����삷�邱�ƂɂȂ�܂��B<BR>
 * @version 1.00
 * @since 2007/12/17
 * @author Masatoshi Tsuge
 */
class GgafOrder : public GgafObject {
    friend class GgafGod;
    friend class GgafFactory;

private:
    /** ������ */
    GgafObject* _pOrderer;
    /** ���\��l(nullptr�̏ꍇ�́A����ł��󂯎���) */
    GgafObject* _pReceiver;
    /** �������� */
    DWORD _time_of_order;
    /** �����J�n���� */
    DWORD _time_of_create_begin;
    /** ������������ */
    DWORD _time_of_create_finish;
    /** ����̒��� */
    GgafOrder* _pOrder_next;
    /** ��O�̒��� */
    GgafOrder* _pOrder_prev;
    /** �擪�̒����t���O */
    bool _is_first_order_flg;
    /** �Ō�̒����t���O */
    bool _is_last_order_flg;
    /** ���i�������\�b�h */
    GgafObject* (*_pFunc)(void*, void*, void*);
    /** ���i�������\�b�h�̃p�����[�^1 */
    void* _pArg1;
    /** ���i�������\�b�h�̃p�����[�^2 */
    void* _pArg2;
    /** ���i�������\�b�h�̃p�����[�^3 */
    void* _pArg3;

public:
    /** ��������ID */
    uint64_t _order_id;
    /** �i����i0:������/1:������/2:�����ς݁j */
    int _progress;
    /** ���i�ւ̃|�C���^ */
    GgafObject* _pObject_creation;

public:
    GgafOrder(uint64_t prm_order_id);
    virtual ~GgafOrder();
};

}
#endif /*GGAFCORE_GGAFORDER_H_*/
