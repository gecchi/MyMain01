#ifndef GGAFOBJECT_H_
#define GGAFOBJECT_H_
namespace GgafCore {


class GgafObject
{

public:
	/** �ʂ��ԍ� */
	//static int _iSeq;

	/** �I�u�W�F�N�g�ԍ� */
	//int _iObjectNo;

	GgafObject();
	virtual string toString();
	virtual ~GgafObject();
};


}
#endif /*GGAFOBJECT_H_*/
