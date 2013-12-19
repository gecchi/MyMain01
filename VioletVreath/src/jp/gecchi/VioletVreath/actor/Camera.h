#ifndef CAMERA_H_
#define CAMERA_H_
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VioletVreath {

/**
 * カメラ.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

    coord tx_, ty_, tz_;
    int vcv_face_;
    int vcv_face_prev_;
    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

public:

    int up_face_;


    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** カメラのUPベクトル用アクター */
    GgafLib::DefaultGeometricActor* pUp_;
    /** pUp_ の平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;

    Camera(const char* prm_name);

    GgafDxCore::GgafDxCameraViewPoint* createViewPoint() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * カメラ→視点ベクトルの面番号を取得します .
     * @return カメラ→視点ベクトルの面番号(1～6)
     */
    int getCamToVpFaceNo();

    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_cam_up_face カメラのUP面番号
     */
    void setCamUpFace(int prm_cam_up_face);

    /**
     * カメラを指定位置に滑らか移動させます。 .
     * @param tx
     * @param ty
     * @param tz
     * @param t 所要フレーム
     */
    void slideMvTo(coord tx, coord ty, coord tz, frame t);

    /**
     * カメラを指のアクターの位置に滑らか移動させます。 .
     * @param pTarget
     * @param t 所要フレーム
     */
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~Camera(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
