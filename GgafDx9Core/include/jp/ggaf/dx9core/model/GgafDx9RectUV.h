#ifndef GGAFDX9UV_H_
#define GGAFDX9UV_H_

class GgafDx9RectUV : public Ggaf::GgafObject {

	struct UV {
		float tu;
		float tv;
	};


public:
	UV _aUV[4];
	GgafDx9RectUV();
	virtual ~GgafDx9RectUV();
};

#endif /*GGAFDX9UV_H_*/
