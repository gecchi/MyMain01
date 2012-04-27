#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_CURSOR_MOVE_METER = 0   ,
    SE_CURSOR_MOVE_LEVEL       ,
    SE_CURSOR_MOVE_LEVEL_CANCEL,
    SE_CURSOR_BAD_MOVE,
    SE_EXECUTE_LEVELUP_MAGIC   ,
    SE_EXECUTE_LEVELDOWN_MAGIC ,
    SE_EXECUTE_CANCEL_LEVELUP_MAGIC   ,
    SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC ,
    SE_EXECUTE_BAD_LEVEL       ,
};

MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx;
    width_ = PX_C(width_px_);
    height_ = PX_C(height_px_);

//    _X = PX_C(100);
//    _Y = PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - (height_px_*2));
    _Z = 5;
//    AmountGraph qu_;
//    qu_.set(1.0);
//    qu_.config(400.0, 1.0);
//    float value_ = 1000;
//    qu_.config(400.0f, value_);
//    AmountGraph qu_();
//    [0][0]  [1][0]  [2][0]  [3][0]
//    [0][1]  [1][1]  [2][1]  [3][1]
//    [0][2]  [1][2]  [2][2]  [3][2]
//    [0][3]  [1][3]  [2][3]  [3][3]
//    [0][4]  [1][4]  [2][4]  [3][4]
//    [0][5]  [1][5]  [2][5]  [3][5]
//    [0][6]  [1][6]  [2][6]  [3][6]
//    [0][7]  [1][7]  [2][7]  [3][7]
//
//    [4][0]  [5][0]  [6][0]  [7][0]
//    [4][1]  [5][1]  [6][1]  [7][1]
//    [4][2]  [5][2]  [6][2]  [7][2]
//    [4][3]  [5][3]  [6][3]  [7][3]
//    [4][4]  [5][4]  [6][4]  [7][4]
//    [4][5]  [5][5]  [6][5]  [7][5]
//    [4][6]  [5][6]  [6][6]  [7][6]
//    [4][7]  [5][7]  [6][7]  [7][7]
//


    mp_.config(600, 10000); //�l 10000 �ŕ\����400px�Ƃ���B
    mp_.set(10000);           //�����l��5000
    ringMagics_.addLast(NEW TractorMagic("TRACTOR", &mp_));
    ringMagics_.addLast(NEW SpeedMagic("SPEED", &mp_));
    ringMagics_.addLast(NEW LockonMagic("LOCKON", &mp_));
    ringMagics_.addLast(NEW TorpedoMagic("TORPEDO", &mp_));
    ringMagics_.addLast(NEW LaserMagic("LASER", &mp_));
    ringMagics_.addLast(NEW OptionMagic("OPTION", &mp_));
    for (int i = 0; i < ringMagics_.length(); i++) {
        addSubGroup(ringMagics_.getNext(i));
    }

    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this); //���[�^��J�[�\��
    pMagicCursor_->_Z = _Z - 3; //�ł���O�ɕ\��������
    addSubGroup(pMagicCursor_);

    papLvTargetCursor_ = NEW MagicLvCursor001*[ringMagics_.length()];
    papLvHilightCursor_ = NEW MagicLvCursor002*[ringMagics_.length()];
    papLvCastMarkCursor_ = NEW MagicLvCursor003*[ringMagics_.length()];
    paFloat_rr_ = NEW float[ringMagics_.length()];
    paFloat_velo_rr_ = NEW float[ringMagics_.length()];
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);

        papLvTargetCursor_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //���[�^���J�[�\��
        papLvTargetCursor_[i]->_Z = _Z - 3;
//        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        addSubGroup(papLvTargetCursor_[i]);

        papLvHilightCursor_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //�����x�������J�[�\��
        papLvHilightCursor_[i]->_Z = _Z - 1;
//        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        addSubGroup(papLvHilightCursor_[i]);

        papLvCastMarkCursor_[i] = NEW MagicLvCursor003("LvCastMarkCursor_", this, pMagic); //�r�����x�������J�[�\��
        papLvCastMarkCursor_[i]->_Z = _Z - 2;
//        papLvCastMarkCursor_[i]->moveTo(0);
        papLvCastMarkCursor_[i]->markOff();
        addSubGroup(papLvCastMarkCursor_[i]);

        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;
    }

    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    pMagicMeterStatus_->locatedBy(this);
    addSubGroup(pMagicMeterStatus_);

    //�G�l���M�[�o�[�ݒu
    pEnagyBar_ = NEW EnagyBar("EnagyBar", &mp_);
    pEnagyBar_->locate(PX_C(100), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f), _Z);
    addSubGroup(pEnagyBar_);

    _pSeTransmitter->useSe(SE_EXECUTE_BAD_LEVEL+1);
    _pSeTransmitter->set(SE_CURSOR_MOVE_METER, "click07");  //���[�^�[�ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL, "G_EFC5");    //���x���ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL_CANCEL, "yume_ashi_022"); //���x���ړ��L�����Z��
    _pSeTransmitter->set(SE_CURSOR_BAD_MOVE, "break_glass01"); //�_���Ȉړ�
    _pSeTransmitter->set(SE_EXECUTE_LEVELUP_MAGIC, "warp");      //���x���_�E���A�b�v
    _pSeTransmitter->set(SE_EXECUTE_LEVELDOWN_MAGIC, "SwingA@11"); //���x���_�E�����s
    _pSeTransmitter->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC, "warp");      //���x���_�E���A�b�v
    _pSeTransmitter->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "SwingA@11"); //���x���_�E�����s
    _pSeTransmitter->set(SE_EXECUTE_BAD_LEVEL , "yume_SUZU"); //�u�u�[
}
void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(stringstream::beg); //���o��
    load(st_[prm_saveno]);
}
void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(stringstream& sts) {
    sts << mp_.get() << " ";
    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::load(stringstream& sts) {
    int mp;
    sts >> mp;
    mp_.set(mp);

    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = ringMagics_.next();
    }
}
void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //�A�j������
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastMarkCursor_[i]->moveTo(0);
    }
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        Magic* pActiveMagic = ringMagics_.getCurrent();
        int i = ringMagics_.getCurrentIndex();
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            rollOpen(i);
        }

        progress prg = pActiveMagic->_pProg->get();
        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (papLvTargetCursor_[i]->point_lv_ != pActiveMagic->level_) {
                _pSeTransmitter->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[i]->moveTo(pActiveMagic->level_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(i);
            //���[�^�\��
            ringMagics_.next(); //���[�^�[���P�i�߂�
            rollOpen(ringMagics_.getCurrentIndex()); //�i�߂�������[���I�[�v��
            pMagicCursor_->moveTo(ringMagics_.getCurrentIndex()); //���[�^�[�J�[�\�����P�i�߂�
            _pSeTransmitter->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (papLvTargetCursor_[i]->point_lv_ != pActiveMagic->level_) {
                _pSeTransmitter->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[i]->moveTo(pActiveMagic->level_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(i);
            //���[�^�\��
            ringMagics_.prev(); //���[�^�[���P�߂�
            rollOpen(ringMagics_.getCurrentIndex()); //�߂���������[���I�[�v��
            pMagicCursor_->moveTo(ringMagics_.getCurrentIndex()); //���[�^�[�J�[�\�����P�߂�
            _pSeTransmitter->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_UP) && prg != MAGIC_STATE_INVOKING) {  // �u���v������
            if (pActiveMagic->max_level_ > papLvTargetCursor_[i]->point_lv_) {
                _pSeTransmitter->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[i]->moveTo(papLvTargetCursor_[i]->point_lv_ + 1);
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN) && prg != MAGIC_STATE_INVOKING) {  //�u���v������
            if (0 < papLvTargetCursor_[i]->point_lv_) {
                _pSeTransmitter->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[i]->moveTo(papLvTargetCursor_[i]->point_lv_ - 1);
            }
        }


        if (VB_PLAY->isPushedDown(VB_SHOT1)) { //�u����v��
            Magic* pActiveMagic = ringMagics_.getCurrent();
            progress prg = pActiveMagic->_pProg->get();
            int i = ringMagics_.indexOf(pActiveMagic);
            int r = pActiveMagic->cast(papLvTargetCursor_[i]->point_lv_);

            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    _pSeTransmitter->play(SE_EXECUTE_BAD_LEVEL);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    _pSeTransmitter->play(SE_EXECUTE_BAD_LEVEL);
                    break;
                }
                case MAGIC_CAST_NOTHING: {
                    papLvHilightCursor_[i]->moveTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_CANCEL: {
                    _pSeTransmitter->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[i]->beginBlinking(); //�s�J�s�J�I
                    papLvCastMarkCursor_[i]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[i]->moveTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELUP: {
                    _pSeTransmitter->play(SE_EXECUTE_LEVELUP_MAGIC);
                    papLvTargetCursor_[i]->beginBlinking(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastMarkCursor_[i]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELDOWN: {
                    _pSeTransmitter->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[i]->beginBlinking(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastMarkCursor_[i]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[i]->moveTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    _pSeTransmitter->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                    papLvTargetCursor_[i]->beginBlinking(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastMarkCursor_[i]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
                    _pSeTransmitter->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[i]->beginBlinking(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastMarkCursor_[i]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[i]->moveTo(pActiveMagic->level_);
                    break;
                }
            }
        }
    } else  {
        if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
            rollClose(ringMagics_.getCurrentIndex());
        }
    }

    //�e���@�ɂ��Ă̏���
    GgafProgress* pMagicProg = NULL;
    Magic* pMagic = NULL;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        pMagicProg = pMagic->_pProg;

        paFloat_rr_[i] += paFloat_velo_rr_[i];
        if (paFloat_rr_[i] < 0.0f) {
            paFloat_rr_[i] = 0.0f;
            paFloat_velo_rr_[i] = 0.0f;
        }
        if (paFloat_rr_[i] > 1.0f) {
            paFloat_rr_[i] = 1.0f;
            paFloat_velo_rr_[i] = 0.0f;
        }


        if (pMagicProg->isJustChangedTo(MAGIC_STATE_INVOKING)) {
            papLvTargetCursor_[i]->dispDisable();
            papLvHilightCursor_[i]->dispDisable();
            if (papLvTargetCursor_[i]->point_lv_ == pMagic->level_) {
                //�����x�����w���Ă���ꍇ
                //�V�������x���ɂ������蓮�����Ă�����B
                papLvTargetCursor_[i]->moveTo(pMagic->new_level_);
            }
            papLvHilightCursor_[i]->moveTo(pMagic->new_level_);
            papLvCastMarkCursor_[i]->markOnInvoke(pMagic->new_level_);
        }
        if (pMagicProg->isJustChangedFrom(MAGIC_STATE_INVOKING)) {
            papLvTargetCursor_[i]->dispEnable();
            papLvHilightCursor_[i]->dispEnable();
        }


        if (pMagicProg->isJustChangedTo(MAGIC_STATE_EFFECT_BEGEIN)) {
            if (pMagic->last_level_ < pMagic->level_) {
                //���x���A�b�vEFFECT_BEGEIN�������Ȃ��
                papLvCastMarkCursor_[i]->markOff(); //�}�[�N�I�t�I
            } else {
                //���x���_�E��EFFECT_BEGEIN�������Ȃ��
                //markOnLevelDownCast() ��������ł���B�������Ȃ��B
            }
        }

    }


    if (GgafDxInput::isPushedDownKey(DIK_K)) {
        saveStatus(0);
    }

    if (GgafDxInput::isPushedDownKey(DIK_L)) {
        loadStatus(0);
    }

}

void MagicMeter::processJudgement() {


}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    //GgafDxRectUV* pRectUV_Active;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = ringMagics_.getElemFirst();
    Magic* pMagic;
    int len_magics = ringMagics_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_X));
    float y = float(C_PX(_Y));
    float z = float(C_PX(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        n = 0;

        //�}�W�b�N���[�^�[�w�i
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x +width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(2, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        if (paFloat_rr_[i] > 0.1) {
            //�e�}�W�b�N�v�f
            for (int j = 0; j < pMagic->max_level_+1; j++) {
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y - (height_px_*(j+1)*paFloat_rr_[i]));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], paFloat_rr_[i]); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT �� MAGIC_CAST_NG_INVOKING_NOW
                    //�r���s�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //�E�ׂ̃e�N�X�`���p�^�[���� DISABLE �ȃp�^�[���O��
                } else {
                    //�r���\�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                }
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
                n++;
            }

//            //�e�}�W�b�N�̌����x�������\��
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y - ((height_px_*(pMagic->level_+1))*paFloat_rr_[i]));
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], paFloat_rr_[i]*2);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
//            _pUvFlipper->getUV(1, u, v);
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
//            n++;
        }

        _pBoardSetModel->draw(this, n);
        pElem = pElem->_pNext;
    }
}

void MagicMeter::rollOpen(int prm_meter_index) {
    paFloat_velo_rr_[prm_meter_index] = 0.1;
}

void MagicMeter::rollClose(int prm_meter_index) {
    paFloat_velo_rr_[prm_meter_index] = -0.01;
}


MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(papLvTargetCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvHilightCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvCastMarkCursor_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_rr_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_velo_rr_);
}
