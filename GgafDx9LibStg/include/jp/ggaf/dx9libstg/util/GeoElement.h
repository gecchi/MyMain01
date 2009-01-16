#ifndef GEOELEMENT_H_
#define GEOELEMENT_H_

class GeoElement {
public:
	int _X;
	int _Y;
	int _Z;
	GeoElement* _next;
	GeoElement(int prm_X, int prm_Y, int prm_Z) {
		_X = prm_X; _Y = prm_Y; _Z = prm_Z;
		_next = NULL;
	};

	GeoElement(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
		_X = prm_pActor->_X;
		_Y = prm_pActor->_Y;
		_Z = prm_pActor->_Z;
		_next = NULL;
	};

	void set(int prm_X, int prm_Y, int prm_Z) {
		_X = prm_X;
		_Y = prm_Y;
		_Z = prm_Z;
	};
	void set(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
		_X = prm_pActor->_X;
		_Y = prm_pActor->_Y;
		_Z = prm_pActor->_Z;
	};
	virtual ~GeoElement() {
		_next = NULL;
	}
};


#endif /*GEOELEMENT_H_*/
