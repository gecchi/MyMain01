#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"

#include "jp/ggaf/core/util/RepeatSeq.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SeTransmitterForActor::SeTransmitterForActor(GeometricActor* prm_pActor) : SeTransmitter() ,
_pActor(prm_pActor) {
}

void SeTransmitterForActor::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    int se_num = _vec_is_playing_3d.size();
    if (prm_se_no >= se_num) {
        for (int i = se_num; i <= prm_se_no; i++) {
            _vec_is_playing_3d.push_back(false);
        }
    }
    SeTransmitter::set(prm_se_no, prm_se_key, prm_cannel);
}

void SeTransmitterForActor::set(int prm_se_no, const char* prm_se_key) {
    std::string ch_key = std::string(prm_se_key) + std::string("_CH");
    if (GgafCore::RepeatSeq::isExist(ch_key)) {
        set(prm_se_no, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
    } else {
        if (GgafCore::Config::_properties.isExistKey(ch_key)) {
            int max_ch_num = GgafCore::Config::_properties.getInt(ch_key);
            GgafCore::RepeatSeq::create(ch_key, 1, max_ch_num);
            set(prm_se_no, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
        } else {
            set(prm_se_no, prm_se_key, 0);
        }
    }
}
void SeTransmitterForActor::play(int prm_se_no, bool prm_can_looping) {
    SeTransmitter::play(prm_se_no, prm_can_looping);
    _vec_is_playing_3d[prm_se_no] = false;
}

void SeTransmitterForActor::play3D(int prm_se_no) {
    Spacetime* const pSpacetime = pGOD->getSpacetime();
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。_pActor="<<_pActor->getName()<<" prm_se_no="<<prm_se_no);
    }
#endif
    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    const Camera* const pCam = pSpacetime->getCamera();
    //距離計算
    //遅延なし、音量100％の場所をP_CAMの場所とする
    //自身とP_CAMの距離
    const double DX = C_PX(pCam->_x - _pActor->_x);
    const double DY = C_PX(pCam->_y - _pActor->_y);
    const double DZ = C_PX(pCam->_z - _pActor->_z);
    const double d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル
    int vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); // 0.6 は調整補正、最遠でもMAX*0.4倍の音量となる。
                                                                                          // 値を減らすと、遠くても音量がより大きくなる。
    if (GGAF_MAX_VOLUME < vol) {
        vol = GGAF_MAX_VOLUME;
    } else if (GGAF_MIN_VOLUME > vol) {
        vol = GGAF_MIN_VOLUME;
    }

    const dxcoord fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    const angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_infront );
    const float pan = ANG_COS(ang) * 0.9; //0.9は完全に右のみ或いは左のみから聞こえるのをやや緩和

    int delay = (d / DX_PX(pCam->getZFar()))*CONFIG::MAX_SE_DELAY - 10; //10フレーム底上げ
                                                                    //pCam->getZFar() はカメラの表示範囲の最遠距離
                                                                    //最遠に位置したアクターのSEはMAX_SE_DELAYフレーム遅れる
    if (delay < 0) {
        delay = 0;
    } else if (delay > CONFIG::MAX_SE_DELAY) {
        delay = CONFIG::MAX_SE_DELAY;
    }

    float rate_frequency = 1.0;
    if (_pActor->_dest_from_vppln_infront > 0) { //背後の場合周波数を下げ、音を少しぐぐもらせる。
        if (_pActor->_dest_from_vppln_infront > PX_DX(800)) {
            //背後800px ～
            rate_frequency = 0.9;
        } else {
            //背後0px ～ 800px
            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_infront / PX_DX(800)));
        }
    }

    pSpacetime->registerSe(getSe(prm_se_no), vol, pan, rate_frequency, delay, _pActor); // + (Se::VOLUME_RANGE / 6) は音量底上げ

    _vec_is_playing_3d[prm_se_no] = true;
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
   // _papSe[prm_se_no]->play();
}

void SeTransmitterForActor::updatePanVolume3D() {
    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;

    bool calc_flg = true;
    const Camera* const pCam = pGOD->getSpacetime()->getCamera();
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
    const int se_num = _se_num;
    for (int i = 0; i < se_num; i++) {
        if (_vec_is_playing_3d[i]) {
            if (_vecSeConnection[i]) {
                Se* pSe = getSe(i);
                if (pSe->isPlaying() && pSe->_pActor_last_played == _pActor) {
                    if (calc_flg) {
                        calc_flg = false; //最初の１回目のループだけ距離計算

                        //距離計算
                        //遅延なし、音量100％の場所をP_CAMの場所とする
                        //自身とP_CAMの距離
                        const double DX = C_PX(pCam->_x - _pActor->_x);
                        const double DY = C_PX(pCam->_y - _pActor->_y);
                        const double DZ = C_PX(pCam->_z - _pActor->_z);

                        //備忘録
                        //例えば消滅時の爆発だった場合、_pActor->_x みたいに、消滅後も値を参照したい。
                        //そこで GGAF_END_DELAY が重要になっている

                        //リアルタイムの音量を計算
                        const double d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル
                        vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); //0.6 は調整補正

                        if (GGAF_MAX_VOLUME < vol) {
                            vol = GGAF_MAX_VOLUME;
                        } else if (GGAF_MIN_VOLUME > vol) {
                            vol = GGAF_MIN_VOLUME;
                        }

                        //リアルタイムのパンを計算
                        const dxcoord fDist_VpVerticalCenter  =
                                pCam->_plnVerticalCenter.a * _pActor->_fX +
                                pCam->_plnVerticalCenter.b * _pActor->_fY +
                                pCam->_plnVerticalCenter.c * _pActor->_fZ +
                                pCam->_plnVerticalCenter.d;
                        const angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_infront );
                        pan = ANG_COS(ang) * 0.9; //0.9意味は、完全に右のみ或いは左のみから聞こえるのを避けるため
                                                              //最高で 0.1 : 0.9 の割合に留めるため。
                        //リアルタイムのパンを計算
                        if (_pActor->_dest_from_vppln_infront > 0) { //背後の場合周波数を下げ、音を少しぐぐもらせる。
                            if (_pActor->_dest_from_vppln_infront > PX_DX(800)) {
                                //背後800px ～
                                rate_frequency = 0.9;
                            } else {
                                //背後0px ～ 800px
//                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_infront / PX_DX(800)));
                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_infront * (1.0 / PX_DX(800))));
                            }
                        }
                    }
                    //擬似３D音
                    pSe->setPan(pan);
                    pSe->setVolume(vol);
                    pSe->setFrequencyRate(rate_frequency);
                } else {
                    _vec_is_playing_3d[i] = false;
                }
            }
        }
    }
}

void SeTransmitterForActor::behave() {
    if ((_pActor->_frame_of_life & 1) == 0) {//2回に1回
        //擬似３D音効果の為2フレームに１回SEの環境効果更新
        updatePanVolume3D();
    }
}

SeTransmitterForActor::~SeTransmitterForActor() {
}

