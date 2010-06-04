#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


//MyOptionParent::MyOptionParent(const char* prm_name) :
//    DefaultMeshActor(prm_name, "Gizmo") {

MyOptionParent::MyOptionParent(const char* prm_name) :
  GgafDx9GeometricActor(prm_name,
                            NULL) {
    _is_handle_move_mode = false;
    _is_free_from_myship_mode = false;
    _return_to_default_position_seq = false;
    _angVelo_Turn = 3000;
    _veloOptionsMv = 20000;



    _renge = 80000;
    _pMover->forceVxMvVeloRange(-_renge, _renge);
    _pMover->forceVyMvVeloRange(-_renge, _renge);
    _pMover->forceVzMvVeloRange(-_renge, _renge);

    _pMover->forceVxMvAcceRange(-_renge / 30, _renge / 30);
    _pMover->forceVyMvAcceRange(-_renge / 30, _renge / 30);
    _pMover->forceVzMvAcceRange(-_renge / 30, _renge / 30);


    for (int i = 0; i < 8; i++) {
        _paMyOption[i] = NULL;
    }

    _paMyOption[0] = NEW MyOption("MY_OPTION01", 0, this);
    _paMyOption[0]->setInitializeProperty(60000, ANGLE0, 0, 500);
    _paMyOption[0]->setMaterialColor(1.0, 1.0, 1.0);
    addSubGroup(_paMyOption[0]);

    _paMyOption[1] = NEW MyOption("MY_OPTION02", 1, this);
    _paMyOption[1]->setInitializeProperty(60000, ANGLE90, 0, 500);
    _paMyOption[1]->setMaterialColor(0.0, 1.0, 1.0);
    addSubGroup(_paMyOption[1]);

    _paMyOption[2] = NEW MyOption("MY_OPTION03", 2, this);
    _paMyOption[2]->setInitializeProperty(60000, ANGLE180, 0, 500);
    _paMyOption[2]->setMaterialColor(1.0, 0, 1.0);
    addSubGroup(_paMyOption[2]);

    _paMyOption[3] = NEW MyOption("MY_OPTION04", 4, this);
    _paMyOption[3]->setInitializeProperty(60000, ANGLE270, 0, 500);
    _paMyOption[3]->setMaterialColor(0, 1.0, 0);
    addSubGroup(_paMyOption[3]);

    _paMyOption[4] = NEW MyOption("MY_OPTION05", 5, this);
    _paMyOption[4]->setInitializeProperty(120000, ANGLE0, 0, -500);
    _paMyOption[4]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
    addSubGroup(_paMyOption[4]);

    _paMyOption[5] = NEW MyOption("MY_OPTION06", 6, this);
    _paMyOption[5]->setInitializeProperty(120000, ANGLE90, 0, -500);
    _paMyOption[5]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
    addSubGroup(_paMyOption[5]);

    _paMyOption[6] = NEW MyOption("MY_OPTION07", 7, this);
    _paMyOption[6]->setInitializeProperty(120000, ANGLE180, 0, -500);
    _paMyOption[6]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
    addSubGroup(_paMyOption[6]);

    _paMyOption[7] = NEW MyOption("MY_OPTION08", 8, this);
    _paMyOption[7]->setInitializeProperty(120000, ANGLE270, 0, -500);
    _paMyOption[7]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
    _paMyOption[7]->setAlpha(0.3);
    addSubGroup(_paMyOption[7]);



    for (int i = 0; i < 8; i++) {
        _paMyOption[i]->activate();
    }

    //�M�Y��
    _pGizmo = NEW MyOptionParentGizmo("MyPGizmo");
    addSubGroup(_pGizmo);
    //�����x�N�g��
    _pDirectionVector = NEW MyOptionParentDirectionVector("MyPDirectionVector");
    addSubGroup(_pDirectionVector);

    //�g���[�X�p����
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(pMYSHIP));
    }

}

void MyOptionParent::initialize() {

    _pMover->setMvVelo(0);
    _pMover->forceRyMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->forceRzMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->setRzRyMvAng(0,0);
    _way_myship_prev = pMYSHIP->_way;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->behave();
}

void MyOptionParent::processBehavior() {

    if (VB->isDoublePushedDown(VB_OPTION,8,8)) {
        //���Ƃɖ߂�
        _pMover->execTagettingMvAngSequence(
                        0,
                        0,
                        20000, 0,
                        TURN_CLOSE_TO,
                        false
                 );
        _is_free_from_myship_mode = false;
        _is_handle_move_mode = false;
        _return_to_default_position_seq = true;

        for (int i = 0; i < 8; i++) {
            //�I�v�V�����̔��a�ʒu�����ɖ߂��w��
            _paMyOption[i]->_return_to_default_radiusPosition_seq = true;
            _paMyOption[i]->_return_to_default_angExpanse_seq= true;
        }


    } else if (VB->isBeingPressed(VB_OPTION) && !VB->isBeingPressed(VB_TURBO)) {
        //�I�v�V������������
        if (VB->isBeingPressed(VB_UP)) {
            _pMover->addRzMvAng(_angVelo_Turn);
        }
        if (VB->isBeingPressed(VB_DOWN)) {
            _pMover->addRzMvAng(-_angVelo_Turn);
        }
        if (VB->isBeingPressed(VB_RIGHT)) {
            _pMover->addRyMvAng(_angVelo_Turn);
        }
        if (VB->isBeingPressed(VB_LEFT)) {
            _pMover->addRyMvAng(-_angVelo_Turn);
        }

    }

    if (VB->isRoundPush(VB_OPTION)) {
    //if (VB->isPushedDown(VB_OPTION) && GgafDx9Input::isBeingPressedKey(DIK_S)) {
        if (_paMyOption[0]) {
            _is_free_from_myship_mode = true;
            _is_handle_move_mode = true;
            _pMover->setVxMvAcce(0);
            _pMover->setVyMvAcce(0);
            _pMover->setVzMvAcce(0);
            _pMover->setVxMvVelo(0);
            _pMover->setVyMvVelo(0);
            _pMover->setVzMvVelo(0);

        }
    }

    if (_is_free_from_myship_mode) {
        if (VB->isBeingPressed(VB_OPTION) && _is_handle_move_mode) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̃I�v�V�����ړ����x�݂̂�ݒ�B
            _pMover->setMvVelo(GgafDx9Util::COS[_paMyOption[0]->_angExpanse/ ANGLE_RATE] * _veloOptionsMv);
            //���񔼌a�������x�̏�����MyOption�N���X�ōs���B
        } else {
            _is_handle_move_mode = false;
            _pMover->setMvVelo(0);
        }
    } else {
        if (_return_to_default_position_seq) {
            //���̈ʒu��
            int dx = pMYSHIP->_X - (_X + _pMover->_veloVxMv*6);
            int dy = pMYSHIP->_Y - (_Y + _pMover->_veloVyMv*6);
            int dz = pMYSHIP->_Z - (_Z + _pMover->_veloVzMv*6);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
            if (abs(_X - pMYSHIP->_X) < 10000 &&
                abs(_Y - pMYSHIP->_Y) < 10000 &&
                abs(_Z - pMYSHIP->_Z) < 10000 &&
                abs(_pMover->_veloVxMv) < 20000 &&
                abs(_pMover->_veloVyMv) < 20000 &&
                abs(_pMover->_veloVzMv) < 20000    ) {

                _TRACE_("���ǂ����I");
                _pMover->setVxMvVelo(0);
                _pMover->setVyMvVelo(0);
                _pMover->setVzMvVelo(0);
                _pMover->setVxMvAcce(0);
                _pMover->setVyMvAcce(0);
                _pMover->setVzMvAcce(0);
                setGeometry(pMYSHIP);
                _return_to_default_position_seq = false;
            }

        } else {
            setGeometry(pMYSHIP);
        }
    }

    //�M�Y��
    _pGizmo->setGeometry(this);
    _pGizmo->_pMover->setRzRyMvAng(_pMover->_angRzMv, _pMover->_angRyMv);

    _pMover->behave();
    _pRing_GeoHistory->next()->set(this);
}



MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}

