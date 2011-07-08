#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9StringBoardActor::GgafDx9StringBoardActor(const char* prm_name, const char* prm_model)
  : GgafDx9BoardSetActor(prm_name, prm_model, "StringBoardEffect", "StringBoardTechnique") {

    _class_name = "GgafDx9StringBoardActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[1024];
    _buf[0] = '\0';
    //�f�t�H���g�̂P�����̕�(px)�ݒ�
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx);
    }
    _chr_width_px = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //�P�����̕�(px)
}

void GgafDx9StringBoardActor::onCreateModel() {

}


void GgafDx9StringBoardActor::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    locate(X, Y);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, char* prm_str) {
    update(prm_str);
    locate(X, Y);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    locate(X, Y, Z);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, coord Z, char* prm_str) {
    update(prm_str);
    locate(X, Y, Z);
}

void GgafDx9StringBoardActor::update(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
}

void GgafDx9StringBoardActor::update(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
}


void GgafDx9StringBoardActor::processSettlementBehavior() {
}


void GgafDx9StringBoardActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[0], float(cnvCoordApp2Pix(_Y)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[0], float(cnvCoordApp2Pix(_Z)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[0], _fAlpha); //���ӁF�A���t�@�͕������Ƃ͕s��
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
    int strindex, pattno;
    pixcoord x = cnvCoordApp2Pix(_X);
    pixcoord x_tmp = x;
    float u,v;
    for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
        _draw_set_num = pack < _len_pack_num ? _pBoardSetModel->_set_num : _remainder_len;
        for (int i = 0; i < _draw_set_num; i++) {
            strindex = pack * _pBoardSetModel->_set_num + i;
            if (_draw_string[strindex] == '\0') {
                break;
            } else if (_draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //�͈͊O��"?"��\��
            } else {
                pattno = _draw_string[strindex] - ' '; //�ʏ핶����
            }
            //�v���|�[�V���i���ȕ��v�Z
            int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
            x = x_tmp - w;
            x_tmp = x + _chr_width_px - w;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], float(x));
            checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], u);
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], v);
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
        }
        _pBoardSetModel->draw(this, _draw_set_num);
    }
}

GgafDx9StringBoardActor::~GgafDx9StringBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}

