#ifndef GGAFOBJECT_H_
#define GGAFOBJECT_H_
namespace GgafCore {


class GgafObject
{

public:
	/** 通し番号 */
	//static int _iSeq;

	/** オブジェクト番号 */
	//int _iObjectNo;

	GgafObject();
	virtual string toString();
	virtual ~GgafObject();
};


}
#endif /*GGAFOBJECT_H_*/
