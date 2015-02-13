#ifndef MGRCAMERAUPVECTOR_H_
#define MGRCAMERAUPVECTOR_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace Mogera {

/**
 * カメラの上の位置ベクトル .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class MgrCameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    face26 up_face_;

    MgrCameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     */
    void moveTo(face26 prm_face_no, frame prm_spent);


    virtual ~MgrCameraUpVector(); //デストラクタ
};


}
#endif /*MGRCAMERAUPVECTOR_H_*/
