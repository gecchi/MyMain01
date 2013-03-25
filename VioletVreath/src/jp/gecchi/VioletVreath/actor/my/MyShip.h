#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace VioletVreath {

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0
//Ternary numeral -1,0.1 ��3����3�i�@ �� �z��v�f�̂��ߐ���10�i���ɕϊ�����}�N��
#define TN(X,Y,Z) (((3*3)*(X+1)) + ((3)*(Y+1)) + (Z+1))

#define EQ_OPTION 1
#define EQ_MAX_OPTION 0
/** �\�t�g�A�ː� */
#define SOFT_RAPIDSHOT_NUM 3
/** �\�t�g�A�ˊԊu */
#define SOFT_RAPIDSHOT_INTERVAL 4

#define MY_SHIP_VREATH_COST (500)
//���ċz�� 1000000/500/60 = ��33.3�b�Ŏ���
/**
 * ���@�N���X
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
class MyShip : public GgafLib::DefaultD3DXMeshActor {
//class MyShip : public GgafLib::DefaultMeshActor {
//class MyShip : public GgafLib::CubeMapMeshActor {
//class MyShip : public GgafLib::DefaultD3DXAniMeshActor {
public:
    enum Switch {
        SW_ADD = 1,
        SW_NOP = 0,
        SW_SUB = -1
    };

    enum MoveWay {
        WAY_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
        WAY_DOWN_BEHIND,              //1    TN(-1,-1, 0)
        WAY_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
        WAY_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
        WAY_BEHIND,                   //4    TN(-1, 0, 0)
        WAY_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
        WAY_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
        WAY_UP_BEHIND,                //7    TN(-1, 1, 0)
        WAY_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
        WAY_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
        WAY_DOWN,                     //10   TN( 0,-1, 0)
        WAY_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
        WAY_ZRIGHT,                   //12   TN( 0, 0,-1)
        WAY_NONE,                     //13   TN( 0, 0, 0)
        WAY_ZLEFT,                    //14   TN( 0, 0, 1)
        WAY_ZRIGHT_UP,                //15   TN( 0, 1,-1)
        WAY_UP,                       //16   TN( 0, 1, 0)
        WAY_ZLEFT_UP,                 //17   TN( 0, 1, 1)
        WAY_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
        WAY_DOWN_FRONT,               //19   TN( 1,-1, 0)
        WAY_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
        WAY_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
        WAY_FRONT,                    //22   TN( 1, 0, 0)
        WAY_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
        WAY_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
        WAY_UP_FRONT,                 //25   TN( 1, 1, 0)
        WAY_ZLEFT_UP_FRONT            //26   TN( 1, 1, 1)
    };

    enum {
        SE_DAMAGED = 0,
        SE_FIRE_LASER,
        SE_FIRE_SHOT,
        SE_FIRE_TORPEDO,
    };

    class MyShipWaySwitch {
    public :
        class SW {
            public:
            int X, Y, Z;
            SW() { X = Y = Z = SW_NOP; }
        };
        bool sw_UP_, sw_LEFT_, sw_RIGHT_, sw_DOWN_;
        SW on_UP_, on_LEFT_, on_RIGHT_, on_DOWN_;

        /** ���݂̕��� */
        SW way_;
        MyShipWaySwitch() {
            way_.X = way_.Y = way_.Z = SW_NOP;
            sw_UP_ = sw_LEFT_ = sw_RIGHT_ = sw_DOWN_ = false;
        }

        void reset() {
            way_.X = way_.Y = way_.Z = SW_NOP;
            sw_UP_ = sw_LEFT_ = sw_RIGHT_ = sw_DOWN_ = false;
        }
        inline void ON_UP(Switch swX, Switch swY, Switch swZ) {
            if (!sw_UP_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_UP_.X = swX;
                on_UP_.Y = swY;
                on_UP_.Z = swZ;
                sw_UP_ = true;
            }
        }
        inline void ON_LEFT(Switch swX, Switch swY, Switch swZ) {
            if (!sw_LEFT_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_LEFT_.X = swX;
                on_LEFT_.Y = swY;
                on_LEFT_.Z = swZ;
                sw_LEFT_ = true;
            }
        }
        inline void ON_RIGHT(Switch swX, Switch swY, Switch swZ) {
            if (!sw_RIGHT_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_RIGHT_.X = swX;
                on_RIGHT_.Y = swY;
                on_RIGHT_.Z = swZ;
                sw_RIGHT_ = true;
            }
        }
        inline void ON_DOWN(Switch swX, Switch swY, Switch swZ) {
            if (!sw_DOWN_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_DOWN_.X = swX;
                on_DOWN_.Y = swY;
                on_DOWN_.Z = swZ;
                sw_DOWN_ = true;
            }
        }
        inline void OFF_UP() {
            if (sw_UP_) {
                way_.X -= on_UP_.X;
                way_.Y -= on_UP_.Y;
                way_.Z -= on_UP_.Z;
                sw_UP_ = false;
            }
        }
        inline void OFF_RIGHT() {
            if (sw_RIGHT_) {
                way_.X -= on_RIGHT_.X;
                way_.Y -= on_RIGHT_.Y;
                way_.Z -= on_RIGHT_.Z;
                sw_RIGHT_ = false;
            }
        }
        inline void OFF_LEFT() {
            if (sw_LEFT_) {
                way_.X -= on_LEFT_.X;
                way_.Y -= on_LEFT_.Y;
                way_.Z -= on_LEFT_.Z;
                sw_LEFT_ = false;
            }
        }
        inline void OFF_DOWN() {
            if (sw_DOWN_) {
                way_.X -= on_DOWN_.X;
                way_.Y -= on_DOWN_.Y;
                way_.Z -= on_DOWN_.Z;
                sw_DOWN_ = false;
            }
        }
        inline int getIndex() {
            //3�i����10�i���ϊ�
            //_TRACE_("way_.X, way_.Y, way_.Z="<<way_.X<<","<<way_.Y<<","<< way_.Z);
            return (3*3*(SGN(way_.X)+1)) + (3*(SGN(way_.Y)+1)) + (SGN(way_.Z)+1);
        }
    };
public:
    /** �ړ�Y���W��� */
    static coord lim_top_;
    /** �ړ�Y���W���� */
    static coord lim_bottom_;
    /** �ړ�X���W��� */
    static coord lim_front_;
    /** �ړ�X���W���� */
    static coord lim_behaind_;
    /** �ړ�Z���W��� */
    static coord lim_zleft_;
    /** �ړ�Z���W���� */
    static coord lim_zright_;

    MyShipWaySwitch way_switch_;
    void (MyShip::*paFuncMove[3*3*3])();
    void (MyShip::*paFuncTurbo[3*3*3])();

    /** [r]���b�N�I���R���g���[���[ */
    MyLockonController* pLockonCtrler_;
    /** [r]�����R���g���[���[ */
    MyTorpedoController* pTorpedoCtrler_;
    /** �������͒l */
    int stc_;

    /** �^�[�{���A�ړ����p */
    MoveWay way_;
    MoveWay prev_way_;
    bool is_just_change_way_;
    /** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
    int iMoveSpeed_;

    velo veloTurboTop_;
    velo veloTurboBottom_;

    /** Turbo�ړ��J�n���̈ړ����x�̏����x */
    velo veloBeginMT_; //Move Velo when I Begin To Move with Turbo
    //Z�������ޏꍇ�A���܂����̒l����v�Z���悤�iZ���̈ړ����x�͐����ŊǗ����Ă邽�߁j

    /** Turbo�ړ����̈ړ����x�̉����x */
    acce acce_MT_; //Move Acce while I Move with Turbo
    //�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** Turbo�ړ����̈ړ����x�̍Œᑬ�x */
    velo iMvBtmVelo_MT_; //Move Bottom Velo while I Move with Turbo
    //�A�� �l < 0 �ł��邱�ƁB
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** Turbo�ړ����I���Ɣ��f�����ړ����x */
//    velo veloFMT_; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //�A�� �l < 0 �ł��邱�ƁB
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ��J�n����X����]�p���x�̏����x */
    angvelo angRXVelo_BeginMZ_; //Rotation axisX angle Velo when I Begin To Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ�����X����]�p���x�̊p�����x */
    angacce angRXAcce_MZ_; //Rotation axisX angle Acce while I Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�ֈړ�����X����]�p���x�̏���p���x */
    angvelo angRXTopVelo_MZ_; //Rotation axisX Top angle Velo while I Move Z
    //�����p���x�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x */
    angle angRXStop_MZ_; //Rotation axisX Stop angle while I Move Z


    /** ��(+Y)���͉�(-Y)��Turbo�ړ��J�n����Z����]�p���x�̏����x */
    angvelo angRXVelo_BeginMZT_; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_MyShipGeoHistory4OptCtrler_;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_MyShipGeoHistory2_;
    GgafCore::GgafActorDepository* pDepo_MyShots001_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    EffectTurbo001* pEffectTurbo001_;

//    //debug ---->
//    GgafCore::GgafActorDepository* pDepo_TestGuShot_;
//    GgafCore::GgafActorDepository* pDepo_TestChokiShot_;
//    GgafCore::GgafActorDepository* pDepo_TestPaShot_;
//    GgafCore::GgafActorDepository* pDepo_TestNomalShot_;
//    //<---- debug

    /** �\�t�g�A�ˊJ�n����̌o�߃t���[���� */
    frame frame_soft_rapidshot_;
    /** �\�t�g�A�˒��ł��邩�ۂ� */
    bool is_being_soft_rapidshot_;
    /** �V���b�g�����t���[���̂� true �ɂȂ� */
    bool just_shot_;
    /** ���[�U�[���˂��ǂ��� */
    bool is_shooting_laser_;
    /** SHOT�{�^���������ςȂ��o�߃t���[�����i���[�U�[���ˊJ�n����̂��߁j */
    frame frame_shot_pressed_;

    /** �V�[���˓������ǂ��� */
    bool is_diving_;

    /** ����� */
    bool can_control_;

    /** �������X���� */
    int blown_veloX_;
    /** �������Y���� */
    int blown_veloY_;
    /** �������Z���� */
    int blown_veloZ_;

    /** ������ь����� */
    double r_blown_velo_attenuate_;

    /** MP */
    GgafLib::AmountGraph mp_;
    /** Vreath */
    GgafLib::AmountGraph vreath_;

    int invincible_frames_;

    /** ���@���[�^�[ */
    MagicMeter* pMagicMeter_;


public:
    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;
    void onInactive() override;
    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void setMoveSpeedLv(int lv);

    //��ʎ�O�ֈړ�����X����]����

    void doNotingMoveInput();

    static angle wk_dist, wk_angRx;
    void move_WAY_NONE();
    /**
     * ��ړ�
     */
    void move_WAY_UP();
    /**
     * �O���΂ߏ�ړ�
     */
    void move_WAY_UP_FRONT();
    /**
     * ����΂ߏ�ړ�
     */
    void move_WAY_UP_BEHIND();
    /**
     * �O�ړ�
     */
    void move_WAY_FRONT();
    /**
     * ���ړ�
     */
    void move_WAY_BEHIND();
    /**
     * ���ړ�
     */
    void move_WAY_DOWN();
    /**
     * ����΂߉��ړ�
     */
    void move_WAY_DOWN_BEHIND();
    /**
     * �O���΂߉��ړ�
     */
    void move_WAY_DOWN_FRONT();
    /**
     * ���ړ�
     */
    void move_WAY_ZLEFT();
    /**
     * �O���΂ߍ��ړ�
     */
    void move_WAY_ZLEFT_FRONT();
    /**
     * ����΂ߍ��ړ�
     */
    void move_WAY_ZLEFT_BEHIND();
    /**
     * �O���΂߉E�ړ�
     */
    void move_WAY_ZRIGHT_FRONT();
    /**
     * �E�ړ�
     */
    void move_WAY_ZRIGHT();
    /**
     * ����΂߉E
     */
    void move_WAY_ZRIGHT_BEHIND();
    /**
     * ���΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP();
    /**
     * ���΂߉��ړ�
     */
    void move_WAY_ZLEFT_DOWN();
    /**
     * �E�΂ߏ�ړ�
     */
    void move_WAY_ZRIGHT_UP();
    /**
     * �E�΂߉��ړ�
     */
    void move_WAY_ZRIGHT_DOWN();
    /**
     * �O�����΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP_FRONT();
    /**
     * ������΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP_BEHIND();
    /**
     * �O�����΂߉��ړ�
     */
    void move_WAY_ZLEFT_DOWN_FRONT();

    /**
     * ������΂߉��ړ�
     */
    void move_WAY_ZLEFT_DOWN_BEHIND();

    /**
     * �O���E�΂ߏ�ړ�
     */
    void move_WAY_ZRIGHT_UP_FRONT();
    /**
     * ����E�΂ߏ�ړ�
     */
    void move_WAY_ZRIGHT_UP_BEHIND();
    /**
     * �O���E�΂߉��ړ�
     */
    void move_WAY_ZRIGHT_DOWN_FRONT();
    /**
     * ����E�΂߉��ړ�
     */
    void move_WAY_ZRIGHT_DOWN_BEHIND();

    /////////////////TURBO_BEGIN

    void turbo_WAY_NONE();
    /**
     * ��^�[�{�J�n
     */
    void turbo_WAY_UP();
    /**
     * �O���΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_UP_FRONT();
    /**
     * ����΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_UP_BEHIND();
    /**
     * �O�^�[�{�J�n
     */
    void turbo_WAY_FRONT();
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_BEHIND();
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_DOWN();
    /**
     * ����΂߉��^�[�{�J�n
     */
    void turbo_WAY_DOWN_BEHIND();
    /**
     * �O���΂߉��^�[�{�J�n
     */
    void turbo_WAY_DOWN_FRONT();
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_ZLEFT();
    /**
     * �O���΂ߍ��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_FRONT();
    /**
     * ����΂ߍ��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_BEHIND();
    /**
     * �O���΂߉E�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_FRONT();
    /**
     * �E�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT();
    /**
     * ����΂߉E
     */
    void turbo_WAY_ZRIGHT_BEHIND();
    /**
     * ���΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP();
    /**
     * ���΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_DOWN();
    /**
     * �E�΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_UP();
    /**
     * �E�΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_DOWN();
    /**
     * �O�����΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP_FRONT();
    /**
     * ������΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP_BEHIND();
    /**
     * �O�����΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_DOWN_FRONT();
    /**
     * ������΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_DOWN_BEHIND();
    /**
     * �O���E�΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_UP_FRONT();
    /**
     * ����E�΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_UP_BEHIND();
    /**
     * �O���E�΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_DOWN_FRONT();
    /**
     * ����E�΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_DOWN_BEHIND();

    void onChangeWay(MoveWay prev_way, MoveWay new_way) {

        switch(new_way) {
            case 0: {
                break;
            }
            default:
                break;
        }

    }

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    /**
     * ���@������� .
     * @param prm_blown_veloX X����������ё��x
     * @param prm_blown_veloY Y����������ё��x
     * @param prm_blown_veloZ Z����������ё��x
     * @param prm_r_blown_velo_attenuate ������ь�����
     */
    void setBlownVelo(velo prm_blown_veloX, velo prm_blown_veloY, velo prm_blown_veloZ, double prm_r_blown_velo_attenuate);
    /**
     * ���@���G�ݒ� .
     * @param prm_frames ���G����(�t���[��)
     */
    void setInvincibleFrames(int prm_frames);

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

