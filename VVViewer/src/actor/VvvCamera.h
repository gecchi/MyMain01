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

    /** カメラのUP要素ベクトルの面番号と、視線の反対ベクトルの面番号との関連テーブル */
    int relation_up_vec_[3*3*3][3*3*3];

public:
    int vcv_face_;
    int vcv_face_prev_;

    /** 自動UP制御機能を一時的にOFFにするフレーム */
    frame auto_up_wait_frames;

    /** relation_up_vec_アクセス用 */
    int (*relation_up_by_vec_)[3*3*3];


    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    VvvCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;
    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    virtual void initialize() override;

    void processBehavior() override;


    /**
     * カメラ→視点ベクトルが突き刺さるの面番号を取得します .
     * @return カメラ→視点ベクトルが突き刺さる面番号
     */
    int getCamToVpFaceNo();


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
