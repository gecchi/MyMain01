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

    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

public:

    enum {
        FACE_FRONT = 1,
        FACE_BEHIND = 6,
        FACE_TOP = 2,
        FACE_BOTTOM = 5,
        FACE_ZLEFT = 3,
        FACE_ZRIGHT = 4,
    };

    int up_face_;
    /** [r]カメラ→視線ベクトルが突き刺さる面番号 */
    int vcv_face_;
    /** [r]カメラ→視線ベクトルが突き刺さる面番号 */
    int vcv_face_prev_;

    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]カメラのUPベクトルにコピーされて同期を取るベクトル座標のアクター */
    GgafLib::DefaultGeometricActor* pUp_;
    /** [r]pUp_を滑らかに移動させるためのヘルパー */
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
     * カメラのUPを設定、UPベクトルをスライド移動を開始させます。
     * @param tx カメラのUPベクトルX要素ターゲット
     * @param ty カメラのUPベクトルY要素ターゲット
     * @param tz カメラのUPベクトルZ要素ターゲット
     * @param t スライド移動所要時間
     */
    void slideUpCamTo(coord tx, coord ty, coord tz, frame t);

    /**
     * カメラのUPを面番号で設定、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     * @param prm_t スライド移動所要時間
     *
     */
    void slideUpCamTo(int prm_face_no, frame prm_t);

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
