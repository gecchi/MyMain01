#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"

#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeTransmitterForActor::GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor) :
        GgafDxSeTransmitter() {
    _pActor = prm_pActor;
    _paBool_is_playing_3d = nullptr;
}

void GgafDxSeTransmitterForActor::declareSeNum(int prm_se_num) {
    GgafDxSeTransmitter::declareSeNum(prm_se_num);
    _paBool_is_playing_3d = NEW bool[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _paBool_is_playing_3d[i] = false;
    }
}

void GgafDxSeTransmitterForActor::set(int prm_id, const char* prm_se_key, int prm_cannel) {
    if (prm_id < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() IDが範囲外です。正の数でお願いします。 prm_id="<<prm_id);
    } else if (prm_id >= _se_num) {
        GGAF_DELETEARR_NULLABLE(_paBool_is_playing_3d);
        //declareSeNum が再呼び出しされるため、_paBool_is_playing_3d は再確保される。
    }
    GgafDxSeTransmitter::set(prm_id, prm_se_key, prm_cannel);
}

void GgafDxSeTransmitterForActor::set(int prm_id, const char* prm_se_key) {
    std::string ch_key = std::string(prm_se_key) + "_CH";
    if (GgafRepeatSeq::isExist(ch_key)) {
        set(prm_id, prm_se_key, GgafRepeatSeq::nextVal(ch_key));
    } else {
        if (GgafProperties::isExistKey(ch_key)) {
            int max_ch_num = GgafProperties::getInt(ch_key);
            GgafRepeatSeq::create(ch_key, 1, max_ch_num);
            set(prm_id, prm_se_key, GgafRepeatSeq::nextVal(ch_key));
        } else {
            set(prm_id, prm_se_key, 0);
        }
    }
}
void GgafDxSeTransmitterForActor::play(int prm_id) {
    GgafDxSeTransmitter::play(prm_id);
    _paBool_is_playing_3d[prm_id] = false;
}

void GgafDxSeTransmitterForActor::play3D(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitterForActor::play3D() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    static const int VOLUME_MAX_3D = GGAF_MAX_VOLUME;
    static const int VOLUME_MIN_3D = GGAF_MIN_VOLUME;
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;
    GgafDxCamera* pCam = P_CAM;
    //距離計算
    //遅延なし、音量100％の場所をP_CAMの場所とする
    //自身とP_CAMの距離
    double DX = C_PX(pCam->_X - _pActor->_X);
    double DY = C_PX(pCam->_Y - _pActor->_Y);
    double DZ = C_PX(pCam->_Z - _pActor->_Z);
    double d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル
    int vol =  VOLUME_MIN_3D + ((1.0 - (d / (DX_PX(pCam->_zf)*0.6) )) * VOLUME_RANGE_3D); // 0.6 は調整補正、最遠でもMAX*0.4倍の音量となる。
                                                                                          // 値を減らすと、遠くても音量がより大きくなる。
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }

    dxcoord fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
    float pan = ANG_COS(ang) * 0.9; //0.9は完全に右のみ或いは左のみから聞こえるのをやや緩和

    int delay = (d / (pCam->_zf*PX_UNIT))*PROPERTY::MAX_SE_DELAY-10; //10フレーム底上げ
    if (delay < 0) {
        delay = 0;
    } else if (delay > PROPERTY::MAX_SE_DELAY) {
        delay = PROPERTY::MAX_SE_DELAY;
    }

    float rate_frequency = 1.0;
    if (_pActor->_dest_from_vppln_front > 0) { //背後の場合周波数を下げ、音を少しぐぐもらせる。
        if (_pActor->_dest_from_vppln_front > PX_DX(800)) {
            //背後800px ～
            rate_frequency = 0.9;
        } else {
            //背後0px ～ 800px
            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX_DX(800)));
        }
    }


    P_UNIVERSE->registerSe(_papSeConnection[prm_id]->peek(), vol, pan, rate_frequency, delay, _pActor); // + (GgafDxSe::VOLUME_RANGE / 6) は音量底上げ

    _paBool_is_playing_3d[prm_id] = true;
    //真ん中からの距離
   //                float dPlnLeft = ABS(_dest_from_vppln_left);
   //                float dPlnRight = ABS(_dest_from_vppln_right);
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

void GgafDxSeTransmitterForActor::updatePanVolume3D() {
    static const int VOLUME_MAX_3D = GGAF_MAX_VOLUME;
    static const int VOLUME_MIN_3D = GGAF_MIN_VOLUME;
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;

    bool calc_flg = true;
    GgafDxCamera* pCam = P_CAM;
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
    for (int i = 0; i < _se_num; i++) {
        if (_paBool_is_playing_3d[i]) {
            if (_papSeConnection[i]) {
                GgafDxSe* pSe = _papSeConnection[i]->peek();
                if (pSe->isPlaying() && pSe->_pActor_LastPlayed == _pActor) {
                    if (calc_flg) {
                        calc_flg = false;

                        //距離計算
                        //遅延なし、音量100％の場所をP_CAMの場所とする
                        //自身とP_CAMの距離
                        double DX = C_PX(pCam->_X - _pActor->_X);
                        double DY = C_PX(pCam->_Y - _pActor->_Y);
                        double DZ = C_PX(pCam->_Z - _pActor->_Z);

                        //備忘録
                        //例えば消滅時の爆発だった場合、_pActor->_X みたいに、消滅後も値を参照したい。
                        //そこで GGAF_END_DELAY が重要になっている

                        //リアルタイムの音量を計算
                        double d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル
                        vol =  VOLUME_MIN_3D + ((1.0 - (d / (DX_PX(pCam->_zf)*0.6) )) * VOLUME_RANGE_3D); //0.6 は調整補正

                        if (VOLUME_MAX_3D < vol) {
                            vol = VOLUME_MAX_3D;
                        } else if (VOLUME_MIN_3D > vol) {
                            vol = VOLUME_MIN_3D;
                        }

                        //リアルタイムのパンを計算
                        dxcoord fDist_VpVerticalCenter  =
                                pCam->_plnVerticalCenter.a*_pActor->_fX +
                                pCam->_plnVerticalCenter.b*_pActor->_fY +
                                pCam->_plnVerticalCenter.c*_pActor->_fZ +
                                pCam->_plnVerticalCenter.d;
                        angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
                        pan = ANG_COS(ang) * 0.8; //0.8意味は、完全に右のみ或いは左のみから聞こえるのを避けるため
                                                              //最高で 0.2 : 0.8 の割合に留めるため。
                        //リアルタイムのパンを計算
                        if (_pActor->_dest_from_vppln_front > 0) { //背後の場合周波数を下げ、音を少しぐぐもらせる。
                            if (_pActor->_dest_from_vppln_front > PX_DX(800)) {
                                //背後800px ～
                                rate_frequency = 0.9;
                            } else {
                                //背後0px ～ 800px
//                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX_DX(800)));
                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front * (1.0 / PX_DX(800))));
                            }
                        }
                    }
                    //擬似３D音
                    pSe->setPan(pan);
                    pSe->setVolume(vol);
                    pSe->setFrequencyRate(rate_frequency);
                } else {
                    _paBool_is_playing_3d[i] = false;
                }
            }
        }
    }
}

void GgafDxSeTransmitterForActor::behave() {
    if (_pActor->_frame_of_life % 2U == 0) {
        //擬似３D音効果の為2フレームに１回SEの環境効果更新
        updatePanVolume3D();
    }
}

GgafDxSeTransmitterForActor::~GgafDxSeTransmitterForActor() {
    GGAF_DELETEARR_NULLABLE(_paBool_is_playing_3d);
}

