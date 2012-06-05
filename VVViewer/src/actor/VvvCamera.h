#ifndef SMPCAMERA_H_
#define SMPCAMERA_H_
namespace VVViewer {

/**
 * VVViewerÇÃÉJÉÅÉâ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamera : public GgafLib::DefaultCamera {

public:
    VvvCamera(const char* prm_name);

    virtual ~VvvCamera();
};

}
#endif /*SMPCAMERA_H_*/
