#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace MyStg2nd {

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

    class State {
    public:
        int eq_option;
        int eq_speed;
        int mp;
        State() {
            eq_option = 0;
            eq_speed = 1;
            mp = 10000;
        }

    };

    struct VERTEX {
        float x, y, z; // ���_���W
        float nx, ny, nz; // �@��
        DWORD color; // ���_�̐F
        float tu, tv; // �e�N�X�`�����W
    };






    class MyShipWaySwitch {
    public :
        class SW {
            public:
            int X, Y, Z;
            SW() { X = Y = Z = SW_NOP; }
        };
        bool _sw_UP, _sw_LEFT, _sw_RIGHT, _sw_DOWN;
        SW _on_UP, _on_LEFT, _on_RIGHT, _on_DOWN;

        /** ���݂̕��� */
        SW _way;



        MyShipWaySwitch() {
            _way.X = _way.Y = _way.Z = SW_NOP;
            _sw_UP = _sw_LEFT = _sw_RIGHT = _sw_DOWN = false;
        }

        void reset() {
            _way.X = _way.Y = _way.Z = SW_NOP;
            _sw_UP = _sw_LEFT = _sw_RIGHT = _sw_DOWN = false;
        }
        void ON_UP(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_UP) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_UP.X = swX;
                _on_UP.Y = swY;
                _on_UP.Z = swZ;
                _sw_UP = true;
            }
        }
        void ON_LEFT(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_LEFT) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_LEFT.X = swX;
                _on_LEFT.Y = swY;
                _on_LEFT.Z = swZ;
                _sw_LEFT = true;
            }
        }
        void ON_RIGHT(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_RIGHT) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_RIGHT.X = swX;
                _on_RIGHT.Y = swY;
                _on_RIGHT.Z = swZ;
                _sw_RIGHT = true;
            }
        }
        void ON_DOWN(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_DOWN) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_DOWN.X = swX;
                _on_DOWN.Y = swY;
                _on_DOWN.Z = swZ;
                _sw_DOWN = true;
            }
        }
        void OFF_UP() {
            if (_sw_UP) {
                _way.X -= _on_UP.X;
                _way.Y -= _on_UP.Y;
                _way.Z -= _on_UP.Z;
                _sw_UP = false;
            }
        }
        void OFF_RIGHT() {
            if (_sw_RIGHT) {
                _way.X -= _on_RIGHT.X;
                _way.Y -= _on_RIGHT.Y;
                _way.Z -= _on_RIGHT.Z;
                _sw_RIGHT = false;
            }
        }
        void OFF_LEFT() {
            if (_sw_LEFT) {
                _way.X -= _on_LEFT.X;
                _way.Y -= _on_LEFT.Y;
                _way.Z -= _on_LEFT.Z;
                _sw_LEFT = false;
            }
        }
        void OFF_DOWN() {
            if (_sw_DOWN) {
                _way.X -= _on_DOWN.X;
                _way.Y -= _on_DOWN.Y;
                _way.Z -= _on_DOWN.Z;
                _sw_DOWN = false;
            }
        }
        int getIndex() {
            //3�i����10�i���ϊ�
            //_TRACE_("_way.X, _way.Y, _way.Z="<<_way.X<<","<<_way.Y<<","<< _way.Z);
            return (3*3*(sgn(_way.X)+1)) + (3*(sgn(_way.Y)+1)) + (sgn(_way.Z)+1);
        }
    };
public:
    /** �ړ�Y���W��� */
    static coord _lim_top;
    /** �ړ�Y���W���� */
    static coord _lim_bottom;
    /** �ړ�X���W��� */
    static coord _lim_front;
    /** �ړ�X���W���� */
    static coord _lim_behaind;
    /** �ړ�Z���W��� */
    static coord _lim_zleft;
    /** �ړ�Z���W���� */
    static coord _lim_zright;

    MyShipWaySwitch _way_switch;
    void (MyShip::*paFuncMove[3*3*3])();
    void (MyShip::*paFuncTurbo[3*3*3])();

//    void (MyShip::*fpaFunc[])() =  {
//          move_WAY_UP,
//          move_WAY_UP_FRONT
//    };




    /** �������͒l */
    int _stc;

    /** �^�[�{���A�ړ����p */
    MoveWay _way;
    MoveWay _prev_way;
    bool _is_just_change_way;
    /** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
    int _iMoveSpeed;

    velo _iMoveVelo;


    velo _iMvVelo_TurboTop;
    velo _iMvVelo_TurboBottom;

    /** Turbo�ړ��J�n���̈ړ����x�̏����x */
    velo _iMvVelo_BeginMT; //Move Velo when I Begin To Move with Turbo
    //Z�������ޏꍇ�A���܂����̒l����v�Z���悤�iZ���̈ړ����x�͐����ŊǗ����Ă邽�߁j

    /** Turbo�ړ����̈ړ����x�̉����x */
    acce _iMvAcce_MT; //Move Acce while I Move with Turbo
    //�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** Turbo�ړ����̈ړ����x�̍Œᑬ�x */
    velo _iMvBtmVelo_MT; //Move Bottom Velo while I Move with Turbo
    //�A�� �l < 0 �ł��邱�ƁB
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** Turbo�ړ����I���Ɣ��f�����ړ����x */
    velo _iMvVelo_FMT; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //�A�� �l < 0 �ł��邱�ƁB
    //�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ��J�n����X����]�p���x�̏����x */
    ang_velo _angRXVelo_BeginMZ; //Rotation axisX angle Velo when I Begin To Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ�����X����]�p���x�̊p�����x */
    ang_acce _angRXAcce_MZ; //Rotation axisX angle Acce while I Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�ֈړ�����X����]�p���x�̏���p���x */
    ang_velo _angRXTopVelo_MZ; //Rotation axisX Top angle Velo while I Move Z
    //�����p���x�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x */
    angle _angRXStop_MZ; //Rotation axisX Stop angle while I Move Z


    /** ��(+Y)���͉�(-Y)��Turbo�ړ��J�n����Z����]�p���x�̏����x */
    ang_velo _angRXVelo_BeginMZT; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��




    State _state;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* _pRing_GeoHistory;

    GgafCore::GgafActorDepository* _pDepo_MyShots001;
    GgafCore::GgafActorDepository* _pDP_EffectExplosion001;
    GgafLib::LaserChipDepository* _pLaserChipDepo;

//    MyOptionController* _pMyOptionController;
    EffectTurbo001* _pEffectTurbo001;

    /** �\�t�g�A�ˊJ�n����̌o�߃t���[���� */
    frame _frame_soft_rapidshot;
    /** �\�t�g�A�˒��ł��邩�ۂ� */
    bool _is_being_soft_rapidshot;
    /** �V���b�g�����t���[���̂� true �ɂȂ� */
    bool _just_shot;
    /** ���[�U�[���˂��ǂ��� */
    bool _is_shooting_laser;
    /** SHOT�{�^���������ςȂ��o�߃t���[�����i���[�U�[���ˊJ�n����̂��߁j */
    frame _frame_shot_pressed;

    /** �V�[���˓������ǂ��� */
    bool _is_diving;

    /** ����� */
    bool _can_control;

    /** �������X���� */
    int _blown_veloX;
    /** �������Y���� */
    int _blown_veloY;
    /** �������Z���� */
    int _blown_veloZ;
    /** ������т�}����� */
    int _anti_blown_velo;

    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void setMoveSpeedLv(int lv);

    //��ʎ�O�ֈړ�����X����]����

    void doNotingMoveInput();

    static angle wk_dist, wk_angRx;
    void move_WAY_NONE() {
        //_way = WAY_NONE;
        _iMoveVelo = 0;
    }
    /**
     * ��ړ�
     */
    void move_WAY_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D90ANG, 0);
        }
        _Y += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * �O���΂ߏ�ړ�
     */
    void move_WAY_UP_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, 0);
        }
        _Y += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * ����΂ߏ�ړ�
     */
    void move_WAY_UP_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D135ANG, 0);
        }
        _Y += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �O�ړ�
     */
    void move_WAY_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, 0);
        }
        _X += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * ���ړ�
     */
    void move_WAY_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, 0);
        }
        _X -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * ���ړ�
     */
    void move_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _Y -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * ����΂߉��ړ�
     */
    void move_WAY_DOWN_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D255ANG, 0);
        }
        _Y -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �O���΂߉��ړ�
     */
    void move_WAY_DOWN_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, 0);
        }
        _Y -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * ���ړ�
     */
    void move_WAY_ZLEFT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D270ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * �O���΂ߍ��ړ�
     */
    void move_WAY_ZLEFT_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D315ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2)); //�����v���
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * ����΂ߍ��ړ�
     */
    void move_WAY_ZLEFT_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �O���΂߉E�ړ�
     */
    void move_WAY_ZRIGHT_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �E�ړ�
     */
    void move_WAY_ZRIGHT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D90ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * ����΂߉E
     */
    void move_WAY_ZRIGHT_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D135ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * ���΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * ���΂߉��ړ�
     */
    void move_WAY_ZLEFT_DOWN() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ/2);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);

        }
        _Z += _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �E�΂ߏ�ړ�
     */
    void move_WAY_ZRIGHT_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �E�΂߉��ړ�
     */
    void move_WAY_ZRIGHT_DOWN() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
            //����
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * �O�����΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP_FRONT() {
        _TRACE_("move_WAY_ZLEFT_UP_FRONTLEFT() came!");
    }
    /**
     * ������΂ߏ�ړ�
     */
    void move_WAY_ZLEFT_UP_BEHIND() {
        _TRACE_("move_WAY_ZLEFT_UP_BEHINDLEFT() came!");
    }

    void move_WAY_ZLEFT_DOWN_FRONT() {
        _TRACE_("move_WAY_ZLEFT_DOWN_FRONTLEFT() came!");
    }

    void move_WAY_ZLEFT_DOWN_BEHIND() {
        _TRACE_("move_WAY_ZLEFT_DOWN_BEHINDLEFT() came!");
    }

    void move_WAY_ZRIGHT_UP_FRONT() {
        _TRACE_("move_WAY_ZRIGHT_UP_FRONTLEFT() came!");
    }

    void move_WAY_ZRIGHT_UP_BEHIND() {
        _TRACE_("move_WAY_ZRIGHT_UP_BEHINDLEFT() came!");
    }

    void move_WAY_ZRIGHT_DOWN_FRONT() {
        _TRACE_("move_WAY_ZRIGHT_DOWN_FRONTLEFT() came!");
    }

    void move_WAY_ZRIGHT_DOWN_BEHIND() {
        _TRACE_("move_WAY_ZRIGHT_DOWN_BEHIND() came!");
    }


    /////////////////TURBO_BEGIN

    void turbo_WAY_NONE() {

    }

    /**
     * ��^�[�{�J�n
     */
    void turbo_WAY_UP() {
        _pKurokoA->setRzRyMvAng(D90ANG, 0);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * �O���΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_UP_FRONT() {
        _pKurokoA->setRzRyMvAng(D45ANG, 0);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * ����΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_UP_BEHIND() {
        _pKurokoA->setRzRyMvAng(D135ANG, 0);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * �O�^�[�{�J�n
     */
    void turbo_WAY_FRONT() {
        _pKurokoA->setRzRyMvAng(0, 0);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, 0);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * ����΂߉��^�[�{�J�n
     */
    void turbo_WAY_DOWN_BEHIND() {
        _pKurokoA->setRzRyMvAng(D255ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * �O���΂߉��^�[�{�J�n
     */
    void turbo_WAY_DOWN_FRONT() {
        _pKurokoA->setRzRyMvAng(D315ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * ���^�[�{�J�n
     */
    void turbo_WAY_ZLEFT() {
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT); //�����悭��]�J�n
    }
    /**
     * �O���΂ߍ��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_FRONT() {
        _pKurokoA->setRzRyMvAng(0, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * ����΂ߍ��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * �O���΂߉E�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_FRONT() {
        _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * �E�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT() {
        _pKurokoA->setRzRyMvAng(0, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT); //�����悭��]�J�n
    }
    /**
     * ����΂߉E
     */
    void turbo_WAY_ZRIGHT_BEHIND() {
        _pKurokoA->setRzRyMvAng(0, D135ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * ���΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * ���΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * �E�΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * �E�΂߉��^�[�{�J�n
     */
    void turbo_WAY_ZRIGHT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //����
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //�����悭��]�J�n
    }
    /**
     * �O�����΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP_FRONT() {
        _TRACE_("turbo_WAY_ZLEFT_UP_FRONTLEFT() came!");
    }
    /**
     * ������΂ߏ�^�[�{�J�n
     */
    void turbo_WAY_ZLEFT_UP_BEHIND() {
        _TRACE_("turbo_WAY_ZLEFT_UP_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZLEFT_DOWN_FRONT() {
        _TRACE_("turbo_WAY_ZLEFT_DOWN_FRONTLEFT() came!");
    }

    void turbo_WAY_ZLEFT_DOWN_BEHIND() {
        _TRACE_("turbo_WAY_ZLEFT_DOWN_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_UP_FRONT() {
        _TRACE_("turbo_WAY_ZRIGHT_UP_FRONTLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_UP_BEHIND() {
        _TRACE_("turbo_WAY_ZRIGHT_UP_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_DOWN_FRONT() {
        _TRACE_("turbo_WAY_ZRIGHT_DOWN_FRONTLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_DOWN_BEHIND() {
        _TRACE_("turbo_WAY_ZRIGHT_DOWN_BEHIND() came!");
    }
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

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

