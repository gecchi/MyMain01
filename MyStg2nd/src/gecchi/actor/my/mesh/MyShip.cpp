#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
int MyShip::wk_dist = 0;
angle MyShip::wk_angRx = 0;

#define S_OPTION 0
int MyShip::_lim_top     =  0;
int MyShip::_lim_bottom  =  0;
int MyShip::_lim_front   =  0;
int MyShip::_lim_behaind =  0;
int MyShip::_lim_zleft   =  0;
int MyShip::_lim_zright  =  0;

//MyShip::MyShip(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "Flora") {
MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "jiki") {
//MyShip::MyShip(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "MyShip";
    MyStgUtil::resetMyShipStatus(_pStatus);
    //chengeEffectTechnique("DestBlendOne"); //���Z����Technique�w��

    GameGlobal::init();
    GameGlobal::_pMyShip = this;
    //��ʂ̑傫���ɔ����āA�ړ��͈͂�����
    //���̂������FovX�Ɉˑ�����̂Ŕ������B
    _lim_top     = GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2;      //�㉺�͉�ʍ����̑�̂S��ʕ�
    _lim_bottom  = -(GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2);
    _lim_front   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*3*LEN_UNIT / 2 ;    //�O��͉�ʕ��̑�̂R��ʕ�
    _lim_behaind = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*0.45*LEN_UNIT / 2 );
    _lim_zleft   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2;       //����O�͉�ʕ��̑�̂S��ʕ�
    _lim_zright  = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2);

    /** �ړ��X�s�[�h���x�� */
    _lv_MoveSpeed = 2;
    /** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
    _iMoveSpeed = 5000;
    //CommonScene��new�̏ꍇ�ݒ�
    _angRXVelo_BeginMZ = 1000; //�����͎�O�֒ʏ�Z�ʏ�ړ��J�n����X����]�p���x�̏����x
    _angRXAcce_MZ = 300; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏��p�����x
    _angRXTopVelo_MZ = 5000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏���p���x
    _angRXStop_MZ = 90000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p�̖ڕW��~�p�x

    //_angRXVelo_BeginMZT = 23000; //�����͎�O��Turbo�ړ��J�n����X����]�p���x�̏����x
    _angRXVelo_BeginMZT = 40000;

    _iMvBtmVelo_MT = 0; //Turbo�ړ����̈ړ����x�̍Œᑬ�x
    _iMvVelo_BeginMT = 10000; //Turbo�ړ��J�n���̈ړ����x�̏����x
    _iMvAcce_MT = -200; //Turbo�ړ����̈ړ����x�̉����x

    _way = WAY_FRONT;
    MyOptionParent* pMyOptionParent = NEW MyOptionParent("MY_OPTION_PARENT");
    addSubLast(pMyOptionParent);

    _pDispatcher_MyShots001 = NEW GgafActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 10; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubLast(_pDispatcher_MyShots001); //���T�u

    _pDispatcher_MyWaves001 = NEW GgafActorDispatcher("RotWave001");
    MyWave001* pWave;
    for (int i = 0; i < 10; i++) { //���e�X�g�b�N
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateImmediately();
        _pDispatcher_MyWaves001->addSubLast(pWave);
    }
    addSubLast(_pDispatcher_MyWaves001); //���T�u

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        Sleep(2); //�H��ɋC���g���B
        stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setPositionSource(this); //�ʒu��������
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipDispatcher);


    _pEffectTurbo001 = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(_pEffectTurbo001);
    _pEffectTurbo002 = NEW EffectTurbo002("EffectTurbo002");
    addSubGroup(_pEffectTurbo002);
    //�g���[�X�p����
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }

    _iMoveVelo = 0;

    //     X   Y   Z
    //    -----------
    //    -1  -1  -1
    //     0   0   0    �̑S�̂�+1����3�i���ň���
    //    +1  +1  +1

    //���ꂼ��̃X�C�b�`�̏�Ԃɉ����������̊֐��e�[�u���z��B
    /////////////// X  Y  Z
    paFuncMove[TN(-1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    paFuncMove[TN(-1,-1, 0)] = &MyShip::move_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    paFuncMove[TN(-1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    paFuncMove[TN(-1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    paFuncMove[TN(-1, 0, 0)] = &MyShip::move_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    paFuncMove[TN(-1, 0, 1)] = &MyShip::move_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    paFuncMove[TN(-1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    paFuncMove[TN(-1, 1, 0)] = &MyShip::move_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    paFuncMove[TN(-1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    paFuncMove[TN( 0,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    paFuncMove[TN( 0,-1, 0)] = &MyShip::move_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    paFuncMove[TN( 0,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    paFuncMove[TN( 0, 0,-1)] = &MyShip::move_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    paFuncMove[TN( 0, 0, 0)] = &MyShip::move_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    paFuncMove[TN( 0, 0, 1)] = &MyShip::move_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    paFuncMove[TN( 0, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    paFuncMove[TN( 0, 1, 0)] = &MyShip::move_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    paFuncMove[TN( 0, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    paFuncMove[TN( 1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    paFuncMove[TN( 1,-1, 0)] = &MyShip::move_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    paFuncMove[TN( 1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    paFuncMove[TN( 1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    paFuncMove[TN( 1, 0, 0)] = &MyShip::move_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    paFuncMove[TN( 1, 0, 1)] = &MyShip::move_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    paFuncMove[TN( 1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    paFuncMove[TN( 1, 1, 0)] = &MyShip::move_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    paFuncMove[TN( 1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26


    paFuncTurbo[TN(-1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    paFuncTurbo[TN(-1,-1, 0)] = &MyShip::turbo_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    paFuncTurbo[TN(-1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    paFuncTurbo[TN(-1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    paFuncTurbo[TN(-1, 0, 0)] = &MyShip::turbo_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    paFuncTurbo[TN(-1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    paFuncTurbo[TN(-1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    paFuncTurbo[TN(-1, 1, 0)] = &MyShip::turbo_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    paFuncTurbo[TN(-1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    paFuncTurbo[TN( 0,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    paFuncTurbo[TN( 0,-1, 0)] = &MyShip::turbo_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    paFuncTurbo[TN( 0,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    paFuncTurbo[TN( 0, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    paFuncTurbo[TN( 0, 0, 0)] = &MyShip::turbo_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    paFuncTurbo[TN( 0, 0, 1)] = &MyShip::turbo_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    paFuncTurbo[TN( 0, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    paFuncTurbo[TN( 0, 1, 0)] = &MyShip::turbo_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    paFuncTurbo[TN( 0, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    paFuncTurbo[TN( 1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    paFuncTurbo[TN( 1,-1, 0)] = &MyShip::turbo_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    paFuncTurbo[TN( 1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    paFuncTurbo[TN( 1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    paFuncTurbo[TN( 1, 0, 0)] = &MyShip::turbo_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    paFuncTurbo[TN( 1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    paFuncTurbo[TN( 1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    paFuncTurbo[TN( 1, 1, 0)] = &MyShip::turbo_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    paFuncTurbo[TN( 1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26

    _pSeReflector->useSe(2);
    _pSeReflector->set(0, "se-020");
    _pSeReflector->set(1,"laser001", 99);

    char rankstr[80] = {0} ;// �S��0�ŏ�����
    MyStgUtil::getRankStr(99999, rankstr);
    _TRACE_("RANKSTR:"<<rankstr);


    _iMvVelo_TurboTop = 30000;
    _iMvVelo_TurboBottom = 10000;
}

void MyShip::onActive() {
    MyStgUtil::resetMyShipStatus(_pStatus);
}


void MyShip::initialize() {



    //��ʂɐU�蕪��
    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyShots001->extract());
    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyWaves001->extract());
    //getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 5000);
//    _pCollisionChecker->setColliAAB(0, -20000, -20000, -20000, 20000, 20000, 20000);
//    _pCollisionChecker->setColliSphere(1, 0,-100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(2, 0,100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(3, 0,0,-100000, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(4, 0,0,100000, 30000, true, true, true);

    _pMover->setMvVelo(0);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 7000);

    _pMover->forceVxMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pMover->forceVyMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pMover->forceVzMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);

    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    //        _pMover->forceMvVeloRange(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    //        _pMover->addMvVelo(_iMvVelo_BeginMT);  //���x�ǉ�
    //        _pMover->setMvAcce(_iMvAcce_MT);

    _pMover->setFaceAngVelo(AXIS_X, 300);
}

void MyShip::processBehavior() {

    //�I���W�i���V�X�e�� VAMSystem�̎���
    // (Viewpoint Adaptive Moving System ���_�K���^�ړ��V�X�e��)
    _stc = VB->getBeingPressedStick();
    if (GameMainScene::_pGameMainScene->_pos_camera == CAM_POS_RIGHT) {
        //�E�T�C�h�r���[(�E���獶�փX�N���[��)
        if (VB->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //�O��
        }
        if (VB->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //���
        }
        if (VB->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (GameMainScene::_pGameMainScene->_pos_camera == CAM_POS_LEFT) {
        //���T�C�h�r���[(������E�փX�N���[��)
        if (VB->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //���
        }
        if (VB->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
        if (VB->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (GameMainScene::_pGameMainScene->_pos_camera == CAM_POS_TOP) {
        //�g�b�v�r���[(�ォ�牺�փX�N���[��)
        if (VB->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //�O��
        }
        if (VB->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //���
        }
    } else if (GameMainScene::_pGameMainScene->_pos_camera == CAM_POS_BOTTOM) {
        //�{�g���r���[(�������փX�N���[��)
        if (VB->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //���
        }
        if (VB->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
    } else if (GameMainScene::_pGameMainScene->_pos_camera > CAM_POS_TO_BEHIND) {
        //�w��r���[�i�������O�ɃX�N���[���j
        if (VB->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    }
    if (VB->isReleasedUp(VB_UP)) {
        _way_switch.OFF_UP();    // �� �𗣂�
    }
    if (VB->isReleasedUp(VB_RIGHT)) {
        _way_switch.OFF_RIGHT(); // �� �𗣂�
    }
    if (VB->isReleasedUp(VB_LEFT)) {
        _way_switch.OFF_LEFT();  // �� �𗣂�
    }
    if (VB->isReleasedUp(VB_DOWN)) {
        _way_switch.OFF_DOWN();  // �� �𗣂�
    }
    _way = (MoveWay)(_way_switch.getIndex()); //��L���l�����ꂽ�����l������

    if (VB->isBeingPressed(VB_OPTION)) {
        int tmp = _iMoveSpeed;
        _iMoveSpeed = _iMoveSpeed / 8; //�I�v�V�������쒆�ړ��͒x��
        (this->*paFuncMove[_way])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
        _iMoveSpeed = tmp;
    } else {
        (this->*paFuncMove[_way])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
    }

    if (VB->isPushedDown(VB_TURBO)) {
        //�^�[�{�J�n��
        _pEffectTurbo002->activate();
        _pEffectTurbo002->setGeometry(this);
        (this->*paFuncTurbo[_way])();
    } else {
        //Not�^�[�{�J�n��
        if (VB->isBeingPressed(VB_TURBO)) {
            //�^�[�{�����������邱�ƂŁA�ړ�������L�΂�
            _pMover->_veloVxMv *= 0.95;
            _pMover->_veloVyMv *= 0.95;
            _pMover->_veloVzMv *= 0.95;
        } else {
            _pMover->_veloVxMv *= 0.9;
            _pMover->_veloVyMv *= 0.9;
            _pMover->_veloVzMv *= 0.9;
        }
    }

    //�X�s���������悭����Ă���Ȃ�Α��x����߂�
    angvelo MZ = _angRXTopVelo_MZ-3000; //3000�͒ʏ���񎞂ɑ��x����߂�_angRXTopVelo_MZ�𒴂��Ȃ��悤�ɂ��邽�߁A����O�Ō�������ƌ����Ӗ��iTODO:�v�����j�B
    if (_pMover->_angveloFace[AXIS_X] >= MZ) {
        _pMover->_angveloFace[AXIS_X] *= 0.93;
        //_pMover->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pMover->_angveloFace[AXIS_X] <= -MZ) {
        _pMover->_angveloFace[AXIS_X] *= 0.93;
        //_pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ*2);
    }

    //���E�������͂Ȃ�A�@�̂𐅕��ɂ���i�A�������悭����Ă��Ȃ��ꍇ�Ɍ���BsetStopTarget_FaceAng�̑�4�������p���x����邢�ꍇ�󂯓���j
    if (VB->isBeingPressed(VB_LEFT) || VB->isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pMover->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < ANGLE180) {
            _pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 < dist && dist < 0) {
            _pMover->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setMvAcce(0);
        _pMover->setStopTarget_FaceAng(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
    }

    ////////////////////////////////////////////////////



    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
        _TRACE_("(X,Y,Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
    }


    //���W�ɔ��f
    _pMover->behave();
    _pSeReflector->behave();

    if (_Y > MyShip::_lim_top) {
        _Y = MyShip::_lim_top;
    }
    if (_Y < MyShip::_lim_bottom ) {
        _Y = MyShip::_lim_bottom;
    }

    if (_X > MyShip::_lim_front) {
        _X = MyShip::_lim_front;
    }
    if (_X < MyShip::_lim_behaind) {
        _X = MyShip::_lim_behaind;
    }

    if (_Z > MyShip::_lim_zleft) {
        _Z = MyShip::_lim_zleft;
    }
    if (_Z < MyShip::_lim_zright) {
        _Z = MyShip::_lim_zright;
    }
    _pRing_GeoHistory->next()->set(this);
}

void MyShip::processJudgement() {
    //�V���b�g�֘A����
    if (VB->isBeingPressed(VB_SHOT2)) {//isBeingPressed

        //GgafActorDispatcher�̐�����A�����A�N�^�[�� play ���Ă��Ȃ���΁A�S�Ă̗v�f�� play ���Ă��Ȃ����ƂɂȂ�?�B
        MyStraightLaserChip001* pLaser = (MyStraightLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaser != NULL) {
            pLaser->activate();
            if (pLaser->_pChip_front == NULL) {
                _pSeReflector->play3D(1);
            }
        }
    }

    //�V���b�g�{�^��
    if (VB->isPushedDown(VB_SHOT1)) {
        MyWave001* pWave = (MyWave001*)_pDispatcher_MyWaves001->employ();
        if (pWave != NULL) {
            pWave->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->activate();
                pExplo001->setGeometry(this);
            }
        }
    } else if (VB->arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot != NULL) {
            pShot->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
                pExplo001->activate();
            }
        }
    }
}

void MyShip::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    _pSeReflector->play3D(0);
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(pOther);
        pExplo001->activate();
    }
    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g


    }

}



void MyShip::doNotingMoveInput() {

}

void MyShip::transactShot(GgafDx9GeometricActor* prm_pActor) {

}

void MyShip::equipOption() {
//
//    if (_state.eq_option >= EQ_MAX_OPTION) {
//        return;
//    }
//    MyOption* pOption = (MyOption*)_pSubFirst;
//    for (int i = 0; i < _state.eq_option; i++) {
//        pOption = (MyOption*)(pOption->getNext());
//    }
//    if (_state.eq_option == 0) {
//        pOption->setRadicalActor(this);
//    } else {
//        pOption->setRadicalActor((GgafDx9GeometricActor*)pOption->getPrev());
//    }
//
//    _state.eq_option++;
//    pOption->activate();

}




bool MyShip::isDoublePushedDown(vbsta prm_VB) {
    //�ߋ��ɑk��Ȃ��猟��
    DWORD dwFrameApply;
    DWORD dwFrameAgo = 1;
    VirtualButton::VBMap* pVBMap = VB->getPastVBMap(dwFrameAgo);
    //���O�͕K��������Ă��Ă͑ʖځA�j���[�g�����łȂ���΂���
    if ((pVBMap->_state & prm_VB) == 0) {

        dwFrameAgo++;
        //���̑O��5�t���[���ȓ��̂ǂ����ŉ����Ă��Ȃ���΂Ȃ�Ȃ�
        dwFrameApply = dwFrameAgo + 7;//���e�t���[��
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB->getPastVBMap(dwFrameAgo);
            if (pVBMap->_state & prm_VB) {
                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //�s���i
        }

        //����ɂ�������ȑO5�t���[���ȓ��̂ǂ����ŉ�����Ă��Ă͑ʖ�
        dwFrameApply = dwFrameAgo + 7;//���e�t���[��
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB->getPastVBMap(dwFrameAgo);
            if ((pVBMap->_state & prm_VB) == 0) {

                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //�s���i
        }
        return true;

    } else {
        return false;
    }

}


MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);

}

