#ifndef VVVCAMERA_H_
#define VVVCAMERA_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VVViewer {

/**
 * VVViewerのカメラ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamera : public GgafLib::DefaultCamera {
public:
    coord tx_, ty_, tz_;
    int vcv_face_;
    int vcv_face_prev_;
    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

    int up_face_;
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** カメラのUPベクトル用アクター */
    GgafLib::DefaultGeometricActor* pUp_;
    /** pUp_ の平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;

public:


    VvvCamera(const char* prm_name);
    GgafDxCore::GgafDxCameraViewPoint* createViewPoint() override;

    virtual void initialize() override;
    void processBehavior() override;


    /**
     * カメラ→視点ベクトルが突き刺さるの面番号を取得します .
     * @return カメラ→視点ベクトルが突き刺さる面番号
     */
    int getCamToVpFaceNo();

    /**
     * カメラのUP面番号、引数の面番号にセットし、UPベクトルをスライド移動を開始させます。
     * @param prm_face_no カメラのUP面番号
     */
    void slideUpCamTo(int prm_face_no);

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


    virtual ~VvvCamera();
};

}
#endif /*VVVCAMERAH_*/
