#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "HomingLaserChip";
    _is_leader = false;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _prev_x = _x;
    _prev_y = _y;
    _prev_z = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _is_fix_begin_pos = true;
}

void HomingLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //レーザーチップ出現時処理
    if (pChip_front == nullptr) {
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front == nullptr");
        _is_leader = true;
        //自身が先頭の場合
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
    } else {
        _is_leader = false;
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front =="<<(pChip_front->getName()));
        _begining_x = pChip_front->_begining_x;
        _begining_y = pChip_front->_begining_y;
        _begining_z = pChip_front->_begining_z;
        _begining_rx = pChip_front->_begining_rx;
        _begining_ry = pChip_front->_begining_ry;
        _begining_rz = pChip_front->_begining_rz;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
        }
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
        LaserChip* pChip_behind = _pChip_behind;
        //中間チップ消失時の場合
        //自身のチップが消失することにより、レーザーの数珠つなぎ構造が２分されてしまう。
        //消失前の先頭以外のチップは、一つ前に追従してるだけなので、中間チップ Mover 内部パラメータは不定。
        //後方チップが新たな先頭チップとなるレーザー構造のグループを getKuroko()->behave() で動作を継続させるために、
        //新たな先頭チップへ現在の移動方向と移動速度の情報を伝達する必要がある。
        if (pChip_behind) {
            int D = (int)(sqrt(
                              (
                                ((double)(pChip_behind->_x - _x)) * ((double)(pChip_behind->_x - _x))
                              ) + (
                                ((double)(pChip_behind->_y - _y)) * ((double)(pChip_behind->_y - _y))
                              ) + (
                                ((double)(pChip_behind->_z - _z)) * ((double)(pChip_behind->_z - _z))
                              )
                            )
                         );
            pChip_behind->getKuroko()->setMvVelo(D); //距離が速度になる
            pChip_behind->getKuroko()->setMvAngTwd(this);
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 であるにも関わらず、_pChip_behindが存在しません");
        }
    } else if (_chip_kind == 3) {
        //中間先頭チップ消失時の場合
        //殆どの場合、先頭から順に消えていくはずである。
        //行いたいことは中間チップ消失時の場合と同じで、後方チップへ情報を伝達する必要がある。
        //先端チップ Mover 内部パラメータの移動方向と移動速度の情報をコピーすることでOK
        //計算速度を稼ぐ
        if (_pChip_behind && _pChip_front) {
            GgafDxKuroko* const pChip_behind_pKuroko = _pChip_behind->getKuroko();
            GgafDxKuroko* const pChip_front_pKuroko = _pChip_front->getKuroko();
            pChip_behind_pKuroko->_vX = pChip_front_pKuroko->_vX;
            pChip_behind_pKuroko->_vY = pChip_front_pKuroko->_vY;
            pChip_behind_pKuroko->_vZ = pChip_front_pKuroko->_vZ;
            pChip_behind_pKuroko->_angRzMv = pChip_front_pKuroko->_angRzMv;
            pChip_behind_pKuroko->_angRyMv = pChip_front_pKuroko->_angRyMv;
            pChip_behind_pKuroko->_veloMv =  pChip_front_pKuroko->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 であるにも関わらず、_pChip_front と _pChip_behind が両方存在しません");
        }
    } else if (_chip_kind == 4) {
        if (_pChip_behind) {
            GgafDxKuroko* const pChip_behind_pKuroko = _pChip_behind->getKuroko();
            GgafDxKuroko* pKuroko = getKuroko();
            pChip_behind_pKuroko->_vX = pKuroko->_vX;
            pChip_behind_pKuroko->_vY = pKuroko->_vY;
            pChip_behind_pKuroko->_vZ = pKuroko->_vZ;
            pChip_behind_pKuroko->_angRzMv = pKuroko->_angRzMv;
            pChip_behind_pKuroko->_angRyMv = pKuroko->_angRyMv;
            pChip_behind_pKuroko->_veloMv  = pKuroko->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 4 であるにも関わらず、_pChip_behind が存在しません");
        }
    }
    LaserChip::onInactive(); //つながりを切断処理
}

void HomingLaserChip::processBehavior() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    //座標に反映
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (getActiveFrame() > 1) {
        //GgafActorDepository::dispatch() は
        //取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動される。
        //したがって、レーザーの先頭から順番にprocessBehavior() が呼ばれるため、以下のようにすると
        //数珠繋ぎになる。
        if (pChip_front == nullptr) {
            //本当の先頭チップか、或いはにわか先頭チップの場合の共通処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            processBehaviorHeadChip(); //先頭チップのみ移動実装
        } else {
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _x  = pChip_front->_prev_x;
            _y  = pChip_front->_prev_y;
            _z  = pChip_front->_prev_z;
            _rx = pChip_front->_prev_rx;
            _ry = pChip_front->_prev_ry;
            _rz = pChip_front->_prev_rz;
        }
    }
}

void HomingLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

HomingLaserChip::~HomingLaserChip() {
}

