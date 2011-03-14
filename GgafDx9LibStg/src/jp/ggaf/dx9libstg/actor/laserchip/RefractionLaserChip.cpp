#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 2;
    _frame_standstill_refraction = 10;
    _frame_between_refraction = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_out = 0;
    _isRefracting = false;

    _pDispatche_RefractionEffect = NULL;
    _pRefractionEffect = NULL;
    _prev_pRefractionEffect = NULL;
}

void RefractionLaserChip::initialize() {
    //初期設定です。
    //30px/frame の移動速度
    //当たり判定あり。
    //α＝0.99
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    _pKuroko->setMvVelo(30000);
    _fAlpha = 0.99;
}


void RefractionLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();

    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    //レーザーチップ出現時処理
    if (pChip_front == NULL) {
        _is_leader = true;
        //自身が先頭の場合
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_RX = _RX;
        _begining_RY = _RY;
        _begining_RZ = _RZ;
        _cnt_refraction = 0;
        _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
        _frame_refraction_out = _frame_refraction_enter + _frame_standstill_refraction;
        //onRefractionBegin(_cnt_refraction);
        onRefractionFinish(_cnt_refraction);  //0回目の屈折終了からスタートする
    } else {
        _is_leader = false;
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_RX = pChip_front->_begining_RX;
        _begining_RY = pChip_front->_begining_RY;
        _begining_RZ = pChip_front->_begining_RZ;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _RX = _begining_RX;
        _RY = _begining_RY;
        _RZ = _begining_RZ;
        _cnt_refraction = 0;
        _frame_refraction_enter = INT_MAX;
        _frame_refraction_out = INT_MAX;
    }

    _isRefracting = false;
    _prev_isRefracting = false;
}

void RefractionLaserChip::onInactive() {
    //レーザーチップ消失時処理

    //一つ後方のチップがあれば、自分の意思（移動など）を引き継がせる
    //これは、レーザーがちぎれた場合、以下のパラメーターのみ引き継がせ、移動を継続させるため。
    //加速度なや、移動予約など引き継がれないものが多数あるので、複雑な移動をする際は、ココに注意を払うこと！
    //レーザーがゲーム領域外にたっしたときも、先頭チップから順に連続で引継ぎが発生することになる。
    //ちょっと無駄っぽいけど、さもなば先頭の次のチップが領域外に向かって移動するとは限らないので、やはり必要。
    if (_pChip_behind) {
        RefractionLaserChip* pChip_behind = (RefractionLaserChip*)_pChip_behind;
        pChip_behind->_pKuroko->_vX = _pKuroko->_vX;
        pChip_behind->_pKuroko->_vY = _pKuroko->_vY;
        pChip_behind->_pKuroko->_vZ = _pKuroko->_vZ;
        pChip_behind->_pKuroko->_angRzMv = _pKuroko->_angRzMv;
        pChip_behind->_pKuroko->_angRyMv = _pKuroko->_angRyMv;
        pChip_behind->_pKuroko->_veloMv = _pKuroko->_veloMv;
        pChip_behind->_pKuroko->_angFace[AXIS_X] = _pKuroko->_angFace[AXIS_X];
        pChip_behind->_pKuroko->_angFace[AXIS_Y] = _pKuroko->_angFace[AXIS_Y];
        pChip_behind->_pKuroko->_angFace[AXIS_Z] = _pKuroko->_angFace[AXIS_Z];
        pChip_behind->_cnt_refraction = _cnt_refraction;
        pChip_behind->_frame_refraction_enter = _frame_refraction_enter;
        pChip_behind->_frame_refraction_out = _frame_refraction_out;
        pChip_behind->_isRefracting = _isRefracting;
        //屈折エフェクトを解除
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = NULL;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = NULL;
        }
        pChip_behind->_pRefractionEffect = _pRefractionEffect;
    } else {
        //屈折エフェクトを解除
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = NULL;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = NULL;
        }
    }

    LaserChip::onInactive(); //つながりを切断処理
}

void RefractionLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    //座標に反映
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    if (getActivePartFrame() > 1) {
        //GgafActorDispatcher::employ() は
        //取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動される。
        //したがって、レーザーの先頭から順番にprocessBehavior() が呼ばれるため、以下のようにすると
        //数珠繋ぎになる。
        if (pChip_front == NULL) {
            //本当の先頭チップか、或いはにわか先頭チップの場合の共通処理
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _prev_isRefracting = _isRefracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = NULL;
            if (!_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionBegin(_cnt_refraction);
                        _frame_refraction_out = getBehaveingFrame()  + _frame_standstill_refraction;
                        _isRefracting = true;

                        if (_pDispatche_RefractionEffect) {
                            _pRefractionEffect = (GgafDx9DrawableActor*)_pDispatche_RefractionEffect->employ();
                            if (_pRefractionEffect) {
                                _pRefractionEffect->locateWith(this);
                                //最長時間の解除予約。
                                //何かの拍子でレーザーチップが消滅した場合、正しくsayonara()出来ない場合がある。その場合の保険。
                                _pRefractionEffect->activateOnlyFor(_pDispatcher->_num_chip_max +_frame_standstill_refraction);
                            }
                        }
                    }
                }
            }

            if (_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_out) {
                    onRefractionFinish(_cnt_refraction);
                    _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
                    //座標を変えず方向だけ転換
                    int X, Y, Z;
                    X = _X; Y = _Y; Z = _Z;
                    _pKuroko->behave(); //
                    _X = X; _Y = Y; _Z = Z;
                    _isRefracting = false;

                    return;
                }
            }

            if (!_isRefracting) {
                //_isRefracting中は停止しなくてはいけないため_pKuroko->behave()を実行しない。
                //_pKuroko->behave();以外で座標を操作している場合は、完全な停止にならないので注意
                _pKuroko->behave();
            }

        } else {
            //先頭以外のチップ数珠繋ぎ処理
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _prev_isRefracting = _isRefracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
            _isRefracting =  pChip_front->_prev_isRefracting;
            _pRefractionEffect = pChip_front->_prev_pRefractionEffect;
            if (_pChip_behind == NULL) {
                if (_pRefractionEffect) {
                    //_TRACE_("_pRefractionEffect->sayonara();");
                    _pRefractionEffect->sayonara(_frame_standstill_refraction);
                }
            }
        }
    }
}

void RefractionLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDx9GeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void RefractionLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //TODO:コメント未検証　たぶん問題なし
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

RefractionLaserChip::~RefractionLaserChip() {
}

