#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 2;
    _frame_standstill = 10;
    _frame_refraction_interval = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_outer = 0;
    _isRefracting = false;
}

void RefractionLaserChip::initialize() {
    //初期設定です。
    //30px/frame の移動速度
    //当たり判定あり。
    //α＝0.99
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    _pMover->setMvVelo(30000);
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
        _frame_refraction_enter = getBehaveingFrame() + _frame_refraction_interval;
        _frame_refraction_outer = _frame_refraction_enter + _frame_standstill;
		onRefractionEnter(_cnt_refraction); //0回目の屈折
		onRefractionOut(_cnt_refraction);
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
        _frame_refraction_outer = INT_MAX;
    }

    _isRefracting = false;
}

void RefractionLaserChip::onInactive() {
    //レーザーチップ消失時処理

    //一つ後方のチップがあれば、自分の意思（移動など）を引き継がせる
    //これは、レーザーがちぎれた場合、以下のパラメーターのみ引き継がせ、移動を継続させるため。
    //加速度なや、移動予約など引き継がれないものが多数あるので、複雑な移動をする際は、ココに注意を払うこと！
    //レーザーがゲーム領域外にたっしたときも、先頭チップから順に連続で引継ぎが発生することになる。
    //ちょっと無駄っぽいけど、さもなば先頭の次のチップが領域外に向かって移動するとは限らないので、やはり必要。
    if (_pChip_behind) {
        _pChip_behind->_pMover->_vX = _pMover->_vX;
        _pChip_behind->_pMover->_vY = _pMover->_vY;
        _pChip_behind->_pMover->_vZ = _pMover->_vZ;
        _pChip_behind->_pMover->_angRzMv = _pMover->_angRzMv;
        _pChip_behind->_pMover->_angRyMv = _pMover->_angRyMv;
        _pChip_behind->_pMover->_veloMv = _pMover->_veloMv;
        _pChip_behind->_pMover->_angFace[AXIS_X] = _pMover->_angFace[AXIS_X];
        _pChip_behind->_pMover->_angFace[AXIS_Y] = _pMover->_angFace[AXIS_Y];
        _pChip_behind->_pMover->_angFace[AXIS_Z] = _pMover->_angFace[AXIS_Z];
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
    if (getPartFrame() > 1) {
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

            if (!_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionEnter(_cnt_refraction);
                        _frame_refraction_outer = getBehaveingFrame()  + _frame_standstill;
                        _isRefracting = true;
                    }
//                    else {
//                        _cnt_refraction = INT_MAX;
//                        _frame_refraction_enter = INT_MAX;
//                        _frame_refraction_outer = INT_MAX;
//                    }
                }
            }

            if (_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_outer) {
                    onRefractionOut(_cnt_refraction);
                    _frame_refraction_enter = getBehaveingFrame() + _frame_refraction_interval;
                    //座標を変えず方向だけ転換
                    int X, Y, Z;
                    X = _X; Y = _Y; Z = _Z;
                    _pMover->behave(); //
                    _X = X; _Y = Y; _Z = Z;
                    _isRefracting = false;
                }
            }

            if (!_isRefracting) {
                //_isRefracting中は停止しなくてはいけないため_pMover->behave()を実行しない。
                //_pMover->behave();以外で座標を操作している場合は、完全な停止にならないので注意
                _pMover->behave();
            }

        } else {
            //先頭以外のチップ処理
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
        }
    }
}

void RefractionLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //TODO:コメント未検証　たぶん問題なし
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

RefractionLaserChip::~RefractionLaserChip() {
}

