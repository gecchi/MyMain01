#ifndef GGAFDX9UV_H_
#define GGAFDX9UV_H_
namespace GgafDx9Core {

/**
 * テクスチャーのU,V座標コンテナ.
 */
class GgafDx9RectUV : public GgafCore::GgafObject {

    struct UV {
        float tu;
        float tv;
    };

public:
    /** テクスチャー座標１セットの配列 */
    UV _aUV[4];

    GgafDx9RectUV();

    virtual ~GgafDx9RectUV();
};

}
#endif /*GGAFDX9UV_H_*/
