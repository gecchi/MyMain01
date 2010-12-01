#ifndef VAMSYSCAMPOSITION_H_
#define VAMSYSCAMPOSITION_H_
namespace MyStg2nd {

#define VAM_POS_CAM_MYSHIP_RIGHT  1
#define VAM_POS_CAM_MYSHIP_LEFT   2
#define VAM_POS_CAM_MYSHIP_TOP    3
#define VAM_POS_CAM_MYSHIP_BOTTOM 4
#define VAM_POS_CAM_MYSHIP_BEHIND 5
#define VAM_POS_CAM_MYSHIP_FRONT  6

#define VAM_WAY_CAM_UP_SX    1
#define VAM_WAY_CAM_UP_UX    2
#define VAM_WAY_CAM_UP_SY    3
#define VAM_WAY_CAM_UP_UY    4
#define VAM_WAY_CAM_UP_SZ    5
#define VAM_WAY_CAM_UP_UZ    6

class VamSysCamPosition : public GgafCore::GgafObject {


    class Pos {
        int _pos_cam;
        angle _Rz_up;
        angle _Ry_up;

        Pos* _pLeft;
        Pos* _pUp;
        Pos* _pRight;
        Pos* _pDown;

        Pos(int prm_pos_cam, angle prm_Rz_up, angle prm_Ry_up) {
            _pLeft = _pUp = _pRight = _pDown = NULL;
            _pos_cam = _pos_cam;
            _Rz_up = prm_Rz_up;
            _Ry_up = prm_Ry_up;
        }
        void set(Pos* prm_pLeft, Pos* prm_pUp, Pos* prm_pRight, Pos* prm_pDown) {
            _pLeft  = prm_pLeft;
            _pUp    = prm_pUp;
            _pRight = prm_pRight;
            _pDown  = prm_pDown;
        }
    };
public:

    Pos* _pPos;

    VamSysCamPosition(MyShip* prm_pMyShip);

    virtual ~VamSysCamPosition();
};

}
#endif /*VAMSYSCAMPOSITION_H_*/
