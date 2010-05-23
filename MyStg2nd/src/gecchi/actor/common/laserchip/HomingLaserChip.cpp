#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "HomingLaserChip";
    _is_leader = false;
}

void HomingLaserChip::initialize() {
    //初期設定です。
    //30px/frame の移動速度
    //当たり判定あり。
    //α＝0.99
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    _pMover->setMvVelo(30000);
    _fAlpha = 0.99;
}


void HomingLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //レーザーチップ出現時処理
    if (pChip_front == NULL) {
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front == NULL");
        _is_leader = true;
        //自身が先頭の場合
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_RX = _RX;
        _begining_RY = _RY;
        _begining_RZ = _RZ;
    } else {
        _is_leader = false;
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front =="<<(pChip_front->getName()));
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
    }




}

void HomingLaserChip::onInactive() {



    //レーザーチップ消失時処理
    //      -==========<>            レーザーは
    //
    //      -= === === === <>        こんなふうに分断されています。
    //
    //    | -=|===|===|===|<> |      左図はレーザーをオブジェクトで区切ったつもりの図
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:先端チップ(非表示で、中間先頭チップを表示するためだけに存在)
    //    |   |   |   |    `----- 3:中間先頭チップ(表示される実質の先頭)
    //    |   |   |    `----- 2:中間チップ
    //    |   |    `----- 2:中間チップ
    //    |    `----- 2:中間チップ
    //     `----- 1:末尾チップ
    //

    //_TRACE_("A HomingLaserChip::onInactive() _chip_kind ="<<_chip_kind <<")");
    if (_chip_kind == 1) {

    } else if (_chip_kind == 2) {
        //中間チップ消失時の場合
        //自身のチップが消失することにより、レーザーの数珠つなぎ構造が２分されてしまう。
        //消失前の先頭以外のチップは、一つ前に追従してるだけなので、中間チップ Mover 内部パラメータは不定。
        //後方チップが新たな先頭チップとなるレーザー構造のグループを _pMover->behave() で動作を継続させるために、
        //新たな先頭チップへ現在の移動方向と移動速度の情報を伝達する必要がある。
        if (_pChip_behind) {
            int D = (int)(GgafUtil::sqrt_fast(
                              (
                                ((double)(_pChip_behind->_X - _X)) * ((double)(_pChip_behind->_X - _X))
                              ) + (
                                ((double)(_pChip_behind->_Y - _Y)) * ((double)(_pChip_behind->_Y - _Y))
                              ) + (
                                ((double)(_pChip_behind->_Z - _Z)) * ((double)(_pChip_behind->_Z - _Z))
                              )
                            )
                         );
            _pChip_behind->_pMover->setMvVelo(D); //距離が速度になる
            _pChip_behind->_pMover->setMvAng(this);
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 であるにも関わらず、_pChip_behindが存在しません");
        }
    } else if (_chip_kind == 3) {
        //中間先頭チップ消失時の場合
        //殆どの場合、先頭から順に消えていくはずである。
        //行いたいことは中間チップ消失時の場合と同じだが、
        //先端チップ Mover 内部パラメータの移動方向と移動速度の情報をコピーすることでOK
        //計算速度を稼ぐ
        if (_pChip_behind && _pChip_front) {
            _pChip_behind->_pMover->_vX = _pChip_front->_pMover->_vX;
            _pChip_behind->_pMover->_vY = _pChip_front->_pMover->_vY;
            _pChip_behind->_pMover->_vZ = _pChip_front->_pMover->_vZ;
            _pChip_behind->_pMover->_angRzMv = _pChip_front->_pMover->_angRzMv;
            _pChip_behind->_pMover->_angRyMv = _pChip_front->_pMover->_angRyMv;
            _pChip_behind->_pMover->_veloMv = _pChip_front->_pMover->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 であるにも関わらず、_pChip_front と _pChip_behind が両方存在しません");
        }
    } else if (_chip_kind == 4) {
        if (_pChip_behind) {
            _pChip_behind->_pMover->_vX = _pMover->_vX;
            _pChip_behind->_pMover->_vY = _pMover->_vY;
            _pChip_behind->_pMover->_vZ = _pMover->_vZ;
            _pChip_behind->_pMover->_angRzMv = _pMover->_angRzMv;
            _pChip_behind->_pMover->_angRyMv = _pMover->_angRyMv;
            _pChip_behind->_pMover->_veloMv = _pMover->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 4 であるにも関わらず、_pChip_behind が存在しません");
        }
    }
    LaserChip::onInactive(); //つながりを切断処理
}

void HomingLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    //座標に反映
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
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
//            _prev_vX = _pMover->_vX;
//            _prev_vY = _pMover->_vY;
//            _prev_vZ = _pMover->_vZ;
//            _prev_RzMvAng = _pMover->_angRzMv;
//            _prev_RyMvAng = _pMover->_angRyMv;

            processBehaviorHeadChip(); //先頭チップのみ移動実装
        } else {

            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
//            _prev_vX = _pMover->_vX;
//            _prev_vY = _pMover->_vY;
//            _prev_vZ = _pMover->_vZ;
//            _prev_RzMvAng = _pMover->_angRzMv;
//            _prev_RyMvAng = _pMover->_angRyMv;

            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
//            _pMover->_vX = pChip_front->_prev_vX;
//            _pMover->_vY = pChip_front->_prev_vY;
//            _pMover->_vZ = pChip_front->_prev_vZ;
//            _pMover->_angRzMv = pChip_front->_prev_RzMvAng;
//            _pMover->_angRyMv = pChip_front->_prev_RyMvAng;
        }
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}

