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
};

MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    width_ = PX2CO(width_px_);
    height_ = PX2CO(height_px_);

    _X = 100*LEN_UNIT;
    _Y = (GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - (height_px_*2)) * LEN_UNIT;
    _Z = 10;
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
    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMagicCursor_);

    paCursorLv_ = NEW int[ringMagics_.length()];
    papLvCursor_ = NEW MagicMeterCursor002*[ringMagics_.length()];
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        paCursorLv_[i] = pMagic->level_;
        papLvCursor_[i] = NEW MagicMeterCursor002("LvCursor", this, pMagic);
        addSubGroup(papLvCursor_[i]);
    }

    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    pMagicMeterStatus_->locateAs(this);
    addSubGroup(pMagicMeterStatus_);

    //�G�l���M�[�o�[�ݒu
    pEnagyBar_ = NEW EnagyBar("EnagyBar", &mp_);
    pEnagyBar_->locate(PX2CO(100), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f), 0.00000001f );
    addSubGroup(pEnagyBar_);

    _pSeTransmitter->useSe(SE_EXECUTE_LEVELDOWN_MAGIC+1);
    _pSeTransmitter->set(SE_CURSOR_MOVE_METER, "click07"); //���[�^�[�ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL, "G_EFC5");    //���x���ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL_CANCEL, "yume_ashi_022"); //���x���ړ��L�����Z��
    _pSeTransmitter->set(SE_CURSOR_BAD_MOVE, "break_glass01"); //�_���Ȉړ�
    _pSeTransmitter->set(SE_EXECUTE_LEVELUP_MAGIC, "warp");      //���x���_�E���A�b�v
    _pSeTransmitter->set(SE_EXECUTE_LEVELDOWN_MAGIC, "SwingA@11"); //���x���_�E�����s
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
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        Magic* pActiveMagic = ringMagics_.getCurrent();
        int i = ringMagics_.indexOf(pActiveMagic);
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            pActiveMagic->rollOpen();
        }

        progress prg = pActiveMagic->_pProg->get();
        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (paCursorLv_[i] != pActiveMagic->level_) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //�r���`�������́A�A�N�e�B�u���x���ɖ߂��Ȃ�
            } else {
                paCursorLv_[i] = pActiveMagic->level_; //���s����Ȃ������ׁA�A�N�e�B�u���x���ɖ߂�
                papLvCursor_[i]->moveToLv(paCursorLv_[i]); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            pActiveMagic->rollClose();
            //���[�^�\��
            ringMagics_.next(); //���[�^�[���P�i�߂�
            ringMagics_.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            pMagicCursor_->moveTo(ringMagics_.indexOf(ringMagics_.getCurrent())); //���[�^�[�J�[�\�����P�i�߂�

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (paCursorLv_[i] != pActiveMagic->level_) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //�r���`�������́A�A�N�e�B�u���x���ɖ߂��Ȃ�
            } else {
                paCursorLv_[i] = pActiveMagic->level_; //���s����Ȃ������ׁA�A�N�e�B�u���x���ɖ߂�
                papLvCursor_[i]->moveToLv(paCursorLv_[i]); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            pActiveMagic->rollClose();
            //���[�^�\��
            ringMagics_.prev(); //���[�^�[���P�߂�
            ringMagics_.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            pMagicCursor_->moveTo(ringMagics_.indexOf(ringMagics_.getCurrent())); //���[�^�[�J�[�\�����P�߂�

        } else if (VB_PLAY->isAutoRepeat(VB_UP)) {  // �u���v������
            if (pActiveMagic->max_level_ > paCursorLv_[i] ) {
                if (prg != MAGIC_STATE_INVOKING) { //�A���������͑���s��
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    paCursorLv_[i] ++;
                    papLvCursor_[i]->moveToLv(paCursorLv_[i]);
                } else {
                    _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //�u�b�u�[�T�E���h
                }
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN) && prg != MAGIC_STATE_INVOKING) {  //�u���v������
            if (prg != MAGIC_STATE_INVOKING) { //�A���������͑���s��
                if (0 < paCursorLv_[i]) {
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    paCursorLv_[i] --;
                    papLvCursor_[i]->moveToLv(paCursorLv_[i]);
                }
            } else {
                _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //�u�b�u�[�T�E���h
            }
        }

    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) { //����

        Magic* pActiveMagic = ringMagics_.getCurrent();
        progress prg = pActiveMagic->_pProg->get();
        int i = ringMagics_.indexOf(pActiveMagic);
        if (pActiveMagic->level_ < paCursorLv_[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELUP_MAGIC);
            pActiveMagic->cast(paCursorLv_[i]); //���x���A�b�v���@���s�I
            papLvCursor_[i]->beginBlinking(); //�s�J�s�J�I
        } else if (pActiveMagic->level_ > paCursorLv_[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELDOWN_MAGIC);
            pActiveMagic->cast(paCursorLv_[i]);  //���x���_�E�����@���s�I
            papLvCursor_[i]->beginBlinking(); //�s�J�s�J�I
        } else if (pActiveMagic->level_ == paCursorLv_[i]) {
            if (MAGIC_STATE_CASTING <= prg && prg < MAGIC_STATE_INVOKING) {
                //�r���`�����O�܂ł̏ꍇ�́A�L�����Z�����Ӗ�����B
            } else {
                //�������x�����s���������Ȃ�
            }
        }
        pActiveMagic->rollClose();
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
    float x = float(CO2PX(_X));
    float y = float(CO2PX(_Y));
    float z = float(CO2PX(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        n = 0;

        //�}�W�b�N���[�^�[�w�i
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x +width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.010f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(2, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.009f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        if (pMagic->rr_ > 0.1) {
            //�e�}�W�b�N�v�f
            for (int j = 0; j < pMagic->max_level_+1; j++) {
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - (height_px_*(j+1)*pMagic->rr_));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.015f+(0.001f*(j+1)));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->rr_); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
                _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
                n++;
            }

            //�e�}�W�b�N�̌����x�������\��
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((height_px_*(pMagic->level_+1))*pMagic->rr_));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.012f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->rr_*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
            _pUvFlipper->getUV(1, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
            n++;
        }

        _pBoardSetModel->draw(this, n);
        pElem = pElem->_pNext;
    }
}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(paCursorLv_);
    DELETEARR_IMPOSSIBLE_NULL(papLvCursor_);
}
