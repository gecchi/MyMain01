#ifndef GGAFDYNAMICVARIABLE_H_
#define GGAFDYNAMICVARIABLE_H_
namespace GgafCore {

/**
 */
template<class T>  //T:管理する要素のポインタの型
class GgafDynamicVariable : public GgafObject {

public:

    T* _pVariable;

    /**
     * コンストラクタ .
     */
    GgafDynamicVariable(T* prm_variable, T prm_max_velo, T prm_max_acce);


    /** [r/w]X軸方向移動速度 */
    T _velo;
    /** [r/w]X軸方向移動速度上限 */
    T _veloTop;
    /** [r/w]X軸方向移動速度下限 */
    T _veloBottom;
    /** [r/w]X軸方向移動加速度 */
    T _acce;
    /** [r/w]X軸方向移動加速度上限*/
    T _acceTop;
    /** [r/w]X軸方向移動加速度下限*/
    T _acceBottom;

    /** [r]なめらかな移動シークエンスを実行中はtrue */
    bool _smooth_velo_seq_flg;
    /** [r]なめらかな移動シークエンスを実行完了時の加速度設定（true：加速度0に設定／false:加速度をそのままにしておく） */
    bool _smooth_velo_seq_endacc_flg;
    /** [r]なめらかな移動シークエンスで設定されたトップスピード（等速移動時速度） */
    T _smooth_velo_seq_top_velo;
    /** [r]なめらかな移動シークエンスで設定された終了時の速度 */
    T _smooth_velo_seq_end_velo;
    /** [r]なめらかな移動シークエンスで設定された目標移動距離 */
    T _smooth_velo_seq_target_distance;
    /** [r]なめらかな移動シークエンスに開始から現在までの移動距離 */
    T _smooth_velo_seq_distance;
    /** [r]なめらかな移動シークエンスで設定された目標時間 */
    int  _smooth_velo_seq_target_frames;
    /** [r]なめらかな移動シークエンスに開始から現在までの経過時間 */
    int  _smooth_velo_seq_frame_of_spent;
    /** [r]なめらかな移動シークエンスで設定された加速～等速へ切り替わる位置 */
    int  _smooth_velo_seq_p1;
    /** [r]なめらかな移動シークエンスで設定された等速～減速へ切り替わる位置 */
    int  _smooth_velo_seq_p2;
    /** [r]なめらかな移動シークエンスの進捗状況 */
    int  _smooth_velo_seq_progress;

    /**
     * X軸方向移動速度設定 .
     * @param prm_velo X軸方向移動速度
     */
    void setVelo(T prm_velo);

    /**
     * X軸方向移動速度加算 .
     * @param prm_velo X軸方向移動速度差分
     */
    void addVelo(T prm_velo);

    /**
     * X軸方向移動速度の上限下限を強制 .
     * @param prm_velo01 速度１
     * @param prm_velo02 速度２
     */
    void forceVeloRange(T prm_velo01, T prm_velo02);

    /**
     * X軸方向移動加速度設定 .
     * @param prm_acce X軸方向移動加速度
     */
    void setAcce(T prm_acce);

    /**
     * X軸方向移動加速度加算 .
     * @param prm_acce X軸方向移動加速度差分
     */
    void addAcce(T prm_acce);

    /**
     * X軸方向移動加速度の上限下限を強制 .
     * @param prm_acce01 加速度１
     * @param prm_acce02 加速度２
     */
    void forceAcceRange(T prm_acce01, T prm_acce02);



    /**
     * 黒子Bが振る舞う .
     * 黒子B機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に黒子Bを必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();








    /**
     * なめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * 移動に費やされる時間(Te)を3つのセクションに分け、次のような速度制御を自動的に行う。<BR>
     * ・時間 0     ～ 時間 p1*Te まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・時間 p1*Te ～ 時間 p2*Te まで ・・・ トップスピードで等速移動<BR>
     * ・時間 p2*Te ～ 時間 Te    まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    速度(v)
     *     ^
     *     |
     *     |                         Vo:現時点の速度
     *     |                         Ve:最終速度
     *     |                          D:目標移動距離
     *   Vt|....___________          Te:目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     *     | /  :         :    |     Vt:距離・時間から導きだされるトップスピード
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * 最終スピード(Ve)、目標移動距離(D)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * トップスピード(Vt)は内部で自動計算し決定される。<BR>
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_endacc_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void execSmoothSequence(T prm_end_velo, T prm_target_distance,
                              int prm_target_frames, float prm_p1, float prm_p2,
                              bool prm_endacc_flg = true);


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(速度・距離指定、時間変動) .
     * 移動距離を3つのセクション(d1,d2,d3)に分け、次のような速度制御を自動的に行う。<BR>
     * ・距離 0     ～ 距離 d1       まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・距離 d1    ～ 距離 d1+d2    まで ・・・ トップスピードで等速移動<BR>
     * ・距離 d1+d2 ～ 距離 d1+d2+d3 まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *    速度(v)
     *     ^
     *     |                         Vo:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *     |         D=d1+d2+d3       D:目標移動距離(D=d1+d2+d3)
     *   Vt|....___________          p1:トップスピードに達する距離となるような、距離(D)に対する割合
     *     |   /|         |＼            つまり    d1 = D*p1 となるような p1 (0.0～1.0)
     *   Ve|../.|.........|..＼      p2:減速を開始距離となるような、距離(D)に対する割合
     *     | /  |         |    |         つまり d1+d2 = D*p2 となるような p2 (0.0～1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *   Vo| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、目標移動距離(D)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_p1 トップスピードに達する距離となるような、距離(D)に対する割合
     * @param prm_p2 減速を開始距離となるような、距離(D)に対する割合
     * @param prm_endacc_flg
     */
    void execSmoothSequenceD(T prm_top_velo, T prm_end_velo,
                               T prm_target_distance, float prm_p1, float prm_p2,
                               bool prm_endacc_flg = true);


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(速度・時間指定、距離変動)  .
     * 移動に費やされる時間(Te)を3つのセクションに分け、次のような速度制御を自動的に行う。<BR>
     * ・時間 0     ～ 時間 p1*Te まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・時間 p1*Te ～ 時間 p2*Te まで ・・・ トップスピードで等速移動<BR>
     * ・時間 p2*Te ～ 時間 Te    まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    速度(v)
     *     ^
     *     |
     *     |                         Vo:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *   Vt|....___________          Te:到達目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     *     | /  :         :    |      D:必要な移動距離
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * 必要な移動距離(D)は内部で自動計算し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_frames 到達目標時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     * @param prm_endacc_flg true:目標時間に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void execSmoothSequenceT(T prm_top_velo, T prm_end_velo,
                               int prm_target_frames, float prm_p1, float prm_p2,
                               bool prm_endacc_flg = true);






    /**
     * 移動加速度を、「停止時移動距離」により設定する .
     * <pre><code>
     *
     *    速度(v)
     *     ^       a:減加速度
     *     |       D:移動距離（停止に費やす距離）
     *     |      Vo:現時点の速度
     *   Vo|      Te:停止するフレーム
     *     |＼
     *     |  ＼
     *     |    ＼ 斜辺の傾きa
     *     |   D  ＼
     *     |        ＼
     *   --+----------＼-----> 時間(t)
     *   0 |          Te
     *
     *    D = (1/2) Vo Te  ・・・①
     *    a = -Vo / Te     ・・・②
     *    ①より
     *    Te = 2D / Vo
     *    これを②へ代入
     *    a = -Vo / (2D / Vo)
     *    ∴ a = -(Vo^2) / 2D
     * </code></pre>
     * 上図のような状態を想定し、引数の距離(D)から、加速度(a)を計算し設定している。<BR>
     * 停止までのフレーム(Te) は 距離(D) により変化するため指定不可。<BR>
     * @param prm_target_distance 停止時移動距離(D)
     */
    void setAcceToStop(T prm_target_distance);

    /**
     * 移動加速度を、「目標到達速度」「移動距離(達するまでに費やす距離)」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度
     *     |        D:移動距離（目標到達速度に達するまでに費やす距離）
     *     |       Vo:現時点の速度
     *     |       Vt:目標到達速度
     *     |       Te:目標到達速度に達した時の時間（フレーム数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> 時間(t)
     *   0 |        Te
     *
     *    D = (1/2) (Vo + Vt) Te   ・・・①
     *    a = (Vt - Vo) / Te         ・・・②
     *    ①より Te = (Vt - Vo) / a
     *    これを②へ代入
     *    D = (Vt^2 - Vo^2) / 2a
     *    ∴ a = (Vt^2 - Vo^2) / 2D
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、移動距離(D)から、加速度(a)を計算し設定している。<BR>
     * 目標到達まで必要なフレーム(Te) はパラメータにより変化するため指定不可。<BR>
     * 捕捉：setAcceBy_Dv(0, D) は setAcceToStop(D) と同じである
     * @param prm_target_distance  目標到達速度に達するまでに費やす距離(D)
     * @param prm_target_velo 目標到達速度(Vt)
     */
    void setAcceBy_Dv(T prm_target_distance, T prm_target_velo);


    /**
     * 移動加速度を、「目標到達速度」「費やす時間」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度
     *     |        D:移動距離
     *     |       Vo:現時点の速度
     *     |       Vt:目標到達速度
     *     |       Te:目標到達速度に達した時の時間（フレーム数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     *    a = (Vt-Vo) / Te
     *    Dは無視
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param prm_target_frames 費やす時間(Te)
     * @param prm_target_velo  目標到達速度(Vt)
     */
    void setAcceBy_tv(int prm_target_frames, T prm_target_velo);

    /**
     * デストラクタ.
     * 内部保持する要素の値は、nullptrで無い場合、それぞれ delete により解放されます。<BR>
     * TODO:delete[] やその他の解放方法に対応
     */
    virtual ~GgafDynamicVariable();


};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafDynamicVariable<T>::GgafDynamicVariable(T* prm_pVariable, T prm_max_velo, T prm_max_acce) :
    GgafObject() {
    _pVariable = prm_pVariable;
    _velo = (T)0;
    _acce = (T)0;
    _veloTop =  (T)prm_max_velo;
    _veloBottom =  (T)(-prm_max_velo);
    _acceTop =  (T)prm_max_acce;
    _acceBottom =  (T)(-prm_max_acce);


    _smooth_velo_seq_flg = false;
    _smooth_velo_seq_endacc_flg = true;
    _smooth_velo_seq_top_velo = (T)0;
    _smooth_velo_seq_end_velo = (T)0;
    _smooth_velo_seq_target_distance = (T)0;
    _smooth_velo_seq_distance = (T)0;
    _smooth_velo_seq_target_frames = 0;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = 0;
    _smooth_velo_seq_p2 = 0;
    _smooth_velo_seq_progress = -1;
}

template<class T>
void GgafDynamicVariable<T>::behave() {
    //X軸方向移動加速度の処理
    _velo += _acce;
    setVelo(_velo);

    //なめらか移動シークエンス起動時
    if (_smooth_velo_seq_flg) {
        if (_smooth_velo_seq_target_frames < 0) {
            //目標距離指定の場合
            if (_smooth_velo_seq_progress == 0) {
                //加速設定
                setAcceBy_Dv(_smooth_velo_seq_p1, _smooth_velo_seq_top_velo);
                _smooth_velo_seq_progress++;
            } else if (_smooth_velo_seq_progress == 1) {
                //加速中
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_p1) {
                    //p1 に到達すれば 等速へ
                    setAcce(0);
                    setVelo(_smooth_velo_seq_top_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 2) {
                //等速中
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setAcceBy_Dv(_smooth_velo_seq_target_distance - _smooth_velo_seq_distance, _smooth_velo_seq_end_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 3) {
                //減速中
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_target_distance) {
                    //目標距離へ到達
                    setVelo(_smooth_velo_seq_end_velo);
                    if (_smooth_velo_seq_endacc_flg) {
                        setAcce(0);
                    }
                    _smooth_velo_seq_progress++;
                    _smooth_velo_seq_flg = false; //おしまい
                }
            }
        } else {
            //目標時間指定の場合
            if (_smooth_velo_seq_progress == 0) {
                //加速設定
                setAcceBy_tv(_smooth_velo_seq_p1, _smooth_velo_seq_top_velo);
                _smooth_velo_seq_progress++;
            } else if (_smooth_velo_seq_progress == 1) {
                //加速中
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_p1) {
                    //p1 に到達すれば 等速へ
                    setAcce(0);
                    setVelo(_smooth_velo_seq_top_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 2) {
                //等速中
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setAcceBy_tv(_smooth_velo_seq_target_frames - _smooth_velo_seq_frame_of_spent, _smooth_velo_seq_end_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 3) {
                //減速中
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_target_frames) {
                    //目標距離へ到達
                    setVelo(_smooth_velo_seq_end_velo);
                    if (_smooth_velo_seq_endacc_flg) {
                        setAcce(0);
                    }
                    _smooth_velo_seq_progress++;
                    _smooth_velo_seq_flg = false; //おしまい
                }
            }
        }
    } else {
        _smooth_velo_seq_progress = -1;
    }

    if (_smooth_velo_seq_flg) {
        if (_smooth_velo_seq_target_frames < 0) {
            _smooth_velo_seq_distance+=ABS(_velo);
        } else {
            _smooth_velo_seq_frame_of_spent++;
        }
    } else {

    }


    //Actorに反映
    (*_pVariable)+= _velo;
}


template<class T>
void GgafDynamicVariable<T>::forceVeloRange(T prm_velo01, T prm_velo02) {
    if (prm_velo01 < prm_velo02) {
        _veloTop = prm_velo02;
        _veloBottom = prm_velo01;
    } else {
        _veloTop = prm_velo01;
        _veloBottom = prm_velo02;
    }
    setVelo(_velo); //再設定して範囲内に補正
}

template<class T>
void GgafDynamicVariable<T>::setVelo(T prm_velo) {
    if (prm_velo > _veloTop) {
        _velo = _veloTop;
    } else if (prm_velo < _veloBottom) {
        _velo = _veloBottom;
    } else {
        _velo = prm_velo;
    }
}

template<class T>
void GgafDynamicVariable<T>::addVelo(T prm_velo) {
    _velo += prm_velo;
    if (_velo > _veloTop) {
        _velo = _veloTop;
    } else if (_velo < _veloBottom) {
        _velo = _veloBottom;
    }
}

template<class T>
void GgafDynamicVariable<T>::setAcce(T prm_acce) {
    if (prm_acce > _acceTop) {
        _acce = _acceTop;
    } else if (prm_acce < _acceBottom) {
        _acce = _acceBottom;
    } else {
        _acce = prm_acce;
    }
}

template<class T>
void GgafDynamicVariable<T>::addAcce(T prm_acce) {
    setAcce(_acce + prm_acce);
}

template<class T>
void GgafDynamicVariable<T>::forceAcceRange(T prm_acce01, T prm_acce02) {
    if (prm_acce01 < prm_acce02) {
        _acceTop = prm_acce02;
        _acceBottom = prm_acce01;
    } else {
        _acceTop = prm_acce01;
        _acceBottom = prm_acce02;
    }
    setAcce(_acce); //再設定して範囲内に補正
}
template<class T>
void GgafDynamicVariable<T>::setAcceToStop(T prm_target_distance) {
    // a = -(Vo^2) / 2D
    _acce  =  -(1.0*_velo*_velo) / (2.0*prm_target_distance);
    if (_acce < 0) {
        _acce += 1;
    } else {
        _acce -= 1;
    }
    //(frame)((2.0*prm_target_distance) / _velo); //使用フレーム数
}

template<class T>
void GgafDynamicVariable<T>::setAcceBy_tv(int prm_target_frames, T prm_target_velo) {
    //a = (Vt-Vo) / Te
    _acce = (prm_target_velo - _velo) / (1.0f*prm_target_frames);
}

template<class T>
void GgafDynamicVariable<T>::setAcceBy_Dv(T prm_target_distance, T prm_target_velo) {
    // a = (Vt^2 - Vo^2) / 2D
    _acce =  ((1.0f*prm_target_velo*prm_target_velo) - (1.0f*_velo*_velo)) / (2.0f*prm_target_distance);
    if (_acce < 0) {
        _acce += 1;
    } else {
        _acce -= 1;
    }
    //(frame)((1.0*prm_target_velo - _velo) / _acce); //使用フレーム数

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
    //      = (Vo Tc + Vt Te - Vt Tc) / 2    ・・・①
    //
    //    直線 v = a t + Vo において v = 0 → t = Tc であるので
    //    0 = a Tc + Vo
    //    Tc = -Vo / a
    //    これを ① へ代入
    //    D = (Vo (-Vo / a) + Vt Te - Vt (-Vo / a)) / 2 ・・・②
    //    また a = (Vt - Vo) / Te であるので
    //    Te = (Vt - Vo) / a これを ② へ代入
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

template<class T>
void GgafDynamicVariable<T>::execSmoothSequence(T prm_end_velo, T prm_target_distance,
                                         int prm_target_frames, float prm_p1, float prm_p2,
                                         bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = prm_target_distance;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = prm_target_frames;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_progress = 0;

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
    _smooth_velo_seq_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_velo) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

template<class T>
void GgafDynamicVariable<T>::execSmoothSequenceD(T prm_top_velo, T prm_end_velo,
                                          T prm_target_distance, float prm_p1, float prm_p2,
                                          bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_velo_seq_top_velo = prm_top_velo;
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = prm_target_distance;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = (int)(prm_target_distance*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_distance*prm_p2);
    _smooth_velo_seq_progress = 0;
}

template<class T>
void GgafDynamicVariable<T>::execSmoothSequenceT(T prm_top_velo, T prm_end_velo,
                                          int prm_target_frames, float prm_p1, float prm_p2,
                                          bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_velo_seq_top_velo = prm_top_velo;
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = 0;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = prm_target_frames;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_progress = 0;
}


template<class T>
GgafDynamicVariable<T>::~GgafDynamicVariable() {
}

}
#endif /*GGAFDYNAMICVARIABLE_H_*/
