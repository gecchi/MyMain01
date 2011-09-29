#ifndef GGAFDXUV_H_
#define GGAFDXUV_H_
namespace GgafDxCore {

/**
 * テクスチャーのU,V座標コンテナ.
 * @version 1.00
 * @since 2008/02/19
 * @author Masatoshi Tsuge
 */
class GgafDxRectUV : public GgafCore::GgafObject {

    struct UV {
        float tu;
        float tv;
    };

public:
    /** テクスチャー座標１セットの配列 */
    UV _aUV[4];

    GgafDxRectUV();

    virtual ~GgafDxRectUV();
};

}
#endif /*GGAFDXUV_H_*/
