#ifndef VVVVIEWPOINT_H_
#define VVVVIEWPOINT_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultCameraUpVector.h"

namespace VVViewer {

/**
 * 視点.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class VvvCameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    int up_face_;

    VvvCameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     */
    void setFaceNo(int prm_face_no);


    virtual ~VvvCameraUpVector(); //デストラクタ
};


}
#endif /*VVVVIEWPOINT_H_*/
