#ifndef VAMSYSCAMPOSITION_H_
#define VAMSYSCAMPOSITION_H_
namespace VioletVreath {

#define VAM_POS_CAM_MYSHIP_RIGHT  1
#define VAM_POS_CAM_MYSHIP_LEFT   2
#define VAM_POS_CAM_MYSHIP_TOP    3
#define VAM_POS_CAM_MYSHIP_BOTTOM 4
#define VAM_POS_CAM_MYSHIP_BEHIND 5
#define VAM_POS_CAM_MYSHIP_FRONT  6

//現在未使用
/**
 * 現在未使用 .
 */
class VamSysCamPosition : public GgafCore::GgafObject {

public:

    class Pos {
    public:
        int pos_cam_;
        angle Rz_up_;
        angle Ry_up_;

        Pos* pLeft_;
        Pos* pUp_;
        Pos* pRight_;
        Pos* pDown_;

        Pos(int prm_pos_cam, angle prm_Rz_up, angle prm_Ry_up) {
            pLeft_ = pUp_ = pRight_ = pDown_ = NULL;
            pos_cam_ = prm_pos_cam;
            Rz_up_ = prm_Rz_up;
            Ry_up_ = prm_Ry_up;
        }
        void set(Pos* prm_pLeft, Pos* prm_pUp, Pos* prm_pRight, Pos* prm_pDown) {
            pLeft_  = prm_pLeft;
            pUp_    = prm_pUp;
            pRight_ = prm_pRight;
            pDown_  = prm_pDown;
        }
    };



    VamSysCamPosition(MyShip* prm_pMyShip);

    virtual ~VamSysCamPosition();
};

}
#endif /*VAMSYSCAMPOSITION_H_*/
