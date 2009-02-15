#ifndef GGAFORDER_H_
#define GGAFORDER_H_
namespace GgafCore {

/**
 * ���i�i�����̃C���X�^���X�j�̒����N���X .
 * �H��(GgafFactory)�ɓn��������\�����N���X�ŁA ���i�i�����̃C���X�^���X�j�P������ێ����܂��B<BR>
 * �܂������I�u�W�F�N�g���m�ŘA�����X�g���쐬�ł��A���̃��X�g�͍H��(GgafFactory)�����삷�邱�ƂɂȂ�܂��B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafOrder : public GgafObject {
    friend class GgafGod;
    friend class GgafFactory;

private:
    /** ��������ID */
    unsigned long _id;
    /** ����̒��� */
    GgafOrder* _pOrder_Next;
    /** ��O�̒��� */
    GgafOrder* _pOrder_Prev;
    /** �擪�̒����t���O */
    bool _isFirstOrderFlg;
    /** �Ō�̒����t���O */
    bool _isLastOrderFlg;
    /** ���i�ւ̃|�C���^ */
    GgafObject* _pObject_Creation;
    /** ���i�������\�b�h */
    GgafObject* (*_pFunc)(void*, void*, void*);
    /** ���i�������\�b�h�̃p�����[�^1 */
    void* _pArg1;
    /** ���i�������\�b�h�̃p�����[�^2 */
    void* _pArg2;
    /** ���i�������\�b�h�̃p�����[�^3 */
    void* _pArg3;
    /** �i����i0:������/1:������/2:�����ς݁j */
    int _progress;

public:
    GgafOrder(unsigned long prm_id);
    virtual ~GgafOrder();
};

}
#endif /*GGAFORDER_H_*/
