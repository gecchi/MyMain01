#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                     prm_model,
                     "x/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW StgChecker(this) ) {
    _pStgChecker = (StgChecker*)_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);


    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcher�� new ���ɐݒ肳���B
    _chiptex_kind = 1;

    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
//    _ahKind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind009" );
//    _ahKind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind010" );
//    _ahKind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind011" );
//    _ahKind[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind012" );
//    _ahKind[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind013" );
//    _ahKind[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind014" );
//    _ahKind[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind015" );
//    _ahKind[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind016" );

//    _hX = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
//    _hY = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
//    _hZ = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );
    _ahRevPosZ[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ001" );
    _ahRevPosZ[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ002" );
    _ahRevPosZ[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ003" );
    _ahRevPosZ[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ004" );
    _ahRevPosZ[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ005" );
    _ahRevPosZ[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ006" );
    _ahRevPosZ[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ007" );
    _ahRevPosZ[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ008" );
//    _ahRevPosZ[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ009" );
//    _ahRevPosZ[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ010" );
//    _ahRevPosZ[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ011" );
//    _ahRevPosZ[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ012" );
//    _ahRevPosZ[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ013" );
//    _ahRevPosZ[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ014" );
//    _ahRevPosZ[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ015" );
//    _ahRevPosZ[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ016" );

    //_hMatWorld_front = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );

    _ahMatWorld_front[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ahMatWorld_front[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ahMatWorld_front[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ahMatWorld_front[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ahMatWorld_front[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ahMatWorld_front[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ahMatWorld_front[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ahMatWorld_front[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
//    _ahMatWorld_front[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front009" );
//    _ahMatWorld_front[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front010" );
//    _ahMatWorld_front[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front011" );
//    _ahMatWorld_front[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
//    _ahMatWorld_front[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
//    _ahMatWorld_front[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
//    _ahMatWorld_front[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
//    _ahMatWorld_front[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );


    _h_nVertexs = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_nVertexs" );

   // _h_cnt_vertec = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_cnt_vertec" );

}

void LaserChip::initialize() {

    _pMover->setMoveVelocity(30000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void LaserChip::onActive() {
    //�o����
    _chiptex_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs�������v�Z�񐔂�ߖ�B
    //���dx,dy,dz�����X�V����B
    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
}

void LaserChip::onInactive() {
    //������
    _pDispatcher->_num_chip_active--;
    //�O��̌q�����ؒf
    if (_pChip_front) {
        _pChip_front->_pChip_behind = NULL;
    }
    _pChip_front = NULL;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;

}

void LaserChip::processBehavior() {

    //���W�ɔ��f
    _pMover->behave();
/*
    //���Ԓn�_�ɂ������蔻��
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //���Ԃ̓����蔻��
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void LaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //���[�U�[���  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chiptex_kind = 2; //���ԃe�N�X�`��
                } else {
                    _chiptex_kind = 3; //�擪�e�N�X�`��
                }
            } else {
                _chiptex_kind = 1; //���ˌ��̖����e�N�X�`��
            }
        } else {
            _chiptex_kind = 1; //�����e�N�X�`��
        }
    } else {
        _chiptex_kind = 4; //�����`�悵�����Ȃ�
    }

    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior,processJudgement�� _pChip_front ���K����Ɏ��s�����B���ӂ���B
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

void LaserChip::processDrawMain() {
TRACE4("--------begin------------------------------LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  001 "<<getName());
    int cnt = 1; //����`��[�x�ɁAGgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  002");
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model =  _pNextDrawActor->_pGgafDx9Model;
            if (pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                cnt++;
                if (cnt > 8) {
                    break;
                }
                //_TRACE_("��cnt="<<cnt<<" _pNextDrawActor="<<_pNextDrawActor->getName());

                _pNextDrawActor= _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  003");
    _set_index = 0;
    _draw_object_num = 1;
    //index   0 1 2 3 4
    //object  1 2 4 8 16
//    if (cnt >= 16) {
//        _set_index = 4;
//        _draw_object_num = 16;
//    } else

    if (cnt >= 8) {
        _set_index = 3;
        _draw_object_num = 8;
    } else if (4 <= cnt &&  cnt <= 7) {
        _set_index = 2;
        _draw_object_num = 4;
    } else if (2 <= cnt &&  cnt <= 3) {
        _set_index = 1;
        _draw_object_num = 2;
    } else {
        _set_index = 0;
        _draw_object_num = 1;
    }
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  cnt="<<cnt<<"/_set_index="<<_set_index<<"/_draw_object_num="<<_draw_object_num);

TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  004");

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshSetEffect SetMatrix(g_matView) �Ɏ��s���܂����B");

//    hr = pID3DXEffect->SetTechnique(_technique);
//    mightDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");


    hr = pID3DXEffect->SetInt(_h_nVertexs, _pMeshSetModel->_nVertices);


    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_h_nVertexs) �Ɏ��s���܂����B2");
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  005");
    //hr = pID3DXEffect->SetInt(_h_cnt_vertec, 0);
    //mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_h_cnt_vertec) �Ɏ��s���܂����B2");



    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;
    for (int i = 0; i < _draw_object_num; i++) {
        //GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(pDrawLaserChipActor, _aMatWorld[i]);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawLaserChipActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
TRACE4("roopstart LaserChip::processDrawMain() pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  006");



        //�e�N�X�`�����
        hr = pID3DXEffect->SetInt(_ahKind[i], pDrawLaserChipActor->_chiptex_kind);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B2");
TRACE4("LaserChip::processDrawMain() pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  007");

        if (pDrawLaserChipActor->_pChip_front != NULL) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  008");

    //        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
    //        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B1");
    //        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
    //        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B1");
    //        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
    //        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B1");
            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_pChip_front->_matWorld)); //TODO:�����ƍs���Ă邩������
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  009");

            //�`�b�v�̏\���̍��E�̉H�̕`�揇�����l����B
            static bool rev_pos_Z; //true = ���_��Z��-1���悸��Bfalse = �������Ȃ�
            static float slant;
            slant = (pDrawLaserChipActor->_pChip_front->_Z - pDrawLaserChipActor->_Z)*1.0 / (pDrawLaserChipActor->_pChip_front->_X - pDrawLaserChipActor->_X)*1.0;
            if (pDrawLaserChipActor->_pChip_front->_X == pDrawLaserChipActor->_X) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  010");

                rev_pos_Z = false;
            } else if (GgafDx9Universe::_pCamera->_view_border_slant2_XZ < slant && slant < GgafDx9Universe::_pCamera->_view_border_slant1_XZ) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  011");
                if (pDrawLaserChipActor->_pChip_front->_X > pDrawLaserChipActor->_X ) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  012");
                    rev_pos_Z = false;
                } else {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  013");
                    rev_pos_Z = true;
                }
            } else {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  014");
                if (pDrawLaserChipActor->_pChip_front->_Z == pDrawLaserChipActor->_Z) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  015");
                    rev_pos_Z = false;
                } else {
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  016");
                    //��2009/5/19 �����F���𔻒肵�悤�Ƃ��Ă���̂���
                    //XZ���ʂɂ����āA���[�U�[�`�b�v���J�����̉E��ʉ߂���̂�����ʉ߂���̂��A
                    //�Q�_(X1,Z1)(X2,Z2) ��ʂ钼���̕������ɂ����āA Z = CamZ �̎���X���W��
                    //X = ((CamZ-Z1)*(X2-X1)/ (Z2-Z1))+X1 �ƂȂ�B�Q�_�Ƀ`�b�v�̍��W�A���̃`�b�v�̍��W������
                    //���̎���X��CamX��菬������΂̃J��������ʉ߂��邱�ƂɂȂ�B���̏ꍇ�`�b�v�̒��_�o�b�t�@��Z���W�𔽓](-1�{)���H�̕`�揇����ύX����B
                    //�H�Ƃ͉��}�̇@�ƇC�̃|���S���̂��Ƃ������B�@�`�C���f�t�H���g�̕`�揇���B
                    //����̊p�x�ł͂��̇@�ƇC�̕`�揇�Ԃ�ς��Ȃ���΁A�������̂��߃M�U�M�U�ɂȂ�ꍇ������Ƃ������Ƃł���̂��B
                    //         ������
                    //         ��
                    //
                    //          �_
                    //         �� �_
                    //         ���A �_
                    //  (0,0,0)��    ��        ����
                    // ����������----����   ����
                    //  �_  �C �F�_  ��   �_
                    //    �_   �F  �_��  �@ �_
                    //       ������������������
                    //         ��    ��
                    //          �_ �B��  �_
                    //            �_ ��    �_ �����i�����j
                    //               ��      ��

                    static float crossCamX;
                    crossCamX = ((float)(GgafDx9Universe::_pCamera->_Z - pDrawLaserChipActor->_Z)) *
                                 ((float)(pDrawLaserChipActor->_pChip_front->_X - pDrawLaserChipActor->_X) /
                                  (float)(pDrawLaserChipActor->_pChip_front->_Z - pDrawLaserChipActor->_Z)
                                 ) + pDrawLaserChipActor->_X;
                    if (crossCamX < GgafDx9Universe::_pCamera->_X) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  017");
                        rev_pos_Z = true;
                    } else {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  018");
                        rev_pos_Z = false;
                    }
                }
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  019");

                if (pDrawLaserChipActor->_pChip_front->_Z > pDrawLaserChipActor->_Z) {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  020");

                    //��L�̔���̓��[�U�[�͉������O�֗��Ă�ꍇ�̔���A��O���牜�֔�ԏꍇ�͔���͔��]���邱�ƂɂȂ�B
                    rev_pos_Z = !rev_pos_Z;
                }
            }
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  021");

            hr = pID3DXEffect->SetBool(_ahRevPosZ[i], rev_pos_Z);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) �Ɏ��s���܂����B1");

        } else {
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  022");

            //�O���ɘA���̃`�b�v�������ꍇ�B
//            hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
//            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B2");
//            hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
//            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B2");
//            hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
//            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B2");

            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_matWorld) ); //�擪���Ȃ��̂Ŏ��M��_matWorld
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  022-2");
            hr = pID3DXEffect->SetBool(_ahRevPosZ[i], false);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) �Ɏ��s���܂����B2");
        }
TRACE4("LaserChip::processDrawMain()  pDrawLaserChipActor="<<pDrawLaserChipActor->getName()<<" _pMeshSetModel="<<_pMeshSetModel->getName()<<"  i="<<i<<"  023");


        pDrawLaserChipActor = (LaserChip*)(pDrawLaserChipActor -> _pNext_TheSameDrawDepthLevel);
    }
TRACE4("loopend LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  024");

    _pMeshSetModel->draw(this);

    //�A�N�e�B�u��i�߂Ă���
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  _pMeshSetModel->draw(this) Done");
TRACE4("LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  _draw_object_num - 1 = "<<(_draw_object_num - 1)<<"��  _pActor_DrawActive��i�߂Ƃ��܂�");

    for(int i = 0; i < _draw_object_num - 1; i++) {
        GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
TRACE4("--------end------------------------------LaserChip::processDrawMain() _pMeshSetModel="<<_pMeshSetModel->getName()<<"  999 "<<getName());

}

#ifdef OREDEBUG

void LaserChip::processDrawTerminate() {
    //�����蔻��̈�\��
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);

}

