#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultCameraUpVector.h"

namespace VioletVreath {

/**
 * カメラの上の位置ベクトル .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class CameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    int up_face_;

    CameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     */
    void setFaceNo(int prm_face_no);


    virtual ~CameraUpVector(); //デストラクタ
};


}
#endif /*CAMERAUPVECTOR_H_*/
