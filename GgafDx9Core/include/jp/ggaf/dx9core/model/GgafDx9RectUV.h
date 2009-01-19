#ifndef GGAFDX9UV_H_
#define GGAFDX9UV_H_
namespace GgafDx9Core {


class GgafDx9RectUV : public GgafCore::GgafObject {

	struct UV {
		float tu;
		float tv;
	};


public:
	UV _aUV[4];
	GgafDx9RectUV();
	virtual ~GgafDx9RectUV();
};


}
#endif /*GGAFDX9UV_H_*/
