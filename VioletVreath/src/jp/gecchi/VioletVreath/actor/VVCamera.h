#ifndef VVCAMERA_H_
#define VVCAMERA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VioletVreath {


/**
 * カメラ2.
 * @version 1.00
 * @since 2014/12/05
 * @author Masatoshi Tsuge
 */
class VVCamera : public GgafLib::DefaultCamera {

    coord tx_, ty_, tz_;

    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

public:

    enum {
        FACE_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
        FACE_DOWN_BEHIND,              //1    TN(-1,-1, 0)
        FACE_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
        FACE_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
        FACE_BEHIND,                   //4    TN(-1, 0, 0)
        FACE_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
        FACE_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
        FACE_UP_BEHIND,                //7    TN(-1, 1, 0)
        FACE_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
        FACE_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
        FACE_DOWN,                     //10   TN( 0,-1, 0)
        FACE_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
        FACE_ZRIGHT,                   //12   TN( 0, 0,-1)
        FACE_NONE,                     //13   TN( 0, 0, 0)
        FACE_ZLEFT,                    //14   TN( 0, 0, 1)
        FACE_ZRIGHT_UP,                //15   TN( 0, 1,-1)
        FACE_UP,                       //16   TN( 0, 1, 0)
        FACE_ZLEFT_UP,                 //17   TN( 0, 1, 1)
        FACE_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
        FACE_DOWN_FRONT,               //19   TN( 1,-1, 0)
        FACE_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
        FACE_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
        FACE_FRONT,                    //22   TN( 1, 0, 0)
        FACE_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
        FACE_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
        FACE_UP_FRONT,                 //25   TN( 1, 1, 0)
        FACE_ZLEFT_UP_FRONT            //26   TN( 1, 1, 1)
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

    VVCamera(const char* prm_name);

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
    virtual ~VVCamera(); //デストラクタ
};

}
#endif /*VVCAMERA_H_*/
