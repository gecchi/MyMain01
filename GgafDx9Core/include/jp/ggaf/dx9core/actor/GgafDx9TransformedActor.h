#ifndef GGAFDX9TRANSFORMEDACTOR_H_
#define GGAFDX9TRANSFORMEDACTOR_H_
namespace GgafDx9Core {


class GgafDx9TransformedActor : public GgafDx9BaseActor {

private:

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual bool isOffscreen() {
		return false;
	};

public:
	/** ���X���W */
	float _x;
	/** ���X���W */
	float _y;
	/** ���Z���W */
	float _z;

	GgafDx9TransformedActor(std::string prm_name);

	virtual GgafDx9TransformedActor* getPrev() {
		return (GgafDx9TransformedActor*)GgafActor::getPrev();
	}

	virtual GgafDx9TransformedActor* getNext() {
		return (GgafDx9TransformedActor*)GgafActor::getNext();
	}

	virtual ~GgafDx9TransformedActor();		//�f�X�g���N�^

};


}
#endif /*GGAFDX9TRANSFORMEDACTOR_H_*/
