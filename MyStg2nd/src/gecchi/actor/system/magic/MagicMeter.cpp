#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    //_z = 0.99;//���Ԃ�Ŕw�� �i0 <= _z < 1.0�jZ=(0�`+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
    _width = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    _height = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    _x = 100;
    _y = Properties::VIEW_SCREEN_HEIGHT - (_height*2);



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

    _ringMagics.addLast(NEW SpeedMagic("SPEED", this));
    _ringMagics.addLast(NEW LockonMagic("LOCKON", this));
    _ringMagics.addLast(NEW TorpedoMagic("TORPEDO", this));
    _ringMagics.addLast(NEW LaserMagic("LASER", this));
    _ringMagics.addLast(NEW OptionMagic("OPTION", this));


    _paLevelCursor = NEW int[_ringMagics.length()];
    for (int i = 0; i < _ringMagics.length(); i++) {
        _paLevelCursor[i] = _ringMagics.getNextFromFirst(i)->_level;
    }
    _pSeTransmitter->useSe(4);
    _pSeTransmitter->set(0, "click07_2"); //���[�^�[�ړ�
    _pSeTransmitter->set(1, "G_EFC5");  //���x���ړ�
    _pSeTransmitter->set(2, "warp");  //����
    _pSeTransmitter->set(3, "SwingA@11"); //�L�����Z��
}

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

        if (VB_PLAY->isPushedDown(VB_RIGHT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(0);
            pActiveMagic->rollClose();
            _ringMagics.next();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isPushedDown(VB_LEFT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(0);
            pActiveMagic->rollClose();
            _ringMagics.prev();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isPushedDown(VB_UP)) {
            if (pActiveMagic->_max_level > _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(1);
                _paLevelCursor[i] ++;
            }
        } else if (VB_PLAY->isPushedDown(VB_DOWN)) {
            if (0 < _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(1);
                _paLevelCursor[i] --;
            }
        }
    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (pActiveMagic->_level < _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(2);
            if (pActiveMagic->setLevel(_paLevelCursor[i])) {
                pActiveMagic->cast(); //���x���A�b�v���@���s�I
            }
        } else if (pActiveMagic->_level > _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(3);
            if (pActiveMagic->setLevel(_paLevelCursor[i])) {
                pActiveMagic->cast(); //���x���_�E�����@���s�I
            }
        }
        pActiveMagic->rollClose();
    }
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    GgafDx9RectUV* pRectUV_Active;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    Magic* pMagic;
    int len_magics = _ringMagics.length();
    int n = 0;
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        //�e�}�W�b�N�v�f
        n = 0;
        if (pMagic->_rr > 0.1) {
            for (int j = 0; j < pMagic->_max_level+1; j++) {
                n++;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], _x + _width*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], _y - (_height*(j+1)*pMagic->_rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000002f);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
                pRectUV_Active = _pBoardSetModel->_paRectUV + pMagic->_lvinfo[j]._pno;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], pRectUV_Active->_aUV[0].tu);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], pRectUV_Active->_aUV[0].tv);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
            }

            //�e�}�W�b�N�̃J�[�\��
            n++;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], _x + _width*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], _y - ((_height*(_paLevelCursor[i]+1))*pMagic->_rr));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
            pRectUV_Active = _pBoardSetModel->_paRectUV + 1; //�p�^�[��1�����[�^�[�v�f�A�N�e�B�u
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], pRectUV_Active->_aUV[0].tu);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], pRectUV_Active->_aUV[0].tv);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        }


        //�}�W�b�N���[�^�[�w�i
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], _x +_width*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], _y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], _z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        pRectUV_Active = _pBoardSetModel->_paRectUV + 2; //3�Ԗڂ̃p�^�[����������I
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        //���݂̃}�W�b�N���x���\��
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], _x + _width*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], _y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
        pRectUV_Active = _pBoardSetModel->_paRectUV + pMagic->_lvinfo[pMagic->_level]._pno;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

        _pBoardSetModel->draw(this, n+1);
        pElem = pElem->_pNext;
    }




    //�p���[���[�^�[�A�N�e�B�u�J�[�\��
    n = 0;
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], _x+_width*_ringMagics.indexOf(_ringMagics.getCurrent()));
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], _y) ;
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], _z);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
    pRectUV_Active = _pBoardSetModel->_paRectUV + 0; //�p�^�[��0��
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], pRectUV_Active->_aUV[0].tu);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], pRectUV_Active->_aUV[0].tv);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
    _pBoardSetModel->draw(this, n+1);
}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(_paLevelCursor);
}
