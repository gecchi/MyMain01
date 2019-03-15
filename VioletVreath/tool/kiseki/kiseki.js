msOpMax=5;// マウスストーカーの数
msOpHis=10;// マウスの軌跡を覚える数
msOMx=new Array(msOpHis);// マウスの軌跡の座標
msOMy=new Array(msOpHis);
msOr=new Array(msOpMax);// 履歴の何番目を読むかの変数
msOw=0;// マウスの軌跡を書き込む位置
msOstart=true;// 初めて実行したかのフラグ
mouse_down=false;
out_put="";

for(var i=0;i<msOpMax;i++)
{
   document.write("<img src='kiseki.gif' style='position:absolute;left:-200px;' name='msop"+i+"'>");
}
msOpInit();

function msOpInit()// 初期設定
{

   for(var i=0;i<msOpMax;i++)// マウスの座標履歴から読む位置を設定
   {
      msOr[i]=Math.floor(msOpHis/(msOpMax+1)*(i+1))-1;// 個数に等間隔に設定
   }
   document.onmousemove=msOpMove;// イベント発生時に実行する関数の設定
   document.onmousedown = function(){ mouse_down=true };
   document.onmouseup = function(){
     mouse_down=false;
     out_put "-------------------\n" += out_put;
     var mogera = document.getElementById("mogera");
     mogera.value=out_put;
     mogera.select();
     document.execCommand("copy");
     out_put="";

   };
}




function msOpMove(e)// マウスが動くとここが実行されます
{
    if (mouse_down == false) {
        return;
    }
   var mx,my,msWx,msWy;// ローカル変数の宣言

  mx=document.body.scrollLeft+event.clientX;// マウスの座標を取得
  my=document.body.scrollTop+event.clientY;
  msWx=window.document.body.clientWidth+document.body.scrollLeft;
  msWy=window.document.body.clientHeight+document.body.scrollTop;
   out_put += mx+","+my+"\n";
   msOMx[msOw]=mx;// マウスの座標を履歴に書き込み
   msOMy[msOw]=my;
   msOw++;// 書き込む位置の設定
   if(msOw>=msOpHis){msOw=0;}
   if(msOstart==true)// 初めて実行された時にストーカーの座標を初期化
   {
      for(var i=0;i<msOpHis;i++)
      {
         msOMx[i]=mx;
         msOMy[i]=my;
      }
      msOstart=false;
   }
   for(var i=0;i<msOpMax;i++)// ストーカーの移動
   {
      mx=msOMx[msOr[i]];// 読み出す位置からマウス移動履歴を取得
      my=msOMy[msOr[i]];
      msOr[i]++;// 読み出し位置をずらす
      if(msOr[i]>=msOpHis){msOr[i]=0;}// 最後まで読んだら始めに戻す
      if(mx>msWx-document.images["msop"+i].width){mx=-100;}
      if(my>msWy-document.images["msop"+i].height){my=-100;}
      document.images["msop"+i].style.left=mx;// 画像の座標を変更
      document.images["msop"+i].style.top=my;
   }
}
