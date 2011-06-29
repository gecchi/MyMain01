#ifndef VAMSYSCAMPOSITION_H_
#define VAMSYSCAMPOSITION_H_
namespace MyStg2nd {

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
        int _pos_cam;
        appangle _Rz_up;
        appangle _Ry_up;

        Pos* _pLeft;
        Pos* _pUp;
        Pos* _pRight;
        Pos* _pDown;

        Pos(int prm_pos_cam, appangle prm_Rz_up, appangle prm_Ry_up) {
            _pLeft = _pUp = _pRight = _pDown = NULL;
            _pos_cam = prm_pos_cam;
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


    Pos* _pPos;

    VamSysCamPosition(MyShip* prm_pMyShip);

    virtual ~VamSysCamPosition();
};

}
#endif /*VAMSYSCAMPOSITION_H_*/
