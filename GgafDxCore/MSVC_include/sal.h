//【sal.h がなぜこんなところにあるのですか忘備録メモ】
//
//前提として、本プログラムはGCC(MINGW環境のGCC4.X w32 & w64)、VC++2005、VC++2008、VC++2010 の x86 & x64 で
//コンパイル及び実行出来るように目指している。
//VC++では問題ないが、MINGW-GCCでコンパイルする際に、本ヘッダファイルは必要となる。
//
//DirectX SDK August 2009 以降、DirectXのヘッダーコード内で、直接VC用ヘッダファイル("sal.h"等)をincludeしているコードが現れた！。
//ヘッダーパスの優先順位を調整しても、どうにもこうにも回避できず、もはや DirectX SDK + MINGW のみでコンパイル出来なくなった（と思う）。
//しかし調べていく内に、
//「必要なVCのヘッダは sal.h 一つだけでなんとかなるんじゃないか・・・？。」
//と、疑心暗鬼にかかり、sal.h をインクルードパスの通った場所にコピーして、なんとかコンパイルしていた。そのうち、
//「sal.h の #define 定義は、GCCでは全部空実装で問題無いんじゃないのか？」
//という身勝手な疑心暗鬼にまたもかかってしまった。
//そこで、コンパイルが通るように、sal.h の define定義を空定義にしまくったファイルを MINGW用の sal.h（本ファイル）とすることにした。
//VCでコンパイルする場合、本ファイルが参照されないようにインクルードパスを調整する。
//MINGW-GCCでコンパイルする場合、本ファイルが参照さるようにインクルードパスを通す。
//
//いいじゃないかと思った時、別の問題が発生。
//GCC では、最近 C++コンパイルの場合
//
//#define NULL __null
//
//となっている。で、 __null の定義はどこにもない。いろいろ実験した結果、__null は埋め込み定数のようである。
//64bit環境で sizeof は自動的に8バイトになる、__null は GCC 独特のものだと考えている。
//だがしかし、sal.h になんと __null がなんか別のものに #define 定義されているぽいのを発見した。
//そして案の定、DirectXヘッダの dsound.h 内で、__null の記述がある。(↓例)
//
//extern HRESULT WINAPI DirectSoundCreate(__in_opt LPCGUID pcGuidDevice, __deref_out LPDIRECTSOUND *ppDS, __null LPUNKNOWN pUnkOuter);
//
//つまり __null は、GCC では埋め込み定数。VC ではマクロという別の扱いになっているのだ。あ～って感じ。GCCの時にコンパイルできん。
//で、調べていくうちに、GCCでコンパイル時、 dsound.h 内では
//「__null  → 何もない。という定義状態でたぶん問題ない」
//と思ったので、GCCの場合のみ #include <dsound.h> の前後にプリプロセッサで
//
//#ifdef __GNUG__
//    #define __null
//#endif
//#include <dsound.h>  //←sal.h を include する
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif
//
//という対処を行なっている。
//GCCでコンパイル時
//
//#define __null
//
//とすると 「__null  → 何もない」という状況になり、その状況下で
//
//#undef __null
//
//と記述しすると、元の __null 定義に戻る。GCCに限っては #undef で __null が未定義になってしまうわけではないようだ。
//すこし奇妙な気分だが、たぶん __null は特別な定数であって、マクロでは無いから今はこうなるんだと思われる！
//__null を内部使用しているDirectXヘッダファイル等があれば、そのヘッダの前後に上記対策を付与しなくてはならない。が、
//幸い、私の影響範囲は dsound.h のみで大丈夫そうだった。
//#undef __in と #undef __out は、GCC ヘッダコードで、ローカル変数名で __in , __out という名前が使用されている箇所が
//あるためだ。無効にしておかないと怒られる。
//
//よし・・・、コンパイルが通ったっと・・・、なんとも不細工である。
//TODO:しばらくこれでいいのじゃないかなぁ～！！ ＼(T_T)／
//TODO:最近 mingw-w64 のライブラリヘッダに、独自の"sal.h"が加わった・・・。毎回消すか、どうしようか。

#ifndef MY_SAL_H_
#define MY_SAL_H_
//Mingw-GCC用にコンパイルが通るように空定義
#define __ecount(size)
#define __bcount(size)
#define __in
#define __in_ecount(size)
#define __in_bcount(size)
#define __in_z
#define __in_ecount_z(size)
#define __in_bcount_z(size)
#define __in_nz
#define __in_ecount_nz(size)
#define __in_bcount_nz(size)
#define __out
#define __out_ecount(size)
#define __out_bcount(size)
#define __out_ecount_part(size,length)
#define __out_bcount_part(size,length)
#define __out_ecount_full(size)
#define __out_bcount_full(size)
#define __out_z
#define __out_z_opt
#define __out_ecount_z(size)
#define __out_bcount_z(size)
#define __out_ecount_part_z(size,length)
#define __out_bcount_part_z(size,length)
#define __out_ecount_full_z(size)
#define __out_bcount_full_z(size)
#define __out_nz
#define __out_nz_opt
#define __out_ecount_nz(size)
#define __out_bcount_nz(size)
#define __inout
#define __inout_ecount(size)
#define __inout_bcount(size)
#define __inout_ecount_part(size,length)
#define __inout_bcount_part(size,length)
#define __inout_ecount_full(size)
#define __inout_bcount_full(size)
#define __inout_z
#define __inout_ecount_z(size)
#define __inout_bcount_z(size)
#define __inout_nz
#define __inout_ecount_nz(size)
#define __inout_bcount_nz(size)
#define __ecount_opt(size)
#define __bcount_opt(size)
#define __in_opt
#define __in_ecount_opt(size)
#define __in_bcount_opt(size)
#define __in_z_opt
#define __in_ecount_z_opt(size)
#define __in_bcount_z_opt(size)
#define __in_nz_opt
#define __in_ecount_nz_opt(size)
#define __in_bcount_nz_opt(size)
#define __out_opt
#define __out_ecount_opt(size)
#define __out_bcount_opt(size)
#define __out_ecount_part_opt(size,length)
#define __out_bcount_part_opt(size,length)
#define __out_ecount_full_opt(size)
#define __out_bcount_full_opt(size)
#define __out_ecount_z_opt(size)
#define __out_bcount_z_opt(size)
#define __out_ecount_part_z_opt(size,length)
#define __out_bcount_part_z_opt(size,length)
#define __out_ecount_full_z_opt(size)
#define __out_bcount_full_z_opt(size)
#define __out_ecount_nz_opt(size)
#define __out_bcount_nz_opt(size)
#define __inout_opt
#define __inout_ecount_opt(size)
#define __inout_bcount_opt(size)
#define __inout_ecount_part_opt(size,length)
#define __inout_bcount_part_opt(size,length)
#define __inout_ecount_full_opt(size)
#define __inout_bcount_full_opt(size)
#define __inout_z_opt
#define __inout_ecount_z_opt(size)
#define __inout_ecount_z_opt(size)
#define __inout_bcount_z_opt(size)
#define __inout_nz_opt
#define __inout_ecount_nz_opt(size)
#define __inout_bcount_nz_opt(size)
#define __deref_ecount(size)
#define __deref_bcount(size)
#define __deref_out
#define __deref_out_ecount(size)
#define __deref_out_bcount(size)
#define __deref_out_ecount_part(size,length)
#define __deref_out_bcount_part(size,length)
#define __deref_out_ecount_full(size)
#define __deref_out_bcount_full(size)
#define __deref_out_z
#define __deref_out_ecount_z(size)
#define __deref_out_bcount_z(size)
#define __deref_out_nz
#define __deref_out_ecount_nz(size)
#define __deref_out_bcount_nz(size)
#define __deref_inout
#define __deref_inout_z
#define __deref_inout_ecount(size)
#define __deref_inout_bcount(size)
#define __deref_inout_ecount_part(size,length)
#define __deref_inout_bcount_part(size,length)
#define __deref_inout_ecount_full(size)
#define __deref_inout_bcount_full(size)
#define __deref_inout_z
#define __deref_inout_ecount_z(size)
#define __deref_inout_bcount_z(size)
#define __deref_inout_nz
#define __deref_inout_ecount_nz(size)
#define __deref_inout_bcount_nz(size)
#define __deref_ecount_opt(size)
#define __deref_bcount_opt(size)
#define __deref_out_opt
#define __deref_out_ecount_opt(size)
#define __deref_out_bcount_opt(size)
#define __deref_out_ecount_part_opt(size,length)
#define __deref_out_bcount_part_opt(size,length)
#define __deref_out_ecount_full_opt(size)
#define __deref_out_bcount_full_opt(size)
#define __deref_out_z_opt
#define __deref_out_ecount_z_opt(size)
#define __deref_out_bcount_z_opt(size)
#define __deref_out_nz_opt
#define __deref_out_ecount_nz_opt(size)
#define __deref_out_bcount_nz_opt(size)
#define __deref_inout_opt
#define __deref_inout_ecount_opt(size)
#define __deref_inout_bcount_opt(size)
#define __deref_inout_ecount_part_opt(size,length)
#define __deref_inout_bcount_part_opt(size,length)
#define __deref_inout_ecount_full_opt(size)
#define __deref_inout_bcount_full_opt(size)
#define __deref_inout_z_opt
#define __deref_inout_ecount_z_opt(size)
#define __deref_inout_bcount_z_opt(size)
#define __deref_inout_nz_opt
#define __deref_inout_ecount_nz_opt(size)
#define __deref_inout_bcount_nz_opt(size)
#define __deref_opt_ecount(size)
#define __deref_opt_bcount(size)
#define __deref_opt_out
#define __deref_opt_out_z
#define __deref_opt_out_ecount(size)
#define __deref_opt_out_bcount(size)
#define __deref_opt_out_ecount_part(size,length)
#define __deref_opt_out_bcount_part(size,length)
#define __deref_opt_out_ecount_full(size)
#define __deref_opt_out_bcount_full(size)
#define __deref_opt_inout
#define __deref_opt_inout_ecount(size)
#define __deref_opt_inout_bcount(size)
#define __deref_opt_inout_ecount_part(size,length)
#define __deref_opt_inout_bcount_part(size,length)
#define __deref_opt_inout_ecount_full(size)
#define __deref_opt_inout_bcount_full(size)
#define __deref_opt_inout_z
#define __deref_opt_inout_ecount_z(size)
#define __deref_opt_inout_bcount_z(size)
#define __deref_opt_inout_nz
#define __deref_opt_inout_ecount_nz(size)
#define __deref_opt_inout_bcount_nz(size)
#define __deref_opt_ecount_opt(size)
#define __deref_opt_bcount_opt(size)
#define __deref_opt_out_opt
#define __deref_opt_out_ecount_opt(size)
#define __deref_opt_out_bcount_opt(size)
#define __deref_opt_out_ecount_part_opt(size,length)
#define __deref_opt_out_bcount_part_opt(size,length)
#define __deref_opt_out_ecount_full_opt(size)
#define __deref_opt_out_bcount_full_opt(size)
#define __deref_opt_out_z_opt
#define __deref_opt_out_ecount_z_opt(size)
#define __deref_opt_out_bcount_z_opt(size)
#define __deref_opt_out_nz_opt
#define __deref_opt_out_ecount_nz_opt(size)
#define __deref_opt_out_bcount_nz_opt(size)
#define __deref_opt_inout_opt
#define __deref_opt_inout_ecount_opt(size)
#define __deref_opt_inout_bcount_opt(size)
#define __deref_opt_inout_ecount_part_opt(size,length)
#define __deref_opt_inout_bcount_part_opt(size,length)
#define __deref_opt_inout_ecount_full_opt(size)
#define __deref_opt_inout_bcount_full_opt(size)
#define __deref_opt_inout_z_opt
#define __deref_opt_inout_ecount_z_opt(size)
#define __deref_opt_inout_bcount_z_opt(size)
#define __deref_opt_inout_nz_opt
#define __deref_opt_inout_ecount_nz_opt(size)
#define __deref_opt_inout_bcount_nz_opt(size)

#endif /**MY_SAL_H_*/
