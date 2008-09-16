#ifndef GGAFORDER_H_
#define GGAFORDER_H_

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
	GgafObject* (*_functionForBuild)(void*);
	/** ���i�������\�b�h�̃p�����[�^ */
	void* _argumentForBuild;
	/** �i����i0:������/1:������/2:�����ς݁j */
	int _progress;
	
public:
	GgafOrder(string prm_id);
	virtual ~GgafOrder();
};

#endif /*GGAFORDER_H_*/
