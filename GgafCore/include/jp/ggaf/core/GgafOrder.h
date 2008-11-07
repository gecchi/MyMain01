#ifndef GGAFORDER_H_
#define GGAFORDER_H_

/**
 * ���i�i�����̃C���X�^���X�j�̒����N���X .
 * �H��(GgafFactory)�ɓn��������\�����N���X�ŁA ���i�i�����̃C���X�^���X�j�P������ێ����܂��B<BR>
 * �܂������I�u�W�F�N�g���m�ŘA�����X�g���쐬�ł��A���̃��X�g�͍H��(GgafFactory)�����삷�邱�ƂɂȂ�܂��B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafOrder : public GgafObject {
	friend class GgafGod;
	friend class GgafFactory;

private:
	/** ��������ID */
	string _id;
	/** ����̒��� */
	GgafOrder* _pOrder_Next;
	/** ��O�̒��� */
	GgafOrder* _pOrder_Prev;
	/** �擪�̒����t���O */
	bool _isFirstOrder;
	/** �Ō�̒����t���O */
	bool _isLastOrder;
	/** ���i�ւ̃|�C���^ */
	GgafObject* _pObject_Creation;
	/** ���i�������\�b�h */
	GgafObject* (*_functionForBuild)(void*, void*);
	/** ���i�������\�b�h�̃p�����[�^ */
	void* _argumentForBuild1;
	void* _argumentForBuild2;
	/** �i����i0:������/1:������/2:�����ς݁j */
	int _progress;

public:
	GgafOrder(string prm_id);
	virtual ~GgafOrder();
};

#endif /*GGAFORDER_H_*/
