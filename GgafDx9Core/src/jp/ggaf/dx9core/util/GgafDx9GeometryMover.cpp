#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// 【自分メモ】考え方と単語
//
// ＜２種類の方向＞
// 「方向」には２種類ある。「移動方角（方向）」と「軸回転方角（方向）」である。
// 「移動方角（方向）」はキャラの進行方向のみを表現する。これは「移動速度」と伴って、キャラは座標内を移動することとする。
// 「軸回転方角」はキャラの向きのみを表せる。
// キャラクタが画面の上部から下部へ移動しても、キャラクタは下を向くとは限らず自機に向いてほしい場合もある。
// 右にキャラを向かせて、左に移動させたいこともある。それぞれ設定が必要。

// ＜移動方角＞
// キャラが進む方向、つまり「移動方角」の方向は、原点から単位球の表面に向かって伸びるベクトル (_vX, _vY, _vZ) で表す方法と、
// 緯度と経度(または、アジマスと仰角)の２つのアングル値 (_angRzMove, _angRyMove) で表す方法の２種類用意した。
// 単に「移動方角」と呼ぶ場合は、一般的に移動方向のベクトルのことを指すが、ここでは、２つのアングル値をセットの事を「移動方角」
// と呼ぶ場合が多い（こととする）。
// 緯度経度表現の場合、緯度＝Z軸回転角、経度＝Y軸回転角 と見立てる事ができるので、成分を個別に表現したい場合
// それぞれ「移動方角（Z軸）」「移動方角（Y軸）」と表現することにする。・・・方角、などという言葉だか、内容は角度の値。
// つまり、「移動方角（Y軸）」という言葉の語彙は、まわりくどく説明すると、
// 「キャラの進行方向を、方向ベクトルでは無く緯度経度に見立てたZ軸回転角とY軸回転角で表現した場合のY軸回転角成分のみのアングル値」
// ということとする。
//
// 移動方角にはZ軸回転角とY軸回転角による指定(_angRzMove, _angRyMove)と単位ベクトル指定(_vX, _vY, _vZ) があると言ったが、
// もっぱら使うのは前者の方である。本ライブラリのメソッドも _angRzMove と _angRyMove を操作するものが多い。
// しかし、最終的には ワールド変換行列の移動先の行列を求めるため、「単位ベクトル(_vX, _vY, _vZ)*移動速度 」  という計算をする必要がある。
// 結局最後は単位ベクトル求めているのだが。移動中の座標計算などは、さんざん_angRzMove と _angRyMoveで行って、最後に１回単位ベクトルを
// 求める、というのが理想的。未だ最適化の余地だいぶ残っている（が、またいつか）。
//
// 本クラスライブラリでは、この(_angRzMove, _angRyMove)を操作して、そのアングル値に方向ベクトル(_vX, _vY, _vZ) を追従させている。
// (_vX, _vY, _vZ)のみ直接操作すると、(_angRzMove, _angRyMove)との同期が崩れるため、そこは自己責任で。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらないこととする。
//

// ＜移動速度＞
// キャラは「移動速度」(_veloMove)を保持している。移動する方法は簡単で、毎フレーム「移動方角」に「移動速度」分動くだけである。
// つまり「移動方角」(_vX, _vY, _vZ)に「移動速度」(_veloMove)を掛け算している。１フレーム後の座標は
// (_vX*_veloMove, _vY*_veloMove, _vZ*_veloMove) である。  これに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を掛ける。
// よって、(_vX*_veloMove*LEN_UNIT, _vY*_veloMove*LEN_UNIT, _vZ*_veloMove*LEN_UNIT)が１フレーム後の座標。

// ＜軸回転方角＞
// キャラが向いている方角（方向）、を「軸回転方角」と呼ぶことにする。「軸回転方角」は、ワールド変換行列の軸回転と、１対１に対応している。
// ワールド変換行列の軸回転とは、X軸回転角、Y軸回転角、Z軸回転角のことで、_angFace[AXIS_X]、_angFace[AXIS_Y]、_angFace[AXIS_Z]
// が保持している。
// 本ライブラリでは、キャラが原点にあるとして、単位球の表面に向かって伸びるベクトル(1, 0, 0) をキャラの「前方」と設定している。「後方」は（-1, 0, 0)。
// また、ワールド変換行列の回転行列のかける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 > (拡大縮小) 」 とする。
// (※ X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// そこで、X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「軸回転方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_angFace[AXIS_Z], _angFace[AXIS_Y])で表現できる。
// つまり、「前方」は Z軸回転角・Y軸回転角共に0度とし、例えば「前方を向いて後ろ方向」は[Z軸回転角,Y軸回転角]=[0度,180度] と表現する。。
// 単に「Z軸回転角」などと書くと、「移動方角」のZ軸回転角なのか、「軸回転方角」のZ軸回転角なのか曖昧になるため、
// 「軸回転方角(Z軸)」「軸回転方角(Y軸)」と書くこととする。（※一応「軸回転方角(X軸)」もあるが、これはスピンを表し、前方という向きへの影響は無し）
// ここで注意は、１つのキャラが向いている方角に対して、２通りのアクセスする方法があるということ。例えば、
// 「前方を向いて右向き」 は [軸回転方角(Z軸), 軸回転方角(Y軸)]=[0, 90度] or [180度,270度] とで表現できる。
// （※軸回転方角(Y軸)は左手系座標のためY軸の正方向を向いて反時計回り）
// 実は 「前方」 も [180度,180度]とも表現できるし、「前方を向いて後ろ方向」 は [0度,180度] とも表現できる。
// どちらも向いている方向は同じ、但し姿勢は異なる。
// 当然、「移動方角」でも、２通りのアクセスする方法があるのだが、こちらは見た目に差が無い。

// ＜移動方角と軸回転方角で同期＞
// ここで 「移動方角（Z軸）」を「軸回転方角(Z軸)」へ、「移動方角（Y軸）」を「軸回転方角(Y軸)」 へコピーしてやると、
// なんと移動方角と、キャラクタの向きの同期が簡単に取れるじゃまいか。
// 逆にキャラが向いている方向に移動を追従させることも可能かな。

// ＜自動前方向き機能＞
// 自動前方向き機能とは「移動方角」を設定すると、それに伴って自動的に「軸回転方角」を設定する事を意味している。
// 具体的には、以下のようにフレーム毎に、アングル値を上書きコピーしているだけ。
//  ・移動方角（Z軸） → 軸回転方角(Z軸)
//  ・移動方角（Y軸） → 軸回転方角(Y軸)
// しかし「軸回転方角」を設定ても「移動方角」変化しない（逆は関連しない）ので注意。

// ＜角速度＞
// 「移動方角（Z軸）」「移動方角（Y軸）」、「軸回転方角(Z軸)」「軸回転方角(Y軸)」には、それぞれの「角速度」を設けてある。
// 例えば90度右に向きたい場合、キャラがいきなりカクっと向きを変えては悲しいので、毎フレーム角速度だけ角を加算するようにして、
// 滑らかに向きを変えるようにする。
// 「角速度」は正負の注意が必要。正の場合は反時計回り、負の場合は時計回りになる。
// 方向転換する場合、ターゲットとなる角度への到達する方法の考え方は、5通りある。（アクセス方法は２通りしかない）
// 「常に反時計回で行く」「常に時計回りで行く」「近い角の周り方向で行く」「遠回りな角の周り方向で行く」「現在回っている方向で行く」
// である。それぞれ用途があるので、オプション引数などで、選択できるようにしたいな。

// ＜軸方向移動＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_X,_Y,_Z)にそれぞれの移動増分が
// 加算される。


GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;


    for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す

        //軸回転方角
        _angFace[i] = 0; //0 angle は ３時の方角を向いている
        //軸回転方角の角速度（軸回転方角の増分）= 0 angle/fream
        _angveloRotFace[i] = 0; //1フレームに加算される軸回転方角の角増分。デフォルトは軸回転方角の角増分無し、つまり振り向き無し。
        //軸回転方角の角速度上限 ＝ 360,000 angle/fream
        _angveloRotTopFace[i] = ANGLE360; //_angveloRotFace[n] の増分の上限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角速度下限 ＝ -360,000 angle/fream
        _angveloRotBottomFace[i] = ANGLE360 * -1; //_angveloRotFace[n] の増分の下限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _angacceRotFace[i] = 0; //_angveloRotFace[n] の増分。デフォルトは軸回転方角の角加速度無し
        //目標軸回転方角への自動制御フラグ = 無効
        _face_angle_targeting_flg[i] = false;
        //目標の軸回転方角
        _angTargetRotFace[i] = 0; //目標軸回転方角への自動制御フラグ = 無効、の場合は無意味
        //目標の軸回転方角自動停止機能が有効になる回転方向
        _face_angle_target_allow_way[i] = TURN_BOTH;
        //目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通）
        _face_angle_target_allow_velocity[i] = ANGLE180;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //移動方角のZ軸回転
    _angRzMove = 0;
    //移動方角のY軸回転
    _angRyMove = 0;
    //移動速度
    _veloMove = 0;
    //移動速度上限 = 256 px/fream
    _veloTopMove = 256 * LEN_UNIT; //_veloMove が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。
    //移動速度下限 = 0   px/fream
    _veloBottomMove = -256 * LEN_UNIT; //_veloMove が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _accMove = 0; //_veloMove の増分。デフォルトは加速無し

    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _angveloRzMove = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRzTopMove = ANGLE360; //_angveloRzMove の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRzBottomMove = ANGLE360 * -1; //_angveloRzMove の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _angacceRzMove = 0; //_angveloRzMove の増分。デフォルトは移動方角の角加速度無し
    //目標移動方角（Z軸回転）への自動制御フラグ = 無効
    _move_angle_rz_target_flg = false;
    //目標の移動方角（Z軸回転）
    _angTargetRzMove = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _move_angle_rz_target_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _move_angle_rz_target_allow_velocity = ANGLE180;
    //移動方角（Z軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _synchronize_RzFaceAngle_to_RzMoveAngle_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _angveloRyMove = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRyTopMove = ANGLE360; //_angveloRyMove の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRyBottomMove = ANGLE360 * -1; //_angveloRyMove の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _angacceRyMove = 0; //_angveloRyMove の増分。デフォルトは移動方角の角加速度無し
    //目標移動方角（Y軸回転）への自動制御フラグ = 無効
    _move_angle_ry_target_flg = false;
    //目標の移動方角（Y軸回転）
    _angTargetRyMove = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _move_angle_ry_target_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _move_angle_ry_target_allow_velocity = ANGLE180;
    //移動方角（Y軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _synchronize_RyFaceAngle_to_RyMoveAngle_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMove = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMove = 256 * LEN_UNIT;
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMove = -256 * LEN_UNIT;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMove = 0;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMove = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMove = 256 * LEN_UNIT;
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMove = -256 * LEN_UNIT;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMove = 0;
    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMove = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMove = 256 * LEN_UNIT;
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMove = -256 * LEN_UNIT;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMove = 0;

    _progSP = NULL;

}

void GgafDx9GeometryMover::behave() {

    //スプライン曲線移動
    if (_progSP != NULL) {
        _progSP->behave();
    }

    //軸回転方角処理
    static angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_face_angle_targeting_flg[i]) {
            _angveloRotFace[i] += _angacceRotFace[i];
            setFaceAngleVelocity(i, _angveloRotFace[i]);

            if (_angveloRotFace[i] > 0) { //反時計回りの場合
                angDistance = getFaceAngleDistance(i, _angTargetRotFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloRotFace[i] > angDistance && _face_angle_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_angle_target_allow_velocity[i] >= _angveloRotFace[i]) {
                    addFaceAngle(i, angDistance);
                    _face_angle_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addFaceAngle(i, _angveloRotFace[i]);
                }
            } else if (_angveloRotFace[i] < 0) { //時計回りの場合
                angDistance = getFaceAngleDistance(i, _angTargetRotFace[i], TURN_CLOCKWISE);
                if (_angveloRotFace[i] < angDistance && _face_angle_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_angle_target_allow_velocity[i] <= _angveloRotFace[i]) { //目標を行き過ぎてしまいそう･･･な日
                    addFaceAngle(i, angDistance);
                    _face_angle_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addFaceAngle(i, _angveloRotFace[i]);
                }
            } else {
                //_angveloRotFace[i] == 0
                addFaceAngle(i, 0);
            }

            if (_face_angle_targeting_flg[i] == false) {
                //目標方向に到達した時の処理
                //_angveloRotTopFace[i] = ANGLE360; //軸回転方角の角速度上限 ＝ 360,000 angle/fream
                //_angveloRotBottomFace[i] = ANGLE360 * -1; //軸回転方角の角速度下限 ＝ -360,000 angle/fream

                //目標方向に到達した時、停止処理を行なう
                _angacceRotFace[i] = 0; //軸回転方向角、角速度を０へ
                setFaceAngleVelocity(i, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //if (_angacceRotFace[i] != 0) {
            //フレーム毎の軸回転方角旋廻の処理
            _angveloRotFace[i] += _angacceRotFace[i];
            if (_angveloRotFace[i] != 0) {
                addFaceAngle(i, _angveloRotFace[i]);
            }
            //}
        }
    }

    //Actorに反映
    _pActor->_RX = _angFace[AXIS_X];
    _pActor->_RY = _angFace[AXIS_Y];
    _pActor->_RZ = _angFace[AXIS_Z];

    ///////////////////////////////////////////////////Mover
    //X軸方向移動加速度の処理
    _veloVxMove += _acceVxMove;
    setVxMoveVelocity(_veloVxMove);
    //Y軸方向移動加速度の処理
    _veloVyMove += _acceVyMove;
    setVyMoveVelocity(_veloVyMove);
    //Z軸方向移動加速度の処理
    _veloVzMove += _acceVzMove;
    setVzMoveVelocity(_veloVzMove);

    //移動加速度の処理
    _veloMove += _accMove;
    setMoveVelocity(_veloMove);
    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_move_angle_rz_target_flg) {

        _angveloRzMove += _angacceRzMove;
        setRzMoveAngleVelocity(_angveloRzMove);

        if (_angveloRzMove > 0) { //反時計回りの場合
            angle angDistance = getRzMoveAngleDistance(_angTargetRzMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMove > angDistance && _move_angle_rz_target_allow_way != TURN_CLOCKWISE
                    && _move_angle_rz_target_allow_velocity >= _angveloRzMove) { //目標を行き過ぎてしまいそう･･･な日
                addRzMoveAngle(angDistance);
                _move_angle_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else if (_angveloRzMove < 0) { //時計回りの場合

            angle angDistance = getRzMoveAngleDistance(_angTargetRzMove, TURN_CLOCKWISE);
            if (_angveloRzMove < angDistance && _move_angle_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_move_angle_rz_target_allow_velocity <= _angveloRzMove) {
                addRzMoveAngle(angDistance);
                _move_angle_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else {
            addRzMoveAngle(0);
        }
        if (_move_angle_rz_target_flg == false) {
            //_angveloRzTopMove = ANGLE360; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRzBottomMove = ANGLE360 * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRzMove = 0; //Z軸移動方向角、角加速度を０へ
            setRzMoveAngleVelocity(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacceRzMove != 0) {
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _angveloRzMove += _angacceRzMove;
        if (_angveloRzMove != 0) {
            addRzMoveAngle(_angveloRzMove);
        }
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_move_angle_ry_target_flg) {

        _angveloRyMove += _angacceRyMove;
        setRyMoveAngleVelocity(_angveloRyMove);

        if (_angveloRyMove > 0) { //現在は反時計回りの場合
            angle angDistance = getRyMoveAngleDistance(_angTargetRyMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMove > angDistance &&
                _move_angle_ry_target_allow_way != TURN_CLOCKWISE &&
                _move_angle_ry_target_allow_velocity >= _angveloRyMove)
            { //目標を行き過ぎてしまいそう･･･な日
                addRyMoveAngle(angDistance);
                _move_angle_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else if (_angveloRyMove < 0) { //現在は時計回りの場合

            angle angDistance = getRyMoveAngleDistance(_angTargetRyMove, TURN_CLOCKWISE);
            if (_angveloRyMove < angDistance &&
                _move_angle_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_move_angle_ry_target_allow_velocity <= _angveloRyMove)
            {
                addRyMoveAngle(angDistance);
                _move_angle_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else {
            //_angveloRyMove==0
            addRyMoveAngle(0);
        }
        if (_move_angle_ry_target_flg == false) {
            //_angveloRyTopMove = ANGLE360; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRyBottomMove = ANGLE360*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRyMove = 0; //Y軸移動方向角、角加速度を０へ
            setRyMoveAngleVelocity(0); //Y軸移動方向角、角速度を０へ
        }
    } else {
        //if (_angacceRyMove != 0) {
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _angveloRyMove += _angacceRyMove;
        if(_angveloRyMove != 0) {
            addRyMoveAngle(_angveloRyMove);
        }
        //}
    }
    ///////////////

    //Actorに反映
    _pActor->_X += (int)(_vX * _veloMove + _veloVxMove);
    _pActor->_Y += (int)(_vY * _veloMove + _veloVyMove);
    _pActor->_Z += (int)(_vZ * _veloMove + _veloVzMove);

}


angle GgafDx9GeometryMover::simplifyAngle(angle prm_ang) {
    static angle angSimple;
    angSimple = prm_ang;
    while (angSimple >= ANGLE360) {
        angSimple -= ANGLE360;
    }
    while (angSimple < 0) {
        angSimple += ANGLE360;
    }
    return angSimple;
}

void GgafDx9GeometryMover::setFaceAngle(int prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = simplifyAngle(prm_angFace);
}

void GgafDx9GeometryMover::setFaceAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9GeometryMover::addFaceAngle(int prm_axis, angle prm_angDistance) {
    static angle angOffsetrot_FaceAngle;
    angOffsetrot_FaceAngle = prm_angDistance;
    if (_angveloRotBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAngle = _angveloRotBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloRotTopFace[prm_axis]) {
        angOffsetrot_FaceAngle = _angveloRotTopFace[prm_axis];
    }
    setFaceAngle(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAngle);
}

void GgafDx9GeometryMover::setFaceAngleVelocity(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloRotTopFace[prm_axis]) {
        _angveloRotFace[prm_axis] = _angveloRotTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloRotBottomFace[prm_axis]) {
        _angveloRotFace[prm_axis] = _angveloRotBottomFace[prm_axis];
    } else {
        _angveloRotFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometryMover::setFaceAngleVeloRenge(int prm_axis,
                                                    angvelo prm_angveloRot01,
                                                    angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloRotTopFace[prm_axis] = prm_angveloRot02;
        _angveloRotBottomFace[prm_axis] = prm_angveloRot01;
    } else {
        _angveloRotTopFace[prm_axis] = prm_angveloRot01;
        _angveloRotBottomFace[prm_axis] = prm_angveloRot02;
    }
    setFaceAngleVelocity(prm_axis, _angveloRotFace[prm_axis]); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setFaceAngleVeloAcceleration(int prm_axis, angacce prm_angacceRot) {
    _angacceRotFace[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometryMover::setSuspendTarget_FaceAngleV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_FaceAngle(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMove
    );
}

void GgafDx9GeometryMover::setSuspendTarget_FaceAngle(int prm_axis,
                                             angle prm_angTargetRot,
                                             int prm_way_allow,
                                             angvelo prm_angveloAllow) {
    _face_angle_targeting_flg[prm_axis] = true;
    _angTargetRotFace[prm_axis] = simplifyAngle(prm_angTargetRot);
    _face_angle_target_allow_way[prm_axis] = prm_way_allow;
    _face_angle_target_allow_velocity[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometryMover::getFaceAngleDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getFaceAngleDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometryMover::getFaceAngleDistance(int prm_axis, angle prm_angTargetRot, int prm_way) {
    static angle _angTargetRot;
    _angTargetRot = simplifyAngle(prm_angTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < ANGLE180) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //重なってる場合
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis]
                    + ANGLE180) {
                return _angTargetRot - _angFace[prm_axis];
            } else if (_angTargetRot == _angFace[prm_axis] + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angFace[prm_axis] + ANGLE180 < _angTargetRot && _angTargetRot <= ANGLE360) {
                return -1 * (_angFace[prm_axis] + (ANGLE360 - _angTargetRot));
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - ANGLE180) {
                return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis] - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angFace[prm_axis] - ANGLE180 < _angTargetRot && _angTargetRot
                    < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //重なってる場合
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= ANGLE360) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < ANGLE180) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //重なってる場合
                return ANGLE360;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis] + ANGLE180) {
                return -1 * ( _angFace[prm_axis] + (ANGLE360 -_angTargetRot));
            } else if (_angTargetRot == _angFace[prm_axis] + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angFace[prm_axis] + ANGLE180 < _angTargetRot && _angTargetRot <= ANGLE360) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - ANGLE180) {
                return -1 * (_angTargetRot - _angFace[prm_axis]);
            } else if (_angTargetRot == _angFace[prm_axis] - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return -ANGLE180;
            } else if (_angFace[prm_axis] - ANGLE180 < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return (ANGLE360 - _angFace[prm_axis]) + _angTargetRot;
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //重なってる場合
                return -ANGLE360;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= ANGLE360) {
                return (_angFace[prm_axis] + (ANGLE360 - _angTargetRot)) ;
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] < ANGLE360) {
            return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + ANGLE360 - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] < ANGLE360) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() 何故かしら角の距離が求めれません。(2)");
}


void GgafDx9GeometryMover::setMoveVeloRenge(int prm_veloMove01, int prm_veloMove02) {
    if (prm_veloMove01 < prm_veloMove02) {
        _veloTopMove = prm_veloMove02;
        _veloBottomMove = prm_veloMove01;
    } else {
        _veloTopMove = prm_veloMove01;
        _veloBottomMove = prm_veloMove02;
    }
    setMoveVelocity(_veloMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setMoveVelocity(int prm_veloMove) {
    if (prm_veloMove > _veloTopMove) {
        _veloMove = _veloTopMove;
    } else if (prm_veloMove < _veloBottomMove) {
        _veloMove = _veloBottomMove;
    } else {
        _veloMove = prm_veloMove;
    }
}

void GgafDx9GeometryMover::addMoveVelocity(int prm_veloMove_Offset) {
    setMoveVelocity(_veloMove + prm_veloMove_Offset);
}

void GgafDx9GeometryMover::setMoveVeloAcceleration(int prm_acceMove) {
    _accMove = prm_acceMove;
}

void GgafDx9GeometryMover::setRzMoveAngle(int prm_tX, int prm_tY) {
    setRzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRzMoveAngle(angle prm_angle) {
    if (prm_angle !=  _angRzMove) {
        _angRzMove = simplifyAngle(prm_angle);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_RzFaceAngle_to_RzMoveAngle_flg) {
        setFaceAngle(AXIS_Z, _angRzMove);
    }
}

void GgafDx9GeometryMover::addRzMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMove > prm_angDistance) {
        angOffset = _angveloRzBottomMove;
    } else if (prm_angDistance > _angveloRzTopMove) {
        angOffset = _angveloRzTopMove;
    }
    setRzMoveAngle(_angRzMove + angOffset);
}

void GgafDx9GeometryMover::setRzMoveAngleVelocity(angvelo prm_angveloRzMove) {
    if (prm_angveloRzMove > _angveloRzTopMove) {
        _angveloRzMove = _angveloRzTopMove;
    } else if (prm_angveloRzMove < _angveloRzBottomMove) {
        _angveloRzMove = _angveloRzBottomMove;
    } else {
        _angveloRzMove = prm_angveloRzMove;
    }
}

void GgafDx9GeometryMover::setRzMoveAngleVeloAcceleration(angacce prm_angacceRzMove) {
    _angacceRzMove = prm_angacceRzMove;
}

void GgafDx9GeometryMover::setRzMoveAngleVeloRenge(angvelo prm_angveloRzMove01,
                                                       angvelo prm_angveloRzMove02) {
    if (prm_angveloRzMove01 < prm_angveloRzMove02) {
        _angveloRzTopMove = prm_angveloRzMove02;
        _angveloRzBottomMove = prm_angveloRzMove01;
    } else {
        _angveloRzTopMove = prm_angveloRzMove01;
        _angveloRzBottomMove = prm_angveloRzMove02;
    }
    setRzMoveAngleVelocity(_angveloRzMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setSuspendTarget_RzMoveAngle(angle prm_angTargetRzMove,
                                                    int prm_way_allow,
                                                    angvelo prm_angveloAllowRyMove) {
    _move_angle_rz_target_flg = true;
    _angTargetRzMove = simplifyAngle(prm_angTargetRzMove);
    _move_angle_rz_target_allow_way = prm_way_allow;
    _move_angle_rz_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTarget_RzMoveAngleV(int prm_tX,
                                                     int prm_tY,
                                                     int prm_way_allow,
                                                     angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_RzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRzMoveAngleDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRzMoveAngleDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRzMoveAngleDistance(angle prm_angTargetRzMove, int prm_way) {
    angle angTargetRzMove = simplifyAngle(prm_angTargetRzMove);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRzMove && _angRzMove < ANGLE180) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angTargetRzMove);
            } else if (angTargetRzMove == _angRzMove) {
                //重なってる場合
                return 0;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove < _angRzMove + ANGLE180) {
                return angTargetRzMove - _angRzMove;
            } else if (angTargetRzMove == _angRzMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMove + ANGLE180 < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return -1 * (_angRzMove + (ANGLE360 - angTargetRzMove));
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRzMove && _angRzMove <= ANGLE360) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove - ANGLE180) {
                return ANGLE360 - _angRzMove + angTargetRzMove;
            } else if (angTargetRzMove == _angRzMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRzMove - ANGLE180 < angTargetRzMove && angTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angTargetRzMove);
            } else if (_angRzMove == angTargetRzMove) {
                //重なってる場合
                return 0;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove - _angRzMove;
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRzMove && _angRzMove < ANGLE180) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove) {
                return ANGLE360 - _angRzMove + angTargetRzMove;
            } else if (angTargetRzMove == _angRzMove) {
                //重なってる場合
                return ANGLE360;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove < _angRzMove + ANGLE180) {
                return -1*(_angRzMove + (ANGLE360-angTargetRzMove));
            } else if (angTargetRzMove == _angRzMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMove + ANGLE180 < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove - _angRzMove;
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRzMove && _angRzMove <= ANGLE360) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove - ANGLE180) {
                return  -1*(_angRzMove - angTargetRzMove);
            } else if (angTargetRzMove == _angRzMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRzMove - ANGLE180 < angTargetRzMove && angTargetRzMove < _angRzMove) {
                return _angRzMove + (ANGLE360 - angTargetRzMove);
            } else if (_angRzMove == angTargetRzMove) {
                //重なってる場合
                return -ANGLE360;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove + (ANGLE360 - _angRzMove);
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRzMove && _angRzMove < angTargetRzMove) {
            return (angTargetRzMove - _angRzMove);
        } else if (angTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return ANGLE360 - _angRzMove + angTargetRzMove;
        } else if (_angRzMove == angTargetRzMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRzMove && _angRzMove < angTargetRzMove) {
            return -1 * (_angRzMove + ANGLE360 - angTargetRzMove);
        } else if (angTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return -1 * (_angRzMove - angTargetRzMove);
        } else if (_angRzMove == angTargetRzMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() 何故かしら角の距離が求めれません。(1)");

}


void GgafDx9GeometryMover::setRyMoveAngle(int prm_tX, int prm_tY) {
    setRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRyMoveAngle(angle prm_angle) {
    if (prm_angle != _angRyMove) {
        _angRyMove = simplifyAngle(prm_angle);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_RyFaceAngle_to_RyMoveAngle_flg) {
        setFaceAngle(AXIS_Y, _angRyMove);
    }
}

void GgafDx9GeometryMover::addRyMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMove > prm_angDistance) {
        angOffset = _angveloRyBottomMove;
    } else if (prm_angDistance > _angveloRyTopMove) {
        angOffset = _angveloRyTopMove;
    }
    setRyMoveAngle(_angRyMove + angOffset);
}

void GgafDx9GeometryMover::setRyMoveAngleVelocity(angvelo prm_angveloRyMove) {
    if (prm_angveloRyMove > _angveloRyTopMove) {
        _angveloRyMove = _angveloRyTopMove;
    } else if (prm_angveloRyMove < _angveloRyBottomMove) {
        _angveloRyMove = _angveloRyBottomMove;
    } else {
        _angveloRyMove = prm_angveloRyMove;
    }
}

void GgafDx9GeometryMover::setRyMoveAngleVeloAcceleration(angacce prm_angacceRyMove) {
    _angacceRyMove = prm_angacceRyMove;
}

void GgafDx9GeometryMover::setRyMoveAngleVeloRenge(angvelo prm_angveloRyMove01,
                                                       angvelo prm_angveloRyMove02) {
    if (prm_angveloRyMove01 < prm_angveloRyMove02) {
        _angveloRyTopMove = prm_angveloRyMove02;
        _angveloRyBottomMove = prm_angveloRyMove01;
    } else {
        _angveloRyTopMove = prm_angveloRyMove01;
        _angveloRyBottomMove = prm_angveloRyMove02;
    }
    setRyMoveAngleVelocity(_angveloRyMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setSuspendTarget_RyMoveAngle(angle prm_angTargetRyMove,
                                                int prm_way_allow,
                                                angvelo prm_angveloAllowRyMove) {
    _move_angle_ry_target_flg = true;
    _angTargetRyMove = simplifyAngle(prm_angTargetRyMove);
    _move_angle_ry_target_allow_way = prm_way_allow;
    _move_angle_ry_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTarget_RyMoveAngleV(int prm_tX,
                                                 int prm_tY,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_RyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRyMoveAngleDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRyMoveAngleDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRyMoveAngleDistance(angle prm_angTargetRyMove, int prm_way) {
    static angle angTargetRyMove;
    angTargetRyMove = simplifyAngle(prm_angTargetRyMove);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRyMove && _angRyMove < ANGLE180) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angTargetRyMove);
            } else if (angTargetRyMove == _angRyMove) {
                //重なってる場合
                return 0;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove < _angRyMove + ANGLE180) {
                return angTargetRyMove - _angRyMove;
            } else if (angTargetRyMove == _angRyMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMove + ANGLE180 < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return -1 * (_angRyMove + (ANGLE360 - angTargetRyMove));
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRyMove && _angRyMove <= ANGLE360) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove - ANGLE180) {
                return ANGLE360 - _angRyMove + angTargetRyMove;
            } else if (angTargetRyMove == _angRyMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRyMove - ANGLE180 < angTargetRyMove && angTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angTargetRyMove);
            } else if (_angRyMove == angTargetRyMove) {
                //重なってる場合
                return 0;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove - _angRyMove;
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRyMove && _angRyMove < ANGLE180) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove) {
                return ANGLE360 - _angRyMove + angTargetRyMove;
            } else if (angTargetRyMove == _angRyMove) {
                //重なってる場合
                return ANGLE360;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove < _angRyMove + ANGLE180) {
                return -1*(_angRyMove + (ANGLE360-angTargetRyMove));
            } else if (angTargetRyMove == _angRyMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMove + ANGLE180 < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove - _angRyMove;
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRyMove && _angRyMove <= ANGLE360) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove - ANGLE180) {
                return  -1*(_angRyMove - angTargetRyMove);
            } else if (angTargetRyMove == _angRyMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return -ANGLE180;
            } else if (_angRyMove - ANGLE180 < angTargetRyMove && angTargetRyMove < _angRyMove) {
                return _angRyMove + (ANGLE360 - angTargetRyMove);
            } else if (_angRyMove == angTargetRyMove) {
                //重なってる場合
                return -ANGLE360;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove + (ANGLE360 - _angRyMove);
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRyMove && _angRyMove < angTargetRyMove) {
            return (angTargetRyMove - _angRyMove);
        } else if (angTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return ANGLE360 - _angRyMove + angTargetRyMove;
        } else if (_angRyMove == angTargetRyMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRyMove && _angRyMove < angTargetRyMove) {
            return -1 * (_angRyMove + ANGLE360 - angTargetRyMove);
        } else if (angTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return -1 * (_angRyMove - angTargetRyMove);
        } else if (_angRyMove == angTargetRyMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() 何故かしら角の距離が求めれません。(1)");

}


void GgafDx9GeometryMover::setRzRyMoveAngle(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMove || prm_angRy !=_angRyMove ) {
        _angRzMove = simplifyAngle(prm_angRz);
        _angRyMove = simplifyAngle(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_RzFaceAngle_to_RzMoveAngle_flg) {
        setFaceAngle(AXIS_Z, _angRzMove);
    }
    if (_synchronize_RyFaceAngle_to_RyMoveAngle_flg) {
        setFaceAngle(AXIS_Y, _angRyMove);
    }

}


void GgafDx9GeometryMover::setMoveAngle(GgafDx9GeometricActor* prm_pActor_Target) {
    setMoveAngle(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMove,
                   _angRyMove
                 );
}

void GgafDx9GeometryMover::setSuspendTarget_RzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target) {
    setSuspendTarget_RzRyMoveAngle(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setSuspendTarget_RzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _dummy1,
                   _dummy2,
                   _dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setSuspendTarget_RzMoveAngle(angRz_Target);
    setSuspendTarget_RyMoveAngle(angRy_Target);
}

void GgafDx9GeometryMover::setVxMoveVeloRenge(velo prm_veloVxMove01, velo prm_veloVxMove02) {
    if (prm_veloVxMove01 < prm_veloVxMove02) {
        _veloTopVxMove = prm_veloVxMove02;
        _veloBottomVxMove = prm_veloVxMove01;
    } else {
        _veloTopVxMove = prm_veloVxMove01;
        _veloBottomVxMove = prm_veloVxMove02;
    }
    setVxMoveVelocity(_veloVxMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVxMoveVelocity(velo prm_veloVxMove) {
    if (prm_veloVxMove > _veloTopVxMove) {
        _veloVxMove = _veloTopVxMove;
    } else if (prm_veloVxMove < _veloBottomVxMove) {
        _veloVxMove = _veloBottomVxMove;
    } else {
        _veloVxMove = prm_veloVxMove;
    }
}

void GgafDx9GeometryMover::setVxMoveVeloAcceleration(acce prm_acceVxMove) {
    _acceVxMove = prm_acceVxMove;
}

void GgafDx9GeometryMover::setVyMoveVeloRenge(velo prm_veloVyMove01, velo prm_veloVyMove02) {
    if (prm_veloVyMove01 < prm_veloVyMove02) {
        _veloTopVyMove = prm_veloVyMove02;
        _veloBottomVyMove = prm_veloVyMove01;
    } else {
        _veloTopVyMove = prm_veloVyMove01;
        _veloBottomVyMove = prm_veloVyMove02;
    }
    setVyMoveVelocity(_veloVyMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVyMoveVelocity(velo prm_veloVyMove) {
    if (prm_veloVyMove > _veloTopVyMove) {
        _veloVyMove = _veloTopVyMove;
    } else if (prm_veloVyMove < _veloBottomVyMove) {
        _veloVyMove = _veloBottomVyMove;
    } else {
        _veloVyMove = prm_veloVyMove;
    }
}

void GgafDx9GeometryMover::setVyMoveVeloAcceleration(acce prm_acceVyMove) {
    _acceVyMove = prm_acceVyMove;
}

void GgafDx9GeometryMover::setVzMoveVeloRenge(velo prm_veloVzMove01, velo prm_veloVzMove02) {
    if (prm_veloVzMove01 < prm_veloVzMove02) {
        _veloTopVzMove = prm_veloVzMove02;
        _veloBottomVzMove = prm_veloVzMove01;
    } else {
        _veloTopVzMove = prm_veloVzMove01;
        _veloBottomVzMove = prm_veloVzMove02;
    }
    setVzMoveVelocity(_veloVzMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVzMoveVelocity(velo prm_veloVzMove) {
    if (prm_veloVzMove > _veloTopVzMove) {
        _veloVzMove = _veloTopVzMove;
    } else if (prm_veloVzMove < _veloBottomVzMove) {
        _veloVzMove = _veloBottomVzMove;
    } else {
        _veloVzMove = prm_veloVzMove;
    }
}

void GgafDx9GeometryMover::setVzMoveVeloAcceleration(acce prm_acceVzMove) {
    _acceVzMove = prm_acceVzMove;
}



void GgafDx9GeometryMover::executeSplineMoveProgram(GgafDx9SplineProgram* prm_progSP, int prm_option) {
    _progSP = prm_progSP;
    _progSP->begin(_pActor, prm_option);
}

void GgafDx9GeometryMover::executeTagettingMoveAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                             angvelo prm_angVelocity, int prm_way) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAngle(prm_tX - _pActor->_X,
                              prm_tY - _pActor->_Y,
                              prm_tZ - _pActor->_Z,
                              out_angRz_Target,
                              out_angRy_Target);
    if (getRzMoveAngleDistance(out_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    if (getRyMoveAngleDistance(out_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }

    setSuspendTarget_RzMoveAngle(out_angRz_Target);
    setSuspendTarget_RyMoveAngle(out_angRy_Target);
}

void GgafDx9GeometryMover::executeTagettingMoveAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                             angvelo prm_angVelocity, int prm_way) {
    if (getRzMoveAngleDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    if (getRyMoveAngleDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }

    setSuspendTarget_RzMoveAngle(prm_angRz_Target);
    setSuspendTarget_RyMoveAngle(prm_angRy_Target);

}

void GgafDx9GeometryMover::executeTagettingRzMoveAngleSequence(angle prm_angRz_Target,
                                                               angvelo prm_angVelocity, int prm_way) {
    if (getRzMoveAngleDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    setSuspendTarget_RzMoveAngle(prm_angRz_Target);

}

void GgafDx9GeometryMover::executeTagettingRyMoveAngleSequence(angle prm_angRy_Target,
                                                               angvelo prm_angVelocity, int prm_way) {
    if (getRyMoveAngleDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }
    setSuspendTarget_RyMoveAngle(prm_angRy_Target);
}



GgafDx9GeometryMover::~GgafDx9GeometryMover() {

    //DELETE_POSSIBLE_NULL(_progSP);//Actorで始末する。いらない
}
