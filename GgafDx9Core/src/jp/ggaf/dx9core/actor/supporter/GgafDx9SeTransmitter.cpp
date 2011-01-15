#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9SeTransmitter::GgafDx9SeTransmitter(GgafDx9GeometricActor* prm_pActor) :
                                       GgafObject() {
    _pActor = prm_pActor;
    _se_num = 0;
    _papSeCon = NULL;
}

void GgafDx9SeTransmitter::useSe(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeCon = NEW GgafDx9SeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i] = NULL;
    }
}

void GgafDx9SeTransmitter::set(int prm_id, const char* prm_se_name, int prm_cannel) {
#ifdef MY_DEBUG
    if (_se_num <= 0) {
        throwGgafCriticalException("GgafDx9SeTransmitter::set() useSeで使用するSe数を事前に宣言してください。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDx9SeTransmitter::set() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->getConnection(idstr);
}

void GgafDx9SeTransmitter::playImmediately(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDx9SeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    _papSeCon[prm_id]->refer()->play(DSBVOLUME_MAX, DSBPAN_CENTER);
}


void GgafDx9SeTransmitter::play(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDx9SeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    P_UNIVERSE->registSe(_papSeCon[prm_id]->refer(), DSBVOLUME_MAX, DSBPAN_CENTER, 0, 1.0);
}
void GgafDx9SeTransmitter::play3D(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDx9SeTransmitter::play3D() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    static const int VOLUME_MAX_3D = DSBVOLUME_MAX;
    static const int VOLUME_MIN_3D = DSBVOLUME_MIN + ((DSBVOLUME_MAX - DSBVOLUME_MIN)*0.7);
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;
    GgafDx9Camera* pCam = P_CAM;
    //距離計算
    //遅延なし、音量100％の場所をP_CAMの場所とする
    //自身とP_CAMの距離
    int DX = (pCam->_X - _pActor->_X) / LEN_UNIT;
    int DY = (pCam->_Y - _pActor->_Y) / LEN_UNIT;
    int DZ = (pCam->_Z - _pActor->_Z) / LEN_UNIT;
    double d = GgafUtil::sqrt_fast(double(DX*DX + DY*DY + DZ*DZ));
    LONG vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT))) * VOLUME_RANGE_3D);
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }

    float fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    angle ang = GgafDx9Util::getAngle2D(fDist_VpVerticalCenter, -_pActor->_fDist_VpPlnFront );
    LONG pan = GgafDx9Util::COS[ang/ANGLE_RATE] * DSBPAN_RIGHT;

    int delay = (d / (pCam->_zf*PX_UNIT))*MAX_SE_DELAY-10; //10フレーム底上げ
    if (delay < 0) {
        delay = 0;
    } else if (delay > MAX_SE_DELAY) {
        delay = MAX_SE_DELAY;
    }

    P_UNIVERSE->registSe(_papSeCon[prm_id]->refer(), vol, pan, delay, 1.0); // + (GgafDx9Se::VOLUME_RANGE / 6) は音量底上げ
    //真ん中からの距離
   //                float dPlnLeft = abs(_fDist_VpPlnLeft);
   //                float dPlnRight = abs(_fDist_VpPlnRight);
   //                if (dPlnLeft < dPlnRight) {
   //                    //sinθ = dPlnLeft/d;
   //                    //θ = asin(dPlnLeft/d)
   //                    //X = (_rad_half_fovY - θ)
   //                    //tan X = 距離 / d
   //                    //d * tan X = 距離
   //                    //d * tan (_rad_half_fovY - θ) = 距離
   //                    //d * tan (_rad_half_fovY - asin(dPlnLeft/d)) = 距離
   //                    //本当にこうしなければいけない？



   // _papSe[prm_id]->play();
}

void GgafDx9SeTransmitter::updatePanVolume3D() {
    static const int VOLUME_MAX_3D = DSBVOLUME_MAX;
    static const int VOLUME_MIN_3D = DSBVOLUME_MIN + ((DSBVOLUME_MAX - DSBVOLUME_MIN)*0.7);
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;
    GgafDx9Camera* pCam = P_CAM;
    //距離計算
    //遅延なし、音量100％の場所をP_CAMの場所とする
    //自身とP_CAMの距離
    int DX = (pCam->_X - _pActor->_X) / LEN_UNIT;
    int DY = (pCam->_Y - _pActor->_Y) / LEN_UNIT;
    int DZ = (pCam->_Z - _pActor->_Z) / LEN_UNIT;

    //備忘録
    //例えば消滅時の爆発だった場合、_pActor->_X みたいに、消滅後も値を参照したい。
    //そこで GGAF_SAYONARA_DELAY が重要になっている

    double d = GgafUtil::sqrt_fast(double(DX*DX + DY*DY + DZ*DZ));
    LONG vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT))) * VOLUME_RANGE_3D);
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }

    float fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;
    angle ang = GgafDx9Util::getAngle2D(fDist_VpVerticalCenter, -_pActor->_fDist_VpPlnFront );
    LONG pan = GgafDx9Util::COS[ang/ANGLE_RATE] * DSBPAN_RIGHT;
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i]->refer()->setPan(pan);
        _papSeCon[i]->refer()->setVolume(vol);
    }

}

void GgafDx9SeTransmitter::behave() {
    updatePanVolume3D();
}

GgafDx9SeTransmitter::~GgafDx9SeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_POSSIBLE_NULL(_papSeCon);
}

