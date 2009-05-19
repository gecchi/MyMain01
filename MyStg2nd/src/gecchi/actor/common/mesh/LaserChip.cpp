#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshActor(prm_name,
                     prm_model,
                     "X/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {
    _pChecker = (StgChecker*)_pGeoChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcher�� new ���ɐݒ肳���B
    _chiptex_kind = 1;

    _hKind = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind" );
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );
    _hRevPosZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ" );
    _hMatWorld_front = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );
}

void LaserChip::initialize() {

    _pGeoMover->setMoveVelocity(30000);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
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
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
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
    _pGeoMover->behave();
/*
    //���Ԓn�_�ɂ������蔻��
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //���Ԃ̓����蔻��
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);

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
}

void LaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");

//    hr = pID3DXEffect->SetTechnique(_technique);
//    mightDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");

    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior�� _pChip_front ���K����Ɏ��s�����B���ӂ���B
    GgafDx9UntransformedActor::updateWorldMatrix_Mv(this, _matWorld);

    //�e�N�X�`�����
    hr = pID3DXEffect->SetInt(_hKind, _chiptex_kind);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B2");

    if (_pChip_front != NULL) {
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &(_pChip_front->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");

        //�`�b�v�̏\���̍��E�̉H�̕`�揇�����l����B
        static bool rev_pos_Z; //true = ���_��Z��-1���悸��Bfalse = �������Ȃ�
        static float slant;
        slant = (_pChip_front->_Z - _Z)*1.0 / (_pChip_front->_X - _X)*1.0;
        if (_pChip_front->_X == _X) {
            rev_pos_Z = false;
        } else if (GgafDx9Universe::_pCamera->_view_border_slant2_XZ < slant && slant < GgafDx9Universe::_pCamera->_view_border_slant1_XZ) {
            if (_pChip_front->_X > _X ) {
                rev_pos_Z = false;
            } else {
                rev_pos_Z = true;
            }
        } else {
            if (_pChip_front->_Z == _Z) {
                rev_pos_Z = false;
            } else {
                //��2009/5/19 �����F���𔻒肵�悤�Ƃ��Ă���̂���
                //XZ���ʂɂ����āA���[�U�[�`�b�v���J�����̉E��ʉ߂���̂�����ʉ߂���̂��A
                //�Q�_(X1,Z1)(X2,Z2) ��ʂ钼���̕����� Z = CamZ �̎���X���W��
                //X = ((CamZ-Z1)*(X2-X1)/ (Z2-Z1))+X1 �ƂȂ�B�Q�_�Ƀ`�b�v�̍��W�A���̃`�b�v�̍��W������
                //���̎���X��CamX��菬������΂̃J��������ʉ߂��邱�ƂɂȂ�B���̏ꍇ�`�b�v��Z���W���_�𔽓]���H�̕`�揇����ύX����B
                //�H�Ƃ͉��}�̇@�ƇC�̃|���S���̂��Ƃł���B�@�`�C���f�t�H���g�̕`�揇���B
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
                crossCamX = ((float)(GgafDx9Universe::_pCamera->_Z - _Z)) * ((float)(_pChip_front->_X - _X) / (float)(_pChip_front->_Z - _Z)) + _X;
                if (crossCamX < GgafDx9Universe::_pCamera->_X) {
                    rev_pos_Z = true;
                } else {
                    rev_pos_Z = false;
                }
            }
            if (_pChip_front->_Z > _Z) {
                //��L�̔���̓��[�U�[�͉������O�֗��Ă�ꍇ�̔���A��O���牜�̏ꍇ�͔���͔��]���邱�ƂɂȂ�B
                rev_pos_Z = !rev_pos_Z;
            }
        }
        hr = pID3DXEffect->SetBool(_hRevPosZ, rev_pos_Z);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) �Ɏ��s���܂����B1");

    } else {
        //�O���ɘA���̃`�b�v�������ꍇ�B
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &_matWorld );
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetBool(_hRevPosZ, false);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) �Ɏ��s���܂����B2");
    }

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

//	UINT numPass;
//    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() �Ɏ��s���܂����B");
//
//    //TODO:2009/05/15 BeginPass�̏����͂��d�������ƂɋC�����B���ʂ�BeginPass��EndPass����菜���������@���������̂��E�E�E�B
//    hr = pID3DXEffect->BeginPass(0);
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass(0) �Ɏ��s���܂����B");
    _pMeshModel->draw(this);
//    hr = pID3DXEffect->EndPass();
//
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() �Ɏ��s���܂����B");
//    hr = pID3DXEffect->End();
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() �Ɏ��s���܂����B");

}

#ifdef OREDEBUG

void LaserChip::processDrawTerminate() {
    //�����蔻��̈�\��
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {

}

