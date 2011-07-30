#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// 【メモ】本クラスの考え方と単語の表現
//
// ＜２種類の方向＞
// 「キャラの方向」という言葉が曖昧なため、次の２種類の単語を定義する。「移動方角（方向）」と「正面方角（方向）」。
// 「移動方角」はキャラの進行方向のみを表現する。これは「移動速度」と伴って、キャラは座標内を移動することとする。
// 「正面方角」はキャラの向き（前方方向等）のみを表現する事とする。
// キャラクタが画面の上部から下部へ移動しても、キャラクタは下を向くとは限らず自機に向いてほしい場合もある。
// または、右にキャラを向かせて、左に移動させたいこともある。それぞれ２つの方向設定が必要。
//
// ＜移動方角の２種類の表現方法＞
// キャラが進む方向、つまり移動方角の方向は、原点から単位球の表面に向かって伸びるベクトル (_vX, _vY, _vZ) で表す方法と、
// ２つの軸回転アングル値 (_angRzMv, _angRyMv) で表す方法の２種類用意した。クォータニオンは今のところ無し。
// _angRzMv は Z軸回転角、 _angRyMv は Y軸回転角 を意味している。
// これは方向ベクトルを、緯度と経度、（仰角とアジマス）の関係に見立て、対応させようとした設計。
// 注意することは、Y軸回転角＝経度 は常に成り立つが、Z軸回転角＝緯度 は、Z軸回転角 → Y軸回転角の順番である場合に限り成り立つ。
// 本クラスでは、「Z軸回転 → Y軸回転の順番でのZ軸回転角・Y軸回転角」を簡略して、単に「Z軸回転角・Y軸回転角」と表現する事とする。
// 成分を個別に表現したい場合は、それぞれ「移動方角（Z軸）」「移動方角（Y軸）」と書くことにする。
//
// ソースコード中の、変数やメソッドの
// 「Rz」という表記は「移動方角（Z軸）」を意味している。
// 「Ry」という表記は「移動方角（Y軸）」を意味している。
// 「RzRy」という表現は「Z軸回転 → Y軸回転の順番の移動方角」を表している。
//
// Z軸回転角、Y軸回転角が両方とも0度を、方向ベクトル(1, 0, 0) の方向と定義する。
// Z軸回転角の正の増加は、Z軸の正の方向を向いて反時計回り。
// Y軸回転角の正の増加は、Y軸の正の方向を向いて反時計回り。とする。
//
// ところで数学的に「方角」は、方向ベクトル（XYZの値）で表現することが多いと思う。
// しかしこの本クラスでは、よく使うのは２軸表現の方で、メソッドも _angRzMv と _angRyMv を操作するものが中心となっている。
// 実は結局内部で単位方向ベクトルを求めているのだが、座標回転計算を、整数型の _angRzMv と _angRyMv でさんざん行ってから、
// 最後に１回単位ベクトルを求める。という方が速いのではと考えたため、このような設計になった。
// TODO:最適化の余地だいぶ残っているハズ。またいつか。
// (_angRzMv, _angRyMv)をメソッドにより操作して、各フレームの最後の内部処理で方向ベクトル(_vX, _vY, _vZ) を同期させている。
// (_vX, _vY, _vZ)メンバーをメソッドを使わず直接操作すると、(_angRzMv, _angRyMv)との同期が崩れるので注意。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらない。
//
// ＜移動速度:Velo or MvVelo＞
// キャラは「移動速度」(_veloMv)を保持している。移動する方法は簡単で、基本的に毎フレーム「移動方角」に「移動速度」分動くだけ。
// つまり「移動方角」(_vX, _vY, _vZ)に「移動速度」(_veloMv)を掛け算している。１フレーム後の座標は
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) である。  これに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を掛ける。
// よって、(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)が１フレーム後の座標。

// ＜正面方角:AngFace＞
// キャラのローカル座標で向いている方角（方向）を「正面方角」と呼ぶことにする。
//「正面方角」は、ワールド変換行列の軸回転と同じ回転方法である。
// ワールド変換行列の軸回転とは、X軸回転角、Y軸回転角、Z軸回転角のことで、それぞれ、
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] と一致する。
// 本ライブラリでは、方向ベクトル(1, 0, 0) をキャラの「前方」と設定している。
// Xファイルなどのメッシュモデルも、X軸の正の方向に向いているモノとする。また、モデル「上方向は」は（0, 1, 0)とする。
// ワールド変換行列の回転行列の掛ける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 > (拡大縮小) 」 とする。
// (※  X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「正面方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_angFace[AXIS_Z], _angFace[AXIS_Y])で表現できる。
// つまり、「前方」は Z軸回転角・Y軸回転角共に0度とし、例えば「後ろ」は[Z軸回転角,Y軸回転角]=[0度,180度] と表現する。。
// 単に「Z軸回転角」などと書くと、「移動方角」のZ軸回転角なのか、「正面方角」のZ軸回転角なのか曖昧になるため、
// 「正面方角(Z軸)」「正面方角(Y軸)」と書くこととする。（※「正面方角(X軸)」もあるが、これはスピンを表し向きへの影響は無し）
// ここで注意は、１つのキャラが向いている方角に対して、常に２通りのアクセスする方法があるということ。例えば、
// 「前方(1, 0, 0)を向いて真右向き」 は [正面方角(Z軸), 正面方角(Y軸)]=[0, 90度] or [180度,270度] とで表現できる。
// （※正面方角(Y軸)は左手系座標のためY軸の正方向を向いて反時計回り）
// 実は 「前方」 も [180度,180度]とも表現できるし、「真後ろ」 は [0度,180度] とも [180度,0度] とも表現できる。
// どちらも向いている方向は同じだが、姿勢(キャラの上方向)が異なる。姿勢が異なるとまずいキャラは注意すること。
// 当然、「移動方角」でも、２通りのアクセスする方法があるのだが、こちらは見た目は差が無い。差が無いが角度計算するときに影響がでるやもしれない。


// ＜自動前方向き機能＞
// さてここで 「移動方角（Z軸）」「移動方角（Y軸）」を、それぞれ「正面方角(Z軸)」「正面方角(Y軸)」 へコピーしてやると、
// なんと移動方角と、キャラクタの向きの同期が簡単に取れるじゃないか！
// 「自動前方向き機能」とは、「移動方角」を設定すると、それに伴って自動的に「正面方角」を設定する事とする。
// 具体的には、以下のようにフレーム毎に、アングル値を上書きコピー（同期）。或いは差分を加算（向き方向を滑らかに描画）していく。
//  ・移動方角（Z軸） → 正面方角(Z軸)
//  ・移動方角（Y軸） → 正面方角(Y軸)
// しかし「正面方角」を設定ても「移動方角」変化しない（逆は関連しない）ので注意。

// ＜角速度:AngVelo＞
// 「移動方角（Z軸）」「移動方角（Y軸）」、「正面方角(Z軸)」「正面方角(Y軸)」には、それぞれの「角速度」を設けてある。
// 例えば90度右に向きたい場合、キャラがいきなりカクっと向きを変えては悲しいので、毎フレーム角速度だけ角を加算するようにして、
// 滑らかに向きを変えるようにする。
// 「角速度」は正負の注意が必要。正の場合は反時計回り、負の場合は時計回りになる。
// 方向転換する場合、ターゲットとなる角度への到達するアクセス方法は２通りだが、考え方は常に5通りある。
// 「常に反時計回で行く」「常に時計回りで行く」「近い角の周り方向で行く」「遠回りな角の周り方向で行く」「現在回っている方向で行く」
// である。それぞれ用途があるので、オプション引数などで、選択できるようにしたいな。→できた。

// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_X,_Y,_Z)にそれぞれの移動増分が
// 加算される。

//＜その他追記＞
//・移動速度、移動方角角速度、軸回転角角速度には、それぞれ加速度も設定できる。
//・スプラインの基点、補間点を自動で通過するような動きも最近可能になった。（最近っていつ；）
//・軸回転は、本当は Z > X > Y の軸回転順番にするのが一般的のようだ。つまり前方の概念はZ軸で奥であるわけだ、なるほどわかりやすい。
//  現在の X > Z > Y は、奥はZ軸だが前方はX軸である。
//  もともと2Dの横スクロールシューティングを作ろうと思っており、当初 X > Z だけで設計を行っていたのが原因であるが、もうもどれない。
//  まさか、3Dシューティングにするとは自分でも思ってもみなかった・・・

//2010/02/19追記
// ※たまに「RyRz」という表現が存在する（「RzRy」と異なる）が、これは「Y軸回転 → Z軸回転の順番の移動方角」を表しているので注意。
// 　また、「移動方角（Z軸）」を軸回転の順番の違いを明確にするため
// 　「RzRyのRz」「RyRzのRz」と書いたりしているところもある。（単に「Rz」だけの場合は「RzRyのRz」を意味している）

//追記
//・滑らか移動が可能に！

//TODO:
//躍度（加加速度）の追加
//任意軸回転（クォータニオン）
//クラスの肥大化
//【メモ】を纏める



GgafDx9KurokoA::GgafDx9KurokoA(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;
    for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す

        //正面方角
        _angFace[i] = 0; //0 angle は ３時の方角を向いている
        //正面方角の角速度（正面方角の増分）= 0 angle/fream
        _ang_veloFace[i] = 0; //1フレームに加算される正面方角の角増分。デフォルトは正面方角の角増分無し、つまり振り向き無し。
        //正面方角の角速度上限 ＝ 360,000 angle/fream
        _ang_veloTopFace[i] = ANGLE360; //_ang_veloFace[n] の増分の上限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角速度下限 ＝ -360,000 angle/fream
        _ang_veloBottomFace[i] = ANGLE360 * -1; //_ang_veloFace[n] の増分の下限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _ang_acceFace[i] = 0; //_ang_veloFace[n] の増分。デフォルトは正面方角の角加速度無し

        _ang_jerkFace[i] = 0;
        //目標正面方角への自動向きフラグ = 無効
        _face_ang_targeting_flg[i] = false;
        //目標正面方角への自動停止フラグ = 無効
        _face_ang_targeting_stop_flg[i] = false;
        //目標の正面方角
        _angTargetFace[i] = 0; //目標正面方角への自動制御フラグ = 無効、の場合は無意味
        //目標の正面方角自動停止機能が有効になる回転方向
        _face_ang_target_allow_way[i] = TURN_BOTH;
        //目標の正面方角自動停止機能が有効になる角速度（回転正負共通）
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
    _veloTopMv = INT_MAX; //_veloMv が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。
    //移動速度下限 = 0   px/fream
    _veloBottomMv = INT_MIN; //_veloMv が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _accMv = 0; //_veloMv の増分。デフォルトは加速無し

    //_jerkMv = 0;
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _ang_veloRzMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _ang_veloRzTopMv = ANGLE360; //_ang_veloRzMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _ang_veloRzBottomMv = ANGLE360 * -1; //_ang_veloRzMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _ang_acceRzMv = 0; //_ang_veloRzMv の増分。デフォルトは移動方角の角加速度無し

    _ang_jerkRzMv = 0;
    //目標移動方角（Z軸回転）への自動向きフラグ = 無効
    _mv_ang_rz_target_flg = false;
    //目標移動方角（Z軸回転）への自動停止フラグ = 無効
    _mv_ang_rz_target_stop_flg = false;

    //目標の移動方角（Z軸回転）
    _angTargetRzMv = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _mv_ang_rz_target_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_rz_target_allow_velo = ANGLE180;
    //移動方角（Z軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RzFaceAng_with_RzMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _ang_veloRyMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _ang_veloRyTopMv = ANGLE360; //_ang_veloRyMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _ang_veloRyBottomMv = ANGLE360 * -1; //_ang_veloRyMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _ang_acceRyMv = 0; //_ang_veloRyMv の増分。デフォルトは移動方角の角加速度無し

    _ang_jerkRyMv = 0;
    //目標移動方角（Y軸回転）への自動向きフラグ = 無効
    _mv_ang_ry_target_flg = false;
    //目標移動方角（Y軸回転）への自動停止フラグ = 無効
    _mv_ang_ry_target_stop_flg = false;
    //目標の移動方角（Y軸回転）
    _angTargetRyMv = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _mv_ang_ry_target_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_ry_target_allow_velo = ANGLE180;
    //移動方角（Y軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RyFaceAng_with_RyMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    _smooth_mv_velo_seq_flg = false;
    _smooth_mv_velo_seq_endacc_flg = true;
    _smooth_mv_velo_seq_top_velo = 0;
    _smooth_mv_velo_seq_end_velo = 0;
    _smooth_mv_velo_seq_target_distance = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = 0;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = 0;
    _smooth_mv_velo_seq_p2 = 0;
    _smooth_mv_velo_seq_progress = -1;


    _taget_mv_ang_alltime_flg = false;
    _taget_mv_ang_alltime_pActor = NULL;
    _taget_mv_ang_alltime_tX = 0;
    _taget_mv_ang_alltime_tY = 0;
    _taget_mv_ang_alltime_tZ = 0;
    _taget_mv_ang_alltime_angVelo = 0;
    _taget_mv_ang_alltime_angAcce = 0;
    _taget_mv_ang_alltime_way = TURN_CLOSE_TO;
    _taget_mv_ang_alltime_optimize_ang = true;

}

void GgafDx9KurokoA::behave() {

    //正面方角処理
    angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_face_ang_targeting_flg[i]) { //ターゲット方向がある場合
            _ang_veloFace[i] += _ang_acceFace[i];
            setFaceAngVelo(i, _ang_veloFace[i]);

            if (_ang_veloFace[i] > 0) { //反時計回りの場合
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_ang_veloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _ang_veloFace[i]) {

                    //_TRACE_("STOP1 _ang_veloFace["<<i<<"]="<<_ang_veloFace[i]<<" angDistance="<<angDistance<<" _face_ang_target_allow_velo["<<i<<"]="<<_face_ang_target_allow_velo[i]<<" _ang_veloFace["<<i<<"]="<<_ang_veloFace[i]);
                    addFaceAng(i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) {
                        _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                        _face_ang_targeting_stop_flg[i] = false;
                    }
                } else {
                    addFaceAng(i, _ang_veloFace[i]);
                }
            } else if (_ang_veloFace[i] < 0) { //時計回りの場合
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_ang_veloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _ang_veloFace[i]) { //目標を行き過ぎてしまいそう・・・な日
                    addFaceAng(i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) { //停止して有りならば
                        _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                    }
                } else {
                    addFaceAng(i, _ang_veloFace[i]);
                }
            } else {
                //_ang_veloFace[i] == 0
                addFaceAng(i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //目標方向に到達した時の処理
                //_ang_veloTopFace[i] = ANGLE360; //正面方角の角速度上限 ＝ 360,000 angle/fream
                //_ang_veloBottomFace[i] = ANGLE360 * -1; //正面方角の角速度下限 ＝ -360,000 angle/fream

                //目標方向に到達した時、停止処理を行なう
                _ang_acceFace[i] = 0; //軸回転方向角、角速度を０へ
                setFaceAngVelo(i, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //if (_ang_acceFace[i] != 0) {
            //フレーム毎の正面方角旋廻の処理
            _ang_veloFace[i] += _ang_acceFace[i];
            if (_ang_veloFace[i] != 0) {
                addFaceAng(i, _ang_veloFace[i]);
            }
            //}
        }
    }

    //Actorに反映
    _pActor->_RX = _angFace[AXIS_X];
    _pActor->_RY = _angFace[AXIS_Y];
    _pActor->_RZ = _angFace[AXIS_Z];

    ///////////////////////////////////////////////////Mover

    //_accMv += _jerkMv;
    //移動加速度の処理
    _veloMv += _accMv;
    setMvVelo(_veloMv);

    //なめらか移動シークエンス起動時
    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_target_frames < 0) {
            //目標距離指定の場合
            if (_smooth_mv_velo_seq_progress == 0) {
                //加速設定
                setMvAcceBy_Dv(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //加速中
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_p1) {
                    //p1 に到達すれば 等速へ
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //等速中
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setMvAcceBy_Dv(_smooth_mv_velo_seq_target_distance - _smooth_mv_velo_seq_mv_distance, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //減速中
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_target_distance) {
                    //目標距離へ到達
                    setMvVelo(_smooth_mv_velo_seq_end_velo);
                    if (_smooth_mv_velo_seq_endacc_flg) {
                        setMvAcce(0);
                    }
                    _smooth_mv_velo_seq_progress++;
                    _smooth_mv_velo_seq_flg = false; //おしまい
                }
            }
        } else {
            //目標時間指定の場合
            if (_smooth_mv_velo_seq_progress == 0) {
                //加速設定
                setMvAcceBy_tv(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //加速中
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_p1) {
                    //p1 に到達すれば 等速へ
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //等速中
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setMvAcceBy_tv(_smooth_mv_velo_seq_target_frames - _smooth_mv_velo_seq_frame_of_spent, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //減速中
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_target_frames) {
                    //目標距離へ到達
                    setMvVelo(_smooth_mv_velo_seq_end_velo);
                    if (_smooth_mv_velo_seq_endacc_flg) {
                        setMvAcce(0);
                    }
                    _smooth_mv_velo_seq_progress++;
                    _smooth_mv_velo_seq_flg = false; //おしまい
                }
            }

        }


    }



    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_target_frames < 0) {
            _smooth_mv_velo_seq_mv_distance+=abs(_veloMv);
        } else {
            _smooth_mv_velo_seq_frame_of_spent++;
        }
    }

    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_rz_target_flg) {

        _ang_veloRzMv += _ang_acceRzMv;
        setRzMvAngVelo(_ang_veloRzMv);

        if (_ang_veloRzMv > 0) { //反時計回りの場合
            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_COUNTERCLOCKWISE);
            if (_ang_veloRzMv > angDistance && _mv_ang_rz_target_allow_way != TURN_CLOCKWISE
                    && _mv_ang_rz_target_allow_velo >= _ang_veloRzMv) { //目標を行き過ぎてしまいそう・・・な日
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //停止指定ありならば
                    _mv_ang_rz_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRzMvAng(_ang_veloRzMv);
            }
        } else if (_ang_veloRzMv < 0) { //時計回りの場合

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_ang_veloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _ang_veloRzMv) {
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //停止指定ありならば
                    _mv_ang_rz_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRzMvAng(_ang_veloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_ang_veloRzTopMv = ANGLE360; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_ang_veloRzBottomMv = ANGLE360 * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _ang_acceRzMv = 0; //Z軸移動方向角、角加速度を０へ
            setRzMvAngVelo(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_ang_acceRzMv != 0) {

        _ang_acceRzMv += _ang_jerkRzMv;
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _ang_veloRzMv += _ang_acceRzMv;
        if (_ang_veloRzMv != 0) {
            addRzMvAng(_ang_veloRzMv);
        }
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_ry_target_flg) {

        _ang_veloRyMv += _ang_acceRyMv;
        setRyMvAngVelo(_ang_veloRyMv);

        if (_ang_veloRyMv > 0) { //現在は反時計回りの場合
            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_COUNTERCLOCKWISE);
            if (_ang_veloRyMv > angDistance &&
                _mv_ang_ry_target_allow_way != TURN_CLOCKWISE &&
                _mv_ang_ry_target_allow_velo >= _ang_veloRyMv)
            { //目標を行き過ぎてしまいそう・・・な日
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //停止指定ありならば
                    _mv_ang_ry_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_ang_veloRyMv);
            }
        } else if (_ang_veloRyMv < 0) { //現在は時計回りの場合

            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_CLOCKWISE);
            if (_ang_veloRyMv < angDistance &&
                _mv_ang_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_mv_ang_ry_target_allow_velo <= _ang_veloRyMv)
            {
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //停止指定ありならば
                    _mv_ang_ry_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_ang_veloRyMv);
            }
        } else {
            //_ang_veloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_ang_veloRyTopMv = ANGLE360; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_ang_veloRyBottomMv = ANGLE360*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _ang_acceRyMv = 0; //Y軸移動方向角、角加速度を０へ
            setRyMvAngVelo(0); //Y軸移動方向角、角速度を０へ
        }

    } else {
        //if (_ang_acceRyMv != 0) {
        _ang_acceRyMv += _ang_jerkRyMv;
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _ang_veloRyMv += _ang_acceRyMv;
        if(_ang_veloRyMv != 0) {
            addRyMvAng(_ang_veloRyMv);
        }
        //}
    }
    ///////////////
    if (_taget_mv_ang_alltime_pActor && _mv_ang_ry_target_flg == false && _mv_ang_ry_target_flg == false) {
        if (_taget_mv_ang_alltime_pActor) {
            keepTurnMvAngAllTime(
                    _taget_mv_ang_alltime_pActor,
                    _taget_mv_ang_alltime_angVelo,
                    _taget_mv_ang_alltime_angAcce,
                    _taget_mv_ang_alltime_optimize_ang);
        } else {
            keepTurnMvAngAllTime(
                    _taget_mv_ang_alltime_pActor->_X - _pActor->_X,
                    _taget_mv_ang_alltime_pActor->_Y - _pActor->_Y,
                    _taget_mv_ang_alltime_pActor->_Z - _pActor->_Z,
                    _taget_mv_ang_alltime_angVelo,
                    _taget_mv_ang_alltime_angAcce,
                    _taget_mv_ang_alltime_optimize_ang);
        }

    }
    //Actorに反映
    _pActor->_X += (int)(_vX * _veloMv);
    _pActor->_Y += (int)(_vY * _veloMv);
    _pActor->_Z += (int)(_vZ * _veloMv);


}

void GgafDx9KurokoA::setFaceAng(axis prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angFace);
}

void GgafDx9KurokoA::setFaceAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9KurokoA::addFaceAng(axis prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_ang_veloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _ang_veloBottomFace[prm_axis];
    } else if (prm_angDistance > _ang_veloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _ang_veloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDx9KurokoA::setFaceAngVelo(axis prm_axis, ang_velo prm_ang_veloRot) {
    if (prm_ang_veloRot > _ang_veloTopFace[prm_axis]) {
        _ang_veloFace[prm_axis] = _ang_veloTopFace[prm_axis];
    } else if (prm_ang_veloRot < _ang_veloBottomFace[prm_axis]) {
        _ang_veloFace[prm_axis] = _ang_veloBottomFace[prm_axis];
    } else {
        _ang_veloFace[prm_axis] = prm_ang_veloRot;
    }
}

void GgafDx9KurokoA::forceFaceAngVeloRange(axis prm_axis,
                                               ang_velo prm_ang_veloRot01,
                                               ang_velo prm_ang_veloRot02) {
    if (prm_ang_veloRot01 < prm_ang_veloRot02) {
        _ang_veloTopFace[prm_axis] = prm_ang_veloRot02;
        _ang_veloBottomFace[prm_axis] = prm_ang_veloRot01;
    } else {
        _ang_veloTopFace[prm_axis] = prm_ang_veloRot01;
        _ang_veloBottomFace[prm_axis] = prm_ang_veloRot02;
    }
    setFaceAngVelo(prm_axis, _ang_veloFace[prm_axis]); //再設定して範囲内に補正
}

void GgafDx9KurokoA::setFaceAngAcce(axis prm_axis, ang_acce prm_ang_acceRot) {
    _ang_acceFace[prm_axis] = prm_ang_acceRot;
}

void GgafDx9KurokoA::setStopTarget_FaceAngV(axis prm_axis,
                                                  coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_FaceAng(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_ang_veloAllowRyMv
    );
}

void GgafDx9KurokoA::setStopTarget_FaceAng(axis prm_axis,
                                                 angle prm_angTargetRot,
                                                 int prm_way_allow,
                                                 ang_velo prm_ang_veloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _face_ang_targeting_stop_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_ang_veloAllow;
}

angle GgafDx9KurokoA::getFaceAngDistance(axis prm_axis, coord prm_tX, coord prm_tY, int prm_way) {
    return getFaceAngDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9KurokoA::getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way) {
    angle _angTargetRot;
    _angTargetRot = GgafDx9Util::simplifyAng(prm_angTargetRot);
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
                throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + ANGLE360 - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9KurokoA::getFaceAngDistance() 何故かしら角の距離が求めれません(2)。_pActor="<<_pActor->getName());
}

void GgafDx9KurokoA::forceMvVeloRange(int prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDx9KurokoA::forceMvVeloRange(int prm_veloMv01, int prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //再設定して範囲内に補正
}

void GgafDx9KurokoA::setMvVelo(int prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDx9KurokoA::addMvVelo(int prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDx9KurokoA::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

void GgafDx9KurokoA::setMvAcceToStop(coord prm_target_distance) {
    // a = -(Vo^2) / 2D
    _accMv  =  -(1.0*_veloMv*_veloMv) / (2.0*prm_target_distance);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((2.0*prm_target_distance) / _veloMv); //使用フレーム数
}
void GgafDx9KurokoA::setMvAcceBy_tv(int prm_target_frames, velo prm_target_velo) {
    //a = (Vt-Vo) / Te
    _accMv = (prm_target_velo - _veloMv) / (1.0f*prm_target_frames);
}
void GgafDx9KurokoA::setMvAcceBy_Dv(coord prm_target_distance, velo prm_target_velo) {
    // a = (Vt^2 - Vo^2) / 2D
    _accMv =  ((1.0f*prm_target_velo*prm_target_velo) - (1.0f*_veloMv*_veloMv)) / (2.0f*prm_target_distance);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((1.0*prm_target_velo - _veloMv) / _accMv); //使用フレーム数

    // 【補足】
    // Vo <= 0  かつ  Vt <= 0 場合、あるいは  Vo >= 0  かつ  Vt >= 0  場合は、D(目標距離)が上記式で問題ない。
    // では
    // Vo < 0   かつ  Vt > 0  場合、あるいは  Vo > 0   かつ  Vt < 0   場合は、どうなるか？
    //
    //    速度(v)
    //     ^        a:加速度
    //     |        D:移動距離（目標到達速度に達するまでに費やす距離）
    //     |       Vo:現時点の速度
    //     |       Vt:目標到達速度
    //     |       Te:目標到達速度に達した時の時間（フレーム数）
    //  Vo |
    //     |＼
    //     |  ＼  傾きはa
    //     | D1 ＼
    //     |      ＼ Tc     Te
    //   --+--------＼------+---> 時間(t)
    //   0 |          ＼ D2 |
    //     |            ＼  |
    //   Vt|..............＼|
    //     |
    //
    //    D を全体の移動距離として
    //    D = D1 - D2 , v = 0 の t を Tc とする
    //
    //    D1 = (1/2) Vo Tc
    //    D2 = (1/2) -Vt (Te - Tc)
    //    D = D1 - D2 より
    //    D = (1/2) Vo Tc -  { (1/2) -Vt (Te - Tc) }
    //      = (Vo Tc + Vt Te - Vt Tc) / 2    ・・・�@
    //
    //    直線 v = a t + Vo において v = 0 → t = Tc であるので
    //    0 = a Tc + Vo
    //    Tc = -Vo / a
    //    これを �@ へ代入
    //    D = (Vo (-Vo / a) + Vt Te - Vt (-Vo / a)) / 2 ・・・�A
    //    また a = (Vt - Vo) / Te であるので
    //    Te = (Vt - Vo) / a これを �A へ代入
    //    よって
    //    D = (Vo (-Vo / a) + Vt ((Vt - Vo) / a) - Vt (-Vo / a)) / 2
    //
    //    a について解く
    //
    //    D = ( -(Vo^2) / a  + (Vt (Vt - Vo)) / a + (Vt Vo) / a) / 2
    //    a D = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2
    //    a = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2D
    //    a = (-(Vo^2) + Vt^2 - Vt Vo + Vt Vo) / 2D
    //    a = (Vt^2 - Vo^2) / 2D
    //
    //    結局 a = (Vt^2 - Vo^2) / 2D となるので
    //    Vo <= 0  かつ  Vt <= 0 場合、あるいは  Vo >= 0  かつ  Vt >= 0  場合と同じである
}

void GgafDx9KurokoA::execSmoothMvVeloSequence(velo prm_end_velo, coord prm_target_distance,
                                                  int prm_target_frames, float prm_p1, float prm_p2,
                                                  bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = prm_target_distance;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = prm_target_frames;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_progress = 0;

    //＜トップスピード(Vt) を計算＞
    //
    //    速度(v)
    //     ^
    //     |                          D:目標移動距離
    //     |                         Vo:現時点の速度
    //     |                         Vt:トップスピード
    //     |                         Ve:最終速度
    //   Vt|....＿＿＿＿＿           Te:目標時間（フレーム数）
    //     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合
    //   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   Vo|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> 時間(t:フレーム)
    //   0 |  p1*Te     p2*Te  Te
    //
    // 移動距離Dは、左の台形＋中央の長方形＋右の台形 の面積である、
    // D = (1/2) (Vo + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // これをVtについて解く
    // Vt = ( 2D - p1 Te Vo + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _smooth_mv_velo_seq_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_veloMv) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

void GgafDx9KurokoA::execSmoothMvVeloSequenceD(velo prm_top_velo, velo prm_end_velo,
                                                   coord prm_target_distance, float prm_p1, float prm_p2,
                                                   bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = prm_target_distance;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_distance*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_distance*prm_p2);
    _smooth_mv_velo_seq_progress = 0;
}


void GgafDx9KurokoA::execSmoothMvVeloSequenceT(velo prm_top_velo, velo prm_end_velo,
                                                   int prm_target_frames, float prm_p1, float prm_p2,
                                                   bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = prm_target_frames;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_progress = 0;
}



//void GgafDx9KurokoA::execSmoothMvVeloSequence4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                                      bool prm_endacc_flg) {
//    _smooth_mv_velo_seq_flg = true;
//    _smooth_mv_velo_seq_p1 = (int)(prm_target_distance*1.0 / 4.0);
//    _smooth_mv_velo_seq_p2 = (int)(prm_target_distance*3.0 / 4.0);
//    _smooth_mv_velo_seq_end_velo = prm_end_velo;
//    _smooth_mv_velo_seq_target_distance = prm_target_distance;
//    _smooth_mv_velo_seq_mv_distance = 0;
//    _smooth_mv_velo_seq_target_frames = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
//    _smooth_mv_velo_seq_frame_of_spent = 0;
//    _smooth_mv_velo_seq_progress = 0;
//
//    //    速度
//    //     ^
//    //     |                       D:移動距離
//    //     |                      Vo:現時点の速度
//    //     |                      Vt:距離1/4 〜 3/4 の速度
//    //     |                      Ve:最終目標到達速度
//    //   Vt|....＿＿＿＿            Te:目標到達速度に達した時の時間（フレーム数）
//    //     |   /|      |＼
//    //   Ve|../.|......|..＼
//    //     | /  |      |   |
//    //     |/   |      |   |
//    //   Vo| 1/4|  2/4 |1/4|
//    //     |  D |   D  | D |
//    //   --+----+------+---+-----> 時間(フレーム)
//    //   0 |   tp1    tp2  Te
//
//    // 距離は 「台形＋長方形＋台形」 の面積。ゆえに
//    // (1/4)D = (1/2) (Vo + Vt) tp1           …�@ 台形
//    // (2/4)D = Vt (tp2 - tp1)                …�A 長方形
//    // (1/4)D = (1/2) (Ve + Vt) (Te - tp2)     …�B 台形
//
//
//    // (1/4)D = Vt tp1 -  (1/2) tp1 (Vt - Vo)
//    // また、距離は 「全体の長方形 ‐ 三角形部分２つ」 の面積でもある。ゆえに
//    // D = Te Vt - (1/2) tp1 (Vt - Vo) - (1/2) (Te - tp2) (Vt - Ve) …�C
//
//    //�@より
//    //tp1 = (D / 2 (Vo + Vt) )        …�D
//    //�Bより
//    //(Te - tp2) = (D / 2 (Ve + Vt) )  …�E
//    //�D�Eを�Cへ代入
//    //D = Te Vt - D(Vt - Vo) / 4 (Vo + Vt) - D(Vt - Ve) / 4 (Ve + Vt)
//    //これをVtについて解くと
//
//    //    Vt =
//    //    (sqrt((-9*Vo^2+9*Ve*Vo-9*Ve^2)*D^4-(4*Te*Vo^3-6*Te*Ve*Vo^2-6*Te*Ve^2*Vo+4*Te*Ve^3)*D^3+(-4*Te^2*Vo^4+8*Te^2*Ve*Vo^3-12*Te^2*Ve^2*Vo^2+8*Te^2*Ve^3*Vo-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*Vo^4+8*Te^4*Ve^3*Vo^3-4*Te^4*Ve^4*Vo^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*Vo^3-12*Ve*Vo^2-12*Ve^2*Vo+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3)+(9*D^2+Te^2*(4*Vo^2-4*Ve*Vo+4*Ve^2))/(36*Te^2*(
//    //    sqrt((-9*Vo^2+9*Ve*Vo-9*Ve^2)*D^4-(4*Te*Vo^3-6*Te*Ve*Vo^2-6*Te*Ve^2*Vo+4*Te*Ve^3)*D^3+(-4*Te^2*Vo^4+8*Te^2*Ve*Vo^3-12*Te^2*Ve^2*Vo^2+8*Te^2*Ve^3*Vo-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*Vo^4+8*Te^4*Ve^3*Vo^3-4*Te^4*Ve^4*Vo^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*Vo^3-12*Ve*Vo^2-12*Ve^2*Vo+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3))+(3*D-Te*(2*Vo+2*Ve))/(6*Te)
//    //なんじゃこれ・・・
//
//
//
//
//
//    _smooth_mv_velo_seq_top_velo = (8.0*prm_target_distance/prm_target_frames - _veloMv - prm_end_velo) / 6.0;
//}



bool GgafDx9KurokoA::isMoveingSmooth() {
    return _smooth_mv_velo_seq_flg;
}


void GgafDx9KurokoA::setRzMvAng(coord prm_tX, coord prm_tY) {
    setRzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9KurokoA::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDx9KurokoA::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_ang_veloRzBottomMv > prm_angDistance) {
        angOffset = _ang_veloRzBottomMv;
    } else if (prm_angDistance > _ang_veloRzTopMv) {
        angOffset = _ang_veloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDx9KurokoA::setRzMvAngVelo(ang_velo prm_ang_veloRzMv) {
    if (prm_ang_veloRzMv > _ang_veloRzTopMv) {
        _ang_veloRzMv = _ang_veloRzTopMv;
    } else if (prm_ang_veloRzMv < _ang_veloRzBottomMv) {
        _ang_veloRzMv = _ang_veloRzBottomMv;
    } else {
        _ang_veloRzMv = prm_ang_veloRzMv;
    }
}

void GgafDx9KurokoA::setRzMvAngAcce(ang_acce prm_ang_acceRzMv) {
    _ang_acceRzMv = prm_ang_acceRzMv;
}

void GgafDx9KurokoA::forceRzMvAngVeloRange(ang_velo prm_ang_veloRzMv01,
                                                 ang_velo prm_ang_veloRzMv02) {
    if (prm_ang_veloRzMv01 < prm_ang_veloRzMv02) {
        _ang_veloRzTopMv = prm_ang_veloRzMv02;
        _ang_veloRzBottomMv = prm_ang_veloRzMv01;
    } else {
        _ang_veloRzTopMv = prm_ang_veloRzMv01;
        _ang_veloRzBottomMv = prm_ang_veloRzMv02;
    }
    setRzMvAngVelo(_ang_veloRzMv); //再設定して範囲内に補正
}

void GgafDx9KurokoA::setStopTarget_RzMvAng(angle prm_angTargetRzMv,
                                                 int prm_way_allow,
                                                 ang_velo prm_ang_veloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _mv_ang_rz_target_stop_flg = true;
    _angTargetRzMv = GgafDx9Util::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_ang_veloAllowRyMv;
}

void GgafDx9KurokoA::setStopTarget_RzMvAngV(coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_RzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9KurokoA::getRzMvAngDistance(coord prm_tX, coord prm_tY, int prm_way) {
    return getRzMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9KurokoA::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = GgafDx9Util::simplifyAng(prm_angTargetRzMv);
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
                throwGgafCriticalException("GgafDx9KurokoA::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return (angTargetRzMv - _angRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= ANGLE360) {
            return ANGLE360 - _angRzMv + angTargetRzMv;
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9KurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return -1 * (_angRzMv + ANGLE360 - angTargetRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= ANGLE360) {
            return -1 * (_angRzMv - angTargetRzMv);
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9KurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDx9KurokoA::getRzMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}


void GgafDx9KurokoA::setRyMvAng(coord prm_tX, coord prm_tY) {
    setRyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9KurokoA::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9KurokoA::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_ang_veloRyBottomMv > prm_angDistance) {
        angOffset = _ang_veloRyBottomMv;
    } else if (prm_angDistance > _ang_veloRyTopMv) {
        angOffset = _ang_veloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDx9KurokoA::setRyMvAngVelo(ang_velo prm_ang_veloRyMv) {
    if (prm_ang_veloRyMv > _ang_veloRyTopMv) {
        _ang_veloRyMv = _ang_veloRyTopMv;
    } else if (prm_ang_veloRyMv < _ang_veloRyBottomMv) {
        _ang_veloRyMv = _ang_veloRyBottomMv;
    } else {
        _ang_veloRyMv = prm_ang_veloRyMv;
    }
}

void GgafDx9KurokoA::setRyMvAngAcce(ang_acce prm_ang_acceRyMv) {
    _ang_acceRyMv = prm_ang_acceRyMv;
}

void GgafDx9KurokoA::forceRyMvAngVeloRange(ang_velo prm_ang_veloRyMv01,
                                               ang_velo prm_ang_veloRyMv02) {
    if (prm_ang_veloRyMv01 < prm_ang_veloRyMv02) {
        _ang_veloRyTopMv = prm_ang_veloRyMv02;
        _ang_veloRyBottomMv = prm_ang_veloRyMv01;
    } else {
        _ang_veloRyTopMv = prm_ang_veloRyMv01;
        _ang_veloRyBottomMv = prm_ang_veloRyMv02;
    }
    setRyMvAngVelo(_ang_veloRyMv); //再設定して範囲内に補正
}

void GgafDx9KurokoA::setStopTarget_RyMvAng(angle prm_angTargetRyMv,
                                          int prm_way_allow,
                                          ang_velo prm_ang_veloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _mv_ang_ry_target_stop_flg = true;
    _angTargetRyMv = GgafDx9Util::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_ang_veloAllowRyMv;
}

void GgafDx9KurokoA::setStopTarget_RyMvAngV(coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_RyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9KurokoA::getRyMvAngDistance(coord prm_tX, coord prm_tY, int prm_way) {
    return getRyMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9KurokoA::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    angle angTargetRyMv;
    angTargetRyMv = GgafDx9Util::simplifyAng(prm_angTargetRyMv);
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
                throwGgafCriticalException("GgafDx9KurokoA::behave() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9KurokoA::getRyMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return (angTargetRyMv - _angRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= ANGLE360) {
            return ANGLE360 - _angRyMv + angTargetRyMv;
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9KurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return -1 * (_angRyMv + ANGLE360 - angTargetRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= ANGLE360) {
            return -1 * (_angRyMv - angTargetRyMv);
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9KurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDx9KurokoA::getRyMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}

void GgafDx9KurokoA::getRzRyMvAngDistance(int prm_way,
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
        throwGgafCriticalException("GgafDx9KurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDx9KurokoA::getRzRyFaceAngDistance(int prm_way,
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
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[GgafDx9Util::simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
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
        throwGgafCriticalException("GgafDx9KurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDx9KurokoA::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_angRz);
        _angRyMv = GgafDx9Util::simplifyAng(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9KurokoA::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = GgafDx9Util::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = GgafDx9Util::simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    GgafDx9Util::getNormalizeVectorZY(RyRz_Ry, ANGLE360-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    GgafDx9Util::getRzRyAng(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9KurokoA::setMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}
void GgafDx9KurokoA::setMvAng(coord prm_tX, coord prm_tY) {
    setMvAng(prm_tX, prm_tY, _pActor->_Z);
}
void GgafDx9KurokoA::setMvAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
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
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9KurokoA::setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setStopTarget_RzRyMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9KurokoA::setStopTarget_RzRyMvAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
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




void GgafDx9KurokoA::execTurnFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
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

void GgafDx9KurokoA::execTurnFaceAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTurnFaceAngSequence(out_angRz_Target, out_angRy_Target,
                                 prm_angVelo, prm_angAcce,
                                 prm_way, prm_optimize_ang);
}

void GgafDx9KurokoA::execTurnRzFaceAngSequence(angle prm_angRz_Target,
                                                          ang_velo prm_angVelo, ang_acce prm_angAcce,
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

void GgafDx9KurokoA::execTurnRyFaceAngSequence(angle prm_angRy_Target,
                                                          ang_velo prm_angVelo, ang_acce prm_angAcce,
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

void GgafDx9KurokoA::execTurnRxSpinAngSequence(angle prm_angRx_Target,
                                                            ang_velo prm_angVelo, ang_acce prm_angAcce,
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

void GgafDx9KurokoA::execTurnMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
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


void GgafDx9KurokoA::execTurnMvAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTurnMvAngSequence(out_angRz_Target, out_angRy_Target,
                               prm_angVelo, prm_angAcce,
                               prm_way, prm_optimize_ang);
}


void GgafDx9KurokoA::execTurnRzMvAngSequence(angle prm_angRz_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
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

void GgafDx9KurokoA::execTurnRyMvAngSequence(angle prm_angRy_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
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




void GgafDx9KurokoA::takeoverMvFrom(GgafDx9KurokoA* prm_pKurokoA) {
    // キャラの移動方角単位ベクトル
    _vX = prm_pKurokoA->_vX;
    _vY = prm_pKurokoA->_vY;
    _vZ = prm_pKurokoA->_vZ;
    // 移動方角のZ軸回転角
    _angRzMv = prm_pKurokoA->_angRzMv;
    // 移動方角のY軸回転角
    _angRyMv = prm_pKurokoA->_angRyMv;
    // 移動速度
    _veloMv = prm_pKurokoA->_veloMv;
    // 移動速度上限
    _veloTopMv = prm_pKurokoA->_veloTopMv;
    // 移動速度下限
    _veloBottomMv = prm_pKurokoA->_veloBottomMv;
    // 移動加速度
    _accMv = prm_pKurokoA->_accMv;
    // 移動躍度
    //_jerkMv = prm_pKurokoA->_jerkMv;

}

void GgafDx9KurokoA::resetMv() {
    //キャラの移動方角単位ベクトル
    _vX = _vY = _vZ = 0.0f;
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

    //_jerkMv = 0;
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _ang_veloRzMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _ang_veloRzTopMv = ANGLE360; //_ang_veloRzMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _ang_veloRzBottomMv = ANGLE360 * -1; //_ang_veloRzMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _ang_acceRzMv = 0; //_ang_veloRzMv の増分。デフォルトは移動方角の角加速度無し

    _ang_jerkRzMv = 0;


}

GgafDx9KurokoA::~GgafDx9KurokoA() {
}
