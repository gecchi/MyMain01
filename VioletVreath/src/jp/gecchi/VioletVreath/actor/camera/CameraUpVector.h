#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

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

    dir26 up_dir_;

    CameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     */
    void moveTo(dir26 prm_dir_no, frame prm_spent);
    void moveTo(coord tx, coord ty, coord tz, frame prm_spent);

    virtual ~CameraUpVector(); //デストラクタ
};


}
#endif /*CAMERAUPVECTOR_H_*/
