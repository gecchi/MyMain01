﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// 【メモ】本クラスの考え方と単語の表現
//
// ＜２種類の方向＞
// 「方向」には２種類意味があり、「移動方角（方向）」と「軸回転方角（方向）」とする。
// 「移動方角（方向）」はキャラの進行方向のみを表現する。これは「移動速度」と伴って、キャラは座標内を移動することとする。
// 「軸回転方角」はキャラの向きのみを表せる。
// キャラクタが画面の上部から下部へ移動しても、キャラクタは下を向くとは限らず自機に向いてほしい場合もある。
// 右にキャラを向かせて、左に移動させたいこともある。それぞれ設定が必要。
// 「軸回転方角（方向）」は以下。
//
// ＜移動方角:AngMv＞
// キャラが進む方向、つまり移動方角の方向は、原点から単位球の表面に向かって伸びるベクトル (_vX, _vY, _vZ) で表す方法と、
// ２つのアングル値 (_angRzMv, _angRyMv) で表す方法の２種類用意した。
// 単に「移動方角」と呼ぶ場合は、世間一般は移動方向の方向ベクトル（XYZの値）のことを指す。
// しかしここでは、２つのアングル値のセットの事を主に移動方角と呼んでいる。
// _angRzMv は Z軸回転角、 _angRyMv は Y軸回転角 を意味している。
// これは方向ベクトルを、緯度と経度、（仰角とアジマス）の関係に対応させようとした設計。しかし、Y軸回転角≡経度 であるが、Z軸回転角は
// Z軸回転角 → Y軸回転角の順番である場合に限り、緯度と意味が同じになるという制限がある。必ず Z軸回転 → Y軸回転の順番であると定義する。
// しかしここでは簡略して、緯度経度の、「緯度」＝「Z軸回転角」、「経度」＝「Y軸回転角」 と表現することとする。
// 成分を個別に表現したい場合は、それぞれ「移動方角（Z軸）」「移動方角（Y軸）」と書くことにする。
// 本クラスで単に「移動方角」と書いてある場合は、2つのアングル値を指していることが多い。
// これらを踏まえて「移動方角（Z軸）」という言葉の語彙は、まわりくどく一気に説明すると、
// 「原点から単位球表面に伸びる方向ベクトルを、XYZ座標では無く球表面に緯度経度の座標を引いた２つの数値で表現するとして、
//  緯度＝Z軸回転角、経度＝Y軸回転角 とみなした（∵Z軸回転 → Y軸回転の順番）場合のZ軸回転角成分のみのアングル値」
// ということになる。
// 「Rz」という表記は「移動方角（Z軸）（但しZ軸回転 → Y軸回転の順番）」を意味している。
// 「Ry」という表記は「移動方角（Y軸）」を意味している。
// 「RzRy」という表現は「Z軸回転 → Y軸回転の順番の移動方角」を表している。
//
// 緯度＝Z軸回転角、経度＝Y軸回転角（但しZ軸回転 → Y軸回転の順番） が両方とも0度を、方向ベクトル(1, 0, 0) の方向と定義する。
// Z軸回転角の正の増加は、方向ベクトル(0, 0, 1) を軸とした反時計回り。
// Y軸回転角の正の増加は、方向ベクトル(0, 1, 0) を軸とした反時計回り。とする。
//
// 移動方角にはZ軸回転角とY軸回転角による指定(_angRzMv, _angRyMv)と単位ベクトル指定(_vX, _vY, _vZ) があるとしたが、
// よく使うのは前者の方で、本クラスのメソッドも _angRzMv と _angRyMv を操作するものがほとんどである。
// しかし、最終的には ワールド変換行列の行列を作成するため、「単位ベクトル(_vX, _vY, _vZ)*移動速度 」  という計算をする必要がある。
// 結局最後は単位ベクトル求めているのだが、移動中の座標計算などは、さんざん_angRzMv と _angRyMvで行って、最後に１回単位ベクトルを
// 求める、というのが理想。未だ最適化の余地だいぶ残っている（が、またいつか）。
//
// 本クラスライブラリでは、この(_angRzMv, _angRyMv)を操作して、内部で方向ベクトル(_vX, _vY, _vZ) を自動計算している。
// (_vX, _vY, _vZ)のみをメソッドを使わず直接操作すると、(_angRzMv, _angRyMv)との同期が崩れるので注意。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらないこととする。
//
// ＜移動速度:Velo or MvVelo＞
// キャラは「移動速度」(_veloMv)を保持している。移動する方法は簡単で、基本的に毎フレーム「移動方角」に「移動速度」分動くだけ。
// つまり「移動方角」(_vX, _vY, _vZ)に「移動速度」(_veloMv)を掛け算している。１フレーム後の座標は
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) である。  これに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を掛ける。
// よって、(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)が１フレーム後の座標。

// ＜軸回転方角:AngFace＞
// キャラが向いている方角（方向）、を「軸回転方角」と呼ぶことにする。「軸回転方角」は、ワールド変換行列の軸回転と対応している（倍率が違うけど）。
// ワールド変換行列の軸回転とは、X軸回転角、Y軸回転角、Z軸回転角のことで、それぞれ、
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] が保持している。
// 本ライブラリでは、キャラが原点にあるとして、単位球の表面に向かって伸びるベクトル(1, 0, 0) をキャラの「前方」と設定している。
// XファイルなどのモデルもX軸の正の方向に向いているモノとする。モデル「上方向は」は（0, 1, 0)。
// また、ワールド変換行列の回転行列のかける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 > (拡大縮小) 」 とする。
// (※  X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// そこで、X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「軸回転方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_angFace[AXIS_Z], _angFace[AXIS_Y])で表現できる。
// つまり、「前方」は Z軸回転角・Y軸回転角共に0度とし、例えば「前方を向いて後ろ方向」は[Z軸回転角,Y軸回転角]=[0度,180度] と表現する。。
// 単に「Z軸回転角」などと書くと、「移動方角」のZ軸回転角なのか、「軸回転方角」のZ軸回転角なのか曖昧になるため、
// 「軸回転方角(Z軸)」「軸回転方角(Y軸)」と書くこととする。（※「軸回転方角(X軸)」もあるが、これはスピンを表し向きへの影響は無し）
// ここで注意は、１つのキャラが向いている方角に対して、２通りのアクセスする方法があるということ。例えば、
// 「前方(1, 0, 0)を向いて真右向き」 は [軸回転方角(Z軸), 軸回転方角(Y軸)]=[0, 90度] or [180度,270度] とで表現できる。
// （※軸回転方角(Y軸)は左手系座標のためY軸の正方向を向いて反時計回り）
// 実は 「前方」 も [180度,180度]とも表現できるし、「真後ろ」 は [0度,180度] とも表現できる。
// どちらも向いている方向は同じ、但し姿勢(キャラの上方向)は異なる。姿勢が異なるとまずいキャラは注意すること。
// 当然、「移動方角」でも、２通りのアクセスする方法があるのだが、こちらは見た目は差が無い。差が無いが角度計算するときに影響がでるやもしれない。

// ＜移動方角と軸回転方角で同期＞
// ここで 「移動方角（Z軸）」を「軸回転方角(Z軸)」へ、「移動方角（Y軸）」を「軸回転方角(Y軸)」 へコピーしてやると、
// なんと移動方角と、キャラクタの向きの同期が簡単に取れるじゃまいか。
// 逆にキャラが向いている方向に移動を追従させることも可能かな。

// ＜自動前方向き機能＞
// 自動前方向き機能とは「移動方角」を設定すると、それに伴って自動的に「軸回転方角」を設定する事を意味している。
// 具体的には、以下のようにフレーム毎に、アングル値を上書きコピー（完全同期）。或いは差分を加算（向き方向を滑らかに描画）していく。
//  ・移動方角（Z軸） → 軸回転方角(Z軸)
//  ・移動方角（Y軸） → 軸回転方角(Y軸)
// しかし「軸回転方角」を設定ても「移動方角」変化しない（逆は関連しない）ので注意。

// ＜角速度:AngVelo＞
// 「移動方角（Z軸）」「移動方角（Y軸）」、「軸回転方角(Z軸)」「軸回転方角(Y軸)」には、それぞれの「角速度」を設けてある。
// 例えば90度右に向きたい場合、キャラがいきなりカクっと向きを変えては悲しいので、毎フレーム角速度だけ角を加算するようにして、
// 滑らかに向きを変えるようにする。
// 「角速度」は正負の注意が必要。正の場合は反時計回り、負の場合は時計回りになる。
// 方向転換する場合、ターゲットとなる角度への到達する方法の考え方は、5通りある。（アクセス方法は２通りしかない）
// 「常に反時計回で行く」「常に時計回りで行く」「近い角の周り方向で行く」「遠回りな角の周り方向で行く」「現在回っている方向で行く」
// である。それぞれ用途があるので、オプション引数などで、選択できるようにしたいな。

// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_X,_Y,_Z)にそれぞれの移動増分が
// 加算される。

//＜その他＞
//移動速度、移動方角角速度、軸回転角角速度には、それぞれ加速度も設定できる。
//スプラインの基点、補間点を自動で通過するような動きも最近可能。（いつの事だ）
//軸回転は、本当は Z > X > Y の軸回転順番にするのが一般的のようだ。現在の X > Z > Y は、
//もともと2D横スクロールシューティングを作ろうと思っており、当初 X > Z だけで処理を行っていたのが原因。もうもどれない。
//3Dにするとは思ってもみなかったぁー！

//2010/02/19追記
// ※たまに「RyRz」という表現が存在する（「RzRy」と異なる）が、これは「Y軸回転 → Z軸回転の順番の移動方角」を表しているので注意。
// 　また、「移動方角（Z軸）」を軸回転の順番の違いを明確にするため
// 　「RzRyのRz」「RyRzのRz」と書いたりしているところもある。（単に「Rz」だけの場合は「RzRyのRz」を意味している）

//TODO:
//躍度（加加速度）の追加
//任意軸回転（クォータニオン）
//

GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;


    for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す

        //軸回転方角
        _angFace[i] = 0; //0 angle は ３時の方角を向いている
        //軸回転方角の角速度（軸回転方角の増分）= 0 angle/fream
        _angveloFace[i] = 0; //1フレームに加算される軸回転方角の角増分。デフォルトは軸回転方角の角増分無し、つまり振り向き無し。
        //軸回転方角の角速度上限 ＝ 360,000 angle/fream
        _angveloTopFace[i] = ANGLE360; //_angveloFace[n] の増分の上限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角速度下限 ＝ -360,000 angle/fream
        _angveloBottomFace[i] = ANGLE360 * -1; //_angveloFace[n] の増分の下限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _angacceFace[i] = 0; //_angveloFace[n] の増分。デフォルトは軸回転方角の角加速度無し

        _angjerkFace[i] = 0;
        //目標軸回転方角への自動制御フラグ = 無効
        _face_ang_targeting_flg[i] = false;
        //目標の軸回転方角
        _angTargetFace[i] = 0; //目標軸回転方角への自動制御フラグ = 無効、の場合は無意味
        //目標の軸回転方角自動停止機能が有効になる回転方向
        _face_ang_target_allow_way[i] = TURN_BOTH;
        //目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通）
        _face_ang_target_allow_velo[i] = ANGLE180;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //移動方角のZ軸回転
    _angRzMv = 0;
    //移動方角のY軸回転
    _angRyMv = 0;
    //移動速度
    _veloMv = 0;
    //移動速度上限 = 256 px/fream
    _veloTopMv = 256 * LEN_UNIT; //_veloMv が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。
    //移動速度下限 = 0   px/fream
    _veloBottomMv = -256 * LEN_UNIT; //_veloMv が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _accMv = 0; //_veloMv の増分。デフォルトは加速無し

    _jerkMv = 0;
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _angveloRzMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRzTopMv = ANGLE360; //_angveloRzMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRzBottomMv = ANGLE360 * -1; //_angveloRzMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _angacceRzMv = 0; //_angveloRzMv の増分。デフォルトは移動方角の角加速度無し

    _angjerkRzMv = 0;
    //目標移動方角（Z軸回転）への自動制御フラグ = 無効
    _mv_ang_rz_target_flg = false;
    //目標の移動方角（Z軸回転）
    _angTargetRzMv = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _mv_ang_rz_target_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_rz_target_allow_velo = ANGLE180;
    //移動方角（Z軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _relate_RzFaceAng_to_RzMvAng_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _angveloRyMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRyTopMv = ANGLE360; //_angveloRyMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRyBottomMv = ANGLE360 * -1; //_angveloRyMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _angacceRyMv = 0; //_angveloRyMv の増分。デフォルトは移動方角の角加速度無し

    _angjerkRyMv = 0;
    //目標移動方角（Y軸回転）への自動制御フラグ = 無効
    _mv_ang_ry_target_flg = false;
    //目標の移動方角（Y軸回転）
    _angTargetRyMv = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _mv_ang_ry_target_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_ry_target_allow_velo = ANGLE180;
    //移動方角（Y軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _relate_RyFaceAng_to_RyMvAng_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMv = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMv = 256 * LEN_UNIT;
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMv = -256 * LEN_UNIT;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMv = 0;
    _acceTopVxMv = 256 * LEN_UNIT;
    _acceBottomVxMv = -256 * LEN_UNIT;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMv = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMv = 256 * LEN_UNIT;
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMv = -256 * LEN_UNIT;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMv = 0;

    _acceTopVyMv = 256 * LEN_UNIT;
    _acceBottomVyMv = -256 * LEN_UNIT;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMv = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMv = 256 * LEN_UNIT;
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMv = -256 * LEN_UNIT;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMv = 0;
    _acceTopVzMv = 256 * LEN_UNIT;
    _acceBottomVzMv = -256 * LEN_UNIT;
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
        if (_face_ang_targeting_flg[i]) { //ターゲット方向がある場合
            _angveloFace[i] += _angacceFace[i];
            setFaceAngVelo(i, _angveloFace[i]);

            if (_angveloFace[i] > 0) { //反時計回りの場合
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _angveloFace[i]) {

                    //_TRACE_("STOP1 _angveloFace["<<i<<"]="<<_angveloFace[i]<<" angDistance="<<angDistance<<" _face_ang_target_allow_velo["<<i<<"]="<<_face_ang_target_allow_velo[i]<<" _angveloFace["<<i<<"]="<<_angveloFace[i]);
                    addFaceAng(i, angDistance);
                    _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addFaceAng(i, _angveloFace[i]);
                }
            } else if (_angveloFace[i] < 0) { //時計回りの場合
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_angveloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _angveloFace[i]) { //目標を行き過ぎてしまいそう・・・な日
                    addFaceAng(i, angDistance);
                    _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addFaceAng(i, _angveloFace[i]);
                }
            } else {
                //_angveloFace[i] == 0
                addFaceAng(i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //目標方向に到達した時の処理
                //_angveloTopFace[i] = ANGLE360; //軸回転方角の角速度上限 ＝ 360,000 angle/fream
                //_angveloBottomFace[i] = ANGLE360 * -1; //軸回転方角の角速度下限 ＝ -360,000 angle/fream

                //目標方向に到達した時、停止処理を行なう
                _angacceFace[i] = 0; //軸回転方向角、角速度を０へ
                setFaceAngVelo(i, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //if (_angacceFace[i] != 0) {
            //フレーム毎の軸回転方角旋廻の処理
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] != 0) {
                addFaceAng(i, _angveloFace[i]);
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
    _veloVxMv += _acceVxMv;
    setVxMvVelo(_veloVxMv);
    //Y軸方向移動加速度の処理
    _veloVyMv += _acceVyMv;
    setVyMvVelo(_veloVyMv);
    //Z軸方向移動加速度の処理
    _veloVzMv += _acceVzMv;
    setVzMvVelo(_veloVzMv);


    _accMv += _jerkMv;
    //移動加速度の処理
    _veloMv += _accMv;
    setMvVelo(_veloMv);
    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_rz_target_flg) {

        _angveloRzMv += _angacceRzMv;
        setRzMvAngVelo(_angveloRzMv);

        if (_angveloRzMv > 0) { //反時計回りの場合
            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMv > angDistance && _mv_ang_rz_target_allow_way != TURN_CLOCKWISE
                    && _mv_ang_rz_target_allow_velo >= _angveloRzMv) { //目標を行き過ぎてしまいそう・・・な日
                addRzMvAng(angDistance);
                _mv_ang_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else if (_angveloRzMv < 0) { //時計回りの場合

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_angveloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _angveloRzMv) {
                addRzMvAng(angDistance);
                _mv_ang_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_angveloRzTopMv = ANGLE360; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRzBottomMv = ANGLE360 * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRzMv = 0; //Z軸移動方向角、角加速度を０へ
            setRzMvAngVelo(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacceRzMv != 0) {

        _angacceRzMv += _angjerkRzMv;
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _angveloRzMv += _angacceRzMv;
        if (_angveloRzMv != 0) {
            addRzMvAng(_angveloRzMv);
        }
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_ry_target_flg) {

        _angveloRyMv += _angacceRyMv;
        setRyMvAngVelo(_angveloRyMv);

        if (_angveloRyMv > 0) { //現在は反時計回りの場合
            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMv > angDistance &&
                _mv_ang_ry_target_allow_way != TURN_CLOCKWISE &&
                _mv_ang_ry_target_allow_velo >= _angveloRyMv)
            { //目標を行き過ぎてしまいそう・・・な日
                addRyMvAng(angDistance);
                _mv_ang_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else if (_angveloRyMv < 0) { //現在は時計回りの場合

            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_CLOCKWISE);
            if (_angveloRyMv < angDistance &&
                _mv_ang_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_mv_ang_ry_target_allow_velo <= _angveloRyMv)
            {
                addRyMvAng(angDistance);
                _mv_ang_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else {
            //_angveloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_angveloRyTopMv = ANGLE360; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRyBottomMv = ANGLE360*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRyMv = 0; //Y軸移動方向角、角加速度を０へ
            setRyMvAngVelo(0); //Y軸移動方向角、角速度を０へ
        }
    } else {
        //if (_angacceRyMv != 0) {
        _angacceRyMv += _angjerkRyMv;
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _angveloRyMv += _angacceRyMv;
        if(_angveloRyMv != 0) {
            addRyMvAng(_angveloRyMv);
        }
        //}
    }
    ///////////////

    //Actorに反映
    _pActor->_X += (int)(_vX * _veloMv + _veloVxMv);
    _pActor->_Y += (int)(_vY * _veloMv + _veloVyMv);
    _pActor->_Z += (int)(_vZ * _veloMv + _veloVzMv);

}


angle GgafDx9GeometryMover::simplifyAng(angle prm_ang) {
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

void GgafDx9GeometryMover::setFaceAng(int prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = simplifyAng(prm_angFace);
}

void GgafDx9GeometryMover::setFaceAng(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9GeometryMover::addFaceAng(int prm_axis, angle prm_angDistance) {
    static angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDx9GeometryMover::setFaceAngVelo(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometryMover::forceFaceAngVeloRange(int prm_axis,
                                               angvelo prm_angveloRot01,
                                               angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloTopFace[prm_axis] = prm_angveloRot02;
        _angveloBottomFace[prm_axis] = prm_angveloRot01;
    } else {
        _angveloTopFace[prm_axis] = prm_angveloRot01;
        _angveloBottomFace[prm_axis] = prm_angveloRot02;
    }
    setFaceAngVelo(prm_axis, _angveloFace[prm_axis]); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setFaceAngAcce(int prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometryMover::setStopTarget_FaceAngV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_FaceAng(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMv
    );
}

void GgafDx9GeometryMover::setStopTarget_FaceAng(int prm_axis,
                                                 angle prm_angTargetRot,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometryMover::getFaceAngDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getFaceAngDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometryMover::getFaceAngDistance(int prm_axis, angle prm_angTargetRot, int prm_way) {
    static angle _angTargetRot;
    _angTargetRot = simplifyAng(prm_angTargetRot);
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
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
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
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
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
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
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
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(3)。");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngDistance() 何故かしら角の距離が求めれません。(2)");
}


void GgafDx9GeometryMover::forceMvVeloRange(int prm_veloMv01, int prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setMvVelo(int prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDx9GeometryMover::addMvVelo(int prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDx9GeometryMover::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

void GgafDx9GeometryMover::setRzMvAng(int prm_tX, int prm_tY) {
    setRzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDx9GeometryMover::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDx9GeometryMover::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDx9GeometryMover::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDx9GeometryMover::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
                                                       angvelo prm_angveloRzMv02) {
    if (prm_angveloRzMv01 < prm_angveloRzMv02) {
        _angveloRzTopMv = prm_angveloRzMv02;
        _angveloRzBottomMv = prm_angveloRzMv01;
    } else {
        _angveloRzTopMv = prm_angveloRzMv01;
        _angveloRzBottomMv = prm_angveloRzMv02;
    }
    setRzMvAngVelo(_angveloRzMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setStopTarget_RzMvAng(angle prm_angTargetRzMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _angTargetRzMv = simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9GeometryMover::setStopTarget_RzMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRzMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRzMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = simplifyAng(prm_angTargetRzMv);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRzMv && _angRzMv < ANGLE180) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv) {
                //重なってる場合
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + ANGLE180) {
                return angTargetRzMv - _angRzMv;
            } else if (angTargetRzMv == _angRzMv + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMv + ANGLE180 < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return -1 * (_angRzMv + (ANGLE360 - angTargetRzMv));
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRzMv && _angRzMv <= ANGLE360) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - ANGLE180) {
                return ANGLE360 - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRzMv - ANGLE180 < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //重なってる場合
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv - _angRzMv;
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRzMv && _angRzMv < ANGLE180) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return ANGLE360 - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv) {
                //重なってる場合
                return ANGLE360;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + ANGLE180) {
                return -1*(_angRzMv + (ANGLE360-angTargetRzMv));
            } else if (angTargetRzMv == _angRzMv + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMv + ANGLE180 < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv - _angRzMv;
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRzMv && _angRzMv <= ANGLE360) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - ANGLE180) {
                return  -1*(_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRzMv - ANGLE180 < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return _angRzMv + (ANGLE360 - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //重なってる場合
                return -ANGLE360;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv + (ANGLE360 - _angRzMv);
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return (angTargetRzMv - _angRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv < ANGLE360) {
            return ANGLE360 - _angRzMv + angTargetRzMv;
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return -1 * (_angRzMv + ANGLE360 - angTargetRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv < ANGLE360) {
            return -1 * (_angRzMv - angTargetRzMv);
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDx9GeometryMover::getRzMvAngDistance() 何故かしら角の距離が求めれません。(1)");

}


void GgafDx9GeometryMover::setRyMvAng(int prm_tX, int prm_tY) {
    setRyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometryMover::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDx9GeometryMover::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDx9GeometryMover::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDx9GeometryMover::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
                                               angvelo prm_angveloRyMv02) {
    if (prm_angveloRyMv01 < prm_angveloRyMv02) {
        _angveloRyTopMv = prm_angveloRyMv02;
        _angveloRyBottomMv = prm_angveloRyMv01;
    } else {
        _angveloRyTopMv = prm_angveloRyMv01;
        _angveloRyBottomMv = prm_angveloRyMv02;
    }
    setRyMvAngVelo(_angveloRyMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setStopTarget_RyMvAng(angle prm_angTargetRyMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _angTargetRyMv = simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9GeometryMover::setStopTarget_RyMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRyMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRyMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    static angle angTargetRyMv;
    angTargetRyMv = simplifyAng(prm_angTargetRyMv);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRyMv && _angRyMv < ANGLE180) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv) {
                //重なってる場合
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + ANGLE180) {
                return angTargetRyMv - _angRyMv;
            } else if (angTargetRyMv == _angRyMv + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMv + ANGLE180 < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return -1 * (_angRyMv + (ANGLE360 - angTargetRyMv));
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRyMv && _angRyMv <= ANGLE360) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - ANGLE180) {
                return ANGLE360 - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -ANGLE180;
            } else if (_angRyMv - ANGLE180 < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //重なってる場合
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv - _angRyMv;
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRyMv && _angRyMv < ANGLE180) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return ANGLE360 - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv) {
                //重なってる場合
                return ANGLE360;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + ANGLE180) {
                return -1*(_angRyMv + (ANGLE360-angTargetRyMv));
            } else if (angTargetRyMv == _angRyMv + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMv + ANGLE180 < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv - _angRyMv;
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRyMv && _angRyMv <= ANGLE360) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - ANGLE180) {
                return  -1*(_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return -ANGLE180;
            } else if (_angRyMv - ANGLE180 < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return _angRyMv + (ANGLE360 - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //重なってる場合
                return -ANGLE360;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv + (ANGLE360 - _angRyMv);
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return (angTargetRyMv - _angRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv < ANGLE360) {
            return ANGLE360 - _angRyMv + angTargetRyMv;
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return -1 * (_angRyMv + ANGLE360 - angTargetRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv < ANGLE360) {
            return -1 * (_angRyMv - angTargetRyMv);
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDx9GeometryMover::getRyMvAngDistance() 何故かしら角の距離が求めれません。(1)");

}


void GgafDx9GeometryMover::getRzRyMvAngDistance(int prm_way,
                                                angle prm_target_angRz, angle prm_target_angRy,
                                                angle& out_d_angRz, angle& out_d_angRy,
                                                angle& out_target_angRz, angle& out_target_angRy) {

//_TRACE_("getRzRyMvAngDistance ---->");
//_TRACE_("this: angMvRz="<<_angRzMv<<" _angRyMv="<<_angRyMv);
//_TRACE_("prm_target_angRz="<<prm_target_angRz<<" prm_target_angRy="<<prm_target_angRy);
    angle target_angRz = prm_target_angRz;
    angle target_angRy = prm_target_angRy;
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        //目標に到達するためには、回り方が常に２パターンある。
        //それぞれ球面上の２点の距離を簡易近似値（速度優先のため）で比較し、近いと思われるほうを採用する。

        //_TRACE_("1 target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO); //Rzの差
        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO);
        //_TRACE_("1 d1_angRz="<<d1_angRz<<" d1_angRy="<<d1_angRy);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        //_TRACE_("1  d1="<<((float)d1));

        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
        //_TRACE_("2 anotherRzRy target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO);
        //_TRACE_("2 d2_angRz="<<d2_angRz<<" d2_angRy="<<d2_angRy);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        //_TRACE_("2  d2="<<((float)d2));
        if (d1 <= d2) {
            //_TRACE_("d1 <= d2 d1が採用されました");
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            //_TRACE_("d1 > d2  d2が採用されました");
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
        //_TRACE_("<--- getRzRyMvAngDistance");
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_COUNTERCLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_CLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else {
        //おかしい
        throwGgafCriticalException("GgafDx9GeometryMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。");
    }
}


//
//void GgafDx9GeometryMover::getRzRyMvAngDistance(int prm_way,
//                                                angle prm_target_angRz, angle prm_target_angRy,
//                                                angle& out_d_angRz, angle& out_d_angRy,
//                                                angle& out_target_angRz, angle& out_target_angRy) {
//
//_TRACE_("getRzRyMvAngDistance ---->");
//_TRACE_("this: angMvRz="<<_angRzMv<<" _angRyMv="<<_angRyMv);
//_TRACE_("prm_target_angRz="<<prm_target_angRz<<" prm_target_angRy="<<prm_target_angRy);
//    angle target_angRz = prm_target_angRz;
//    angle target_angRy = prm_target_angRy;
//    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
//        //目標に到達するためには、回り方が常に２パターンある。
//        //それぞれ球面上の２点の距離を簡易近似値（速度優先のため）で比較し、近いと思われるほうを採用する。
//
//        _TRACE_("1 target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
//        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO); //Rzの差
//        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5); //Ryの差*極地補正
//        _TRACE_("1 ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5)="<<(float)((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5));
//        _TRACE_("1 d1_angRz="<<d1_angRz<<" d1_angRy="<<d1_angRy);
//        //((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5)
//        //この値を乗ずるのは、
//        //Y軸回転角は極地（ANGLE90,ANGLE270付近）でのRzの差の距離は0に近くなることを考慮
//        double d1d1 = 1.0*d1_angRz*d1_angRz + 1.0*d1_angRy*d1_angRy; //RzRyの距離を直角三角形に見立てて斜辺で距離判定する（簡易近似）
//        _TRACE_("1  d1d1="<<((float)d1d1));
//
//        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
//        _TRACE_("2 anotherRzRy target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
//        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO);
//        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        _TRACE_("2 ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5)="<<(float)((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5));
//        _TRACE_("2 d2_angRz="<<d2_angRz<<" d2_angRy="<<d2_angRy);
//        double d2d2 = 1.0*d2_angRz*d2_angRz + 1.0*d2_angRy*d2_angRy;
//        _TRACE_("2  d2d2="<<((float)d2d2));
//        if (d1d1 <= d2d2) {
//            _TRACE_("d1d1 <= d2d2 d1が採用されました");
//            out_d_angRz = d1_angRz;
//            out_d_angRy = d1_angRy;
//            out_target_angRz = prm_target_angRz;
//            out_target_angRy = prm_target_angRy;
//        } else {
//            _TRACE_("d1d1 > d2d2  d2が採用されました");
//            out_d_angRz = d2_angRz;
//            out_d_angRy = d2_angRy;
//            out_target_angRz = target_angRz;
//            out_target_angRy = target_angRy;
//        }
//        _TRACE_("<--- getRzRyMvAngDistance");
//    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
//        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
//        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        double d1d1 = 1.0*d1_angRz*d1_angRz + 1.0*d1_angRy*d1_angRy;
//        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
//        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
//        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        double d2d2 = 1.0*d2_angRz*d2_angRz + 1.0*d2_angRy*d2_angRy;
//        if (d1d1 >= d2d2) {
//            out_d_angRz = d1_angRz;
//            out_d_angRy = d1_angRy;
//            out_target_angRz = prm_target_angRz;
//            out_target_angRy = prm_target_angRy;
//        } else {
//            out_d_angRz = d2_angRz;
//            out_d_angRy = d2_angRy;
//            out_target_angRz = target_angRz;
//            out_target_angRy = target_angRy;
//        }
//    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
//        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_COUNTERCLOCKWISE);
//        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_COUNTERCLOCKWISE);
//        out_target_angRz = target_angRz;
//        out_target_angRy = target_angRy;
//    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
//        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_CLOCKWISE);
//        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_CLOCKWISE);
//        out_target_angRz = target_angRz;
//        out_target_angRy = target_angRy;
//    } else {
//        //おかしい
//        throwGgafCriticalException("GgafDx9GeometryMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。");
//    }
//}


void GgafDx9GeometryMover::getRzRyFaceAngDistance(int prm_way,
                                                  angle prm_target_angRz, angle prm_target_angRy,
                                                  angle& out_d_angRz, angle& out_d_angRy,
                                                  angle& out_target_angRz, angle& out_target_angRy) {

    angle target_angRz = prm_target_angRz;
    angle target_angRy = prm_target_angRy;
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_COUNTERCLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else {
        //おかしい
        throwGgafCriticalException("GgafDx9GeometryMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。");
    }
}

//void GgafDx9GeometryMover::getRzRyFaceAngDistance(int prm_way,
//                                                  angle prm_target_angRz, angle prm_target_angRy,
//                                                  angle& out_d_angRz, angle& out_d_angRy,
//                                                  angle& out_target_angRz, angle& out_target_angRy) {
//
//    angle target_angRz = prm_target_angRz;
//    angle target_angRy = prm_target_angRy;
//    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
//        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
//        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        //GgafDx9Util::SIN[target_angRz/ANGLE_RATE]を乗ずるのは、Y軸回転角は極地になるほどの距離が短くなるため
//        double d1d1 = 1.0*d1_angRz*d1_angRz + 1.0*d1_angRy*d1_angRy;
//        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
//        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
//        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        double d2d2 = 1.0*d2_angRz*d2_angRz + 1.0*d2_angRy*d2_angRy;
//        if (d1d1 <= d2d2) {
//            out_d_angRz = d1_angRz;
//            out_d_angRy = d1_angRy;
//            out_target_angRz = prm_target_angRz;
//            out_target_angRy = prm_target_angRy;
//        } else {
//            out_d_angRz = d2_angRz;
//            out_d_angRy = d2_angRy;
//            out_target_angRz = target_angRz;
//            out_target_angRy = target_angRy;
//        }
//
//    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
//        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
//        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        double d1d1 = 1.0*d1_angRz*d1_angRz + 1.0*d1_angRy*d1_angRy;
//        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
//        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
//        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO) * ((GgafDx9Util::COS[simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
//        double d2d2 = 1.0*d2_angRz*d2_angRz + 1.0*d2_angRy*d2_angRy;
//        if (d1d1 >= d2d2) {
//            out_d_angRz = d1_angRz;
//            out_d_angRy = d1_angRy;
//            out_target_angRz = prm_target_angRz;
//            out_target_angRy = prm_target_angRy;
//        } else {
//            out_d_angRz = d2_angRz;
//            out_d_angRy = d2_angRy;
//            out_target_angRz = target_angRz;
//            out_target_angRy = target_angRy;
//        }
//    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
//        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_COUNTERCLOCKWISE);
//        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_COUNTERCLOCKWISE);
//        out_target_angRz = target_angRz;
//        out_target_angRy = target_angRy;
//    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
//        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOCKWISE);
//        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOCKWISE);
//        out_target_angRz = target_angRz;
//        out_target_angRy = target_angRy;
//    } else {
//        //おかしい
//        throwGgafCriticalException("GgafDx9GeometryMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。");
//    }
//}


void GgafDx9GeometryMover::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = simplifyAng(prm_angRz);
        _angRyMv = simplifyAng(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }

}

void GgafDx9GeometryMover::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    GgafDx9Util::getNormalizeVectorZY(RyRz_Ry, ANGLE360-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    GgafDx9Util::getRzRyAng(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}


void GgafDx9GeometryMover::setMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setMvAng(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMv,
                   _angRyMv
                 );
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometryMover::setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setStopTarget_RzRyMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setStopTarget_RzRyMvAng(int prm_tX, int prm_tY, int prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _dummy1,
                   _dummy2,
                   _dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setStopTarget_RzMvAng(angRz_Target);
    setStopTarget_RyMvAng(angRy_Target);
}

void GgafDx9GeometryMover::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDx9GeometryMover::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDx9GeometryMover::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDx9GeometryMover::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}


void GgafDx9GeometryMover::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //再設定して範囲内に補正
}


void GgafDx9GeometryMover::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDx9GeometryMover::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDx9GeometryMover::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDx9GeometryMover::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}


void GgafDx9GeometryMover::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDx9GeometryMover::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDx9GeometryMover::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDx9GeometryMover::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}


void GgafDx9GeometryMover::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //再設定して範囲内に補正
}



void GgafDx9GeometryMover::executeSplineMoveProgram(GgafDx9SplineProgram* prm_progSP, int prm_option) {
    _progSP = prm_progSP;
    _progSP->begin(_pActor, prm_option);
}

void GgafDx9GeometryMover::execTagettingFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistance(prm_way,
                               prm_angRz_Target, prm_angRy_Target,
                               out_d_angRz, out_d_angRy,
                               prm_angRz_Target, prm_angRy_Target);
    } else {
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way);
    }

    if (out_d_angRz > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    if (out_d_angRy > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }

    setStopTarget_FaceAng(AXIS_Z, prm_angRz_Target);
    setStopTarget_FaceAng(AXIS_Y, prm_angRy_Target);
}

void GgafDx9GeometryMover::execTagettingFaceAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTagettingFaceAngSequence(out_angRz_Target, out_angRy_Target,
                                 prm_angVelo, prm_angAcce,
                                 prm_way, prm_optimize_ang);
}

void GgafDx9GeometryMover::execTagettingRzFaceAngSequence(angle prm_angRz_Target,
                                                          angvelo prm_angVelo, angacce prm_angAcce,
                                                          int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_Z, prm_angRz_Target);

}

void GgafDx9GeometryMover::execTagettingRyFaceAngSequence(angle prm_angRy_Target,
                                                          angvelo prm_angVelo, angacce prm_angAcce,
                                                          int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_Y, prm_angRy_Target);
}

void GgafDx9GeometryMover::execTagettingRxSpinAngleSequence(angle prm_angRx_Target,
                                                            angvelo prm_angVelo, angacce prm_angAcce,
                                                            int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_angRx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angVelo);
        setFaceAngAcce(AXIS_X, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angVelo);
        setFaceAngAcce(AXIS_X, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_X, prm_angRx_Target);
}

void GgafDx9GeometryMover::execTagettingMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                      angvelo prm_angVelo, angacce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    angle out_target_angRz;
    angle out_target_angRy;
    if (prm_optimize_ang) {
        getRzRyMvAngDistance(prm_way,
                             prm_angRz_Target, prm_angRy_Target,
                             out_d_angRz, out_d_angRy,
                             out_target_angRz, out_target_angRy);
    } else {
        out_d_angRz = getRzMvAngDistance(prm_angRz_Target, prm_way);
        out_d_angRy = getRyMvAngDistance(prm_angRy_Target, prm_way);
        out_target_angRz = prm_angRz_Target;
        out_target_angRy = prm_angRy_Target;
    }
    if (out_d_angRz > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    if (out_d_angRy > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }

    setStopTarget_RzMvAng(out_target_angRz);
    setStopTarget_RyMvAng(out_target_angRy);

}


void GgafDx9GeometryMover::execTagettingMvAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                      angvelo prm_angVelo, angacce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTagettingMvAngSequence(out_angRz_Target, out_angRy_Target,
                               prm_angVelo, prm_angAcce,
                               prm_way, prm_optimize_ang);
}


void GgafDx9GeometryMover::execTagettingRzMvAngSequence(angle prm_angRz_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way) {
    if (getRzMvAngDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    setStopTarget_RzMvAng(prm_angRz_Target);

}

void GgafDx9GeometryMover::execTagettingRyMvAngSequence(angle prm_angRy_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way) {
    if (getRyMvAngDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }
    setStopTarget_RyMvAng(prm_angRy_Target);
}



GgafDx9GeometryMover::~GgafDx9GeometryMover() {

    //DELETE_POSSIBLE_NULL(_progSP);//Actorで始末する。いらない
}
