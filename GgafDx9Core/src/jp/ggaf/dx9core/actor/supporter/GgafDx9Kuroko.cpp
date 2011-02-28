#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// 【メモ】本クラスの考え方と単語の表現
//
// ＜２種類の方向＞
// 「キャラの方向」という言葉が曖昧なため、次の２種類の単語を定義する。「移動方角（方向）」と「軸回転方角（方向）」。
// 「移動方角（方向）」はキャラの進行方向のみを表現する。これは「移動速度」と伴って、キャラは座標内を移動することとする。
// 「軸回転方角（方向）」はキャラの向き（前方方向等）のみを表現する事とする。
// キャラクタが画面の上部から下部へ移動しても、キャラクタは下を向くとは限らず自機に向いてほしい場合もある。
// または、右にキャラを向かせて、左に移動させたいこともある。それぞれ２つの方向設定が必要。
//
// ＜移動方角（方向）の２種類の表現方法＞
// キャラが進む方向、つまり移動方角の方向は、原点から単位球の表面に向かって伸びるベクトル (_vX, _vY, _vZ) で表す方法と、
// ２つの軸回転アングル値 (_angRzMv, _angRyMv) で表す方法の２種類用意した。クォータニオンは今のところ無し。
// _angRzMv は Z軸回転角、 _angRyMv は Y軸回転角 を意味している。両方とも0度を、方向ベクトル(1, 0, 0) の方向と定義する。
// これは方向ベクトルを、緯度と経度、（仰角とアジマス）の関係に見立て、対応させようとした設計。
// 注意することは、Y軸回転角＝経度 は常に成り立つが、Z軸回転角＝緯度 は、Z軸回転角 → Y軸回転角の順番である場合に限り成り立つ。
// (※ Y軸回転角 → Z軸回転角 の順番で回転させた場合、Z軸回転角＝緯度 とならないという意味)
// 本クラスでは、「Z軸回転 → Y軸回転の順番でのZ軸回転角」を簡略して、単に「Z軸回転角」と表現する事とする。
// 成分を個別に表現したい場合は、それぞれ「移動方角（Z軸）」「移動方角（Y軸）」と書くことにする。
//
// ソースコード中の、変数やメソッドの
// 「Rz」という表記は「移動方角（Z軸）（但しZ軸回転 → Y軸回転の順番）」を意味している。
// 「Ry」という表記は「移動方角（Y軸）」を意味している。
// 「RzRy」という表現は「Z軸回転 → Y軸回転の順番の移動方角」を表している。
//
// Z軸回転角、Y軸回転角が両方とも0度を、方向ベクトル(1, 0, 0) の方向と定義する。
// Z軸回転角の正の増加は、Z軸の正の方向を向いて反時計回り。
// Y軸回転角の正の増加は、Y軸の正の方向を向いて反時計回り。とする。
//
// 「移動方角」にはZ軸回転角とY軸回転角による指定(_angRzMv, _angRyMv)と単位ベクトル指定(_vX, _vY, _vZ) があると説明したが、
// 「方角」を普通に考えた場合は、世間一般では方向ベクトル（XYZの値）のことを指すことが多いと思う。
// しかしこのクラスでは、よく使うのは前者の方で、本クラスのメソッドも _angRzMv と _angRyMv を操作するものがほとんどである。
// しかし、最終的には ワールド変換行列を作成するため、「単位ベクトル(_vX, _vY, _vZ)*移動速度 」という計算をする必要がある。
// 結局は単位ベクトルを求めているのだが、座標回転計算を、整数型の _angRzMv と _angRyMv でさんざん行ってから、
// 最後に１回単位ベクトルを求める。という方が速いのではと考えたため、このような設計になった。
// TODO:最適化の余地だいぶ残っている（が、またいつか）。
//
// 本クラスライブラリでは、この(_angRzMv, _angRyMv)を主に操作して、内部で方向ベクトル(_vX, _vY, _vZ) を同期させている。
// (_vX, _vY, _vZ)のみをメソッドを使わず直接操作すると、(_angRzMv, _angRyMv)との同期が崩れるので注意。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらないこととする。
//
// ＜移動速度:Velo or MvVelo＞
// キャラは「移動速度」(_veloMv)を保持している。移動する方法は簡単で、基本的に毎フレーム「移動方角」に「移動速度」分動くだけ。
// つまり「移動方角」(_vX, _vY, _vZ)に「移動速度」(_veloMv)を掛け算している。１フレーム後の座標は
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) である。  これに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を掛ける。
// よって、(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)が１フレーム後の座標。

// ＜軸回転方角:AngFace＞
// キャラのローカル座標で向いている方角（方向）を「軸回転方角」と呼ぶことにする。
//「軸回転方角」は、ワールド変換行列の軸回転と同じ回転方法とする。
// ワールド変換行列の軸回転とは、X軸回転角、Y軸回転角、Z軸回転角のことで、それぞれ、
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] が保持している。
// 本ライブラリでは、キャラ毎のローカル座標系の単位球の表面に向かって伸びるベクトル(1, 0, 0) をキャラの「前方」と設定している。
// Xファイルなどのメッシュモデルも、X軸の正の方向に向いているモノとする。また、モデル「上方向は」は（0, 1, 0)とする。
// ワールド変換行列の回転行列の掛ける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 > (拡大縮小) 」 とする。
// (※  X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「軸回転方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_angFace[AXIS_Z], _angFace[AXIS_Y])で表現できる。
// つまり、「前方」は Z軸回転角・Y軸回転角共に0度とし、例えば「後ろ」は[Z軸回転角,Y軸回転角]=[0度,180度] と表現する。。
// 単に「Z軸回転角」などと書くと、「移動方角」のZ軸回転角なのか、「軸回転方角」のZ軸回転角なのか曖昧になるため、
// 「軸回転方角(Z軸)」「軸回転方角(Y軸)」と書くこととする。（※「軸回転方角(X軸)」もあるが、これはスピンを表し向きへの影響は無し）
// ここで注意は、１つのキャラが向いている方角に対して、実は２通りのアクセスする方法があるということ。例えば、
// 「前方(1, 0, 0)を向いて真右向き」 は [軸回転方角(Z軸), 軸回転方角(Y軸)]=[0, 90度] or [180度,270度] とで表現できる。
// （※軸回転方角(Y軸)は左手系座標のためY軸の正方向を向いて反時計回り）
// 実は 「前方」 も [180度,180度]とも表現できるし、「真後ろ」 は [0度,180度] とも [180度,0度] とも表現できる。
// どちらも向いている方向は同じだが、姿勢(キャラの上方向)が異なる。姿勢が異なるとまずいキャラは注意すること。
// 当然、「移動方角」でも、２通りのアクセスする方法があるのだが、こちらは見た目は差が無い。差が無いが角度計算するときに影響がでるやもしれない。


// ＜自動前方向き機能＞
// さてここで 「移動方角（Z軸）」「移動方角（Y軸）」を、それぞれ「軸回転方角(Z軸)」「軸回転方角(Y軸)」 へコピーしてやると、
// なんと移動方角と、キャラクタの向きの同期が簡単に取れるじゃないか！
// 「自動前方向き機能」とは、「移動方角」を設定すると、それに伴って自動的に「軸回転方角」を設定する事とする。
// 具体的には、以下のようにフレーム毎に、アングル値を上書きコピー（同期）。或いは差分を加算（向き方向を滑らかに描画）していく。
//  ・移動方角（Z軸） → 軸回転方角(Z軸)
//  ・移動方角（Y軸） → 軸回転方角(Y軸)
// しかし「軸回転方角」を設定ても「移動方角」変化しない（逆は関連しない）ので注意。

// ＜角速度:AngVelo＞
// 「移動方角（Z軸）」「移動方角（Y軸）」、「軸回転方角(Z軸)」「軸回転方角(Y軸)」には、それぞれの「角速度」を設けてある。
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



GgafDx9Kuroko::GgafDx9Kuroko(GgafDx9GeometricActor* prm_pActor) :
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

    _smooth_mv_velo_seq_flg = false;
    _smooth_mv_velo_seq_endacc_flg = true;
    _smooth_mv_velo_seq_top_velo = 0;
    _smooth_mv_velo_seq_end_velo = 0;
    _smooth_mv_velo_seq_distance_of_target = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = 0;
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = 0;
    _smooth_mv_velo_seq_p2 = 0;
    _smooth_mv_velo_seq_progress = -1;
}

void GgafDx9Kuroko::behave() {

    //軸回転方角処理
    angle angDistance;
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

    //なめらか移動シークエンス起動時
    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_frame_of_spend < 0) {
            //目標距離指定の場合
            if (_smooth_mv_velo_seq_progress == 0) {
                //加速設定
                setMvAcce(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
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
                    setMvAcce(_smooth_mv_velo_seq_distance_of_target - _smooth_mv_velo_seq_mv_distance, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //減速中
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_distance_of_target) {
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
                setMvAcce(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //加速中
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_p1) {
                    //p1 に到達すれば 等速へ
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //等速中
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setMvAcce2(_smooth_mv_velo_seq_frame_of_spend - _smooth_mv_velo_seq_spend_frame, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //減速中
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_frame_of_spend) {
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

    _accMv += _jerkMv;
    //移動加速度の処理
    _veloMv += _accMv;
    setMvVelo(_veloMv);

    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_frame_of_spend < 0) {
            _smooth_mv_velo_seq_mv_distance+=abs(_veloMv);
        } else {
            _smooth_mv_velo_seq_spend_frame++;
        }
    }

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

void GgafDx9Kuroko::setFaceAng(int prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angFace);
}

void GgafDx9Kuroko::setFaceAng(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9Kuroko::addFaceAng(int prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDx9Kuroko::setFaceAngVelo(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9Kuroko::forceFaceAngVeloRange(int prm_axis,
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

void GgafDx9Kuroko::setFaceAngAcce(int prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDx9Kuroko::setStopTarget_FaceAngV(int prm_axis,
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

void GgafDx9Kuroko::setStopTarget_FaceAng(int prm_axis,
                                                 angle prm_angTargetRot,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDx9Kuroko::getFaceAngDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getFaceAngDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9Kuroko::getFaceAngDistance(int prm_axis, angle prm_angTargetRot, int prm_way) {
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
                throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9Kuroko::getFaceAngDistance() 何故かしら角の距離が求めれません(2)。_pActor="<<_pActor->getName());
}

void GgafDx9Kuroko::forceMvVeloRange(int prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDx9Kuroko::forceMvVeloRange(int prm_veloMv01, int prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //再設定して範囲内に補正
}

void GgafDx9Kuroko::setMvVelo(int prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDx9Kuroko::addMvVelo(int prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDx9Kuroko::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

void GgafDx9Kuroko::setMvAcceToStop(int prm_distance_of_target) {
    // a = -(v0^2) / 2S
    _accMv  =  -(1.0*_veloMv*_veloMv) / (2.0*prm_distance_of_target);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((2.0*prm_distance_of_target) / _veloMv); //使用フレーム数
}
void GgafDx9Kuroko::setMvAcce2(int prm_frame_of_spend, velo prm_velo_target) {
    //a = (vx-v0) / t
    _accMv = (prm_velo_target - _veloMv) / (1.0f*prm_velo_target);
}
void GgafDx9Kuroko::setMvAcce(int prm_distance_of_target, velo prm_velo_target) {
    // a = (vx^2 - v0^2) / 2S
    _accMv =  ((1.0f*prm_velo_target*prm_velo_target) - (1.0f*_veloMv*_veloMv)) / (2.0f*prm_distance_of_target);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((1.0*prm_velo_target - _veloMv) / _accMv); //使用フレーム数

    // 【補足】
    // v0 <= 0  かつ  vx <= 0 場合、あるいは  v0 >= 0  かつ  vx >= 0  場合は、S(目標距離)が上記式で問題ない。
    // では
    // v0 < 0   かつ  vx > 0  場合、あるいは  v0 > 0   かつ  vx < 0   場合は、どうなるか？
    //
    //    速度
    //     ^        a:加速度
    //     |        S:移動距離（目標到達速度に達するまでに費やす距離）
    //     |       v0:現時点の速度
    //     |       vx:目標到達速度
    //     |       tx:目標到達速度に達した時の時間（フレーム数）
    //  v0 |
    //     |＼
    //     |  ＼  傾きはa
    //     | S1 ＼
    //     |      ＼ tc     tx
    //   --+--------＼------+---> 時間(フレーム)
    //   0 |          ＼ S2 |
    //     |            ＼  |
    //   vx|..............＼|
    //     |
    //
    //
    //    S = S1 - S2 , 交点を tc とする
    //
    //    S1 = (1/2) v0 tc
    //    S2 = (1/2) -vx (tx - tc)
    //    S = S1 - S2 より
    //    S = (1/2) v0 tc -  { (1/2) -vx (tx - tc) }
    //      = (v0 tc + vx tx - vx tc) / 2    ・・・①
    //
    //    直線 v = a t + v0 において v = 0 の t は tc であるので
    //    tc = -v0 / a
    //    これを ① へ代入
    //    S = (v0 (-v0 / a) + vx tx - vx (-v0 / a)) / 2 ・・・②
    //
    //    また a = (vx - v0) / tx であるので
    //    tx = (vx - v0) / a これを ② へ代入
    //    よって
    //    S = (v0 (-v0 / a) + vx ((vx - v0) / a) - vx (-v0 / a)) / 2
    //
    //    a について解く
    //
    //    S = {( -(v0^2) / a  + (vx (vx - v0)) / a + (vx v0) / a)) / 2
    //    aS = { -(v0^2) + (vx (vx - v0)) + (vx v0) } / 2
    //    a = { -(v0^2) + (vx (vx - v0)) + (vx v0) } / 2S
    //    a = (-(v0^2) + vx^2 - vx v0 + vx v0) / 2S
    //    a = (vx^2 -v0^2) / 2S
    //
    //    結局 a = (vx^2 - v0^2) / 2S となるので
    //    v0 <= 0  かつ  vx <= 0 場合、あるいは  v0 >= 0  かつ  vx >= 0  場合と同じである


}

void GgafDx9Kuroko::orderSmoothMvVeloSequence(velo prm_top_velo, velo prm_end_velo, int prm_distance_of_target,
                                                    bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = prm_distance_of_target;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_distance_of_target*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_distance_of_target*3.0 / 4.0);
    _smooth_mv_velo_seq_progress = 0;
}


void GgafDx9Kuroko::orderSmoothMvVeloSequence2(velo prm_top_velo, velo prm_end_velo, int prm_frame_of_spend,
                                                    bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = prm_frame_of_spend;
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_frame_of_spend*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_frame_of_spend*3.0 / 4.0);
    _smooth_mv_velo_seq_progress = 0;
}

void GgafDx9Kuroko::orderSmoothMvVeloSequence3(velo prm_end_velo, int prm_distance_of_target, int prm_frame_of_spend,
                                                      bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_p1 = (int)(prm_distance_of_target*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_distance_of_target*3.0 / 4.0);
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = prm_distance_of_target;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = -1; //目標時間は使わない(_smooth_mv_velo_seq_top_velo計算で考慮されるため)
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_progress = 0;

    //    速度
    //     ^
    //     |                          S:移動距離
    //     |                         vs:現時点の速度
    //     |                         vx:距離1/4 ～ 3/4 の速度
    //     |                         ve:最終目標到達速度
    //   vx|....＿＿＿＿＿            t:目標到達速度に達した時の時間（フレーム数）
    //     |   /|         |＼
    //   ve|../.|.........|..＼
    //     | /  |         |    |
    //     |/   |         |    |
    //   vs|    |    S    |    |
    //     |    |         |    |
    //   --+----+----+----+----+-----> 時間(フレーム)
    //   0 | (1/4)t    (3/4)t  t

    // 距離は 台形＋長方形＋台形 の面積
    // S  = (1/2) (vs + vx) (1/4)t  + vx (2/4)t  +  (1/2) (ve + vx) (1/4)t
    // これをvxについて解く
    // 8S = (vs + vx)t + 4 vx t + (ve + vx)t
    // 8S/t = vs + vx + 4vx + ve + vx
    // 6vx = 8S/t - vs - ve
    // vx = (8S/t - vs - ve) / 6
    _smooth_mv_velo_seq_top_velo = (8.0*prm_distance_of_target/prm_frame_of_spend - _veloMv - prm_end_velo) / 6.0;
}

bool GgafDx9Kuroko::isMoveingSmooth() {
    return _smooth_mv_velo_seq_flg;
}


void GgafDx9Kuroko::setRzMvAng(int prm_tX, int prm_tY) {
    setRzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9Kuroko::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDx9Kuroko::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDx9Kuroko::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDx9Kuroko::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDx9Kuroko::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
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

void GgafDx9Kuroko::setStopTarget_RzMvAng(angle prm_angTargetRzMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _angTargetRzMv = GgafDx9Util::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9Kuroko::setStopTarget_RzMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9Kuroko::getRzMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRzMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9Kuroko::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
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
                throwGgafCriticalException("GgafDx9Kuroko::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDx9Kuroko::getRzMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}


void GgafDx9Kuroko::setRyMvAng(int prm_tX, int prm_tY) {
    setRyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9Kuroko::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9Kuroko::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDx9Kuroko::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDx9Kuroko::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDx9Kuroko::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
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

void GgafDx9Kuroko::setStopTarget_RyMvAng(angle prm_angTargetRyMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _angTargetRyMv = GgafDx9Util::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9Kuroko::setStopTarget_RyMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9Kuroko::getRyMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRyMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9Kuroko::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
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
                throwGgafCriticalException("GgafDx9Kuroko::behave() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9Kuroko::getRyMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDx9Kuroko::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDx9Kuroko::getRyMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}

void GgafDx9Kuroko::getRzRyMvAngDistance(int prm_way,
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
        throwGgafCriticalException("GgafDx9Kuroko::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDx9Kuroko::getRzRyFaceAngDistance(int prm_way,
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
        throwGgafCriticalException("GgafDx9Kuroko::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDx9Kuroko::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_angRz);
        _angRyMv = GgafDx9Util::simplifyAng(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9Kuroko::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = GgafDx9Util::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = GgafDx9Util::simplifyAng(prm_angRyRz_Rz);
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

void GgafDx9Kuroko::setMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9Kuroko::setMvAng(int prm_tX, int prm_tY, int prm_tZ) {
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

void GgafDx9Kuroko::setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setStopTarget_RzRyMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9Kuroko::setStopTarget_RzRyMvAng(int prm_tX, int prm_tY, int prm_tZ) {
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

void GgafDx9Kuroko::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //再設定して範囲内に補正
}

void GgafDx9Kuroko::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDx9Kuroko::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDx9Kuroko::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDx9Kuroko::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}


void GgafDx9Kuroko::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //再設定して範囲内に補正
}


void GgafDx9Kuroko::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //再設定して範囲内に補正
}

void GgafDx9Kuroko::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDx9Kuroko::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDx9Kuroko::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDx9Kuroko::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}


void GgafDx9Kuroko::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //再設定して範囲内に補正
}

void GgafDx9Kuroko::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //再設定して範囲内に補正
}

void GgafDx9Kuroko::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDx9Kuroko::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDx9Kuroko::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDx9Kuroko::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}


void GgafDx9Kuroko::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //再設定して範囲内に補正
}



void GgafDx9Kuroko::forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02) {
    forceVxMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVyMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVzMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
}
void GgafDx9Kuroko::forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02) {
    forceVxMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVyMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVzMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
}




void GgafDx9Kuroko::orderTagettingFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
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

void GgafDx9Kuroko::orderTagettingFaceAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    orderTagettingFaceAngSequence(out_angRz_Target, out_angRy_Target,
                                 prm_angVelo, prm_angAcce,
                                 prm_way, prm_optimize_ang);
}

void GgafDx9Kuroko::orderTagettingRzFaceAngSequence(angle prm_angRz_Target,
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

void GgafDx9Kuroko::orderTagettingRyFaceAngSequence(angle prm_angRy_Target,
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

void GgafDx9Kuroko::orderTagettingRxSpinAngleSequence(angle prm_angRx_Target,
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

void GgafDx9Kuroko::orderTagettingMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
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


void GgafDx9Kuroko::orderTagettingMvAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                      angvelo prm_angVelo, angacce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    orderTagettingMvAngSequence(out_angRz_Target, out_angRy_Target,
                               prm_angVelo, prm_angAcce,
                               prm_way, prm_optimize_ang);
}


void GgafDx9Kuroko::orderTagettingRzMvAngSequence(angle prm_angRz_Target,
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

void GgafDx9Kuroko::orderTagettingRyMvAngSequence(angle prm_angRy_Target,
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


void GgafDx9Kuroko::takeoverMvFrom(GgafDx9Kuroko* prm_pKuroko) {
    // キャラの移動方角単位ベクトル
    _vX = prm_pKuroko->_vX;
    _vY = prm_pKuroko->_vY;
    _vZ = prm_pKuroko->_vZ;
    // 移動方角のZ軸回転角
    _angRzMv = prm_pKuroko->_angRzMv;
    // 移動方角のY軸回転角
    _angRyMv = prm_pKuroko->_angRyMv;
    // 移動速度
    _veloMv = prm_pKuroko->_veloMv;
    // 移動速度上限
    _veloTopMv = prm_pKuroko->_veloTopMv;
    // 移動速度下限
    _veloBottomMv = prm_pKuroko->_veloBottomMv;
    // 移動加速度
    _accMv = prm_pKuroko->_accMv;
    // 移動躍度
    _jerkMv = prm_pKuroko->_jerkMv;

    // X軸方向移動速度
    _veloVxMv = prm_pKuroko->_veloVxMv;
    // X軸方向移動速度上限
    _veloTopVxMv = prm_pKuroko->_veloTopVxMv;
    // X軸方向移動速度下限
    _veloBottomVxMv = prm_pKuroko->_veloBottomVxMv;
    // X軸方向移動加速度
    _acceVxMv = prm_pKuroko->_acceVxMv;
    // X軸方向移動加速度上限
    _acceTopVxMv = prm_pKuroko->_acceTopVxMv;
    // X軸方向移動加速度下限
    _acceBottomVxMv = prm_pKuroko->_acceBottomVxMv;
    // Y軸方向移動速度
    _veloVyMv = prm_pKuroko->_veloVyMv;
    // Y軸方向移動速度上限
    _veloTopVyMv = prm_pKuroko->_veloTopVyMv;
    // Y軸方向移動速度下限
    _veloBottomVyMv = prm_pKuroko->_veloBottomVyMv;
    // Y軸方向移動加速度
    _acceVyMv = prm_pKuroko->_acceVyMv;
    // Y軸方向移動加速度上限
    _acceTopVyMv = prm_pKuroko->_acceTopVyMv;
    // Y軸方向移動加速度下限
    _acceBottomVyMv = prm_pKuroko->_acceBottomVyMv;
    // Z軸方向移動速度
    _veloVzMv = prm_pKuroko->_veloVzMv;
    // Z軸方向移動速度上限
    _veloTopVzMv = prm_pKuroko->_veloTopVzMv;
    // Z軸方向移動速度下限
    _veloBottomVzMv = prm_pKuroko->_veloBottomVzMv;
    // Z軸方向移動加速度
    _acceVzMv = prm_pKuroko->_acceVzMv;
    // Z軸方向移動加速度上限
    _acceTopVzMv = prm_pKuroko->_acceTopVzMv;
    // Z軸方向移動加速度下限
    _acceBottomVzMv = prm_pKuroko->_acceBottomVzMv;

}

void GgafDx9Kuroko::resetMv() {
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
}

GgafDx9Kuroko::~GgafDx9Kuroko() {
}
