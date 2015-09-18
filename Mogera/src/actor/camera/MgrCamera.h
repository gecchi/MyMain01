#ifndef MGRCAMERA_H_
#define MGRCAMERA_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace Mogera {

/**
 * カメラの雛形 .
 * カメラクラスは本コードのように GgafLib::DefaultMgrCamera を
 * 継承して作成して下さい。<BR>
 * 「この世」を作成する際に、引数でカメラが必要です。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrCamera : public GgafLib::DefaultCamera {

    coord tx_, ty_, tz_;

public:

    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    MgrCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * カメラ→視点ベクトルが突き刺さる面番号を取得します .
     * @return カメラ→視点ベクトルが突き刺さる面番号(1～26)
     */
    dir26 getVpDirNo();

    /**
     * カメラを指定位置に滑らか移動させます。 .
     * @param tx
     * @param ty
     * @param tz
     * @param t 所要フレーム
     */
    void slideMvTo(coord tx, coord ty, coord tz, frame t);

    void slideMvTo(coord tx, coord ty, coord tz, frame t,
                   float prm_x_p1, float prm_y_p1, float prm_z_p1);
    /**
     * カメラを指のアクターの位置に滑らか移動させます。 .
     * @param pTarget
     * @param t 所要フレーム
     */
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
            float prm_x_p1, float prm_y_p1, float prm_z_p1);
    virtual ~MgrCamera(); //デストラクタ
};

}
#endif /*MGRCAMERA_H_*/
