#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
int MyShip::wk_dist = 0;
angle MyShip::wk_angRx = 0;

#define S_OPTION 0
coord MyShip::_lim_top     =  0;
coord MyShip::_lim_bottom  =  0;
coord MyShip::_lim_front   =  0;
coord MyShip::_lim_behaind =  0;
coord MyShip::_lim_zleft   =  0;
coord MyShip::_lim_zright  =  0;

MyShip::MyShip(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "VicViper") {
//MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "jiki") {
//MyShip::MyShip(const char* prm_name) : CubeMapMeshActor(prm_name, "wakka") {
//MyShip::MyShip(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "MyShip";
    MyStgUtil::resetMyShipStatus(_pStatus);
    //changeEffectTechnique("DestBlendOne"); //���Z����Technique�w��

    GameGlobal::init();

    //��ʂ̑傫���ɔ����āA�ړ��͈͂�����
    //���̂������FovX�Ɉˑ�����̂Ŕ������B
    _lim_top     = CFG_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2;      //�㉺�͉�ʍ����̑�̂T��ʕ�
    _lim_bottom  = -(CFG_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2);
    _lim_front   = CFG_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2 ;    //�O�͉�ʕ��̑��2.5��ʕ�
    _lim_behaind = -(CFG_PROPERTY(GAME_BUFFER_WIDTH)*2*LEN_UNIT / 2 ); //��͉�ʕ��̑��1��ʕ�
    _lim_zleft   = CFG_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2;       //����O�͉�ʕ��̑�̂T��ʕ�
    _lim_zright  = -(CFG_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2);
    _TRACE_("MyShip::MyShip �͈� X("<<_lim_behaind<<" ~ "<<_lim_front<<") Y("<<_lim_bottom<<" ~ "<<_lim_top<<") Z("<<_lim_zright<<" ~ "<<_lim_zleft<<")");

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
    _iMvVelo_BeginMT = 40000; //Turbo�ړ��J�n���̈ړ����x�̏����x
    _iMvAcce_MT = -200; //Turbo�ړ����̈ړ����x�̉����x

//    _pMyOptionController = NEW MyOptionController("MY_OPTION_PARENT");
//    addSubLast(_pMyOptionController);

    _pStore_MyShots001 = NEW GgafActorStore("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pStore_MyShots001->addSubLast(pShot);
    }
    addSubGroup(_pStore_MyShots001);

    _pLaserChipStore = NEW LaserChipStore("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setPositionSource(this); //�ʒu��������
        pChip->inactivateImmediately();
        _pLaserChipStore->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipStore);


    _pEffectTurbo001 = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(_pEffectTurbo001);
//    _pEffectTurbo002 = NEW EffectTurbo002("EffectTurbo002");
//    addSubGroup(_pEffectTurbo002);




    //�g���[�X�p����
    _pRing_GeoHistory = NEW GgafLinkedListRing<GgafDx9GeoElem>();
    for (UINT32 i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GgafDx9GeoElem(this));
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

    _pSeTransmitter->useSe(4);
    _pSeTransmitter->set(0, "se-020");
    _pSeTransmitter->set(1,"laser001", 99);
    _pSeTransmitter->set(2,"fire01", 99);
    _pSeTransmitter->set(3,"bse5", 99);

    _iMvVelo_TurboTop = 30000;
    _iMvVelo_TurboBottom = 10000;

    _can_control = true;
    _is_diving = false;

    _blown_veloX = 0;
    _blown_veloY = 0;
    _blown_veloZ = 0;
    _anti_blown_velo = 100;
    _way = WAY_NONE;
    _prev_way = WAY_NONE;
    _is_just_change_way = true;

}
void MyShip::onCreateModel() {
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void MyShip::initialize() {

    //��ʂɐU�蕪��
//    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pStore_MyShots001->extract());
//    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pStore_MyWaves001->extract());
    //getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipStore->extract());

    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
//    _pCollisionChecker->setColliSphere(0, -100000, -50000, 20000, 100000);
// _pCollisionChecker->setColliAAB(0, -100000, -50000, 20000, 10000, 40000, 80000);
      _pCollisionChecker->setColliAAB_Cube(0, 40000);
//    _pCollisionChecker->setColliSphere(1, 0,-100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(2, 0,100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(3, 0,0,-100000, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(4, 0,0,100000, 30000, true, true, true);

    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 7000);

    //setMaterialColor(1.0, 0.5, 0.5);
    setAlpha(1.0);


    _pKurokoB->forceVxMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pKurokoB->forceVyMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pKurokoB->forceVzMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);

    _pKurokoB->setVxMvAcce(0);
    _pKurokoB->setVyMvAcce(0);
    _pKurokoB->setVzMvAcce(0);
    //        _pKurokoA->forceMvVeloRange(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    //        _pKurokoA->addMvVelo(_iMvVelo_BeginMT);  //���x�ǉ�
    //        _pKurokoA->setMvAcce(_iMvAcce_MT);

    _pKurokoA->setFaceAngVelo(AXIS_X, 300);
}


void MyShip::onReset() {
    _frame_soft_rapidshot = 0;
    _is_being_soft_rapidshot = false;
    _just_shot = false;
    _is_shooting_laser = false;
    _frame_shot_pressed = 0;
    _X = _Y = _Z = 0;
    _way = WAY_NONE;
    _prev_way = WAY_NONE;
    _way_switch.reset();
    MyStgUtil::resetMyShipStatus(_pStatus);
}

void MyShip::onActive() {

}




void MyShip::processBehavior() {

    //�X�y�L�����e�X�g
    if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
        _pGgafDx9Model->_specular += 0.1;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pGgafDx9Model->_specular -= 0.1;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
        _pGgafDx9Model->_specular_power += 0.1;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_P)) {
        _pGgafDx9Model->_specular_power -= 0.1;
    }

    if (!_can_control) {
        return;
    }

    //VAMSystem�̎���
    // (Viewpoint Adaptive Moving System ���_�K���^�ړ��V�X�e��)
    _stc = VB_PLAY->getBeingPressedStick();
    if (P_VAM->_pos_camera == VAM_POS_RIGHT) {
        //�E�T�C�h�r���[(�E���獶�փX�N���[��)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //�O��
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //���
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (P_VAM->_pos_camera == VAM_POS_LEFT) {
        //���T�C�h�r���[(������E�փX�N���[��)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //���
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (P_VAM->_pos_camera == VAM_POS_TOP) {
        //�g�b�v�r���[(�ォ�牺�փX�N���[��)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //�O��
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //���
        }
    } else if (P_VAM->_pos_camera == VAM_POS_BOTTOM) {
        //�{�g���r���[(�������փX�N���[��)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //���
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
    } else if (P_VAM->_pos_camera > VAM_POS_TO_BEHIND) {
        //�w��r���[�i�������O�ɃX�N���[���j
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ��
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // ��
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ��
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ��
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    }
    if (VB_PLAY->isReleasedUp(VB_UP)) {
        _way_switch.OFF_UP();    // �� �𗣂�
    }
    if (VB_PLAY->isReleasedUp(VB_RIGHT)) {
        _way_switch.OFF_RIGHT(); // �� �𗣂�
    }
    if (VB_PLAY->isReleasedUp(VB_LEFT)) {
        _way_switch.OFF_LEFT();  // �� �𗣂�
    }
    if (VB_PLAY->isReleasedUp(VB_DOWN)) {
        _way_switch.OFF_DOWN();  // �� �𗣂�
    }
    MoveWay prev_way = _way;
    _way = (MoveWay)(_way_switch.getIndex()); //��L���l�����ꂽ�����l������
    if (prev_way != _way) {
        _is_just_change_way = true;
    } else {
        _is_just_change_way = false;
    }
    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
        int tmp = _iMoveSpeed;
        _iMoveSpeed = _iMoveSpeed / 8; //�I�v�V�������쒆�ړ��͒x��
        (this->*paFuncMove[_way])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
        _iMoveSpeed = tmp;
    } else {
        (this->*paFuncMove[_way])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
    }

    if (VB_PLAY->isPushedDown(VB_TURBO)) {
        //�^�[�{�J�n��
        EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pStore_EffectTurbo002->employForce();
         if (pTurbo002) {
             pTurbo002->locateAs(this);
             pTurbo002->activate();
         }
        (this->*paFuncTurbo[_way])();
    } else {
        //Not�^�[�{�J�n��
        if (VB_PLAY->isBeingPressed(VB_TURBO)) {
            //�^�[�{�����������邱�ƂŁA�ړ�������L�΂�
            _pKurokoB->_veloVxMv *= 0.95;
            _pKurokoB->_veloVyMv *= 0.95;
            _pKurokoB->_veloVzMv *= 0.95;
        } else {
            _pKurokoB->_veloVxMv *= 0.9;
            _pKurokoB->_veloVyMv *= 0.9;
            _pKurokoB->_veloVzMv *= 0.9;
        }
    }

    //�X�s���������悭����Ă���Ȃ�Α��x����߂�
    ang_velo MZ = _angRXTopVelo_MZ-3000; //3000�͒ʏ���񎞂ɑ��x����߂�_angRXTopVelo_MZ�𒴂��Ȃ��悤�ɂ��邽�߁A����O�Ō�������ƌ����Ӗ��iTODO:�v�����j�B
    if (_pKurokoA->_ang_veloFace[AXIS_X] >= MZ) {
        _pKurokoA->_ang_veloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pKurokoA->_ang_veloFace[AXIS_X] <= -MZ) {
        _pKurokoA->_ang_veloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ*2);
    }

    //���E�������͂Ȃ�A�@�̂𐅕��ɂ���i�A�������悭����Ă��Ȃ��ꍇ�Ɍ���BsetStopTarget_FaceAng�̑�4�������p���x����邢�ꍇ�󂯓���j
    if (VB_PLAY->isBeingPressed(VB_LEFT) || VB_PLAY->isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pKurokoA->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < ANGLE180) {
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 < dist && dist < 0) {
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pKurokoA->setMvAcce(0);
        _pKurokoA->setStopTarget_FaceAng(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
    }

    ////////////////////////////////////////////////////



    //���W�ɔ��f
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pScaler->behave();
    _pSeTransmitter->behave();

    //�������
    if (GgafUtil::abs(_blown_veloX) < 1000) {
        _blown_veloX = 0;
    } else if (_blown_veloX > 0) {
        _blown_veloX -= 1000;
    } else if (_blown_veloX < 0) {
        _blown_veloX += 1000;
    }
    if (GgafUtil::abs(_blown_veloY) < 1000) {
        _blown_veloY = 0;
    } else if (_blown_veloY > 0) {
        _blown_veloY -= 1000;
    } else if (_blown_veloY < 0) {
        _blown_veloY += 1000;
    }
    if (GgafUtil::abs(_blown_veloZ) < 1000) {
        _blown_veloZ = 0;
    } else if (_blown_veloZ > 0) {
        _blown_veloZ -= 1000;
    } else if (_blown_veloZ < 0) {
        _blown_veloZ += 1000;
    }
    _X += _blown_veloX;
    _Y += _blown_veloY;
    _Z += _blown_veloZ;


    if (!_is_diving) {
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
    }
    _pRing_GeoHistory->next()->set(this);
}

void MyShip::processJudgement() {
    if (!_can_control) {
        return;
    }
    //���@���Ńe�X�g
    if (VB_PLAY->isBeingPressed(VB_BUTTON8)) {
        _TRACE_("���@���Ńe�X�g");
        throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }


    //�V���b�g�֘A����
    _is_shooting_laser = false;
    if (VB_PLAY->isBeingPressed(VB_SHOT1)) {
        _frame_shot_pressed ++;
        if (_frame_shot_pressed > 30) { //12�t���[���������ςȂ��Ń��[�U�[��
            _is_shooting_laser = true;
        }
    } else {
        _frame_shot_pressed = 0;
    }


    if (_is_shooting_laser) {
        if (VB_PLAY->isBeingPressed(VB_SHOT1)) {//isBeingPressed
            //GgafActorStore�̐�����A�����A�N�^�[�� play ���Ă��Ȃ���΁A�S�Ă̗v�f�� play ���Ă��Ȃ����ƂɂȂ�?�B
            MyStraightLaserChip001* pLaser = (MyStraightLaserChip001*)_pLaserChipStore->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                }
            }
        }
    }

    //�\�t�g�A��
    //1�v�b�V����4F���ɍő�3��
    if (VB_PLAY->isPushedDown(VB_SHOT1)) {
        _is_being_soft_rapidshot = true;
        if (_frame_soft_rapidshot >= SOFT_RAPIDSHOT_INTERVAL) {
            //SOFT_RAPIDSHOT_INTERVAL �t���[�����x���ꍇ
            //�A�˂ƘA�˂̂Ȃ��ڂ������悤�ɂ���
            _frame_soft_rapidshot = _frame_soft_rapidshot % SOFT_RAPIDSHOT_INTERVAL;
        } else {
            //SOFT_RAPIDSHOT_INTERVAL �t���[����葬���A�˂̏ꍇ
            //������󂯓���ċ����I�ɔ��˂ł���(�蓮�A�˂̂ق��������A�˂ł���悤�ɂ������B)
            _frame_soft_rapidshot = 0;
        }
    }
    _just_shot = false;
    if (_is_being_soft_rapidshot) {
        if (_frame_soft_rapidshot % SOFT_RAPIDSHOT_INTERVAL == 0) {
            _just_shot = true;//���������V���b�g���܂����t���O
            MyShot001* pShot = (MyShot001*)_pStore_MyShots001->dispatch();
            if (pShot) {
                _pSeTransmitter->play3D(2);
                pShot->locateAs(this);
            }
            if (_frame_soft_rapidshot >= SOFT_RAPIDSHOT_INTERVAL*(SOFT_RAPIDSHOT_NUM-1)) {
                //SOFT_RAPIDSHOT_NUM ���ł��I������\�t�g�A�ˏI��
                _is_being_soft_rapidshot = false;
            }
        }
    }
    if (_is_being_soft_rapidshot) {
        _frame_soft_rapidshot++;
    }
    MyOptionController* pMyOptionController = P_MYOPTIONCON;

    //    if (VB_PLAY->isPushedDown(VB_SHOT2)) {
    if (VB_PLAY->isBeingPressed(VB_SHOT2)) {
        bool can_fire = true;
        for (int i = 0; i < pMyOptionController->_now_option_num; i++) {
            if (pMyOptionController->_papMyOption[i]->_pTorpedoController->_in_firing) {
                can_fire = false;
                break;
            }
        }
        if (can_fire) {
            for (int i = 0; i < pMyOptionController->_now_option_num; i++) {
                if (i == 0) {
                    _pSeTransmitter->play3D(3);
                }
                pMyOptionController->_papMyOption[i]->_pTorpedoController->fire();
            }
        }
    }



}

void MyShip::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g


    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g
    }

    //�ǂ̏ꍇ���ʂȏ���
    if (pOther->getKind() & KIND_CHIKEI) {

        _blown_veloX = (GgafUtil::sign(_pCollisionChecker->_blown_sgn_vX)*(10000+GgafUtil::abs(_pKurokoB->_veloVxMv)));
        _blown_veloY = (GgafUtil::sign(_pCollisionChecker->_blown_sgn_vY)*(10000+GgafUtil::abs(_pKurokoB->_veloVyMv)));
        _blown_veloZ = (GgafUtil::sign(_pCollisionChecker->_blown_sgn_vZ)*(10000+GgafUtil::abs(_pKurokoB->_veloVzMv)));
    }
    if (pOther->getKind() & KIND_ITEM)  {
    } else {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(0);
    }

    if (pOther->getKind() & KIND_ITEM)  {

    }
}



void MyShip::doNotingMoveInput() {

}

void MyShip::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {

    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_FINISH) {

    }
}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);

}

