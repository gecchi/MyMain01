#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

#define SE_CURSOR_MOVE_METER         (0)
#define SE_CURSOR_MOVE_LEVEL         (1)
#define SE_EXECUTE_LEVELUP_MAGIC     (2)
#define SE_EXECUTE_LEVELDOWN_MAGIC   (3)

MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    _width_px = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    _height_px = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    _X = 100*LEN_UNIT;
    _Y = (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - (_height_px*2)) * LEN_UNIT;
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
    _ringMagics.addLast(NEW TractorMagic("TRACTOR"));
    _ringMagics.addLast(NEW SpeedMagic("SPEED"));
    _ringMagics.addLast(NEW LockonMagic("LOCKON"));
    _ringMagics.addLast(NEW TorpedoMagic("TORPEDO"));
    _ringMagics.addLast(NEW LaserMagic("LASER"));
    _ringMagics.addLast(NEW OptionMagic("OPTION"));
    for (int i = 0; i < _ringMagics.length(); i++) {
        addSubGroup(_ringMagics.getNext(i));
    }
    _paLevelCursor = NEW int[_ringMagics.length()];
    for (int i = 0; i < _ringMagics.length(); i++) {
        _paLevelCursor[i] = _ringMagics.getNextFromFirst(i)->_level;
    }

    _pSeTransmitter->useSe(4);
    _pSeTransmitter->set(SE_CURSOR_MOVE_METER, "click07_2"); //���[�^�[�ړ�
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL, "G_EFC5");    //���x���ړ�
    _pSeTransmitter->set(SE_EXECUTE_LEVELUP_MAGIC, "warp");      //����
    _pSeTransmitter->set(SE_EXECUTE_LEVELDOWN_MAGIC, "SwingA@11"); //�L�����Z��
}

void MagicMeter::save(stringstream& ss) {
    Magic* pOrgMagic = _ringMagics.getCurrent();
    Magic::LevelInfo* info;
    int len_magics = _ringMagics.length();
    for (int i = 0; i < len_magics; i++) {
        for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
            info = &(pOrgMagic->_lvinfo[lv]);
            ss  << info->_is_working <<
                << info->_remaining_time_of_effect <<
                << info->_time_of_effect <<
                << info->_keep_cost <<
                << info->_pno;
        }
        pOrgMagic = _ringMagics.next();
    }
}

void MagicMeter::load(stringstream& ss) {
    Magic* pOrgMagic = _ringMagics.getCurrent();
    Magic::LevelInfo* info;
    int len_magics = _ringMagics.length();
    for (int i = 0; i < len_magics; i++) {
        for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
            info = &(pOrgMagic->_lvinfo[lv]);
            ss  >> info->_is_working >>
                >> info->_remaining_time_of_effect >>
                >> info->_time_of_effect >>
                >> info->_keep_cost >>
                >> info->_pno;
        }
        pOrgMagic = _ringMagics.next();
    }
}
//    VBRecordNote* p = _pFirstVBNote;
//    while (p != NULL) {
//        ofs << p->_state << " " << p->_frame_of_keeping << endl;
//        p = p ->_pNext;
//    }
//    if (_write_realtime) {
//        _ofs_realtime.flush();
//    }
}
//    MagicMeter* pCopy = NEW MagicMeter(getName());
//    Magic* pOrgMagic = _ringMagics.getCurrent();
//    Magic* pCopyMagic = pCopy->_ringMagics.getCurrent();
//
//    int len_magics = _ringMagics.length();
//    for (int i = 0; i < len_magics; i++) {
//        &pCopyMagic = &pOrgMagic;
//        pOrgMagic = _ringMagics.next();
//        pCopyMagic = pCopy->_ringMagics.next();
//    }

void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //�A�j������
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    //_pUvFlipper->behave();
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    for (int i = 0; i < _ringMagics.length(); i++) {
        pElem->_pValue->behave();
        pElem = pElem->_pNext;
    }
    //updatePanVolume3D ���Ȃ����� _pSeTransmitter->behave(); �͕s�v
}

void MagicMeter::processJudgement() {


    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {
        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            pActiveMagic->rollOpen();
        }

        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(SE_CURSOR_MOVE_METER);
            pActiveMagic->rollClose();
            _ringMagics.next();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(SE_CURSOR_MOVE_METER);
            pActiveMagic->rollClose();
            _ringMagics.prev();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isAutoRepeat(VB_UP)) {
            if (pActiveMagic->_max_level > _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(SE_CURSOR_MOVE_LEVEL);
                _paLevelCursor[i] ++;
            }
        } else if (VB_PLAY->isAutoRepeat(VB_DOWN)) {
            if (0 < _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(SE_CURSOR_MOVE_LEVEL);
                _paLevelCursor[i] --;
            }
        }
    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (pActiveMagic->_level < _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(SE_EXECUTE_LEVELUP_MAGIC);
            pActiveMagic->cast(_paLevelCursor[i]);
                 //���x���A�b�v���@���s�I

        } else if (pActiveMagic->_level > _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(SE_EXECUTE_LEVELDOWN_MAGIC);
            pActiveMagic->cast(_paLevelCursor[i]);
                //���x���_�E�����@���s�I

        } else if (pActiveMagic->_level == _paLevelCursor[i]) {
            //�������x�����s���������Ȃ�
        }
        pActiveMagic->rollClose();
    }
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
        //�e�}�W�b�N�v�f
        n = 0;
        if (pMagic->_rr > 0.1) {
            for (int j = 0; j < pMagic->_max_level+1; j++) {
                n++;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - (_height_px*(j+1)*pMagic->_rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000005f);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
//                pRectUV_Active = _pBoardSetModel->_paRectUV + pMagic->_lvinfo[j]._pno;
               // pRectUV_Active = _pUvFlipper->_paRectUV + pMagic->_lvinfo[j]._pno;
                _pUvFlipper->getUV(pMagic->_lvinfo[j]._pno, u, v);

                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
            }
            //�e�}�W�b�N�̌����x�������\��
            n++;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((_height_px*(pMagic->_level+1))*pMagic->_rr));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
            //pRectUV_Active = _pUvFlipper->_paRectUV + 1; //�p�^�[��1�����[�^�[�v�f�A�N�e�B�u
            _pUvFlipper->getUV(1, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");


            //�e�}�W�b�N�̃J�[�\��
            n++;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((_height_px*(_paLevelCursor[i]+1))*pMagic->_rr));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000002f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
            //pRectUV_Active = _pUvFlipper->_paRectUV + 1; //�p�^�[��1�����[�^�[�v�f�A�N�e�B�u
            _pUvFlipper->getUV(0, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        }


        //�}�W�b�N���[�^�[�w�i
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x +_width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        //pRectUV_Active = _pUvFlipper->_paRectUV + 2; //3�Ԗڂ̃p�^�[����������I
        _pUvFlipper->getUV(2, u, v);

        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        //pRectUV_Active = _pUvFlipper->_paRectUV + pMagic->_lvinfo[pMagic->_level]._pno;
        _pUvFlipper->getUV(pMagic->_lvinfo[pMagic->_level]._pno, u, v);

        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        _pBoardSetModel->draw(this, n+1);
        pElem = pElem->_pNext;
    }




    //�p���[���[�^�[�A�N�e�B�u�J�[�\��
    n = 0;
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*_ringMagics.indexOf(_ringMagics.getCurrent()));
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], z);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
    //pRectUV_Active = _pUvFlipper->_paRectUV + 0; //�p�^�[��0��
    _pUvFlipper->getUV(0, u, v);

    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
    _pBoardSetModel->draw(this, n+1);

}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(_paLevelCursor);
}
