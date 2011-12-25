#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

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
    _width_px = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    _height_px = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    _width = PX2CO(_width_px);
    _height = PX2CO(_height_px);

    _X = 100*LEN_UNIT;
    _Y = (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - (_height_px*2)) * LEN_UNIT;
    _Z = 10;
//    AmountGraph _qu;
//    _qu.set(1.0);
//    _qu.config(400.0, 1.0);
//    float _value = 1000;
//    _qu.config(400.0f, _value);
//    AmountGraph _qu();
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


    _mp.config(600, 10000); //�l 10000 �ŕ\����400px�Ƃ���B
    _mp.set(10000);           //�����l��5000
    _ringMagics.addLast(NEW TractorMagic("TRACTOR", &_mp));
    _ringMagics.addLast(NEW SpeedMagic("SPEED", &_mp));
    _ringMagics.addLast(NEW LockonMagic("LOCKON", &_mp));
    _ringMagics.addLast(NEW TorpedoMagic("TORPEDO", &_mp));
    _ringMagics.addLast(NEW LaserMagic("LASER", &_mp));
    _ringMagics.addLast(NEW OptionMagic("OPTION", &_mp));
    for (int i = 0; i < _ringMagics.length(); i++) {
        addSubGroup(_ringMagics.getNext(i));
    }
    _pMagicCursor = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(_pMagicCursor);

    _paCursorLv = NEW int[_ringMagics.length()];
    _papLvCursor = NEW MagicMeterCursor002*[_ringMagics.length()];
    Magic* pMagic;
    for (int i = 0; i < _ringMagics.length(); i++) {
        pMagic = _ringMagics.getFromFirst(i);
        _paCursorLv[i] = pMagic->_level;
        _papLvCursor[i] = NEW MagicMeterCursor002("LvCursor", this, pMagic);
        addSubGroup(_papLvCursor[i]);
    }

    _pMagicMeterStatus = NEW MagicMeterStatus("MagicMeterStatus", this);
    _pMagicMeterStatus->locateAs(this);
    addSubGroup(_pMagicMeterStatus);

    //�G�l���M�[�o�[�ݒu
    _pEnagyBar = NEW EnagyBar("EnagyBar", &_mp);
    _pEnagyBar->locate(PX2CO(100), PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f), 0.00000001f );
    addSubGroup(_pEnagyBar);

    _pSeTransmitter->useSe(SE_EXECUTE_LEVELDOWN_MAGIC+1);
    _pSeTransmitter->set(SE_CURSOR_MOVE_METER, "click07_2"); //���[�^�[�ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL, "G_EFC5");    //���x���ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL_CANCEL, "yume_ashi_022"); //���x���ړ��L�����Z��
    _pSeTransmitter->set(SE_CURSOR_BAD_MOVE, "break_glass01"); //�_���Ȉړ�
    _pSeTransmitter->set(SE_EXECUTE_LEVELUP_MAGIC, "warp");      //���x���_�E���A�b�v
    _pSeTransmitter->set(SE_EXECUTE_LEVELDOWN_MAGIC, "SwingA@11"); //���x���_�E�����s
}
void MagicMeter::loadStatus(int prm_saveno) {
    _st[prm_saveno].seekg(stringstream::beg); //���o��
    load(_st[prm_saveno]);
}
void MagicMeter::saveStatus(int prm_saveno) {
    save(_st[prm_saveno]);
}

void MagicMeter::save(stringstream& sts) {
    sts << _mp.get() << " ";
    Magic* pOrgMagic = _ringMagics.getCurrent();
    int len_magics = _ringMagics.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = _ringMagics.next();
    }
}

void MagicMeter::load(stringstream& sts) {
    int mp;
    sts << mp << " ";
    _mp.set(mp);

    Magic* pOrgMagic = _ringMagics.getCurrent();
    int len_magics = _ringMagics.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = _ringMagics.next();
    }
}
void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //�A�j������
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            pActiveMagic->rollOpen();
        }

        progress prg = pActiveMagic->_pProg->get();
        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (_paCursorLv[i] != pActiveMagic->_level) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //�r���`�������́A�A�N�e�B�u���x���ɖ߂��Ȃ�
            } else {
                _paCursorLv[i] = pActiveMagic->_level; //���s����Ȃ������ׁA�A�N�e�B�u���x���ɖ߂�
                _papLvCursor[i]->moveToLv(_paCursorLv[i]); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            pActiveMagic->rollClose();
            //���[�^�\��
            _ringMagics.next(); //���[�^�[���P�i�߂�
            _ringMagics.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            _pMagicCursor->moveTo(_ringMagics.indexOf(_ringMagics.getCurrent())); //���[�^�[�J�[�\�����P�i�߂�

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (_paCursorLv[i] != pActiveMagic->_level) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //�r���`�������́A�A�N�e�B�u���x���ɖ߂��Ȃ�
            } else {
                _paCursorLv[i] = pActiveMagic->_level; //���s����Ȃ������ׁA�A�N�e�B�u���x���ɖ߂�
                _papLvCursor[i]->moveToLv(_paCursorLv[i]); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            pActiveMagic->rollClose();
            //���[�^�\��
            _ringMagics.prev(); //���[�^�[���P�߂�
            _ringMagics.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            _pMagicCursor->moveTo(_ringMagics.indexOf(_ringMagics.getCurrent())); //���[�^�[�J�[�\�����P�߂�

        } else if (VB_PLAY->isAutoRepeat(VB_UP)) {  // �u���v������
            if (pActiveMagic->_max_level > _paCursorLv[i] ) {
                if (prg != MAGIC_STATE_INVOKING) { //�A���������͑���s��
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    _paCursorLv[i] ++;
                    _papLvCursor[i]->moveToLv(_paCursorLv[i]);
                } else {
                    _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //�u�b�u�[�T�E���h
                }
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN) && prg != MAGIC_STATE_INVOKING) {  //�u���v������
            if (prg != MAGIC_STATE_INVOKING) { //�A���������͑���s��
                if (0 < _paCursorLv[i]) {
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    _paCursorLv[i] --;
                    _papLvCursor[i]->moveToLv(_paCursorLv[i]);
                }
            } else {
                _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //�u�b�u�[�T�E���h
            }
        }

    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) { //����

        Magic* pActiveMagic = _ringMagics.getCurrent();
        progress prg = pActiveMagic->_pProg->get();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (pActiveMagic->_level < _paCursorLv[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELUP_MAGIC);
            pActiveMagic->cast(_paCursorLv[i]); //���x���A�b�v���@���s�I
            _papLvCursor[i]->beginBlinking(); //�s�J�s�J�I
        } else if (pActiveMagic->_level > _paCursorLv[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELDOWN_MAGIC);
            pActiveMagic->cast(_paCursorLv[i]);  //���x���_�E�����@���s�I
            _papLvCursor[i]->beginBlinking(); //�s�J�s�J�I
        } else if (pActiveMagic->_level == _paCursorLv[i]) {
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
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    Magic* pMagic;
    int len_magics = _ringMagics.length();
    int n = 0;
    float u,v;
    float x = float(CO2PX(_X));
    float y = float(CO2PX(_Y));
    float z = float(CO2PX(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        n = 0;

        //�}�W�b�N���[�^�[�w�i
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x +_width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.010f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(2, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
        n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.009f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(pMagic->_lvinfo[pMagic->_level]._pno, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
        n++;

        if (pMagic->_rr > 0.1) {
            //�e�}�W�b�N�v�f
            for (int j = 0; j < pMagic->_max_level+1; j++) {
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - (_height_px*(j+1)*pMagic->_rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.015f+(0.001f*(j+1)));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
                _pUvFlipper->getUV(pMagic->_lvinfo[j]._pno, u, v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
                n++;
            }

            //�e�}�W�b�N�̌����x�������\��
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((_height_px*(pMagic->_level+1))*pMagic->_rr));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.012f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
            //pRectUV_Active = _pUvFlipper->_paRectUV + 1; //�p�^�[��1�����[�^�[�v�f�A�N�e�B�u
            _pUvFlipper->getUV(1, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
            n++;
        }

        _pBoardSetModel->draw(this, n);
        pElem = pElem->_pNext;
    }
}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(_paCursorLv);
    DELETEARR_IMPOSSIBLE_NULL(_papLvCursor);
}
