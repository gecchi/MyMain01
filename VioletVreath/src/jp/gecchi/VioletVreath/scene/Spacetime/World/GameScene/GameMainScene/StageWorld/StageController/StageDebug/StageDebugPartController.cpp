#include "StageDebugPartController.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebug.h"
#include "part/StageDebugPart01.h"
#include "part/StageDebugPart02.h"
#include "part/StageDebugPart03.h"
#include "part/StageDebugPartClimax.h"
#include "part/StageDebugPartWall.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_FAINAL ,
    PHASE_BANPEI,
};

StageDebugPartController::StageDebugPartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "StageDebugPartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,5,15,25,35,45,55,65,75,85,95,100,105,115,125,135,145,155,165,175,185,195,200,205,215,225,235,245,255,265,275,285,295,300,305,315,325,335,345,355,365,375,385,395,400,405,415,425,435,445,455,465,475,485,495,500,505,515,525,535,545,555,565,575,585,595,600,605,615,625,635,645,655,665,675,685,695,700,705,715,725,735,745,755,765,775,785,795,800,805,815,825,835,845,855,865,875,885,895,900,905,915,925,935,945,955,965,975,985,995,1000,1005,1015,1025,1035,1045,1055,1065,1075,1085,1095,1100,1105,1115,1125,1135,1145,1155,1165,1175,1185,1195,1200,1205,1215,1225,1235,1245,1255,1265,1275,1285,1295,1300,1305,1315,1325,1335,1345,1355,1365,1375,1385,1395,1400,1405,1415,1425,1435,1445,1455,1465,1475,1485,1495,1500,1505,1515,1525,1535,1545,1555,1565,1575,1585,1595,1600,1605,1615,1625,1635,1645,1655,1665,1675,1685,1695,1700,1705,1715,1725,1735,1745,1755,1765,1775,1785,1795,1800,1805,1815,1825,1835,1845,1855,1865,1875,1885,1895,1900,1905,1915,1925,1935,1945,1955,1965,1975,1985,1995,2000,2005,2015,2025,2035,2045,2055,2065,2075,2085,2095,2105,2115,2125,2135,2145,2155,2165,2175,2185,2195,2205,2215,2225,2235,2245,2255,2265,2275,2285,2295,2305,2315,2325,2335,2345,2355,2365,2375,2385,2395,2405,2415,2425,2435,2445,2455,2465,2475,2485,2495,2500,2505,2515,2525,2535,2545,2555,2565,2575,2585,2595,2605,2615,2625,2635,2645,2655,2665,2675,2685,2695,2705,2715,2725,2735,2745,2755,2765,2775,2785,2795,2805,2815,2825,2835,2845,2855,2865,2875,2885,2895,2905,2915,2925,2935,2945,2955,2965,2975,2985,2995,3005,3015,3025,3035,3045,3055,3065,3075,3085,3095,3105,3115,3125,3135,3145,3155,3165,3175,3185,3195,3205,3215,3225,3235,3245,3255,3265,3275,3285,3295,3305,3315,3325,3335,3345,3355,3365,3375,3385,3395,3405,3415,3425,3435,3445,3455,3465,3475,3485,3495,3505,3515,3525,3535,3545,3555,3565,3575,3585,3595,3605,3615,3625,3635,3645,3655,3665,3675,3685,3695,3705,3715,3725,3735,3745,3755,3765,3775,3785,3795,3805,3815,3825,3835,3845,3855,3865,3875,3885,3895,3900,3905,3915,3925,3935,3945,3955,3965,3975,3985,3995,4005,4015,4025,4035,4045,4055,4065,4075,4085,4095,4105,4115,4125,4135,4145,4155,4165,4175,4185,4195,4205,4215,4225,4235,4245,4255,4265,4275,4285,4295,4305,4315,4325,4335,4345,4355,4365,4375,4385,4395,4405,4415,4425,4435,4445,4455,4465,4475,4485,4495,4500,4505,4515,4525,4535,4545,4555,4565,4575,4585,4595,4605,4615,4625,4635,4645,4655,4665,4675,4685,4695,4705,4715,4725,4735,4745,4755,4765,4775,4785,4795,4805,4815,4825,4835,4845,4855,4865,4875,4885,4895,4905,4915,4925,4935,4945,4955,4965,4975,4985,4995,5005,5015,5025,5035,5045,5055,5065,5075,5085,5095,5100,5105,5115,5125,5135,5145,5155,5165,5175,5185,5195,5205,5215,5225,5235,5245,5255,5265,5275,5285,5295,5305,5315,5325,5335,5345,5355,5365,5375,5385,5395,5405,5415,5425,5435,5445,5455,5465,5475,5485,5495,5505,5515,5525,5535,5545,5555,5565,5575,5585,5595,5605,5615,5625,5635,5645,5655,5665,5675,5685,5695,5705,5715,5725,5735,5745,5755,5765,5775,5785,5795,5805,5815,5825,5835,5845,5855,5865,5875,5885,5895,5900,5905,5915,5925,5935,5945,5955,5965,5975,5985,5995,6000,6005,6015,6025,6035,6045,6055,6065,6075,6085,6095,6105,6115,6125,6135,6145,6155,6165,6175,6185,6195,6205,6215,6225,6235,6245,6255,6265,6275,6285,6295,6305,6315,6325,6335,6345,6355,6365,6375,6385,6395,6405,6415,6425,6435,6445,6455,6465,6475,6485,6495,6500,6505,6515,6525,6535,6545,6555,6565,6575,6585,6595,6605,6615,6625,6635,6645,6655,6665,6675,6685,6695,6705,6715,6725,6735,6745,6755,6765,6775,6785,6795,6805,6815,6825,6835,6845,6855,6865,6875,6885,6895,6905,6915,6925,6935,6945,6955,6965,6975,6985,6995,7005,7015,7025,7035,7045,7055,7065,7075,7085,7095,7105,7115,7125,7135,7145,7155,7165,7175,7185,7195,7200,7205,7215,7225,7235,7245,7255,7265,7275,7285,7295,7305,7315,7325,7335,7345,7355,7365,7375,7385,7395,7405,7415,7425,7435,7445,7455,7465,7475,7485,7495,7505,7515,7525,7535,7545,7555,7565,7575,7585,7595,7605,7615,7625,7635,7645,7655,7665,7675,7685,7695,7705,7715,7725,7735,7745,7755,7765,7775,7785,7795,7805,7815,7825,7835,7845,7855,7865,7875,7885,7895,7900,7905,7915,7925,7935,7945,7955,7965,7975,7985,7995,8005,8015,8025,8035,8045,8055,8065,8075,8085,8095,8100,8105,8115,8125,8135,8145,8155,8165,8175,8185,8195,8205,8215,8225,8235,8245,8255,8265,8275,8285,8295,8305,8315,8325,8335,8345,8355,8365,8375,8385,8395,8405,8415,8425,8435,8445,8455,8465,8475,8485,8495,8500,8505,8515,8525,8535,8545,8555,8565,8575,8585,8595,8605,8615,8625,8635,8645,8655,8665,8675,8685,8695,8705,8715,8725,8735,8745,8755,8765,8775,8785,8795,8805,8815,8825,8835,8845,8855,8865,8875,8885,8895,8905,8915,8925,8935,8945,8955,8965,8975,8985,8995,9005,9015,9025,9035,9045,9055,9065,9075,9085,9095,9105,9115,9125,9135,9145,9155,9165,9175,9185,9195,9205,9215,9225,9235,9245,9255,9265,9275,9285,9295,9305,9315,9325,9335,9345,9355,9365,9375,9385,9395,9405,9415,9425,9435,9445,9455,9465,9475,9485,9495,9505,9515,9525,9535,9545,9555,9565,9575,9585,9595,9605,9615,9625,9635,9645,9655,9665,9675,9685,9695,9705,9715,9725,9735,9745,9755,9765,9775,9785,9795,9805,9815,9825,9835,9845,9855,9865,9875,9885,9895,9900,9905,9915,9925,9935,9945,9955,9965,9975,9985,9995,10005,10015,10025,10035,10045,10055,10065,10075,10085,10095,10105,10115,10125,10135,10145,10155,10165,10175,10185,10195,10205,10215,10225,10235,10245,10255,10265,10275,10285,10295,10305,10315,10325,10335,10345,10355,10365,10375,10385,10395,10405,10415,10425,10435,10445,10455,10465,10475,10485,10495,10500,10505,10515,10525,10535,10545,10555,10565,10575,10585,10595,10605,10615,10625,10635,10645,10655,10665,10675,10685,10695,10705,10715,10725,10735,10745,10755,10765,10775,10785,10795,10805,10815,10825,10835,10845,10855,10865,10875,10885,10895,10905,10915,10925,10935,10945,10955,10965,10975,10985,10995,11005,11015,11025,11035,11045,11055,11065,11075,11085,11095,11105,11115,11125,11135,11145,11155,11165,11175,11185,11195,11205,11215,11225,11235,11245,11255,11265,11275,11285,11295,11305,11315,11325,11335,11345,11355,11365,11375,11385,11395,11405,11415,11425,11435,11445,11455,11465,11475,11485,11495,11505,11515,11525,11535,11545,11555,11565,11575,11585,11595,11605,11615,11625,11635,11645,11655,11665,11675,11685,11695,11705,11715,11725,11735,11745,11755,11765,11775,11785,11795,11805,11815,11825,11835,11845,11855,11865,11875,11885,11895,11900,11905,11915,11925,11935,11945,11955,11965,11975,11985,11995,12005,12015,12025,12035,12045,12055,12065,12075,12085,12095,12105,12115,12125,12135,12145,12155,12165,12175,12185,12195,12205,12215,12225,12235,12245,12255,12265,12275,12285,12295,12305,12315,12325,12335,12345,12355,12365,12375,12385,12395,12405,12415,12425,12435,12445,12455,12465,12475,12485,12495,12500,12505,12515,12525,12535,12545,12555,12565,12575,12585,12595,12605,12615,12625,12635,12645,12655,12665,12675,12685,12695,12705,12715,12725,12735,12745,12755,12765,12775,12785,12795,12805,12815,12825,12835,12845,12855,12865,12875,12885,12895,12905,12915,12925,12935,12945,12955,12965,12975,12985,12995,13005,13015,13025,13035,13045,13055,13065,13075,13085,13095,13105,13115,13125,13135,13145,13155,13165,13175,13185,13195,13205,13215,13225,13235,13245,13255,13265,13275,13285,13295,13305,13315,13325,13335,13345,13355,13365,13375,13385,13395,13405,13415,13425,13435,13445,13455,13465,13475,13485,13495,13505,13515,13525,13535,13545,13555,13565,13575,13585,13595,13605,13615,13625,13635,13645,13655,13665,13675,13685,13695,13705,13715,13725,13735,13745,13755,13765,13775,13785,13795,13805,13815,13825,13835,13845,13855,13865,13875,13885,13895,13900,13905,13915,13925,13935,13945,13955,13965,13975,13985,13995,14005,14015,14025,14035,14045,14055,14065,14075,14085,14095,14105,14115,14125,14135,14145,14155,14165,14175,14185,14195,14205,14215,14225,14235,14245,14255,14265,14275,14285,14295,14305,14315,14325,14335,14345,14355,14365,14375,14385,14395,14405,14415,14425,14435,14445,14455,14465,14475,14485,14495,14500,14505,14515,14525,14535,14545,14555,14565,14575,14585,14595,14605,14615,14625,14635,14645,14655,14665,14675,14685,14695,14705,14715,14725,14735,14745,14755,14765,14775,14785,14795,14805,14815,14825,14835,14845,14855,14865,14875,14885,14895,14905,14915,14925,14935,14945,14955,14965,14975,14985,14995,15005,15015,15025,15035,15045,15055,15065,15075,15085,15095,15105,15115,15125,15135,15145,15155,15165,15175,15185,15195,15205,15215,15225,15235,15245,15255,15265,15275,15285,15295,15305,15315,15325,15335,15345,15355,15365,15375,15385,15395,15405,15415,15425,15435,15445,15455,15465,15475,15485,15495,15505,15515,15525,15535,15545,15555,15565,15575,15585,15595,15605,15615,15625,15635,15645,15655,15665,15675,15685,15695,15705,15715,15725,15735,15745,15755,15765,15775,15785,15795,15805,15815,15825,15835,15845,15855,15865,15875,15885,15895,15900,15905,15915,15925,15935,15945,15955,15965,15975,15985,15995,16005,16015,16025,16035,16045,16055,16065,16075,16085,16095,16105,16115,16125,16135,16145,16155,16165,16175,16185,16195,16205,16215,16225,16235,16245,16255,16265,16275,16285,16295,16305,16315,16325,16335,16345,16355,16365,16375,16385,16395,16405,16415,16425,16435,16445,16455,16465,16475,16485,16495,16500,16505,16515,16525,16535,16545,16555,16565,16575,16585,16595,16605,16615,16625,16635,16645,16655,16665,16675,16685,16695,16705,16715,16725,16735,16745,16755,16765,16775,16785,16795,16805,16815,16825,16835,16845,16855,16865,16875,16885,16895,16905,16915,16925,16935,16945,16955,16965,16975,16985,16995,17005,17015,17025,17035,17045,17055,17065,17075,17085,17095,17105,17115,17125,17135,17145,17155,17165,17175,17185,17195,17205,17215,17225,17235,17245,17255,17265,17275,17285,17295,17305,17315,17325,17335,17345,17355,17365,17375,17385,17395,17405,17415,17425,17435,17445,17455,17465,17475,17485,17495,17505,17515,17525,17535,17545,17555,17565,17575,17585,17595,17605,17615,17625,17635,17645,17655,17665,17675,17685,17695,17705,17715,17725,17735,17745,17755,17765,17775,17785,17795,17805,17815,17825,17835,17845,17855,17865,17875,17885,17895,17900,17905,17915,17925,17935,17945,17955,17965,17975,17985,17995,18005,18015,18025,18035,18045,18055,18065,18075,18085,18095,18105,18115,18125,18135,18145,18155,18165,18175,18185,18195,18205,18215,18225,18235,18245,18255,18265,18275,18285,18295,18305,18315,18325,18335,18345,18355,18365,18375,18385,18395,18405,18415,18425,18435,18445,18455,18465,18475,18485,18495,18500,18505,18515,18525,18535,18545,18555,18565,18575,18585,18595,18605,18615,18625,18635,18645,18655,18665,18675,18685,18695,18705,18715,18725,18735,18745,18755,18765,18775,18785,18795,18805,18815,18825,18835,18845,18855,18865,18875,18885,18895,18905,18915,18925,18935,18945,18955,18965,18975,18985,18995,19005,19015,19025,19035,19045,19055,19065,19075,19085,19095,19105,19115,19125,19135,19145,19155,19165,19175,19185,19195,19205,19215,19225,19235,19245,19255,19265,19275,19285,19295,19305,19315,19325,19335,19345,19355,19365,19375,19385,19395,19400,19405,19415,19425,19435,19445,19455,19465,19475,19485,19495,19505,19515,19525,19535,19545,19555,19565,19575,19585,19595,19605,19615,19625,19635,19645,19655,19665,19675,19685,19695,19700,19705,19715,19725,19735,19745,19755,19765,19775,19785,19795,19805,19815,19825,19835,19845,19855,19865,19875,19885,19895,19900,19905,19915,19925,19935,19945,19955,19965,19975,19985,19995,20000,20005,20015,20025,20035,20045,20055,20065,20075,20085,20095,20105,20115,20125,20135,20145,20155,20165,20175,20185,20195,20205,20215,20225,20235,20245,20255,20265,20275,20285,20295,20300,20305,20315,20325,20335,20345,20355,20365,20375,20385,20395,20405,20415,20425,20435,20445,20455,20465,20475,20485,20495,20500,20505,20515,20525,20535,20545,20555,20565,20575,20585,20595,20605,20615,20625,20635,20645,20655,20665,20675,20685,20695,20705,20715,20725,20735,20745,20755,20765,20775,20785,20795,20805,20815,20825,20835,20845,20855,20865,20875,20885,20895,20905,20915,20925,20935,20945,20955,20965,20975,20985,20995,21005,21015,21025,21035,21045,21055,21065,21075,21085,21095,21105,21115,21125,21135,21145,21155,21165,21175,21185,21195,21205,21215,21225,21235,21245,21255,21265,21275,21285,21295,21305,21315,21325,21335,21345,21355,21365,21375,21385,21395,21405,21415,21425,21435,21445,21455,21465,21475,21485,21495,21505,21515,21525,21535,21545,21555,21565,21575,21585,21595,21605,21615,21625,21635,21645,21655,21665,21675,21685,21695,21705,21715,21725,21735,21745,21755,21765,21775,21785,21795,21805,21815,21825,21835,21845,21855,21865,21875,21885,21895,21900,21905,21915,21925,21935,21945,21955,21965,21975,21985,21995,22005,22015,22025,22035,22045,22055,22065,22075,22085,22095,22105,22115,22125,22135,22145,22155,22165,22175,22185,22195,22205,22215,22225,22235,22245,22255,22265,22275,22285,22295,22305,22315,22325,22335,22345,22355,22365,22375,22385,22395,22405,22415,22425,22435,22445,22455,22465,22475,22485,22495,22500,22505,22515,22525,22535,22545,22555,22565,22575,22585,22595,22605,22615,22625,22635,22645,22655,22665,22675,22685,22695,22705,22715,22725,22735,22745,22755,22765,22775,22785,22795,22805,22815,22825,22835,22845,22855,22865,22875,22885,22895,22905,22915,22925,22935,22945,22955,22965,22975,22985,22995,23005,23015,23025,23035,23045,23055,23065,23075,23085,23095,23105,23115,23125,23135,23145,23155,23165,23175,23185,23195,23205,23215,23225,23235,23245,23255,23265,23275,23285,23295,23305,23315,23325,23335,23345,23355,23365,23375,23385,23395,23405,23415,23425,23435,23445,23455,23465,23475,23485,23495,23505,23515,23525,23535,23545,23555,23565,23575,23585,23595,23605,23615,23625,23635,23645,23655,23665,23675,23685,23695,23705,23715,23725,23735,23745,23755,23765,23775,23785,23795,23805,23815,23825,23835,23845,23855,23865,23875,23885,23895,23900,23905,23915,23925,23935,23945,23955,23965,23975,23985,23995,24005,24015,24025,24035,24045,24055,24065,24075,24085,24095,24105,24115,24125,24135,24145,24155,24165,24175,24185,24195,24205,24215,24225,24235,24245,24255,24265,24275,24285,24295,24305,24315,24325,24335,24345,24355,24365,24375,24385,24395,24405,24415,24425,24435,24445,24455,24465,24475,24485,24495,24500,24505,24515,24525,24535,24545,24555,24565,24575,24585,24595,24605,24615,24625,24635,24645,24655,24665,24675,24685,24695,24705,24715,24725,24735,24745,24755,24765,24775,24785,24795,24805,24815,24825,24835,24845,24855,24865,24875,24885,24895,24905,24915,24925,24935,24945,24955,24965,24975,24985,24995,25005,25015,25025,25035,25045,25055,25065,25075,25085,25095,25105,25115,25125,25135,25145,25155,25165,25175,25185,25195,25205,25215,25225,25235,25245,25255,25265,25275,25285,25295,25305,25315,25325,25335,25345,25355,25365,25375,25385,25395,25405,25415,25425,25435,25445,25455,25465,25475,25485,25495,25505,25515,25525,25535,25545,25555,25565,25575,25585,25595,25605,25615,25625,25635,25645,25655,25665,25675,25685,25695,25705,25715,25725,25735,25745,25755,25765,25775,25785,25795,25805,25815,25825,25835,25845,25855,25865,25875,25885,25895,25900,25905,25915,25925,25935,25945,25955,25965,25975,25985,25995,26005,26015,26025,26035,26045,26055,26065,26075,26085,26095,26105,26115,26125,26135,26145,26155,26165,26175,26185,26195,26205,26215,26225,26235,26245,26255,26265,26275,26285,26295,26305,26315,26325,26335,26345,26355,26365,26375,26385,26395,26405,26415,26425,26435,26445,26455,26465,26475,26485,26495,26500,26505,26515,26525,26535,26545,26555,26565,26575,26585,26595,26605,26615,26625,26635,26645,26655,26665,26675,26685,26695,26705,26715,26725,26735,26745,26755,26765,26775,26785,26795,26805,26815,26825,26835,26845,26855,26865,26875,26885,26895,26905,26915,26925,26935,26945,26955,26965,26975,26985,26995,27005,27015,27025,27035,27045,27055,27065,27075,27085,27095,27105,27115,27125,27135,27145,27155,27165,27175,27185,27195,27205,27215,27225,27235,27245,27255,27265,27275,27285,27295,27305,27315,27325,27335,27345,27355,27365,27375,27385,27395,27405,27415,27425,27435,27445,27455,27465,27475,27485,27495,27505,27515,27525,27535,27545,27555,27565,27575,27585,27595,27605,27615,27625,27635,27645,27655,27665,27675,27685,27695,27705,27715,27725,27735,27745,27755,27765,27775,27785,27795,27805,27815,27825,27835,27845,27855,27865,27875,27885,27895,27900,27905,27915,27925,27935,27945,27955,27965,27975,27985,27995,28005,28015,28025,28035,28045,28055,28065,28075,28085,28095,28105,28115,28125,28135,28145,28155,28165,28175,28185,28195,28205,28215,28225,28235,28245,28255,28265,28275,28285,28295,28305,28315,28325,28335,28345,28355,28365,28375,28385,28395,28405,28415,28425,28435,28445,28455,28465,28475,28485,28495,28500,28505,28515,28525,28535,28545,28555,28565,28575,28585,28595,28605,28615,28625,28635,28645,28655,28665,28675,28685,28695,28705,28715,28725,28735,28745,28755,28765,28775,28785,28795,28805,28815,28825,28835,28845,28855,28865,28875,28885,28895,28905,28915,28925,28935,28945,28955,28965,28975,28985,28995,29005,29015,29025,29035,29045,29055,29065,29075,29085,29095,29105,29115,29125,29135,29145,29155,29165,29175,29185,29195,29205,29215,29225,29235,29245,29255,29265,29275,29285,29295,29305,29315,29325,29335,29345,29355,29365,29375,29385,29395,29405,29415,29425,29435,29445,29455,29465,29475,29485,29495,29505,29515,29525,29535,29545,29555,29565,29575,29585,29595,29605,29615,29625,29635,29645,29655,29665,29675,29685,29695,29705,29715,29725,29735,29745,29755,29765,29775,29785,29795,29805,29815,29825,29835,29845,29855,29865,29875,29885,29895,29900,29905,29915,29925,29935,29945,29955,29965,29975,29985,29995,30005,30015,30025,30035,30045,30055,30065,30075,30085,30095,30105,30115,30125,30135,30145,30155,30165,30175,30185,30195,30205,30215,30225,30235,30245,30255,30265,30275,30285,30295,30305,30315,30325,30335,30345,30355,30365,30375,30385,30395,30405,30415,30425,30435,30445,30455,30465,30475,30485,30495,30500,30505,30515,30525,30535,30545,30555,30565,30575,30585,30595,30605,30615,30625,30635,30645,30655,30665,30675,30685,30695,30705,30715,30725,30735,30745,30755,30765,30775,30785,30795,30805,30815,30825,30835,30845,30855,30865,30875,30885,30895,30905,30915,30925,30935,30945,30955,30965,30975,30985,30995,31005,31015,31025,31035,31045,31055,31065,31075,31085,31095,31100,31105,31115,31125,31135,31145,31155,31165,31175,31185,31195,31205,31215,31225,31235,31245,31255,31265,31275,31285,31295,31305,31315,31325,31335,31345,31355,31365,31375,31385,31395,31405,31415,31425,31435,31445,31455,31465,31475,31485,31495,31505,31515,31525,31535,31545,31555,31565,31575,31585,31595,31605,31615,31625,31635,31645,31655,31665,31675,31685,31695,31705,31715,31725,31735,31745,31755,31765,31775,31785,31795,31805,31815,31825,31835,31845,31855,31865,31875,31885,31895,31900,31905,31915,31925,31935,31945,31955,31965,31975,31985,31995,32000,32500,33900,34500,35900,36500,37900,38500,39700,39900,40300,40500,41900,42500,43900,44500,45900,46500,47900,48500,49900,50500,51900,52500,53900,54500,55900,56500,57900,58500};
	_paFrame_NextEvent = new frame[3290];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 3290;
	requestActor(10000004, EnemyOebiusController002);
	requestActor(10000005, EnemyOebiusController002);
	requestActor(10000020, EnemyErelmanController002);
	requestActor(10000021, EnemyErelmanController001);
	requestActor(10000022, EnemyErmione);
	requestActor(10000025, EnemyEtis);
	requestActor(10000026, EnemyEtis);
	requestActor(10000027, EnemyEtis);
	requestActor(10000028, EnemyEtis);
	requestActor(10000029, EnemyEtis);
	requestActor(10000030, EnemyEtis);
	requestActor(10000031, EnemyEtis);
	requestActor(10000032, EnemyEtis);
	requestActor(10000033, EnemyEtis);
	requestActor(10000034, EnemyEtis);
	requestActor(10000035, EnemyEtis);
	requestActor(10000036, EnemyEtis);
	requestActor(10000037, EnemyEtis);
	requestActor(10000038, EnemyEtis);
	requestActor(10000039, EnemyEtis);
	requestActor(10000040, EnemyEtis);
	requestActor(10000041, EnemyEtis);
	requestActor(10000042, EnemyEtis);
	requestActor(10000043, EnemyEtis);
	requestActor(10000044, EnemyEtis);
	requestActor(10000045, EnemyEtis);
	requestActor(10000046, EnemyEtis);
	requestActor(10000047, EnemyEtis);
	requestActor(10000048, EnemyEtis);
	requestActor(10000049, EnemyEtis);
	requestActor(10000050, EnemyEtis);
	requestActor(10000051, EnemyEtis);
	requestActor(10000052, EnemyEtis);
	requestActor(10000053, EnemyEtis);
	requestActor(10000054, EnemyEtis);
	requestActor(10000055, EnemyEtis);
	requestActor(10000056, EnemyEtis);
	requestActor(10000057, EnemyEtis);
	requestActor(10000058, EnemyEtis);
	requestActor(10000059, EnemyEtis);
	requestActor(10000060, EnemyEtis);
	requestActor(10000061, EnemyEtis);
	requestActor(10000062, EnemyEtis);
	requestActor(10000063, EnemyEtis);
	requestActor(10000064, EnemyEtis);
	requestActor(10000065, EnemyEtis);
	requestActor(10000066, EnemyEtis);
	requestActor(10000067, EnemyEtis);
	requestActor(10000068, EnemyEtis);
	requestActor(10000069, EnemyEtis);
	requestActor(10000070, EnemyEtis);
	requestActor(10000071, EnemyEtis);
	requestActor(10000072, EnemyEtis);
	requestActor(10000073, EnemyEtis);
	requestActor(10000074, EnemyEtis);
	requestActor(10000075, EnemyEtis);
	requestActor(10000076, EnemyEtis);
	requestActor(10000077, EnemyEtis);
	requestActor(10000078, EnemyEtis);
	requestActor(10000079, EnemyEtis);
	requestActor(10000080, EnemyEtis);
	requestActor(10000081, EnemyEtis);
	requestActor(10000082, EnemyEtis);
	requestActor(10000083, EnemyEtis);
	requestActor(10000084, EnemyEtis);
	requestActor(10003225, EnemyDrastea);
	requestActor(10003255, VarietyRatislavia002);
    // gen01 end
}

void StageDebugPartController::initialize() {
    getPhase()->reset(PHASE_INIT);
}

void StageDebugPartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000025);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000085, EnemyEtis);
				break;
			}
			case 15: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000026);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000086, EnemyEtis);
				break;
			}
			case 25: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000027);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000087, EnemyEtis);
				break;
			}
			case 35: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000028);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000088, EnemyEtis);
				break;
			}
			case 45: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000029);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000089, EnemyEtis);
				break;
			}
			case 55: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000030);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000090, EnemyEtis);
				break;
			}
			case 65: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000031);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000091, EnemyEtis);
				break;
			}
			case 75: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000032);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000092, EnemyEtis);
				break;
			}
			case 85: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000033);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000093, EnemyEtis);
				break;
			}
			case 95: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000034);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000094, EnemyEtis);
				break;
			}
			case 100: {
				requestScene(10000000, StageDebugPart01);
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000004);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(PX_C(800), 0, 0);
				requestActor(10000013, EnemyOebiusController001);
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)receiveActor(10003255);
				getSceneChief()->appendGroupChild(pRatislavia);
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000035);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000095, EnemyEtis);
				break;
			}
			case 115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000036);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000096, EnemyEtis);
				break;
			}
			case 125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000037);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000097, EnemyEtis);
				break;
			}
			case 135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000038);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000098, EnemyEtis);
				break;
			}
			case 145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000039);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000099, EnemyEtis);
				break;
			}
			case 155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000040);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000100, EnemyEtis);
				break;
			}
			case 165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000041);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000101, EnemyEtis);
				break;
			}
			case 175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000042);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000102, EnemyEtis);
				break;
			}
			case 185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000043);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000103, EnemyEtis);
				break;
			}
			case 195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000044);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000104, EnemyEtis);
				break;
			}
			case 200: {
				requestActor(10000006, EnemyOebiusController002);
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000045);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000105, EnemyEtis);
				break;
			}
			case 215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000046);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000106, EnemyEtis);
				break;
			}
			case 225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000047);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000107, EnemyEtis);
				break;
			}
			case 235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000048);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000108, EnemyEtis);
				break;
			}
			case 245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000049);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000109, EnemyEtis);
				break;
			}
			case 255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000050);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000110, EnemyEtis);
				break;
			}
			case 265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000051);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000111, EnemyEtis);
				break;
			}
			case 275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000052);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000112, EnemyEtis);
				break;
			}
			case 285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000053);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000113, EnemyEtis);
				break;
			}
			case 295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000054);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000114, EnemyEtis);
				break;
			}
			case 300: {
				requestActor(10000014, EnemyOebiusController001);
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000022);
				getSceneChief()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000055);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000115, EnemyEtis);
				break;
			}
			case 315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000056);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000116, EnemyEtis);
				break;
			}
			case 325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000057);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000117, EnemyEtis);
				break;
			}
			case 335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000058);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000118, EnemyEtis);
				break;
			}
			case 345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000059);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000119, EnemyEtis);
				break;
			}
			case 355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000060);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000120, EnemyEtis);
				break;
			}
			case 365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000061);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000121, EnemyEtis);
				break;
			}
			case 375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000062);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000122, EnemyEtis);
				break;
			}
			case 385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000063);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000123, EnemyEtis);
				break;
			}
			case 395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000064);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000124, EnemyEtis);
				break;
			}
			case 400: {
				requestActor(10000007, EnemyOebiusController002);
				EnemyErelmanController002* pE1 = (EnemyErelmanController002*)receiveActor(10000020);
				getSceneChief()->appendGroupChild(pE1);
				pE1->setPosition(PX_C(3400), PX_C(0), PX_C(3400));
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000065);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000125, EnemyEtis);
				break;
			}
			case 415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000066);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000126, EnemyEtis);
				break;
			}
			case 425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000067);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000127, EnemyEtis);
				break;
			}
			case 435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000068);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000128, EnemyEtis);
				break;
			}
			case 445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000069);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000129, EnemyEtis);
				break;
			}
			case 455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000070);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000130, EnemyEtis);
				break;
			}
			case 465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000071);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000131, EnemyEtis);
				break;
			}
			case 475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000072);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000132, EnemyEtis);
				break;
			}
			case 485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000073);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000133, EnemyEtis);
				break;
			}
			case 495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000074);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000134, EnemyEtis);
				break;
			}
			case 500: {
				requestActor(10000015, EnemyOebiusController001);
				EnemyErelmanController001* pE2 = (EnemyErelmanController001*)receiveActor(10000021);
				getSceneChief()->appendGroupChild(pE2);
				pE2->setPosition(PX_C(3400), PX_C(0), PX_C(0) );
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003225);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000075);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000135, EnemyEtis);
				break;
			}
			case 515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000076);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000136, EnemyEtis);
				break;
			}
			case 525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000077);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000137, EnemyEtis);
				break;
			}
			case 535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000078);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000138, EnemyEtis);
				break;
			}
			case 545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000079);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000139, EnemyEtis);
				break;
			}
			case 555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000080);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000140, EnemyEtis);
				break;
			}
			case 565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000081);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000141, EnemyEtis);
				break;
			}
			case 575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000082);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000142, EnemyEtis);
				break;
			}
			case 585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000083);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000143, EnemyEtis);
				break;
			}
			case 595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000084);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000144, EnemyEtis);
				break;
			}
			case 600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000005);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000008, EnemyOebiusController002);
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000085);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000145, EnemyEtis);
				break;
			}
			case 615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000086);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000146, EnemyEtis);
				break;
			}
			case 625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000087);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000147, EnemyEtis);
				break;
			}
			case 635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000088);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000148, EnemyEtis);
				break;
			}
			case 645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000089);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000149, EnemyEtis);
				break;
			}
			case 655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000090);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000150, EnemyEtis);
				break;
			}
			case 665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000091);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000151, EnemyEtis);
				break;
			}
			case 675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000092);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000152, EnemyEtis);
				break;
			}
			case 685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000093);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000153, EnemyEtis);
				break;
			}
			case 695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000094);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000154, EnemyEtis);
				break;
			}
			case 700: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000013);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000016, EnemyOebiusController001);
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000095);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000155, EnemyEtis);
				break;
			}
			case 715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000096);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000156, EnemyEtis);
				break;
			}
			case 725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000097);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000157, EnemyEtis);
				break;
			}
			case 735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000098);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000158, EnemyEtis);
				break;
			}
			case 745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000099);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000159, EnemyEtis);
				break;
			}
			case 755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000100);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000160, EnemyEtis);
				break;
			}
			case 765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000101);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000161, EnemyEtis);
				break;
			}
			case 775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000102);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000162, EnemyEtis);
				break;
			}
			case 785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000103);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000163, EnemyEtis);
				break;
			}
			case 795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000104);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000164, EnemyEtis);
				break;
			}
			case 800: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000006);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000009, EnemyOebiusController002);
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000105);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000165, EnemyEtis);
				break;
			}
			case 815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000106);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000166, EnemyEtis);
				break;
			}
			case 825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000107);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000167, EnemyEtis);
				break;
			}
			case 835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000108);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000168, EnemyEtis);
				break;
			}
			case 845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000109);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000169, EnemyEtis);
				break;
			}
			case 855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000110);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000170, EnemyEtis);
				break;
			}
			case 865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000111);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000171, EnemyEtis);
				break;
			}
			case 875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000112);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000172, EnemyEtis);
				break;
			}
			case 885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000113);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000173, EnemyEtis);
				break;
			}
			case 895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000114);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000174, EnemyEtis);
				break;
			}
			case 900: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000014);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000017, EnemyOebiusController001);
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000115);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000175, EnemyEtis);
				break;
			}
			case 915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000116);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000176, EnemyEtis);
				break;
			}
			case 925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000117);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000177, EnemyEtis);
				break;
			}
			case 935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000118);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000178, EnemyEtis);
				break;
			}
			case 945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000119);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000179, EnemyEtis);
				break;
			}
			case 955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000120);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000180, EnemyEtis);
				break;
			}
			case 965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000121);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000181, EnemyEtis);
				break;
			}
			case 975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000122);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000182, EnemyEtis);
				break;
			}
			case 985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000123);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000183, EnemyEtis);
				break;
			}
			case 995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000124);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000184, EnemyEtis);
				break;
			}
			case 1000: {
				appendChild(receiveScene(10000000));
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000007);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000010, EnemyOebiusController002);
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000125);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000185, EnemyEtis);
				break;
			}
			case 1015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000126);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000186, EnemyEtis);
				break;
			}
			case 1025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000127);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000187, EnemyEtis);
				break;
			}
			case 1035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000128);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000188, EnemyEtis);
				break;
			}
			case 1045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000129);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000189, EnemyEtis);
				break;
			}
			case 1055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000130);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000190, EnemyEtis);
				break;
			}
			case 1065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000131);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000191, EnemyEtis);
				break;
			}
			case 1075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000132);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000192, EnemyEtis);
				break;
			}
			case 1085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000133);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000193, EnemyEtis);
				break;
			}
			case 1095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000134);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000194, EnemyEtis);
				break;
			}
			case 1100: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000015);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000018, EnemyOebiusController001);
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000135);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000195, EnemyEtis);
				break;
			}
			case 1115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000136);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000196, EnemyEtis);
				break;
			}
			case 1125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000137);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000197, EnemyEtis);
				break;
			}
			case 1135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000138);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000198, EnemyEtis);
				break;
			}
			case 1145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000139);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000199, EnemyEtis);
				break;
			}
			case 1155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000140);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000200, EnemyEtis);
				break;
			}
			case 1165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000141);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000201, EnemyEtis);
				break;
			}
			case 1175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000142);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000202, EnemyEtis);
				break;
			}
			case 1185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000143);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000203, EnemyEtis);
				break;
			}
			case 1195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000144);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000204, EnemyEtis);
				break;
			}
			case 1200: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000008);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000011, EnemyOebiusController002);
				break;
			}
			case 1205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000145);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000205, EnemyEtis);
				break;
			}
			case 1215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000146);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000206, EnemyEtis);
				break;
			}
			case 1225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000147);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000207, EnemyEtis);
				break;
			}
			case 1235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000148);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000208, EnemyEtis);
				break;
			}
			case 1245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000149);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000209, EnemyEtis);
				break;
			}
			case 1255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000150);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000210, EnemyEtis);
				break;
			}
			case 1265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000151);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000211, EnemyEtis);
				break;
			}
			case 1275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000152);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000212, EnemyEtis);
				break;
			}
			case 1285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000153);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000213, EnemyEtis);
				break;
			}
			case 1295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000154);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000214, EnemyEtis);
				break;
			}
			case 1300: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000016);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000019, EnemyOebiusController001);
				break;
			}
			case 1305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000155);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000215, EnemyEtis);
				break;
			}
			case 1315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000156);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000216, EnemyEtis);
				break;
			}
			case 1325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000157);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000217, EnemyEtis);
				break;
			}
			case 1335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000158);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000218, EnemyEtis);
				break;
			}
			case 1345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000159);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000219, EnemyEtis);
				break;
			}
			case 1355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000160);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000220, EnemyEtis);
				break;
			}
			case 1365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000161);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000221, EnemyEtis);
				break;
			}
			case 1375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000162);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000222, EnemyEtis);
				break;
			}
			case 1385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000163);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000223, EnemyEtis);
				break;
			}
			case 1395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000164);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000224, EnemyEtis);
				break;
			}
			case 1400: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000009);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10000012, EnemyOebiusController002);
				break;
			}
			case 1405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000165);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000225, EnemyEtis);
				break;
			}
			case 1415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000166);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000226, EnemyEtis);
				break;
			}
			case 1425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000167);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000227, EnemyEtis);
				break;
			}
			case 1435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000168);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000228, EnemyEtis);
				break;
			}
			case 1445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000169);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000229, EnemyEtis);
				break;
			}
			case 1455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000170);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000230, EnemyEtis);
				break;
			}
			case 1465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000171);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000231, EnemyEtis);
				break;
			}
			case 1475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000172);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000232, EnemyEtis);
				break;
			}
			case 1485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000173);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000233, EnemyEtis);
				break;
			}
			case 1495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000174);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000234, EnemyEtis);
				break;
			}
			case 1500: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000017);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000175);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000235, EnemyEtis);
				break;
			}
			case 1515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000176);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000236, EnemyEtis);
				break;
			}
			case 1525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000177);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000237, EnemyEtis);
				break;
			}
			case 1535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000178);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000238, EnemyEtis);
				break;
			}
			case 1545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000179);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000239, EnemyEtis);
				break;
			}
			case 1555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000180);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000240, EnemyEtis);
				break;
			}
			case 1565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000181);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000241, EnemyEtis);
				break;
			}
			case 1575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000182);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000242, EnemyEtis);
				break;
			}
			case 1585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000183);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000243, EnemyEtis);
				break;
			}
			case 1595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000184);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000244, EnemyEtis);
				break;
			}
			case 1600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000010);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000185);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000245, EnemyEtis);
				break;
			}
			case 1615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000186);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000246, EnemyEtis);
				break;
			}
			case 1625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000187);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000247, EnemyEtis);
				break;
			}
			case 1635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000188);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000248, EnemyEtis);
				break;
			}
			case 1645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000189);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000249, EnemyEtis);
				break;
			}
			case 1655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000190);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000250, EnemyEtis);
				break;
			}
			case 1665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000191);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000251, EnemyEtis);
				break;
			}
			case 1675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000192);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000252, EnemyEtis);
				break;
			}
			case 1685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000193);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000253, EnemyEtis);
				break;
			}
			case 1695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000194);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000254, EnemyEtis);
				break;
			}
			case 1700: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000018);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000195);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000255, EnemyEtis);
				break;
			}
			case 1715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000196);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000256, EnemyEtis);
				break;
			}
			case 1725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000197);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000257, EnemyEtis);
				break;
			}
			case 1735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000198);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000258, EnemyEtis);
				break;
			}
			case 1745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000199);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000259, EnemyEtis);
				break;
			}
			case 1755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000200);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000260, EnemyEtis);
				break;
			}
			case 1765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000201);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000261, EnemyEtis);
				break;
			}
			case 1775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000202);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000262, EnemyEtis);
				break;
			}
			case 1785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000203);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000263, EnemyEtis);
				break;
			}
			case 1795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000204);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000264, EnemyEtis);
				break;
			}
			case 1800: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000011);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000205);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000265, EnemyEtis);
				break;
			}
			case 1815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000206);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000266, EnemyEtis);
				break;
			}
			case 1825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000207);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000267, EnemyEtis);
				break;
			}
			case 1835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000208);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000268, EnemyEtis);
				break;
			}
			case 1845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000209);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000269, EnemyEtis);
				break;
			}
			case 1855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000210);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000270, EnemyEtis);
				break;
			}
			case 1865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000211);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000271, EnemyEtis);
				break;
			}
			case 1875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000212);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000272, EnemyEtis);
				break;
			}
			case 1885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000213);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000273, EnemyEtis);
				break;
			}
			case 1895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000214);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000274, EnemyEtis);
				break;
			}
			case 1900: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)receiveActor(10000019);
				getSceneChief()->appendGroupChild(p3);
				p3->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				requestActor(10003226, EnemyDrastea);
				break;
			}
			case 1905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000215);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000275, EnemyEtis);
				break;
			}
			case 1915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000216);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000276, EnemyEtis);
				break;
			}
			case 1925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000217);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000277, EnemyEtis);
				break;
			}
			case 1935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000218);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000278, EnemyEtis);
				break;
			}
			case 1945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000219);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000279, EnemyEtis);
				break;
			}
			case 1955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000220);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000280, EnemyEtis);
				break;
			}
			case 1965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000221);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000281, EnemyEtis);
				break;
			}
			case 1975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000222);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000282, EnemyEtis);
				break;
			}
			case 1985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000223);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000283, EnemyEtis);
				break;
			}
			case 1995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000224);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000284, EnemyEtis);
				break;
			}
			case 2000: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000012);
				getSceneChief()->appendGroupChild(p2);
				p2->setPosition(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 2005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000225);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000285, EnemyEtis);
				break;
			}
			case 2015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000226);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000286, EnemyEtis);
				break;
			}
			case 2025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000227);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000287, EnemyEtis);
				break;
			}
			case 2035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000228);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000288, EnemyEtis);
				break;
			}
			case 2045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000229);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000289, EnemyEtis);
				break;
			}
			case 2055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000230);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000290, EnemyEtis);
				break;
			}
			case 2065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000231);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000291, EnemyEtis);
				break;
			}
			case 2075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000232);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000292, EnemyEtis);
				break;
			}
			case 2085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000233);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000293, EnemyEtis);
				break;
			}
			case 2095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000234);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000294, EnemyEtis);
				break;
			}
			case 2105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000235);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000295, EnemyEtis);
				break;
			}
			case 2115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000236);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000296, EnemyEtis);
				break;
			}
			case 2125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000237);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000297, EnemyEtis);
				break;
			}
			case 2135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000238);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000298, EnemyEtis);
				break;
			}
			case 2145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000239);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000299, EnemyEtis);
				break;
			}
			case 2155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000240);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000300, EnemyEtis);
				break;
			}
			case 2165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000241);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000301, EnemyEtis);
				break;
			}
			case 2175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000242);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000302, EnemyEtis);
				break;
			}
			case 2185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000243);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000303, EnemyEtis);
				break;
			}
			case 2195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000244);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000304, EnemyEtis);
				break;
			}
			case 2205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000245);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000305, EnemyEtis);
				break;
			}
			case 2215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000246);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000306, EnemyEtis);
				break;
			}
			case 2225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000247);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000307, EnemyEtis);
				break;
			}
			case 2235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000248);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000308, EnemyEtis);
				break;
			}
			case 2245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000249);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000309, EnemyEtis);
				break;
			}
			case 2255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000250);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000310, EnemyEtis);
				break;
			}
			case 2265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000251);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000311, EnemyEtis);
				break;
			}
			case 2275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000252);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000312, EnemyEtis);
				break;
			}
			case 2285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000253);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000313, EnemyEtis);
				break;
			}
			case 2295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000254);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000314, EnemyEtis);
				break;
			}
			case 2305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000255);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000315, EnemyEtis);
				break;
			}
			case 2315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000256);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000316, EnemyEtis);
				break;
			}
			case 2325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000257);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000317, EnemyEtis);
				break;
			}
			case 2335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000258);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000318, EnemyEtis);
				break;
			}
			case 2345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000259);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000319, EnemyEtis);
				break;
			}
			case 2355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000260);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000320, EnemyEtis);
				break;
			}
			case 2365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000261);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000321, EnemyEtis);
				break;
			}
			case 2375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000262);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000322, EnemyEtis);
				break;
			}
			case 2385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000263);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000323, EnemyEtis);
				break;
			}
			case 2395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000264);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000324, EnemyEtis);
				break;
			}
			case 2405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000265);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000325, EnemyEtis);
				break;
			}
			case 2415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000266);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000326, EnemyEtis);
				break;
			}
			case 2425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000267);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000327, EnemyEtis);
				break;
			}
			case 2435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000268);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000328, EnemyEtis);
				break;
			}
			case 2445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000269);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000329, EnemyEtis);
				break;
			}
			case 2455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000270);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000330, EnemyEtis);
				break;
			}
			case 2465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000271);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000331, EnemyEtis);
				break;
			}
			case 2475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000272);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000332, EnemyEtis);
				break;
			}
			case 2485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000273);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000333, EnemyEtis);
				break;
			}
			case 2495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000274);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000334, EnemyEtis);
				break;
			}
			case 2500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003226);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 2505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000275);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000335, EnemyEtis);
				break;
			}
			case 2515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000276);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000336, EnemyEtis);
				break;
			}
			case 2525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000277);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000337, EnemyEtis);
				break;
			}
			case 2535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000278);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000338, EnemyEtis);
				break;
			}
			case 2545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000279);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000339, EnemyEtis);
				break;
			}
			case 2555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000280);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000340, EnemyEtis);
				break;
			}
			case 2565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000281);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000341, EnemyEtis);
				break;
			}
			case 2575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000282);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000342, EnemyEtis);
				break;
			}
			case 2585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000283);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000343, EnemyEtis);
				break;
			}
			case 2595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000284);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000344, EnemyEtis);
				break;
			}
			case 2605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000285);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000345, EnemyEtis);
				break;
			}
			case 2615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000286);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000346, EnemyEtis);
				break;
			}
			case 2625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000287);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000347, EnemyEtis);
				break;
			}
			case 2635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000288);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000348, EnemyEtis);
				break;
			}
			case 2645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000289);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000349, EnemyEtis);
				break;
			}
			case 2655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000290);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000350, EnemyEtis);
				break;
			}
			case 2665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000291);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000351, EnemyEtis);
				break;
			}
			case 2675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000292);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000352, EnemyEtis);
				break;
			}
			case 2685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000293);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000353, EnemyEtis);
				break;
			}
			case 2695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000294);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000354, EnemyEtis);
				break;
			}
			case 2705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000295);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000355, EnemyEtis);
				break;
			}
			case 2715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000296);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000356, EnemyEtis);
				break;
			}
			case 2725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000297);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000357, EnemyEtis);
				break;
			}
			case 2735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000298);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000358, EnemyEtis);
				break;
			}
			case 2745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000299);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000359, EnemyEtis);
				break;
			}
			case 2755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000300);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000360, EnemyEtis);
				break;
			}
			case 2765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000301);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000361, EnemyEtis);
				break;
			}
			case 2775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000302);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000362, EnemyEtis);
				break;
			}
			case 2785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000303);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000363, EnemyEtis);
				break;
			}
			case 2795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000304);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000364, EnemyEtis);
				break;
			}
			case 2805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000305);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000365, EnemyEtis);
				break;
			}
			case 2815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000306);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000366, EnemyEtis);
				break;
			}
			case 2825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000307);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000367, EnemyEtis);
				break;
			}
			case 2835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000308);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000368, EnemyEtis);
				break;
			}
			case 2845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000309);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000369, EnemyEtis);
				break;
			}
			case 2855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000310);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000370, EnemyEtis);
				break;
			}
			case 2865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000311);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000371, EnemyEtis);
				break;
			}
			case 2875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000312);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000372, EnemyEtis);
				break;
			}
			case 2885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000313);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000373, EnemyEtis);
				break;
			}
			case 2895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000314);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000374, EnemyEtis);
				break;
			}
			case 2905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000315);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000375, EnemyEtis);
				break;
			}
			case 2915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000316);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000376, EnemyEtis);
				break;
			}
			case 2925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000317);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000377, EnemyEtis);
				break;
			}
			case 2935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000318);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000378, EnemyEtis);
				break;
			}
			case 2945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000319);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000379, EnemyEtis);
				break;
			}
			case 2955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000320);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000380, EnemyEtis);
				break;
			}
			case 2965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000321);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000381, EnemyEtis);
				break;
			}
			case 2975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000322);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000382, EnemyEtis);
				break;
			}
			case 2985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000323);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000383, EnemyEtis);
				break;
			}
			case 2995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000324);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000384, EnemyEtis);
				break;
			}
			case 3005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000325);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000385, EnemyEtis);
				break;
			}
			case 3015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000326);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000386, EnemyEtis);
				break;
			}
			case 3025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000327);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000387, EnemyEtis);
				break;
			}
			case 3035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000328);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000388, EnemyEtis);
				break;
			}
			case 3045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000329);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000389, EnemyEtis);
				break;
			}
			case 3055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000330);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000390, EnemyEtis);
				break;
			}
			case 3065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000331);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000391, EnemyEtis);
				break;
			}
			case 3075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000332);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000392, EnemyEtis);
				break;
			}
			case 3085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000333);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000393, EnemyEtis);
				break;
			}
			case 3095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000334);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000394, EnemyEtis);
				break;
			}
			case 3105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000335);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000395, EnemyEtis);
				break;
			}
			case 3115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000336);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000396, EnemyEtis);
				break;
			}
			case 3125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000337);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000397, EnemyEtis);
				break;
			}
			case 3135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000338);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000398, EnemyEtis);
				break;
			}
			case 3145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000339);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000399, EnemyEtis);
				break;
			}
			case 3155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000340);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000400, EnemyEtis);
				break;
			}
			case 3165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000341);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000401, EnemyEtis);
				break;
			}
			case 3175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000342);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000402, EnemyEtis);
				break;
			}
			case 3185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000343);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000403, EnemyEtis);
				break;
			}
			case 3195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000344);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000404, EnemyEtis);
				break;
			}
			case 3205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000345);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000405, EnemyEtis);
				break;
			}
			case 3215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000346);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000406, EnemyEtis);
				break;
			}
			case 3225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000347);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000407, EnemyEtis);
				break;
			}
			case 3235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000348);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000408, EnemyEtis);
				break;
			}
			case 3245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000349);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000409, EnemyEtis);
				break;
			}
			case 3255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000350);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000410, EnemyEtis);
				break;
			}
			case 3265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000351);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000411, EnemyEtis);
				break;
			}
			case 3275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000352);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000412, EnemyEtis);
				break;
			}
			case 3285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000353);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000413, EnemyEtis);
				break;
			}
			case 3295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000354);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000414, EnemyEtis);
				break;
			}
			case 3305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000355);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000415, EnemyEtis);
				break;
			}
			case 3315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000356);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000416, EnemyEtis);
				break;
			}
			case 3325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000357);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000417, EnemyEtis);
				break;
			}
			case 3335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000358);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000418, EnemyEtis);
				break;
			}
			case 3345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000359);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000419, EnemyEtis);
				break;
			}
			case 3355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000360);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000420, EnemyEtis);
				break;
			}
			case 3365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000361);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000421, EnemyEtis);
				break;
			}
			case 3375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000362);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000422, EnemyEtis);
				break;
			}
			case 3385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000363);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000423, EnemyEtis);
				break;
			}
			case 3395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000364);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000424, EnemyEtis);
				break;
			}
			case 3405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000365);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000425, EnemyEtis);
				break;
			}
			case 3415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000366);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000426, EnemyEtis);
				break;
			}
			case 3425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000367);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000427, EnemyEtis);
				break;
			}
			case 3435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000368);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000428, EnemyEtis);
				break;
			}
			case 3445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000369);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000429, EnemyEtis);
				break;
			}
			case 3455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000370);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000430, EnemyEtis);
				break;
			}
			case 3465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000371);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000431, EnemyEtis);
				break;
			}
			case 3475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000372);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000432, EnemyEtis);
				break;
			}
			case 3485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000373);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000433, EnemyEtis);
				break;
			}
			case 3495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000374);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000434, EnemyEtis);
				break;
			}
			case 3505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000375);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000435, EnemyEtis);
				break;
			}
			case 3515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000376);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000436, EnemyEtis);
				break;
			}
			case 3525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000377);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000437, EnemyEtis);
				break;
			}
			case 3535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000378);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000438, EnemyEtis);
				break;
			}
			case 3545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000379);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000439, EnemyEtis);
				break;
			}
			case 3555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000380);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000440, EnemyEtis);
				break;
			}
			case 3565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000381);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000441, EnemyEtis);
				break;
			}
			case 3575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000382);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000442, EnemyEtis);
				break;
			}
			case 3585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000383);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000443, EnemyEtis);
				break;
			}
			case 3595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000384);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000444, EnemyEtis);
				break;
			}
			case 3605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000385);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000445, EnemyEtis);
				break;
			}
			case 3615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000386);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000446, EnemyEtis);
				break;
			}
			case 3625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000387);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000447, EnemyEtis);
				break;
			}
			case 3635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000388);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000448, EnemyEtis);
				break;
			}
			case 3645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000389);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000449, EnemyEtis);
				break;
			}
			case 3655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000390);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000450, EnemyEtis);
				break;
			}
			case 3665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000391);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000451, EnemyEtis);
				break;
			}
			case 3675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000392);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000452, EnemyEtis);
				break;
			}
			case 3685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000393);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000453, EnemyEtis);
				break;
			}
			case 3695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000394);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000454, EnemyEtis);
				break;
			}
			case 3705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000395);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000455, EnemyEtis);
				break;
			}
			case 3715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000396);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000456, EnemyEtis);
				break;
			}
			case 3725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000397);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000457, EnemyEtis);
				break;
			}
			case 3735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000398);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000458, EnemyEtis);
				break;
			}
			case 3745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000399);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000459, EnemyEtis);
				break;
			}
			case 3755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000400);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000460, EnemyEtis);
				break;
			}
			case 3765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000401);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000461, EnemyEtis);
				break;
			}
			case 3775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000402);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000462, EnemyEtis);
				break;
			}
			case 3785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000403);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000463, EnemyEtis);
				break;
			}
			case 3795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000404);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000464, EnemyEtis);
				break;
			}
			case 3805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000405);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000465, EnemyEtis);
				break;
			}
			case 3815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000406);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000466, EnemyEtis);
				break;
			}
			case 3825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000407);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000467, EnemyEtis);
				break;
			}
			case 3835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000408);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000468, EnemyEtis);
				break;
			}
			case 3845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000409);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000469, EnemyEtis);
				break;
			}
			case 3855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000410);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000470, EnemyEtis);
				break;
			}
			case 3865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000411);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000471, EnemyEtis);
				break;
			}
			case 3875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000412);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000472, EnemyEtis);
				break;
			}
			case 3885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000413);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000473, EnemyEtis);
				break;
			}
			case 3895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000414);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000474, EnemyEtis);
				break;
			}
			case 3900: {
				requestActor(10003227, EnemyDrastea);
				break;
			}
			case 3905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000415);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000475, EnemyEtis);
				break;
			}
			case 3915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000416);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000476, EnemyEtis);
				break;
			}
			case 3925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000417);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000477, EnemyEtis);
				break;
			}
			case 3935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000418);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000478, EnemyEtis);
				break;
			}
			case 3945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000419);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000479, EnemyEtis);
				break;
			}
			case 3955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000420);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000480, EnemyEtis);
				break;
			}
			case 3965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000421);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000481, EnemyEtis);
				break;
			}
			case 3975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000422);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000482, EnemyEtis);
				break;
			}
			case 3985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000423);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000483, EnemyEtis);
				break;
			}
			case 3995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000424);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000484, EnemyEtis);
				break;
			}
			case 4005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000425);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000485, EnemyEtis);
				break;
			}
			case 4015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000426);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000486, EnemyEtis);
				break;
			}
			case 4025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000427);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000487, EnemyEtis);
				break;
			}
			case 4035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000428);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000488, EnemyEtis);
				break;
			}
			case 4045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000429);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000489, EnemyEtis);
				break;
			}
			case 4055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000430);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000490, EnemyEtis);
				break;
			}
			case 4065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000431);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000491, EnemyEtis);
				break;
			}
			case 4075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000432);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000492, EnemyEtis);
				break;
			}
			case 4085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000433);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000493, EnemyEtis);
				break;
			}
			case 4095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000434);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000494, EnemyEtis);
				break;
			}
			case 4105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000435);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000495, EnemyEtis);
				break;
			}
			case 4115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000436);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000496, EnemyEtis);
				break;
			}
			case 4125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000437);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000497, EnemyEtis);
				break;
			}
			case 4135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000438);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000498, EnemyEtis);
				break;
			}
			case 4145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000439);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000499, EnemyEtis);
				break;
			}
			case 4155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000440);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000500, EnemyEtis);
				break;
			}
			case 4165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000441);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000501, EnemyEtis);
				break;
			}
			case 4175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000442);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000502, EnemyEtis);
				break;
			}
			case 4185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000443);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000503, EnemyEtis);
				break;
			}
			case 4195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000444);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000504, EnemyEtis);
				break;
			}
			case 4205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000445);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000505, EnemyEtis);
				break;
			}
			case 4215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000446);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000506, EnemyEtis);
				break;
			}
			case 4225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000447);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000507, EnemyEtis);
				break;
			}
			case 4235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000448);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000508, EnemyEtis);
				break;
			}
			case 4245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000449);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000509, EnemyEtis);
				break;
			}
			case 4255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000450);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000510, EnemyEtis);
				break;
			}
			case 4265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000451);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000511, EnemyEtis);
				break;
			}
			case 4275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000452);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000512, EnemyEtis);
				break;
			}
			case 4285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000453);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000513, EnemyEtis);
				break;
			}
			case 4295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000454);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000514, EnemyEtis);
				break;
			}
			case 4305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000455);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000515, EnemyEtis);
				break;
			}
			case 4315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000456);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000516, EnemyEtis);
				break;
			}
			case 4325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000457);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000517, EnemyEtis);
				break;
			}
			case 4335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000458);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000518, EnemyEtis);
				break;
			}
			case 4345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000459);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000519, EnemyEtis);
				break;
			}
			case 4355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000460);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000520, EnemyEtis);
				break;
			}
			case 4365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000461);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000521, EnemyEtis);
				break;
			}
			case 4375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000462);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000522, EnemyEtis);
				break;
			}
			case 4385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000463);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000523, EnemyEtis);
				break;
			}
			case 4395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000464);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000524, EnemyEtis);
				break;
			}
			case 4405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000465);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000525, EnemyEtis);
				break;
			}
			case 4415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000466);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000526, EnemyEtis);
				break;
			}
			case 4425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000467);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000527, EnemyEtis);
				break;
			}
			case 4435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000468);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000528, EnemyEtis);
				break;
			}
			case 4445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000469);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000529, EnemyEtis);
				break;
			}
			case 4455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000470);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000530, EnemyEtis);
				break;
			}
			case 4465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000471);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000531, EnemyEtis);
				break;
			}
			case 4475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000472);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000532, EnemyEtis);
				break;
			}
			case 4485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000473);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000533, EnemyEtis);
				break;
			}
			case 4495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000474);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000534, EnemyEtis);
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003227);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 4505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000475);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000535, EnemyEtis);
				break;
			}
			case 4515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000476);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000536, EnemyEtis);
				break;
			}
			case 4525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000477);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000537, EnemyEtis);
				break;
			}
			case 4535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000478);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000538, EnemyEtis);
				break;
			}
			case 4545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000479);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000539, EnemyEtis);
				break;
			}
			case 4555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000480);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000540, EnemyEtis);
				break;
			}
			case 4565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000481);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000541, EnemyEtis);
				break;
			}
			case 4575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000482);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000542, EnemyEtis);
				break;
			}
			case 4585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000483);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000543, EnemyEtis);
				break;
			}
			case 4595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000484);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000544, EnemyEtis);
				break;
			}
			case 4605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000485);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000545, EnemyEtis);
				break;
			}
			case 4615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000486);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000546, EnemyEtis);
				break;
			}
			case 4625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000487);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000547, EnemyEtis);
				break;
			}
			case 4635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000488);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000548, EnemyEtis);
				break;
			}
			case 4645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000489);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000549, EnemyEtis);
				break;
			}
			case 4655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000490);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000550, EnemyEtis);
				break;
			}
			case 4665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000491);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000551, EnemyEtis);
				break;
			}
			case 4675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000492);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000552, EnemyEtis);
				break;
			}
			case 4685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000493);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000553, EnemyEtis);
				break;
			}
			case 4695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000494);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000554, EnemyEtis);
				break;
			}
			case 4705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000495);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000555, EnemyEtis);
				break;
			}
			case 4715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000496);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000556, EnemyEtis);
				break;
			}
			case 4725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000497);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000557, EnemyEtis);
				break;
			}
			case 4735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000498);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000558, EnemyEtis);
				break;
			}
			case 4745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000499);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000559, EnemyEtis);
				break;
			}
			case 4755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000500);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000560, EnemyEtis);
				break;
			}
			case 4765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000501);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000561, EnemyEtis);
				break;
			}
			case 4775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000502);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000562, EnemyEtis);
				break;
			}
			case 4785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000503);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000563, EnemyEtis);
				break;
			}
			case 4795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000504);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000564, EnemyEtis);
				break;
			}
			case 4805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000505);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000565, EnemyEtis);
				break;
			}
			case 4815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000506);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000566, EnemyEtis);
				break;
			}
			case 4825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000507);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000567, EnemyEtis);
				break;
			}
			case 4835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000508);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000568, EnemyEtis);
				break;
			}
			case 4845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000509);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000569, EnemyEtis);
				break;
			}
			case 4855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000510);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000570, EnemyEtis);
				break;
			}
			case 4865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000511);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000571, EnemyEtis);
				break;
			}
			case 4875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000512);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000572, EnemyEtis);
				break;
			}
			case 4885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000513);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000573, EnemyEtis);
				break;
			}
			case 4895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000514);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000574, EnemyEtis);
				break;
			}
			case 4905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000515);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000575, EnemyEtis);
				break;
			}
			case 4915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000516);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000576, EnemyEtis);
				break;
			}
			case 4925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000517);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000577, EnemyEtis);
				break;
			}
			case 4935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000518);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000578, EnemyEtis);
				break;
			}
			case 4945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000519);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000579, EnemyEtis);
				break;
			}
			case 4955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000520);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000580, EnemyEtis);
				break;
			}
			case 4965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000521);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000581, EnemyEtis);
				break;
			}
			case 4975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000522);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000582, EnemyEtis);
				break;
			}
			case 4985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000523);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000583, EnemyEtis);
				break;
			}
			case 4995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000524);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000584, EnemyEtis);
				break;
			}
			case 5005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000525);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000585, EnemyEtis);
				break;
			}
			case 5015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000526);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000586, EnemyEtis);
				break;
			}
			case 5025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000527);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000587, EnemyEtis);
				break;
			}
			case 5035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000528);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000588, EnemyEtis);
				break;
			}
			case 5045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000529);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000589, EnemyEtis);
				break;
			}
			case 5055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000530);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000590, EnemyEtis);
				break;
			}
			case 5065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000531);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000591, EnemyEtis);
				break;
			}
			case 5075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000532);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000592, EnemyEtis);
				break;
			}
			case 5085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000533);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000593, EnemyEtis);
				break;
			}
			case 5095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000534);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000594, EnemyEtis);
				break;
			}
			case 5100: {
				requestScene(10000001, StageDebugPart02);
				break;
			}
			case 5105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000535);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000595, EnemyEtis);
				break;
			}
			case 5115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000536);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000596, EnemyEtis);
				break;
			}
			case 5125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000537);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000597, EnemyEtis);
				break;
			}
			case 5135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000538);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000598, EnemyEtis);
				break;
			}
			case 5145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000539);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000599, EnemyEtis);
				break;
			}
			case 5155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000540);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000600, EnemyEtis);
				break;
			}
			case 5165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000541);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000601, EnemyEtis);
				break;
			}
			case 5175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000542);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000602, EnemyEtis);
				break;
			}
			case 5185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000543);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000603, EnemyEtis);
				break;
			}
			case 5195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000544);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000604, EnemyEtis);
				break;
			}
			case 5205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000545);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000605, EnemyEtis);
				break;
			}
			case 5215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000546);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000606, EnemyEtis);
				break;
			}
			case 5225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000547);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000607, EnemyEtis);
				break;
			}
			case 5235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000548);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000608, EnemyEtis);
				break;
			}
			case 5245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000549);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000609, EnemyEtis);
				break;
			}
			case 5255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000550);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000610, EnemyEtis);
				break;
			}
			case 5265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000551);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000611, EnemyEtis);
				break;
			}
			case 5275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000552);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000612, EnemyEtis);
				break;
			}
			case 5285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000553);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000613, EnemyEtis);
				break;
			}
			case 5295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000554);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000614, EnemyEtis);
				break;
			}
			case 5305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000555);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000615, EnemyEtis);
				break;
			}
			case 5315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000556);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000616, EnemyEtis);
				break;
			}
			case 5325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000557);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000617, EnemyEtis);
				break;
			}
			case 5335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000558);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000618, EnemyEtis);
				break;
			}
			case 5345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000559);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000619, EnemyEtis);
				break;
			}
			case 5355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000560);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000620, EnemyEtis);
				break;
			}
			case 5365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000561);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000621, EnemyEtis);
				break;
			}
			case 5375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000562);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000622, EnemyEtis);
				break;
			}
			case 5385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000563);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000623, EnemyEtis);
				break;
			}
			case 5395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000564);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000624, EnemyEtis);
				break;
			}
			case 5405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000565);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000625, EnemyEtis);
				break;
			}
			case 5415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000566);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000626, EnemyEtis);
				break;
			}
			case 5425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000567);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000627, EnemyEtis);
				break;
			}
			case 5435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000568);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000628, EnemyEtis);
				break;
			}
			case 5445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000569);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000629, EnemyEtis);
				break;
			}
			case 5455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000570);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000630, EnemyEtis);
				break;
			}
			case 5465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000571);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000631, EnemyEtis);
				break;
			}
			case 5475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000572);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000632, EnemyEtis);
				break;
			}
			case 5485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000573);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000633, EnemyEtis);
				break;
			}
			case 5495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000574);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000634, EnemyEtis);
				break;
			}
			case 5505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000575);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000635, EnemyEtis);
				break;
			}
			case 5515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000576);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000636, EnemyEtis);
				break;
			}
			case 5525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000577);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000637, EnemyEtis);
				break;
			}
			case 5535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000578);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000638, EnemyEtis);
				break;
			}
			case 5545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000579);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000639, EnemyEtis);
				break;
			}
			case 5555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000580);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000640, EnemyEtis);
				break;
			}
			case 5565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000581);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000641, EnemyEtis);
				break;
			}
			case 5575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000582);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000642, EnemyEtis);
				break;
			}
			case 5585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000583);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000643, EnemyEtis);
				break;
			}
			case 5595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000584);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000644, EnemyEtis);
				break;
			}
			case 5605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000585);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000645, EnemyEtis);
				break;
			}
			case 5615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000586);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000646, EnemyEtis);
				break;
			}
			case 5625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000587);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000647, EnemyEtis);
				break;
			}
			case 5635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000588);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000648, EnemyEtis);
				break;
			}
			case 5645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000589);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000649, EnemyEtis);
				break;
			}
			case 5655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000590);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000650, EnemyEtis);
				break;
			}
			case 5665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000591);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000651, EnemyEtis);
				break;
			}
			case 5675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000592);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000652, EnemyEtis);
				break;
			}
			case 5685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000593);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000653, EnemyEtis);
				break;
			}
			case 5695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000594);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000654, EnemyEtis);
				break;
			}
			case 5705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000595);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000655, EnemyEtis);
				break;
			}
			case 5715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000596);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000656, EnemyEtis);
				break;
			}
			case 5725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000597);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000657, EnemyEtis);
				break;
			}
			case 5735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000598);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000658, EnemyEtis);
				break;
			}
			case 5745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000599);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000659, EnemyEtis);
				break;
			}
			case 5755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000600);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000660, EnemyEtis);
				break;
			}
			case 5765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000601);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000661, EnemyEtis);
				break;
			}
			case 5775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000602);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000662, EnemyEtis);
				break;
			}
			case 5785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000603);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000663, EnemyEtis);
				break;
			}
			case 5795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000604);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000664, EnemyEtis);
				break;
			}
			case 5805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000605);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000665, EnemyEtis);
				break;
			}
			case 5815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000606);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000666, EnemyEtis);
				break;
			}
			case 5825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000607);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000667, EnemyEtis);
				break;
			}
			case 5835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000608);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000668, EnemyEtis);
				break;
			}
			case 5845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000609);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000669, EnemyEtis);
				break;
			}
			case 5855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000610);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000670, EnemyEtis);
				break;
			}
			case 5865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000611);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000671, EnemyEtis);
				break;
			}
			case 5875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000612);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000672, EnemyEtis);
				break;
			}
			case 5885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000613);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000673, EnemyEtis);
				break;
			}
			case 5895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000614);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000674, EnemyEtis);
				break;
			}
			case 5900: {
				requestActor(10003228, EnemyDrastea);
				break;
			}
			case 5905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000615);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000675, EnemyEtis);
				break;
			}
			case 5915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000616);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000676, EnemyEtis);
				break;
			}
			case 5925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000617);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000677, EnemyEtis);
				break;
			}
			case 5935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000618);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000678, EnemyEtis);
				break;
			}
			case 5945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000619);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000679, EnemyEtis);
				break;
			}
			case 5955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000620);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000680, EnemyEtis);
				break;
			}
			case 5965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000621);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000681, EnemyEtis);
				break;
			}
			case 5975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000622);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000682, EnemyEtis);
				break;
			}
			case 5985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000623);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000683, EnemyEtis);
				break;
			}
			case 5995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000624);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000684, EnemyEtis);
				break;
			}
			case 6000: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 6005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000625);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000685, EnemyEtis);
				break;
			}
			case 6015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000626);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000686, EnemyEtis);
				break;
			}
			case 6025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000627);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000687, EnemyEtis);
				break;
			}
			case 6035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000628);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000688, EnemyEtis);
				break;
			}
			case 6045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000629);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000689, EnemyEtis);
				break;
			}
			case 6055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000630);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000690, EnemyEtis);
				break;
			}
			case 6065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000631);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000691, EnemyEtis);
				break;
			}
			case 6075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000632);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000692, EnemyEtis);
				break;
			}
			case 6085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000633);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000693, EnemyEtis);
				break;
			}
			case 6095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000634);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000694, EnemyEtis);
				break;
			}
			case 6105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000635);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000695, EnemyEtis);
				break;
			}
			case 6115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000636);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000696, EnemyEtis);
				break;
			}
			case 6125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000637);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000697, EnemyEtis);
				break;
			}
			case 6135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000638);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000698, EnemyEtis);
				break;
			}
			case 6145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000639);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000699, EnemyEtis);
				break;
			}
			case 6155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000640);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000700, EnemyEtis);
				break;
			}
			case 6165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000641);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000701, EnemyEtis);
				break;
			}
			case 6175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000642);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000702, EnemyEtis);
				break;
			}
			case 6185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000643);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000703, EnemyEtis);
				break;
			}
			case 6195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000644);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000704, EnemyEtis);
				break;
			}
			case 6205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000645);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000705, EnemyEtis);
				break;
			}
			case 6215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000646);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000706, EnemyEtis);
				break;
			}
			case 6225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000647);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000707, EnemyEtis);
				break;
			}
			case 6235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000648);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000708, EnemyEtis);
				break;
			}
			case 6245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000649);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000709, EnemyEtis);
				break;
			}
			case 6255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000650);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000710, EnemyEtis);
				break;
			}
			case 6265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000651);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000711, EnemyEtis);
				break;
			}
			case 6275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000652);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000712, EnemyEtis);
				break;
			}
			case 6285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000653);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000713, EnemyEtis);
				break;
			}
			case 6295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000654);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000714, EnemyEtis);
				break;
			}
			case 6305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000655);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000715, EnemyEtis);
				break;
			}
			case 6315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000656);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000716, EnemyEtis);
				break;
			}
			case 6325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000657);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000717, EnemyEtis);
				break;
			}
			case 6335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000658);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000718, EnemyEtis);
				break;
			}
			case 6345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000659);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000719, EnemyEtis);
				break;
			}
			case 6355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000660);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000720, EnemyEtis);
				break;
			}
			case 6365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000661);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000721, EnemyEtis);
				break;
			}
			case 6375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000662);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000722, EnemyEtis);
				break;
			}
			case 6385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000663);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000723, EnemyEtis);
				break;
			}
			case 6395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000664);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000724, EnemyEtis);
				break;
			}
			case 6405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000665);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000725, EnemyEtis);
				break;
			}
			case 6415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000666);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000726, EnemyEtis);
				break;
			}
			case 6425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000667);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000727, EnemyEtis);
				break;
			}
			case 6435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000668);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000728, EnemyEtis);
				break;
			}
			case 6445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000669);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000729, EnemyEtis);
				break;
			}
			case 6455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000670);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000730, EnemyEtis);
				break;
			}
			case 6465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000671);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000731, EnemyEtis);
				break;
			}
			case 6475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000672);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000732, EnemyEtis);
				break;
			}
			case 6485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000673);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000733, EnemyEtis);
				break;
			}
			case 6495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000674);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000734, EnemyEtis);
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003228);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 6505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000675);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000735, EnemyEtis);
				break;
			}
			case 6515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000676);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000736, EnemyEtis);
				break;
			}
			case 6525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000677);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000737, EnemyEtis);
				break;
			}
			case 6535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000678);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000738, EnemyEtis);
				break;
			}
			case 6545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000679);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000739, EnemyEtis);
				break;
			}
			case 6555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000680);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000740, EnemyEtis);
				break;
			}
			case 6565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000681);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000741, EnemyEtis);
				break;
			}
			case 6575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000682);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000742, EnemyEtis);
				break;
			}
			case 6585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000683);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000743, EnemyEtis);
				break;
			}
			case 6595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000684);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000744, EnemyEtis);
				break;
			}
			case 6605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000685);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000745, EnemyEtis);
				break;
			}
			case 6615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000686);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000746, EnemyEtis);
				break;
			}
			case 6625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000687);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000747, EnemyEtis);
				break;
			}
			case 6635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000688);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000748, EnemyEtis);
				break;
			}
			case 6645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000689);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000749, EnemyEtis);
				break;
			}
			case 6655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000690);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000750, EnemyEtis);
				break;
			}
			case 6665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000691);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000751, EnemyEtis);
				break;
			}
			case 6675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000692);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000752, EnemyEtis);
				break;
			}
			case 6685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000693);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000753, EnemyEtis);
				break;
			}
			case 6695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000694);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000754, EnemyEtis);
				break;
			}
			case 6705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000695);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000755, EnemyEtis);
				break;
			}
			case 6715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000696);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000756, EnemyEtis);
				break;
			}
			case 6725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000697);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000757, EnemyEtis);
				break;
			}
			case 6735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000698);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000758, EnemyEtis);
				break;
			}
			case 6745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000699);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000759, EnemyEtis);
				break;
			}
			case 6755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000700);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000760, EnemyEtis);
				break;
			}
			case 6765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000701);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000761, EnemyEtis);
				break;
			}
			case 6775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000702);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000762, EnemyEtis);
				break;
			}
			case 6785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000703);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000763, EnemyEtis);
				break;
			}
			case 6795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000704);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000764, EnemyEtis);
				break;
			}
			case 6805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000705);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000765, EnemyEtis);
				break;
			}
			case 6815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000706);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000766, EnemyEtis);
				break;
			}
			case 6825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000707);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000767, EnemyEtis);
				break;
			}
			case 6835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000708);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000768, EnemyEtis);
				break;
			}
			case 6845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000709);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000769, EnemyEtis);
				break;
			}
			case 6855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000710);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000770, EnemyEtis);
				break;
			}
			case 6865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000711);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000771, EnemyEtis);
				break;
			}
			case 6875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000712);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000772, EnemyEtis);
				break;
			}
			case 6885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000713);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000773, EnemyEtis);
				break;
			}
			case 6895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000714);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000774, EnemyEtis);
				break;
			}
			case 6905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000715);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000775, EnemyEtis);
				break;
			}
			case 6915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000716);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000776, EnemyEtis);
				break;
			}
			case 6925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000717);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000777, EnemyEtis);
				break;
			}
			case 6935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000718);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000778, EnemyEtis);
				break;
			}
			case 6945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000719);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000779, EnemyEtis);
				break;
			}
			case 6955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000720);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000780, EnemyEtis);
				break;
			}
			case 6965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000721);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000781, EnemyEtis);
				break;
			}
			case 6975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000722);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000782, EnemyEtis);
				break;
			}
			case 6985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000723);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000783, EnemyEtis);
				break;
			}
			case 6995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000724);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000784, EnemyEtis);
				break;
			}
			case 7005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000725);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000785, EnemyEtis);
				break;
			}
			case 7015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000726);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000786, EnemyEtis);
				break;
			}
			case 7025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000727);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000787, EnemyEtis);
				break;
			}
			case 7035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000728);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000788, EnemyEtis);
				break;
			}
			case 7045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000729);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000789, EnemyEtis);
				break;
			}
			case 7055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000730);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000790, EnemyEtis);
				break;
			}
			case 7065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000731);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000791, EnemyEtis);
				break;
			}
			case 7075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000732);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000792, EnemyEtis);
				break;
			}
			case 7085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000733);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000793, EnemyEtis);
				break;
			}
			case 7095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000734);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000794, EnemyEtis);
				break;
			}
			case 7105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000735);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000795, EnemyEtis);
				break;
			}
			case 7115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000736);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000796, EnemyEtis);
				break;
			}
			case 7125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000737);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000797, EnemyEtis);
				break;
			}
			case 7135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000738);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000798, EnemyEtis);
				break;
			}
			case 7145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000739);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000799, EnemyEtis);
				break;
			}
			case 7155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000740);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000800, EnemyEtis);
				break;
			}
			case 7165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000741);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000801, EnemyEtis);
				break;
			}
			case 7175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000742);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000802, EnemyEtis);
				break;
			}
			case 7185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000743);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000803, EnemyEtis);
				break;
			}
			case 7195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000744);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000804, EnemyEtis);
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03);
				break;
			}
			case 7205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000745);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000805, EnemyEtis);
				break;
			}
			case 7215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000746);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000806, EnemyEtis);
				break;
			}
			case 7225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000747);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000807, EnemyEtis);
				break;
			}
			case 7235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000748);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000808, EnemyEtis);
				break;
			}
			case 7245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000749);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000809, EnemyEtis);
				break;
			}
			case 7255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000750);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000810, EnemyEtis);
				break;
			}
			case 7265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000751);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000811, EnemyEtis);
				break;
			}
			case 7275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000752);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000812, EnemyEtis);
				break;
			}
			case 7285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000753);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000813, EnemyEtis);
				break;
			}
			case 7295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000754);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000814, EnemyEtis);
				break;
			}
			case 7305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000755);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000815, EnemyEtis);
				break;
			}
			case 7315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000756);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000816, EnemyEtis);
				break;
			}
			case 7325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000757);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000817, EnemyEtis);
				break;
			}
			case 7335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000758);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000818, EnemyEtis);
				break;
			}
			case 7345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000759);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000819, EnemyEtis);
				break;
			}
			case 7355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000760);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000820, EnemyEtis);
				break;
			}
			case 7365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000761);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000821, EnemyEtis);
				break;
			}
			case 7375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000762);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000822, EnemyEtis);
				break;
			}
			case 7385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000763);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000823, EnemyEtis);
				break;
			}
			case 7395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000764);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000824, EnemyEtis);
				break;
			}
			case 7405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000765);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000825, EnemyEtis);
				break;
			}
			case 7415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000766);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000826, EnemyEtis);
				break;
			}
			case 7425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000767);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000827, EnemyEtis);
				break;
			}
			case 7435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000768);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000828, EnemyEtis);
				break;
			}
			case 7445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000769);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000829, EnemyEtis);
				break;
			}
			case 7455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000770);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000830, EnemyEtis);
				break;
			}
			case 7465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000771);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000831, EnemyEtis);
				break;
			}
			case 7475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000772);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000832, EnemyEtis);
				break;
			}
			case 7485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000773);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000833, EnemyEtis);
				break;
			}
			case 7495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000774);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000834, EnemyEtis);
				break;
			}
			case 7505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000775);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000835, EnemyEtis);
				break;
			}
			case 7515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000776);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000836, EnemyEtis);
				break;
			}
			case 7525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000777);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000837, EnemyEtis);
				break;
			}
			case 7535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000778);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000838, EnemyEtis);
				break;
			}
			case 7545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000779);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000839, EnemyEtis);
				break;
			}
			case 7555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000780);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000840, EnemyEtis);
				break;
			}
			case 7565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000781);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000841, EnemyEtis);
				break;
			}
			case 7575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000782);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000842, EnemyEtis);
				break;
			}
			case 7585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000783);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000843, EnemyEtis);
				break;
			}
			case 7595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000784);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000844, EnemyEtis);
				break;
			}
			case 7605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000785);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000845, EnemyEtis);
				break;
			}
			case 7615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000786);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000846, EnemyEtis);
				break;
			}
			case 7625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000787);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000847, EnemyEtis);
				break;
			}
			case 7635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000788);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000848, EnemyEtis);
				break;
			}
			case 7645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000789);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000849, EnemyEtis);
				break;
			}
			case 7655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000790);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000850, EnemyEtis);
				break;
			}
			case 7665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000791);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000851, EnemyEtis);
				break;
			}
			case 7675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000792);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000852, EnemyEtis);
				break;
			}
			case 7685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000793);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000853, EnemyEtis);
				break;
			}
			case 7695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000794);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000854, EnemyEtis);
				break;
			}
			case 7705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000795);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000855, EnemyEtis);
				break;
			}
			case 7715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000796);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000856, EnemyEtis);
				break;
			}
			case 7725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000797);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000857, EnemyEtis);
				break;
			}
			case 7735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000798);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000858, EnemyEtis);
				break;
			}
			case 7745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000799);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000859, EnemyEtis);
				break;
			}
			case 7755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000800);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000860, EnemyEtis);
				break;
			}
			case 7765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000801);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000861, EnemyEtis);
				break;
			}
			case 7775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000802);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000862, EnemyEtis);
				break;
			}
			case 7785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000803);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000863, EnemyEtis);
				break;
			}
			case 7795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000804);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000864, EnemyEtis);
				break;
			}
			case 7805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000805);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000865, EnemyEtis);
				break;
			}
			case 7815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000806);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000866, EnemyEtis);
				break;
			}
			case 7825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000807);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000867, EnemyEtis);
				break;
			}
			case 7835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000808);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000868, EnemyEtis);
				break;
			}
			case 7845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000809);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000869, EnemyEtis);
				break;
			}
			case 7855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000810);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000870, EnemyEtis);
				break;
			}
			case 7865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000811);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000871, EnemyEtis);
				break;
			}
			case 7875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000812);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000872, EnemyEtis);
				break;
			}
			case 7885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000813);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000873, EnemyEtis);
				break;
			}
			case 7895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000814);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000874, EnemyEtis);
				break;
			}
			case 7900: {
				requestActor(10003229, EnemyDrastea);
				break;
			}
			case 7905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000815);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000875, EnemyEtis);
				break;
			}
			case 7915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000816);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000876, EnemyEtis);
				break;
			}
			case 7925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000817);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000877, EnemyEtis);
				break;
			}
			case 7935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000818);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000878, EnemyEtis);
				break;
			}
			case 7945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000819);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000879, EnemyEtis);
				break;
			}
			case 7955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000820);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000880, EnemyEtis);
				break;
			}
			case 7965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000821);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000881, EnemyEtis);
				break;
			}
			case 7975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000822);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000882, EnemyEtis);
				break;
			}
			case 7985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000823);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000883, EnemyEtis);
				break;
			}
			case 7995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000824);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000884, EnemyEtis);
				break;
			}
			case 8005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000825);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000885, EnemyEtis);
				break;
			}
			case 8015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000826);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000886, EnemyEtis);
				break;
			}
			case 8025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000827);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000887, EnemyEtis);
				break;
			}
			case 8035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000828);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000888, EnemyEtis);
				break;
			}
			case 8045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000829);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000889, EnemyEtis);
				break;
			}
			case 8055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000830);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000890, EnemyEtis);
				break;
			}
			case 8065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000831);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000891, EnemyEtis);
				break;
			}
			case 8075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000832);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000892, EnemyEtis);
				break;
			}
			case 8085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000833);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000893, EnemyEtis);
				break;
			}
			case 8095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000834);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000894, EnemyEtis);
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				break;
			}
			case 8105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000835);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000895, EnemyEtis);
				break;
			}
			case 8115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000836);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000896, EnemyEtis);
				break;
			}
			case 8125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000837);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000897, EnemyEtis);
				break;
			}
			case 8135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000838);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000898, EnemyEtis);
				break;
			}
			case 8145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000839);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000899, EnemyEtis);
				break;
			}
			case 8155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000840);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000900, EnemyEtis);
				break;
			}
			case 8165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000841);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000901, EnemyEtis);
				break;
			}
			case 8175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000842);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000902, EnemyEtis);
				break;
			}
			case 8185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000843);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000903, EnemyEtis);
				break;
			}
			case 8195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000844);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000904, EnemyEtis);
				break;
			}
			case 8205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000845);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000905, EnemyEtis);
				break;
			}
			case 8215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000846);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000906, EnemyEtis);
				break;
			}
			case 8225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000847);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000907, EnemyEtis);
				break;
			}
			case 8235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000848);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000908, EnemyEtis);
				break;
			}
			case 8245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000849);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000909, EnemyEtis);
				break;
			}
			case 8255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000850);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000910, EnemyEtis);
				break;
			}
			case 8265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000851);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000911, EnemyEtis);
				break;
			}
			case 8275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000852);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000912, EnemyEtis);
				break;
			}
			case 8285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000853);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000913, EnemyEtis);
				break;
			}
			case 8295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000854);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000914, EnemyEtis);
				break;
			}
			case 8305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000855);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000915, EnemyEtis);
				break;
			}
			case 8315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000856);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000916, EnemyEtis);
				break;
			}
			case 8325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000857);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000917, EnemyEtis);
				break;
			}
			case 8335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000858);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000918, EnemyEtis);
				break;
			}
			case 8345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000859);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000919, EnemyEtis);
				break;
			}
			case 8355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000860);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000920, EnemyEtis);
				break;
			}
			case 8365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000861);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000921, EnemyEtis);
				break;
			}
			case 8375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000862);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000922, EnemyEtis);
				break;
			}
			case 8385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000863);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000923, EnemyEtis);
				break;
			}
			case 8395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000864);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000924, EnemyEtis);
				break;
			}
			case 8405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000865);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000925, EnemyEtis);
				break;
			}
			case 8415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000866);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000926, EnemyEtis);
				break;
			}
			case 8425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000867);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000927, EnemyEtis);
				break;
			}
			case 8435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000868);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000928, EnemyEtis);
				break;
			}
			case 8445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000869);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000929, EnemyEtis);
				break;
			}
			case 8455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000870);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000930, EnemyEtis);
				break;
			}
			case 8465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000871);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000931, EnemyEtis);
				break;
			}
			case 8475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000872);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000932, EnemyEtis);
				break;
			}
			case 8485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000873);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000933, EnemyEtis);
				break;
			}
			case 8495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000874);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000934, EnemyEtis);
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003229);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 8505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000875);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000935, EnemyEtis);
				break;
			}
			case 8515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000876);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000936, EnemyEtis);
				break;
			}
			case 8525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000877);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000937, EnemyEtis);
				break;
			}
			case 8535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000878);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000938, EnemyEtis);
				break;
			}
			case 8545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000879);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000939, EnemyEtis);
				break;
			}
			case 8555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000880);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000940, EnemyEtis);
				break;
			}
			case 8565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000881);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000941, EnemyEtis);
				break;
			}
			case 8575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000882);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000942, EnemyEtis);
				break;
			}
			case 8585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000883);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000943, EnemyEtis);
				break;
			}
			case 8595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000884);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000944, EnemyEtis);
				break;
			}
			case 8605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000885);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000945, EnemyEtis);
				break;
			}
			case 8615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000886);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000946, EnemyEtis);
				break;
			}
			case 8625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000887);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000947, EnemyEtis);
				break;
			}
			case 8635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000888);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000948, EnemyEtis);
				break;
			}
			case 8645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000889);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000949, EnemyEtis);
				break;
			}
			case 8655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000890);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000950, EnemyEtis);
				break;
			}
			case 8665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000891);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000951, EnemyEtis);
				break;
			}
			case 8675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000892);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000952, EnemyEtis);
				break;
			}
			case 8685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000893);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000953, EnemyEtis);
				break;
			}
			case 8695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000894);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000954, EnemyEtis);
				break;
			}
			case 8705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000895);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000955, EnemyEtis);
				break;
			}
			case 8715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000896);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000956, EnemyEtis);
				break;
			}
			case 8725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000897);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000957, EnemyEtis);
				break;
			}
			case 8735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000898);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000958, EnemyEtis);
				break;
			}
			case 8745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000899);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000959, EnemyEtis);
				break;
			}
			case 8755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000900);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000960, EnemyEtis);
				break;
			}
			case 8765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000901);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000961, EnemyEtis);
				break;
			}
			case 8775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000902);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000962, EnemyEtis);
				break;
			}
			case 8785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000903);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000963, EnemyEtis);
				break;
			}
			case 8795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000904);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000964, EnemyEtis);
				break;
			}
			case 8805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000905);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000965, EnemyEtis);
				break;
			}
			case 8815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000906);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000966, EnemyEtis);
				break;
			}
			case 8825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000907);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000967, EnemyEtis);
				break;
			}
			case 8835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000908);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000968, EnemyEtis);
				break;
			}
			case 8845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000909);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000969, EnemyEtis);
				break;
			}
			case 8855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000910);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000970, EnemyEtis);
				break;
			}
			case 8865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000911);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000971, EnemyEtis);
				break;
			}
			case 8875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000912);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000972, EnemyEtis);
				break;
			}
			case 8885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000913);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000973, EnemyEtis);
				break;
			}
			case 8895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000914);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000974, EnemyEtis);
				break;
			}
			case 8905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000915);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000975, EnemyEtis);
				break;
			}
			case 8915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000916);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000976, EnemyEtis);
				break;
			}
			case 8925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000917);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000977, EnemyEtis);
				break;
			}
			case 8935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000918);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000978, EnemyEtis);
				break;
			}
			case 8945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000919);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000979, EnemyEtis);
				break;
			}
			case 8955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000920);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000980, EnemyEtis);
				break;
			}
			case 8965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000921);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000981, EnemyEtis);
				break;
			}
			case 8975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000922);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000982, EnemyEtis);
				break;
			}
			case 8985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000923);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000983, EnemyEtis);
				break;
			}
			case 8995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000924);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000984, EnemyEtis);
				break;
			}
			case 9005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000925);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000985, EnemyEtis);
				break;
			}
			case 9015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000926);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000986, EnemyEtis);
				break;
			}
			case 9025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000927);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000987, EnemyEtis);
				break;
			}
			case 9035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000928);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000988, EnemyEtis);
				break;
			}
			case 9045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000929);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000989, EnemyEtis);
				break;
			}
			case 9055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000930);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000990, EnemyEtis);
				break;
			}
			case 9065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000931);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000991, EnemyEtis);
				break;
			}
			case 9075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000932);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000992, EnemyEtis);
				break;
			}
			case 9085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000933);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000993, EnemyEtis);
				break;
			}
			case 9095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000934);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000994, EnemyEtis);
				break;
			}
			case 9105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000935);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000995, EnemyEtis);
				break;
			}
			case 9115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000936);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000996, EnemyEtis);
				break;
			}
			case 9125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000937);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000997, EnemyEtis);
				break;
			}
			case 9135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000938);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000998, EnemyEtis);
				break;
			}
			case 9145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000939);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10000999, EnemyEtis);
				break;
			}
			case 9155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000940);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001000, EnemyEtis);
				break;
			}
			case 9165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000941);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001001, EnemyEtis);
				break;
			}
			case 9175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000942);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001002, EnemyEtis);
				break;
			}
			case 9185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000943);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001003, EnemyEtis);
				break;
			}
			case 9195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000944);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001004, EnemyEtis);
				break;
			}
			case 9205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000945);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001005, EnemyEtis);
				break;
			}
			case 9215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000946);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001006, EnemyEtis);
				break;
			}
			case 9225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000947);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001007, EnemyEtis);
				break;
			}
			case 9235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000948);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001008, EnemyEtis);
				break;
			}
			case 9245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000949);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001009, EnemyEtis);
				break;
			}
			case 9255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000950);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001010, EnemyEtis);
				break;
			}
			case 9265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000951);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001011, EnemyEtis);
				break;
			}
			case 9275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000952);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001012, EnemyEtis);
				break;
			}
			case 9285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000953);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001013, EnemyEtis);
				break;
			}
			case 9295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000954);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001014, EnemyEtis);
				break;
			}
			case 9305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000955);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001015, EnemyEtis);
				break;
			}
			case 9315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000956);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001016, EnemyEtis);
				break;
			}
			case 9325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000957);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001017, EnemyEtis);
				break;
			}
			case 9335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000958);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001018, EnemyEtis);
				break;
			}
			case 9345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000959);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001019, EnemyEtis);
				break;
			}
			case 9355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000960);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001020, EnemyEtis);
				break;
			}
			case 9365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000961);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001021, EnemyEtis);
				break;
			}
			case 9375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000962);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001022, EnemyEtis);
				break;
			}
			case 9385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000963);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001023, EnemyEtis);
				break;
			}
			case 9395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000964);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001024, EnemyEtis);
				break;
			}
			case 9405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000965);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001025, EnemyEtis);
				break;
			}
			case 9415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000966);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001026, EnemyEtis);
				break;
			}
			case 9425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000967);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001027, EnemyEtis);
				break;
			}
			case 9435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000968);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001028, EnemyEtis);
				break;
			}
			case 9445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000969);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001029, EnemyEtis);
				break;
			}
			case 9455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000970);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001030, EnemyEtis);
				break;
			}
			case 9465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000971);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001031, EnemyEtis);
				break;
			}
			case 9475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000972);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001032, EnemyEtis);
				break;
			}
			case 9485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000973);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001033, EnemyEtis);
				break;
			}
			case 9495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000974);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001034, EnemyEtis);
				break;
			}
			case 9505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000975);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001035, EnemyEtis);
				break;
			}
			case 9515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000976);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001036, EnemyEtis);
				break;
			}
			case 9525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000977);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001037, EnemyEtis);
				break;
			}
			case 9535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000978);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001038, EnemyEtis);
				break;
			}
			case 9545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000979);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001039, EnemyEtis);
				break;
			}
			case 9555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000980);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001040, EnemyEtis);
				break;
			}
			case 9565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000981);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001041, EnemyEtis);
				break;
			}
			case 9575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000982);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001042, EnemyEtis);
				break;
			}
			case 9585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000983);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001043, EnemyEtis);
				break;
			}
			case 9595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000984);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001044, EnemyEtis);
				break;
			}
			case 9605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000985);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001045, EnemyEtis);
				break;
			}
			case 9615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000986);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001046, EnemyEtis);
				break;
			}
			case 9625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000987);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001047, EnemyEtis);
				break;
			}
			case 9635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000988);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001048, EnemyEtis);
				break;
			}
			case 9645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000989);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001049, EnemyEtis);
				break;
			}
			case 9655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000990);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001050, EnemyEtis);
				break;
			}
			case 9665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000991);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001051, EnemyEtis);
				break;
			}
			case 9675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000992);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001052, EnemyEtis);
				break;
			}
			case 9685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000993);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001053, EnemyEtis);
				break;
			}
			case 9695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000994);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001054, EnemyEtis);
				break;
			}
			case 9705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000995);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001055, EnemyEtis);
				break;
			}
			case 9715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000996);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001056, EnemyEtis);
				break;
			}
			case 9725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000997);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001057, EnemyEtis);
				break;
			}
			case 9735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000998);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001058, EnemyEtis);
				break;
			}
			case 9745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000999);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001059, EnemyEtis);
				break;
			}
			case 9755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001000);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001060, EnemyEtis);
				break;
			}
			case 9765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001001);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001061, EnemyEtis);
				break;
			}
			case 9775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001002);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001062, EnemyEtis);
				break;
			}
			case 9785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001003);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001063, EnemyEtis);
				break;
			}
			case 9795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001004);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001064, EnemyEtis);
				break;
			}
			case 9805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001005);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001065, EnemyEtis);
				break;
			}
			case 9815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001006);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001066, EnemyEtis);
				break;
			}
			case 9825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001007);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001067, EnemyEtis);
				break;
			}
			case 9835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001008);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001068, EnemyEtis);
				break;
			}
			case 9845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001009);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001069, EnemyEtis);
				break;
			}
			case 9855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001010);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001070, EnemyEtis);
				break;
			}
			case 9865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001011);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001071, EnemyEtis);
				break;
			}
			case 9875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001012);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001072, EnemyEtis);
				break;
			}
			case 9885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001013);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001073, EnemyEtis);
				break;
			}
			case 9895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001014);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001074, EnemyEtis);
				break;
			}
			case 9900: {
				requestActor(10003230, EnemyDrastea);
				break;
			}
			case 9905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001015);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001075, EnemyEtis);
				break;
			}
			case 9915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001016);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001076, EnemyEtis);
				break;
			}
			case 9925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001017);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001077, EnemyEtis);
				break;
			}
			case 9935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001018);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001078, EnemyEtis);
				break;
			}
			case 9945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001019);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001079, EnemyEtis);
				break;
			}
			case 9955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001020);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001080, EnemyEtis);
				break;
			}
			case 9965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001021);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001081, EnemyEtis);
				break;
			}
			case 9975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001022);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001082, EnemyEtis);
				break;
			}
			case 9985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001023);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001083, EnemyEtis);
				break;
			}
			case 9995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001024);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001084, EnemyEtis);
				break;
			}
			case 10005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001025);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001085, EnemyEtis);
				break;
			}
			case 10015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001026);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001086, EnemyEtis);
				break;
			}
			case 10025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001027);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001087, EnemyEtis);
				break;
			}
			case 10035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001028);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001088, EnemyEtis);
				break;
			}
			case 10045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001029);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001089, EnemyEtis);
				break;
			}
			case 10055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001030);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001090, EnemyEtis);
				break;
			}
			case 10065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001031);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001091, EnemyEtis);
				break;
			}
			case 10075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001032);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001092, EnemyEtis);
				break;
			}
			case 10085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001033);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001093, EnemyEtis);
				break;
			}
			case 10095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001034);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001094, EnemyEtis);
				break;
			}
			case 10105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001035);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001095, EnemyEtis);
				break;
			}
			case 10115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001036);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001096, EnemyEtis);
				break;
			}
			case 10125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001037);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001097, EnemyEtis);
				break;
			}
			case 10135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001038);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001098, EnemyEtis);
				break;
			}
			case 10145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001039);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001099, EnemyEtis);
				break;
			}
			case 10155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001040);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001100, EnemyEtis);
				break;
			}
			case 10165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001041);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001101, EnemyEtis);
				break;
			}
			case 10175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001042);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001102, EnemyEtis);
				break;
			}
			case 10185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001043);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001103, EnemyEtis);
				break;
			}
			case 10195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001044);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001104, EnemyEtis);
				break;
			}
			case 10205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001045);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001105, EnemyEtis);
				break;
			}
			case 10215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001046);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001106, EnemyEtis);
				break;
			}
			case 10225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001047);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001107, EnemyEtis);
				break;
			}
			case 10235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001048);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001108, EnemyEtis);
				break;
			}
			case 10245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001049);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001109, EnemyEtis);
				break;
			}
			case 10255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001050);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001110, EnemyEtis);
				break;
			}
			case 10265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001051);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001111, EnemyEtis);
				break;
			}
			case 10275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001052);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001112, EnemyEtis);
				break;
			}
			case 10285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001053);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001113, EnemyEtis);
				break;
			}
			case 10295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001054);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001114, EnemyEtis);
				break;
			}
			case 10305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001055);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001115, EnemyEtis);
				break;
			}
			case 10315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001056);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001116, EnemyEtis);
				break;
			}
			case 10325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001057);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001117, EnemyEtis);
				break;
			}
			case 10335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001058);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001118, EnemyEtis);
				break;
			}
			case 10345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001059);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001119, EnemyEtis);
				break;
			}
			case 10355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001060);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001120, EnemyEtis);
				break;
			}
			case 10365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001061);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001121, EnemyEtis);
				break;
			}
			case 10375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001062);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001122, EnemyEtis);
				break;
			}
			case 10385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001063);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001123, EnemyEtis);
				break;
			}
			case 10395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001064);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001124, EnemyEtis);
				break;
			}
			case 10405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001065);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001125, EnemyEtis);
				break;
			}
			case 10415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001066);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001126, EnemyEtis);
				break;
			}
			case 10425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001067);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001127, EnemyEtis);
				break;
			}
			case 10435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001068);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001128, EnemyEtis);
				break;
			}
			case 10445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001069);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001129, EnemyEtis);
				break;
			}
			case 10455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001070);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001130, EnemyEtis);
				break;
			}
			case 10465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001071);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001131, EnemyEtis);
				break;
			}
			case 10475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001072);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001132, EnemyEtis);
				break;
			}
			case 10485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001073);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001133, EnemyEtis);
				break;
			}
			case 10495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001074);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001134, EnemyEtis);
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003230);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 10505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001075);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001135, EnemyEtis);
				break;
			}
			case 10515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001076);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001136, EnemyEtis);
				break;
			}
			case 10525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001077);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001137, EnemyEtis);
				break;
			}
			case 10535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001078);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001138, EnemyEtis);
				break;
			}
			case 10545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001079);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001139, EnemyEtis);
				break;
			}
			case 10555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001080);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001140, EnemyEtis);
				break;
			}
			case 10565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001081);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001141, EnemyEtis);
				break;
			}
			case 10575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001082);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001142, EnemyEtis);
				break;
			}
			case 10585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001083);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001143, EnemyEtis);
				break;
			}
			case 10595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001084);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001144, EnemyEtis);
				break;
			}
			case 10605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001085);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001145, EnemyEtis);
				break;
			}
			case 10615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001086);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001146, EnemyEtis);
				break;
			}
			case 10625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001087);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001147, EnemyEtis);
				break;
			}
			case 10635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001088);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001148, EnemyEtis);
				break;
			}
			case 10645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001089);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001149, EnemyEtis);
				break;
			}
			case 10655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001090);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001150, EnemyEtis);
				break;
			}
			case 10665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001091);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001151, EnemyEtis);
				break;
			}
			case 10675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001092);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001152, EnemyEtis);
				break;
			}
			case 10685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001093);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001153, EnemyEtis);
				break;
			}
			case 10695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001094);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001154, EnemyEtis);
				break;
			}
			case 10705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001095);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001155, EnemyEtis);
				break;
			}
			case 10715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001096);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001156, EnemyEtis);
				break;
			}
			case 10725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001097);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001157, EnemyEtis);
				break;
			}
			case 10735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001098);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001158, EnemyEtis);
				break;
			}
			case 10745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001099);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001159, EnemyEtis);
				break;
			}
			case 10755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001100);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001160, EnemyEtis);
				break;
			}
			case 10765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001101);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001161, EnemyEtis);
				break;
			}
			case 10775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001102);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001162, EnemyEtis);
				break;
			}
			case 10785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001103);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001163, EnemyEtis);
				break;
			}
			case 10795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001104);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001164, EnemyEtis);
				break;
			}
			case 10805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001105);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001165, EnemyEtis);
				break;
			}
			case 10815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001106);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001166, EnemyEtis);
				break;
			}
			case 10825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001107);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001167, EnemyEtis);
				break;
			}
			case 10835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001108);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001168, EnemyEtis);
				break;
			}
			case 10845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001109);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001169, EnemyEtis);
				break;
			}
			case 10855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001110);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001170, EnemyEtis);
				break;
			}
			case 10865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001111);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001171, EnemyEtis);
				break;
			}
			case 10875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001112);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001172, EnemyEtis);
				break;
			}
			case 10885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001113);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001173, EnemyEtis);
				break;
			}
			case 10895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001114);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001174, EnemyEtis);
				break;
			}
			case 10905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001115);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001175, EnemyEtis);
				break;
			}
			case 10915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001116);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001176, EnemyEtis);
				break;
			}
			case 10925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001117);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001177, EnemyEtis);
				break;
			}
			case 10935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001118);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001178, EnemyEtis);
				break;
			}
			case 10945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001119);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001179, EnemyEtis);
				break;
			}
			case 10955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001120);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001180, EnemyEtis);
				break;
			}
			case 10965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001121);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001181, EnemyEtis);
				break;
			}
			case 10975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001122);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001182, EnemyEtis);
				break;
			}
			case 10985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001123);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001183, EnemyEtis);
				break;
			}
			case 10995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001124);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001184, EnemyEtis);
				break;
			}
			case 11005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001125);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001185, EnemyEtis);
				break;
			}
			case 11015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001126);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001186, EnemyEtis);
				break;
			}
			case 11025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001127);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001187, EnemyEtis);
				break;
			}
			case 11035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001128);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001188, EnemyEtis);
				break;
			}
			case 11045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001129);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001189, EnemyEtis);
				break;
			}
			case 11055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001130);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001190, EnemyEtis);
				break;
			}
			case 11065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001131);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001191, EnemyEtis);
				break;
			}
			case 11075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001132);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001192, EnemyEtis);
				break;
			}
			case 11085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001133);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001193, EnemyEtis);
				break;
			}
			case 11095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001134);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001194, EnemyEtis);
				break;
			}
			case 11105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001135);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001195, EnemyEtis);
				break;
			}
			case 11115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001136);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001196, EnemyEtis);
				break;
			}
			case 11125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001137);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001197, EnemyEtis);
				break;
			}
			case 11135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001138);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001198, EnemyEtis);
				break;
			}
			case 11145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001139);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001199, EnemyEtis);
				break;
			}
			case 11155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001140);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001200, EnemyEtis);
				break;
			}
			case 11165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001141);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001201, EnemyEtis);
				break;
			}
			case 11175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001142);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001202, EnemyEtis);
				break;
			}
			case 11185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001143);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001203, EnemyEtis);
				break;
			}
			case 11195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001144);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001204, EnemyEtis);
				break;
			}
			case 11205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001145);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001205, EnemyEtis);
				break;
			}
			case 11215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001146);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001206, EnemyEtis);
				break;
			}
			case 11225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001147);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001207, EnemyEtis);
				break;
			}
			case 11235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001148);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001208, EnemyEtis);
				break;
			}
			case 11245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001149);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001209, EnemyEtis);
				break;
			}
			case 11255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001150);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001210, EnemyEtis);
				break;
			}
			case 11265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001151);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001211, EnemyEtis);
				break;
			}
			case 11275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001152);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001212, EnemyEtis);
				break;
			}
			case 11285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001153);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001213, EnemyEtis);
				break;
			}
			case 11295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001154);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001214, EnemyEtis);
				break;
			}
			case 11305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001155);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001215, EnemyEtis);
				break;
			}
			case 11315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001156);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001216, EnemyEtis);
				break;
			}
			case 11325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001157);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001217, EnemyEtis);
				break;
			}
			case 11335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001158);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001218, EnemyEtis);
				break;
			}
			case 11345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001159);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001219, EnemyEtis);
				break;
			}
			case 11355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001160);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001220, EnemyEtis);
				break;
			}
			case 11365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001161);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001221, EnemyEtis);
				break;
			}
			case 11375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001162);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001222, EnemyEtis);
				break;
			}
			case 11385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001163);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001223, EnemyEtis);
				break;
			}
			case 11395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001164);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001224, EnemyEtis);
				break;
			}
			case 11405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001165);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001225, EnemyEtis);
				break;
			}
			case 11415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001166);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001226, EnemyEtis);
				break;
			}
			case 11425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001167);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001227, EnemyEtis);
				break;
			}
			case 11435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001168);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001228, EnemyEtis);
				break;
			}
			case 11445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001169);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001229, EnemyEtis);
				break;
			}
			case 11455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001170);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001230, EnemyEtis);
				break;
			}
			case 11465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001171);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001231, EnemyEtis);
				break;
			}
			case 11475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001172);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001232, EnemyEtis);
				break;
			}
			case 11485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001173);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001233, EnemyEtis);
				break;
			}
			case 11495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001174);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001234, EnemyEtis);
				break;
			}
			case 11505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001175);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001235, EnemyEtis);
				break;
			}
			case 11515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001176);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001236, EnemyEtis);
				break;
			}
			case 11525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001177);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001237, EnemyEtis);
				break;
			}
			case 11535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001178);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001238, EnemyEtis);
				break;
			}
			case 11545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001179);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001239, EnemyEtis);
				break;
			}
			case 11555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001180);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001240, EnemyEtis);
				break;
			}
			case 11565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001181);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001241, EnemyEtis);
				break;
			}
			case 11575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001182);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001242, EnemyEtis);
				break;
			}
			case 11585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001183);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001243, EnemyEtis);
				break;
			}
			case 11595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001184);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001244, EnemyEtis);
				break;
			}
			case 11605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001185);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001245, EnemyEtis);
				break;
			}
			case 11615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001186);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001246, EnemyEtis);
				break;
			}
			case 11625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001187);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001247, EnemyEtis);
				break;
			}
			case 11635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001188);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001248, EnemyEtis);
				break;
			}
			case 11645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001189);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001249, EnemyEtis);
				break;
			}
			case 11655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001190);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001250, EnemyEtis);
				break;
			}
			case 11665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001191);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001251, EnemyEtis);
				break;
			}
			case 11675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001192);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001252, EnemyEtis);
				break;
			}
			case 11685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001193);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001253, EnemyEtis);
				break;
			}
			case 11695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001194);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001254, EnemyEtis);
				break;
			}
			case 11705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001195);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001255, EnemyEtis);
				break;
			}
			case 11715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001196);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001256, EnemyEtis);
				break;
			}
			case 11725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001197);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001257, EnemyEtis);
				break;
			}
			case 11735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001198);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001258, EnemyEtis);
				break;
			}
			case 11745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001199);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001259, EnemyEtis);
				break;
			}
			case 11755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001200);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001260, EnemyEtis);
				break;
			}
			case 11765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001201);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001261, EnemyEtis);
				break;
			}
			case 11775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001202);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001262, EnemyEtis);
				break;
			}
			case 11785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001203);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001263, EnemyEtis);
				break;
			}
			case 11795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001204);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001264, EnemyEtis);
				break;
			}
			case 11805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001205);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001265, EnemyEtis);
				break;
			}
			case 11815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001206);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001266, EnemyEtis);
				break;
			}
			case 11825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001207);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001267, EnemyEtis);
				break;
			}
			case 11835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001208);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001268, EnemyEtis);
				break;
			}
			case 11845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001209);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001269, EnemyEtis);
				break;
			}
			case 11855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001210);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001270, EnemyEtis);
				break;
			}
			case 11865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001211);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001271, EnemyEtis);
				break;
			}
			case 11875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001212);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001272, EnemyEtis);
				break;
			}
			case 11885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001213);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001273, EnemyEtis);
				break;
			}
			case 11895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001214);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001274, EnemyEtis);
				break;
			}
			case 11900: {
				requestActor(10003231, EnemyDrastea);
				break;
			}
			case 11905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001215);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001275, EnemyEtis);
				break;
			}
			case 11915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001216);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001276, EnemyEtis);
				break;
			}
			case 11925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001217);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001277, EnemyEtis);
				break;
			}
			case 11935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001218);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001278, EnemyEtis);
				break;
			}
			case 11945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001219);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001279, EnemyEtis);
				break;
			}
			case 11955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001220);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001280, EnemyEtis);
				break;
			}
			case 11965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001221);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001281, EnemyEtis);
				break;
			}
			case 11975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001222);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001282, EnemyEtis);
				break;
			}
			case 11985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001223);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001283, EnemyEtis);
				break;
			}
			case 11995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001224);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001284, EnemyEtis);
				break;
			}
			case 12005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001225);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001285, EnemyEtis);
				break;
			}
			case 12015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001226);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001286, EnemyEtis);
				break;
			}
			case 12025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001227);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001287, EnemyEtis);
				break;
			}
			case 12035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001228);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001288, EnemyEtis);
				break;
			}
			case 12045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001229);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001289, EnemyEtis);
				break;
			}
			case 12055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001230);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001290, EnemyEtis);
				break;
			}
			case 12065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001231);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001291, EnemyEtis);
				break;
			}
			case 12075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001232);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001292, EnemyEtis);
				break;
			}
			case 12085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001233);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001293, EnemyEtis);
				break;
			}
			case 12095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001234);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001294, EnemyEtis);
				break;
			}
			case 12105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001235);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001295, EnemyEtis);
				break;
			}
			case 12115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001236);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001296, EnemyEtis);
				break;
			}
			case 12125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001237);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001297, EnemyEtis);
				break;
			}
			case 12135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001238);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001298, EnemyEtis);
				break;
			}
			case 12145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001239);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001299, EnemyEtis);
				break;
			}
			case 12155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001240);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001300, EnemyEtis);
				break;
			}
			case 12165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001241);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001301, EnemyEtis);
				break;
			}
			case 12175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001242);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001302, EnemyEtis);
				break;
			}
			case 12185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001243);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001303, EnemyEtis);
				break;
			}
			case 12195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001244);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001304, EnemyEtis);
				break;
			}
			case 12205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001245);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001305, EnemyEtis);
				break;
			}
			case 12215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001246);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001306, EnemyEtis);
				break;
			}
			case 12225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001247);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001307, EnemyEtis);
				break;
			}
			case 12235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001248);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001308, EnemyEtis);
				break;
			}
			case 12245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001249);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001309, EnemyEtis);
				break;
			}
			case 12255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001250);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001310, EnemyEtis);
				break;
			}
			case 12265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001251);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001311, EnemyEtis);
				break;
			}
			case 12275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001252);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001312, EnemyEtis);
				break;
			}
			case 12285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001253);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001313, EnemyEtis);
				break;
			}
			case 12295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001254);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001314, EnemyEtis);
				break;
			}
			case 12305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001255);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001315, EnemyEtis);
				break;
			}
			case 12315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001256);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001316, EnemyEtis);
				break;
			}
			case 12325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001257);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001317, EnemyEtis);
				break;
			}
			case 12335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001258);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001318, EnemyEtis);
				break;
			}
			case 12345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001259);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001319, EnemyEtis);
				break;
			}
			case 12355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001260);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001320, EnemyEtis);
				break;
			}
			case 12365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001261);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001321, EnemyEtis);
				break;
			}
			case 12375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001262);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001322, EnemyEtis);
				break;
			}
			case 12385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001263);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001323, EnemyEtis);
				break;
			}
			case 12395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001264);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001324, EnemyEtis);
				break;
			}
			case 12405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001265);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001325, EnemyEtis);
				break;
			}
			case 12415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001266);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001326, EnemyEtis);
				break;
			}
			case 12425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001267);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001327, EnemyEtis);
				break;
			}
			case 12435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001268);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001328, EnemyEtis);
				break;
			}
			case 12445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001269);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001329, EnemyEtis);
				break;
			}
			case 12455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001270);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001330, EnemyEtis);
				break;
			}
			case 12465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001271);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001331, EnemyEtis);
				break;
			}
			case 12475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001272);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001332, EnemyEtis);
				break;
			}
			case 12485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001273);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001333, EnemyEtis);
				break;
			}
			case 12495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001274);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001334, EnemyEtis);
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003231);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 12505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001275);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001335, EnemyEtis);
				break;
			}
			case 12515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001276);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001336, EnemyEtis);
				break;
			}
			case 12525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001277);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001337, EnemyEtis);
				break;
			}
			case 12535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001278);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001338, EnemyEtis);
				break;
			}
			case 12545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001279);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001339, EnemyEtis);
				break;
			}
			case 12555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001280);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001340, EnemyEtis);
				break;
			}
			case 12565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001281);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001341, EnemyEtis);
				break;
			}
			case 12575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001282);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001342, EnemyEtis);
				break;
			}
			case 12585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001283);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001343, EnemyEtis);
				break;
			}
			case 12595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001284);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001344, EnemyEtis);
				break;
			}
			case 12605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001285);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001345, EnemyEtis);
				break;
			}
			case 12615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001286);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001346, EnemyEtis);
				break;
			}
			case 12625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001287);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001347, EnemyEtis);
				break;
			}
			case 12635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001288);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001348, EnemyEtis);
				break;
			}
			case 12645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001289);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001349, EnemyEtis);
				break;
			}
			case 12655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001290);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001350, EnemyEtis);
				break;
			}
			case 12665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001291);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001351, EnemyEtis);
				break;
			}
			case 12675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001292);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001352, EnemyEtis);
				break;
			}
			case 12685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001293);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001353, EnemyEtis);
				break;
			}
			case 12695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001294);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001354, EnemyEtis);
				break;
			}
			case 12705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001295);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001355, EnemyEtis);
				break;
			}
			case 12715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001296);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001356, EnemyEtis);
				break;
			}
			case 12725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001297);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001357, EnemyEtis);
				break;
			}
			case 12735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001298);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001358, EnemyEtis);
				break;
			}
			case 12745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001299);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001359, EnemyEtis);
				break;
			}
			case 12755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001300);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001360, EnemyEtis);
				break;
			}
			case 12765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001301);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001361, EnemyEtis);
				break;
			}
			case 12775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001302);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001362, EnemyEtis);
				break;
			}
			case 12785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001303);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001363, EnemyEtis);
				break;
			}
			case 12795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001304);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001364, EnemyEtis);
				break;
			}
			case 12805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001305);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001365, EnemyEtis);
				break;
			}
			case 12815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001306);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001366, EnemyEtis);
				break;
			}
			case 12825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001307);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001367, EnemyEtis);
				break;
			}
			case 12835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001308);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001368, EnemyEtis);
				break;
			}
			case 12845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001309);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001369, EnemyEtis);
				break;
			}
			case 12855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001310);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001370, EnemyEtis);
				break;
			}
			case 12865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001311);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001371, EnemyEtis);
				break;
			}
			case 12875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001312);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001372, EnemyEtis);
				break;
			}
			case 12885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001313);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001373, EnemyEtis);
				break;
			}
			case 12895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001314);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001374, EnemyEtis);
				break;
			}
			case 12905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001315);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001375, EnemyEtis);
				break;
			}
			case 12915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001316);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001376, EnemyEtis);
				break;
			}
			case 12925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001317);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001377, EnemyEtis);
				break;
			}
			case 12935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001318);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001378, EnemyEtis);
				break;
			}
			case 12945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001319);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001379, EnemyEtis);
				break;
			}
			case 12955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001320);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001380, EnemyEtis);
				break;
			}
			case 12965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001321);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001381, EnemyEtis);
				break;
			}
			case 12975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001322);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001382, EnemyEtis);
				break;
			}
			case 12985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001323);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001383, EnemyEtis);
				break;
			}
			case 12995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001324);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001384, EnemyEtis);
				break;
			}
			case 13005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001325);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001385, EnemyEtis);
				break;
			}
			case 13015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001326);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001386, EnemyEtis);
				break;
			}
			case 13025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001327);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001387, EnemyEtis);
				break;
			}
			case 13035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001328);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001388, EnemyEtis);
				break;
			}
			case 13045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001329);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001389, EnemyEtis);
				break;
			}
			case 13055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001330);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001390, EnemyEtis);
				break;
			}
			case 13065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001331);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001391, EnemyEtis);
				break;
			}
			case 13075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001332);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001392, EnemyEtis);
				break;
			}
			case 13085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001333);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001393, EnemyEtis);
				break;
			}
			case 13095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001334);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001394, EnemyEtis);
				break;
			}
			case 13105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001335);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001395, EnemyEtis);
				break;
			}
			case 13115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001336);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001396, EnemyEtis);
				break;
			}
			case 13125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001337);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001397, EnemyEtis);
				break;
			}
			case 13135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001338);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001398, EnemyEtis);
				break;
			}
			case 13145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001339);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001399, EnemyEtis);
				break;
			}
			case 13155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001340);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001400, EnemyEtis);
				break;
			}
			case 13165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001341);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001401, EnemyEtis);
				break;
			}
			case 13175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001342);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001402, EnemyEtis);
				break;
			}
			case 13185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001343);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001403, EnemyEtis);
				break;
			}
			case 13195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001344);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001404, EnemyEtis);
				break;
			}
			case 13205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001345);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001405, EnemyEtis);
				break;
			}
			case 13215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001346);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001406, EnemyEtis);
				break;
			}
			case 13225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001347);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001407, EnemyEtis);
				break;
			}
			case 13235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001348);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001408, EnemyEtis);
				break;
			}
			case 13245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001349);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001409, EnemyEtis);
				break;
			}
			case 13255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001350);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001410, EnemyEtis);
				break;
			}
			case 13265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001351);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001411, EnemyEtis);
				break;
			}
			case 13275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001352);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001412, EnemyEtis);
				break;
			}
			case 13285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001353);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001413, EnemyEtis);
				break;
			}
			case 13295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001354);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001414, EnemyEtis);
				break;
			}
			case 13305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001355);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001415, EnemyEtis);
				break;
			}
			case 13315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001356);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001416, EnemyEtis);
				break;
			}
			case 13325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001357);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001417, EnemyEtis);
				break;
			}
			case 13335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001358);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001418, EnemyEtis);
				break;
			}
			case 13345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001359);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001419, EnemyEtis);
				break;
			}
			case 13355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001360);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001420, EnemyEtis);
				break;
			}
			case 13365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001361);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001421, EnemyEtis);
				break;
			}
			case 13375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001362);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001422, EnemyEtis);
				break;
			}
			case 13385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001363);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001423, EnemyEtis);
				break;
			}
			case 13395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001364);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001424, EnemyEtis);
				break;
			}
			case 13405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001365);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001425, EnemyEtis);
				break;
			}
			case 13415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001366);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001426, EnemyEtis);
				break;
			}
			case 13425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001367);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001427, EnemyEtis);
				break;
			}
			case 13435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001368);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001428, EnemyEtis);
				break;
			}
			case 13445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001369);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001429, EnemyEtis);
				break;
			}
			case 13455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001370);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001430, EnemyEtis);
				break;
			}
			case 13465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001371);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001431, EnemyEtis);
				break;
			}
			case 13475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001372);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001432, EnemyEtis);
				break;
			}
			case 13485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001373);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001433, EnemyEtis);
				break;
			}
			case 13495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001374);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001434, EnemyEtis);
				break;
			}
			case 13505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001375);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001435, EnemyEtis);
				break;
			}
			case 13515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001376);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001436, EnemyEtis);
				break;
			}
			case 13525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001377);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001437, EnemyEtis);
				break;
			}
			case 13535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001378);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001438, EnemyEtis);
				break;
			}
			case 13545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001379);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001439, EnemyEtis);
				break;
			}
			case 13555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001380);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001440, EnemyEtis);
				break;
			}
			case 13565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001381);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001441, EnemyEtis);
				break;
			}
			case 13575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001382);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001442, EnemyEtis);
				break;
			}
			case 13585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001383);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001443, EnemyEtis);
				break;
			}
			case 13595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001384);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001444, EnemyEtis);
				break;
			}
			case 13605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001385);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001445, EnemyEtis);
				break;
			}
			case 13615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001386);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001446, EnemyEtis);
				break;
			}
			case 13625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001387);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001447, EnemyEtis);
				break;
			}
			case 13635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001388);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001448, EnemyEtis);
				break;
			}
			case 13645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001389);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001449, EnemyEtis);
				break;
			}
			case 13655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001390);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001450, EnemyEtis);
				break;
			}
			case 13665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001391);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001451, EnemyEtis);
				break;
			}
			case 13675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001392);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001452, EnemyEtis);
				break;
			}
			case 13685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001393);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001453, EnemyEtis);
				break;
			}
			case 13695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001394);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001454, EnemyEtis);
				break;
			}
			case 13705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001395);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001455, EnemyEtis);
				break;
			}
			case 13715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001396);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001456, EnemyEtis);
				break;
			}
			case 13725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001397);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001457, EnemyEtis);
				break;
			}
			case 13735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001398);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001458, EnemyEtis);
				break;
			}
			case 13745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001399);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001459, EnemyEtis);
				break;
			}
			case 13755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001400);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001460, EnemyEtis);
				break;
			}
			case 13765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001401);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001461, EnemyEtis);
				break;
			}
			case 13775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001402);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001462, EnemyEtis);
				break;
			}
			case 13785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001403);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001463, EnemyEtis);
				break;
			}
			case 13795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001404);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001464, EnemyEtis);
				break;
			}
			case 13805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001405);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001465, EnemyEtis);
				break;
			}
			case 13815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001406);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001466, EnemyEtis);
				break;
			}
			case 13825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001407);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001467, EnemyEtis);
				break;
			}
			case 13835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001408);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001468, EnemyEtis);
				break;
			}
			case 13845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001409);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001469, EnemyEtis);
				break;
			}
			case 13855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001410);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001470, EnemyEtis);
				break;
			}
			case 13865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001411);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001471, EnemyEtis);
				break;
			}
			case 13875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001412);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001472, EnemyEtis);
				break;
			}
			case 13885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001413);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001473, EnemyEtis);
				break;
			}
			case 13895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001414);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001474, EnemyEtis);
				break;
			}
			case 13900: {
				requestActor(10003232, EnemyDrastea);
				break;
			}
			case 13905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001415);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001475, EnemyEtis);
				break;
			}
			case 13915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001416);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001476, EnemyEtis);
				break;
			}
			case 13925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001417);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001477, EnemyEtis);
				break;
			}
			case 13935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001418);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001478, EnemyEtis);
				break;
			}
			case 13945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001419);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001479, EnemyEtis);
				break;
			}
			case 13955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001420);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001480, EnemyEtis);
				break;
			}
			case 13965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001421);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001481, EnemyEtis);
				break;
			}
			case 13975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001422);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001482, EnemyEtis);
				break;
			}
			case 13985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001423);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001483, EnemyEtis);
				break;
			}
			case 13995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001424);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001484, EnemyEtis);
				break;
			}
			case 14005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001425);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001485, EnemyEtis);
				break;
			}
			case 14015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001426);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001486, EnemyEtis);
				break;
			}
			case 14025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001427);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001487, EnemyEtis);
				break;
			}
			case 14035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001428);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001488, EnemyEtis);
				break;
			}
			case 14045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001429);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001489, EnemyEtis);
				break;
			}
			case 14055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001430);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001490, EnemyEtis);
				break;
			}
			case 14065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001431);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001491, EnemyEtis);
				break;
			}
			case 14075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001432);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001492, EnemyEtis);
				break;
			}
			case 14085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001433);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001493, EnemyEtis);
				break;
			}
			case 14095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001434);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001494, EnemyEtis);
				break;
			}
			case 14105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001435);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001495, EnemyEtis);
				break;
			}
			case 14115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001436);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001496, EnemyEtis);
				break;
			}
			case 14125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001437);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001497, EnemyEtis);
				break;
			}
			case 14135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001438);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001498, EnemyEtis);
				break;
			}
			case 14145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001439);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001499, EnemyEtis);
				break;
			}
			case 14155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001440);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001500, EnemyEtis);
				break;
			}
			case 14165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001441);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001501, EnemyEtis);
				break;
			}
			case 14175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001442);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001502, EnemyEtis);
				break;
			}
			case 14185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001443);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001503, EnemyEtis);
				break;
			}
			case 14195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001444);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001504, EnemyEtis);
				break;
			}
			case 14205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001445);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001505, EnemyEtis);
				break;
			}
			case 14215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001446);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001506, EnemyEtis);
				break;
			}
			case 14225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001447);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001507, EnemyEtis);
				break;
			}
			case 14235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001448);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001508, EnemyEtis);
				break;
			}
			case 14245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001449);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001509, EnemyEtis);
				break;
			}
			case 14255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001450);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001510, EnemyEtis);
				break;
			}
			case 14265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001451);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001511, EnemyEtis);
				break;
			}
			case 14275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001452);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001512, EnemyEtis);
				break;
			}
			case 14285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001453);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001513, EnemyEtis);
				break;
			}
			case 14295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001454);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001514, EnemyEtis);
				break;
			}
			case 14305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001455);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001515, EnemyEtis);
				break;
			}
			case 14315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001456);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001516, EnemyEtis);
				break;
			}
			case 14325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001457);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001517, EnemyEtis);
				break;
			}
			case 14335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001458);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001518, EnemyEtis);
				break;
			}
			case 14345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001459);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001519, EnemyEtis);
				break;
			}
			case 14355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001460);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001520, EnemyEtis);
				break;
			}
			case 14365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001461);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001521, EnemyEtis);
				break;
			}
			case 14375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001462);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001522, EnemyEtis);
				break;
			}
			case 14385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001463);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001523, EnemyEtis);
				break;
			}
			case 14395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001464);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001524, EnemyEtis);
				break;
			}
			case 14405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001465);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001525, EnemyEtis);
				break;
			}
			case 14415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001466);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001526, EnemyEtis);
				break;
			}
			case 14425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001467);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001527, EnemyEtis);
				break;
			}
			case 14435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001468);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001528, EnemyEtis);
				break;
			}
			case 14445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001469);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001529, EnemyEtis);
				break;
			}
			case 14455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001470);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001530, EnemyEtis);
				break;
			}
			case 14465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001471);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001531, EnemyEtis);
				break;
			}
			case 14475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001472);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001532, EnemyEtis);
				break;
			}
			case 14485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001473);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001533, EnemyEtis);
				break;
			}
			case 14495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001474);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001534, EnemyEtis);
				break;
			}
			case 14500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003232);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 14505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001475);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001535, EnemyEtis);
				break;
			}
			case 14515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001476);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001536, EnemyEtis);
				break;
			}
			case 14525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001477);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001537, EnemyEtis);
				break;
			}
			case 14535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001478);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001538, EnemyEtis);
				break;
			}
			case 14545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001479);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001539, EnemyEtis);
				break;
			}
			case 14555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001480);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001540, EnemyEtis);
				break;
			}
			case 14565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001481);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001541, EnemyEtis);
				break;
			}
			case 14575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001482);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001542, EnemyEtis);
				break;
			}
			case 14585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001483);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001543, EnemyEtis);
				break;
			}
			case 14595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001484);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001544, EnemyEtis);
				break;
			}
			case 14605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001485);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001545, EnemyEtis);
				break;
			}
			case 14615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001486);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001546, EnemyEtis);
				break;
			}
			case 14625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001487);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001547, EnemyEtis);
				break;
			}
			case 14635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001488);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001548, EnemyEtis);
				break;
			}
			case 14645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001489);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001549, EnemyEtis);
				break;
			}
			case 14655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001490);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001550, EnemyEtis);
				break;
			}
			case 14665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001491);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001551, EnemyEtis);
				break;
			}
			case 14675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001492);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001552, EnemyEtis);
				break;
			}
			case 14685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001493);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001553, EnemyEtis);
				break;
			}
			case 14695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001494);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001554, EnemyEtis);
				break;
			}
			case 14705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001495);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001555, EnemyEtis);
				break;
			}
			case 14715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001496);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001556, EnemyEtis);
				break;
			}
			case 14725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001497);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001557, EnemyEtis);
				break;
			}
			case 14735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001498);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001558, EnemyEtis);
				break;
			}
			case 14745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001499);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001559, EnemyEtis);
				break;
			}
			case 14755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001500);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001560, EnemyEtis);
				break;
			}
			case 14765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001501);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001561, EnemyEtis);
				break;
			}
			case 14775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001502);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001562, EnemyEtis);
				break;
			}
			case 14785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001503);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001563, EnemyEtis);
				break;
			}
			case 14795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001504);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001564, EnemyEtis);
				break;
			}
			case 14805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001505);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001565, EnemyEtis);
				break;
			}
			case 14815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001506);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001566, EnemyEtis);
				break;
			}
			case 14825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001507);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001567, EnemyEtis);
				break;
			}
			case 14835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001508);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001568, EnemyEtis);
				break;
			}
			case 14845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001509);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001569, EnemyEtis);
				break;
			}
			case 14855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001510);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001570, EnemyEtis);
				break;
			}
			case 14865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001511);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001571, EnemyEtis);
				break;
			}
			case 14875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001512);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001572, EnemyEtis);
				break;
			}
			case 14885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001513);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001573, EnemyEtis);
				break;
			}
			case 14895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001514);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001574, EnemyEtis);
				break;
			}
			case 14905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001515);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001575, EnemyEtis);
				break;
			}
			case 14915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001516);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001576, EnemyEtis);
				break;
			}
			case 14925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001517);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001577, EnemyEtis);
				break;
			}
			case 14935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001518);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001578, EnemyEtis);
				break;
			}
			case 14945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001519);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001579, EnemyEtis);
				break;
			}
			case 14955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001520);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001580, EnemyEtis);
				break;
			}
			case 14965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001521);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001581, EnemyEtis);
				break;
			}
			case 14975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001522);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001582, EnemyEtis);
				break;
			}
			case 14985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001523);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001583, EnemyEtis);
				break;
			}
			case 14995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001524);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001584, EnemyEtis);
				break;
			}
			case 15005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001525);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001585, EnemyEtis);
				break;
			}
			case 15015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001526);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001586, EnemyEtis);
				break;
			}
			case 15025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001527);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001587, EnemyEtis);
				break;
			}
			case 15035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001528);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001588, EnemyEtis);
				break;
			}
			case 15045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001529);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001589, EnemyEtis);
				break;
			}
			case 15055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001530);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001590, EnemyEtis);
				break;
			}
			case 15065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001531);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001591, EnemyEtis);
				break;
			}
			case 15075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001532);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001592, EnemyEtis);
				break;
			}
			case 15085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001533);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001593, EnemyEtis);
				break;
			}
			case 15095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001534);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001594, EnemyEtis);
				break;
			}
			case 15105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001535);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001595, EnemyEtis);
				break;
			}
			case 15115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001536);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001596, EnemyEtis);
				break;
			}
			case 15125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001537);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001597, EnemyEtis);
				break;
			}
			case 15135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001538);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001598, EnemyEtis);
				break;
			}
			case 15145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001539);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001599, EnemyEtis);
				break;
			}
			case 15155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001540);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001600, EnemyEtis);
				break;
			}
			case 15165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001541);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001601, EnemyEtis);
				break;
			}
			case 15175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001542);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001602, EnemyEtis);
				break;
			}
			case 15185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001543);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001603, EnemyEtis);
				break;
			}
			case 15195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001544);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001604, EnemyEtis);
				break;
			}
			case 15205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001545);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001605, EnemyEtis);
				break;
			}
			case 15215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001546);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001606, EnemyEtis);
				break;
			}
			case 15225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001547);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001607, EnemyEtis);
				break;
			}
			case 15235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001548);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001608, EnemyEtis);
				break;
			}
			case 15245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001549);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001609, EnemyEtis);
				break;
			}
			case 15255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001550);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001610, EnemyEtis);
				break;
			}
			case 15265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001551);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001611, EnemyEtis);
				break;
			}
			case 15275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001552);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001612, EnemyEtis);
				break;
			}
			case 15285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001553);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001613, EnemyEtis);
				break;
			}
			case 15295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001554);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001614, EnemyEtis);
				break;
			}
			case 15305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001555);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001615, EnemyEtis);
				break;
			}
			case 15315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001556);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001616, EnemyEtis);
				break;
			}
			case 15325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001557);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001617, EnemyEtis);
				break;
			}
			case 15335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001558);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001618, EnemyEtis);
				break;
			}
			case 15345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001559);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001619, EnemyEtis);
				break;
			}
			case 15355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001560);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001620, EnemyEtis);
				break;
			}
			case 15365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001561);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001621, EnemyEtis);
				break;
			}
			case 15375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001562);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001622, EnemyEtis);
				break;
			}
			case 15385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001563);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001623, EnemyEtis);
				break;
			}
			case 15395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001564);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001624, EnemyEtis);
				break;
			}
			case 15405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001565);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001625, EnemyEtis);
				break;
			}
			case 15415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001566);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001626, EnemyEtis);
				break;
			}
			case 15425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001567);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001627, EnemyEtis);
				break;
			}
			case 15435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001568);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001628, EnemyEtis);
				break;
			}
			case 15445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001569);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001629, EnemyEtis);
				break;
			}
			case 15455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001570);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001630, EnemyEtis);
				break;
			}
			case 15465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001571);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001631, EnemyEtis);
				break;
			}
			case 15475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001572);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001632, EnemyEtis);
				break;
			}
			case 15485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001573);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001633, EnemyEtis);
				break;
			}
			case 15495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001574);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001634, EnemyEtis);
				break;
			}
			case 15505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001575);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001635, EnemyEtis);
				break;
			}
			case 15515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001576);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001636, EnemyEtis);
				break;
			}
			case 15525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001577);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001637, EnemyEtis);
				break;
			}
			case 15535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001578);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001638, EnemyEtis);
				break;
			}
			case 15545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001579);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001639, EnemyEtis);
				break;
			}
			case 15555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001580);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001640, EnemyEtis);
				break;
			}
			case 15565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001581);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001641, EnemyEtis);
				break;
			}
			case 15575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001582);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001642, EnemyEtis);
				break;
			}
			case 15585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001583);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001643, EnemyEtis);
				break;
			}
			case 15595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001584);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001644, EnemyEtis);
				break;
			}
			case 15605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001585);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001645, EnemyEtis);
				break;
			}
			case 15615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001586);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001646, EnemyEtis);
				break;
			}
			case 15625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001587);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001647, EnemyEtis);
				break;
			}
			case 15635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001588);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001648, EnemyEtis);
				break;
			}
			case 15645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001589);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001649, EnemyEtis);
				break;
			}
			case 15655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001590);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001650, EnemyEtis);
				break;
			}
			case 15665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001591);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001651, EnemyEtis);
				break;
			}
			case 15675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001592);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001652, EnemyEtis);
				break;
			}
			case 15685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001593);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001653, EnemyEtis);
				break;
			}
			case 15695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001594);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001654, EnemyEtis);
				break;
			}
			case 15705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001595);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001655, EnemyEtis);
				break;
			}
			case 15715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001596);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001656, EnemyEtis);
				break;
			}
			case 15725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001597);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001657, EnemyEtis);
				break;
			}
			case 15735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001598);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001658, EnemyEtis);
				break;
			}
			case 15745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001599);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001659, EnemyEtis);
				break;
			}
			case 15755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001600);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001660, EnemyEtis);
				break;
			}
			case 15765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001601);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001661, EnemyEtis);
				break;
			}
			case 15775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001602);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001662, EnemyEtis);
				break;
			}
			case 15785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001603);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001663, EnemyEtis);
				break;
			}
			case 15795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001604);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001664, EnemyEtis);
				break;
			}
			case 15805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001605);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001665, EnemyEtis);
				break;
			}
			case 15815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001606);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001666, EnemyEtis);
				break;
			}
			case 15825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001607);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001667, EnemyEtis);
				break;
			}
			case 15835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001608);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001668, EnemyEtis);
				break;
			}
			case 15845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001609);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001669, EnemyEtis);
				break;
			}
			case 15855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001610);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001670, EnemyEtis);
				break;
			}
			case 15865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001611);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001671, EnemyEtis);
				break;
			}
			case 15875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001612);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001672, EnemyEtis);
				break;
			}
			case 15885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001613);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001673, EnemyEtis);
				break;
			}
			case 15895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001614);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001674, EnemyEtis);
				break;
			}
			case 15900: {
				requestActor(10003233, EnemyDrastea);
				break;
			}
			case 15905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001615);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001675, EnemyEtis);
				break;
			}
			case 15915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001616);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001676, EnemyEtis);
				break;
			}
			case 15925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001617);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001677, EnemyEtis);
				break;
			}
			case 15935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001618);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001678, EnemyEtis);
				break;
			}
			case 15945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001619);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001679, EnemyEtis);
				break;
			}
			case 15955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001620);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001680, EnemyEtis);
				break;
			}
			case 15965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001621);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001681, EnemyEtis);
				break;
			}
			case 15975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001622);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001682, EnemyEtis);
				break;
			}
			case 15985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001623);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001683, EnemyEtis);
				break;
			}
			case 15995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001624);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001684, EnemyEtis);
				break;
			}
			case 16005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001625);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001685, EnemyEtis);
				break;
			}
			case 16015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001626);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001686, EnemyEtis);
				break;
			}
			case 16025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001627);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001687, EnemyEtis);
				break;
			}
			case 16035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001628);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001688, EnemyEtis);
				break;
			}
			case 16045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001629);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001689, EnemyEtis);
				break;
			}
			case 16055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001630);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001690, EnemyEtis);
				break;
			}
			case 16065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001631);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001691, EnemyEtis);
				break;
			}
			case 16075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001632);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001692, EnemyEtis);
				break;
			}
			case 16085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001633);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001693, EnemyEtis);
				break;
			}
			case 16095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001634);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001694, EnemyEtis);
				break;
			}
			case 16105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001635);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001695, EnemyEtis);
				break;
			}
			case 16115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001636);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001696, EnemyEtis);
				break;
			}
			case 16125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001637);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001697, EnemyEtis);
				break;
			}
			case 16135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001638);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001698, EnemyEtis);
				break;
			}
			case 16145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001639);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001699, EnemyEtis);
				break;
			}
			case 16155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001640);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001700, EnemyEtis);
				break;
			}
			case 16165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001641);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001701, EnemyEtis);
				break;
			}
			case 16175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001642);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001702, EnemyEtis);
				break;
			}
			case 16185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001643);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001703, EnemyEtis);
				break;
			}
			case 16195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001644);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001704, EnemyEtis);
				break;
			}
			case 16205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001645);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001705, EnemyEtis);
				break;
			}
			case 16215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001646);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001706, EnemyEtis);
				break;
			}
			case 16225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001647);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001707, EnemyEtis);
				break;
			}
			case 16235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001648);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001708, EnemyEtis);
				break;
			}
			case 16245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001649);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001709, EnemyEtis);
				break;
			}
			case 16255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001650);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001710, EnemyEtis);
				break;
			}
			case 16265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001651);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001711, EnemyEtis);
				break;
			}
			case 16275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001652);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001712, EnemyEtis);
				break;
			}
			case 16285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001653);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001713, EnemyEtis);
				break;
			}
			case 16295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001654);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001714, EnemyEtis);
				break;
			}
			case 16305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001655);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001715, EnemyEtis);
				break;
			}
			case 16315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001656);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001716, EnemyEtis);
				break;
			}
			case 16325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001657);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001717, EnemyEtis);
				break;
			}
			case 16335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001658);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001718, EnemyEtis);
				break;
			}
			case 16345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001659);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001719, EnemyEtis);
				break;
			}
			case 16355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001660);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001720, EnemyEtis);
				break;
			}
			case 16365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001661);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001721, EnemyEtis);
				break;
			}
			case 16375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001662);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001722, EnemyEtis);
				break;
			}
			case 16385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001663);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001723, EnemyEtis);
				break;
			}
			case 16395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001664);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001724, EnemyEtis);
				break;
			}
			case 16405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001665);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001725, EnemyEtis);
				break;
			}
			case 16415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001666);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001726, EnemyEtis);
				break;
			}
			case 16425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001667);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001727, EnemyEtis);
				break;
			}
			case 16435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001668);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001728, EnemyEtis);
				break;
			}
			case 16445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001669);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001729, EnemyEtis);
				break;
			}
			case 16455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001670);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001730, EnemyEtis);
				break;
			}
			case 16465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001671);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001731, EnemyEtis);
				break;
			}
			case 16475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001672);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001732, EnemyEtis);
				break;
			}
			case 16485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001673);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001733, EnemyEtis);
				break;
			}
			case 16495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001674);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001734, EnemyEtis);
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003233);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 16505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001675);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001735, EnemyEtis);
				break;
			}
			case 16515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001676);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001736, EnemyEtis);
				break;
			}
			case 16525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001677);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001737, EnemyEtis);
				break;
			}
			case 16535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001678);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001738, EnemyEtis);
				break;
			}
			case 16545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001679);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001739, EnemyEtis);
				break;
			}
			case 16555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001680);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001740, EnemyEtis);
				break;
			}
			case 16565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001681);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001741, EnemyEtis);
				break;
			}
			case 16575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001682);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001742, EnemyEtis);
				break;
			}
			case 16585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001683);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001743, EnemyEtis);
				break;
			}
			case 16595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001684);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001744, EnemyEtis);
				break;
			}
			case 16605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001685);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001745, EnemyEtis);
				break;
			}
			case 16615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001686);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001746, EnemyEtis);
				break;
			}
			case 16625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001687);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001747, EnemyEtis);
				break;
			}
			case 16635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001688);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001748, EnemyEtis);
				break;
			}
			case 16645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001689);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001749, EnemyEtis);
				break;
			}
			case 16655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001690);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001750, EnemyEtis);
				break;
			}
			case 16665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001691);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001751, EnemyEtis);
				break;
			}
			case 16675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001692);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001752, EnemyEtis);
				break;
			}
			case 16685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001693);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001753, EnemyEtis);
				break;
			}
			case 16695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001694);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001754, EnemyEtis);
				break;
			}
			case 16705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001695);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001755, EnemyEtis);
				break;
			}
			case 16715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001696);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001756, EnemyEtis);
				break;
			}
			case 16725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001697);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001757, EnemyEtis);
				break;
			}
			case 16735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001698);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001758, EnemyEtis);
				break;
			}
			case 16745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001699);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001759, EnemyEtis);
				break;
			}
			case 16755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001700);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001760, EnemyEtis);
				break;
			}
			case 16765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001701);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001761, EnemyEtis);
				break;
			}
			case 16775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001702);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001762, EnemyEtis);
				break;
			}
			case 16785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001703);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001763, EnemyEtis);
				break;
			}
			case 16795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001704);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001764, EnemyEtis);
				break;
			}
			case 16805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001705);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001765, EnemyEtis);
				break;
			}
			case 16815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001706);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001766, EnemyEtis);
				break;
			}
			case 16825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001707);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001767, EnemyEtis);
				break;
			}
			case 16835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001708);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001768, EnemyEtis);
				break;
			}
			case 16845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001709);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001769, EnemyEtis);
				break;
			}
			case 16855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001710);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001770, EnemyEtis);
				break;
			}
			case 16865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001711);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001771, EnemyEtis);
				break;
			}
			case 16875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001712);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001772, EnemyEtis);
				break;
			}
			case 16885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001713);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001773, EnemyEtis);
				break;
			}
			case 16895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001714);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001774, EnemyEtis);
				break;
			}
			case 16905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001715);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001775, EnemyEtis);
				break;
			}
			case 16915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001716);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001776, EnemyEtis);
				break;
			}
			case 16925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001717);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001777, EnemyEtis);
				break;
			}
			case 16935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001718);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001778, EnemyEtis);
				break;
			}
			case 16945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001719);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001779, EnemyEtis);
				break;
			}
			case 16955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001720);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001780, EnemyEtis);
				break;
			}
			case 16965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001721);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001781, EnemyEtis);
				break;
			}
			case 16975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001722);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001782, EnemyEtis);
				break;
			}
			case 16985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001723);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001783, EnemyEtis);
				break;
			}
			case 16995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001724);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001784, EnemyEtis);
				break;
			}
			case 17005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001725);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001785, EnemyEtis);
				break;
			}
			case 17015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001726);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001786, EnemyEtis);
				break;
			}
			case 17025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001727);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001787, EnemyEtis);
				break;
			}
			case 17035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001728);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001788, EnemyEtis);
				break;
			}
			case 17045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001729);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001789, EnemyEtis);
				break;
			}
			case 17055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001730);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001790, EnemyEtis);
				break;
			}
			case 17065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001731);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001791, EnemyEtis);
				break;
			}
			case 17075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001732);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001792, EnemyEtis);
				break;
			}
			case 17085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001733);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001793, EnemyEtis);
				break;
			}
			case 17095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001734);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001794, EnemyEtis);
				break;
			}
			case 17105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001735);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001795, EnemyEtis);
				break;
			}
			case 17115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001736);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001796, EnemyEtis);
				break;
			}
			case 17125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001737);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001797, EnemyEtis);
				break;
			}
			case 17135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001738);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001798, EnemyEtis);
				break;
			}
			case 17145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001739);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001799, EnemyEtis);
				break;
			}
			case 17155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001740);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001800, EnemyEtis);
				break;
			}
			case 17165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001741);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001801, EnemyEtis);
				break;
			}
			case 17175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001742);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001802, EnemyEtis);
				break;
			}
			case 17185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001743);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001803, EnemyEtis);
				break;
			}
			case 17195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001744);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001804, EnemyEtis);
				break;
			}
			case 17205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001745);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001805, EnemyEtis);
				break;
			}
			case 17215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001746);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001806, EnemyEtis);
				break;
			}
			case 17225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001747);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001807, EnemyEtis);
				break;
			}
			case 17235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001748);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001808, EnemyEtis);
				break;
			}
			case 17245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001749);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001809, EnemyEtis);
				break;
			}
			case 17255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001750);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001810, EnemyEtis);
				break;
			}
			case 17265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001751);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001811, EnemyEtis);
				break;
			}
			case 17275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001752);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001812, EnemyEtis);
				break;
			}
			case 17285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001753);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001813, EnemyEtis);
				break;
			}
			case 17295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001754);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001814, EnemyEtis);
				break;
			}
			case 17305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001755);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001815, EnemyEtis);
				break;
			}
			case 17315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001756);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001816, EnemyEtis);
				break;
			}
			case 17325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001757);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001817, EnemyEtis);
				break;
			}
			case 17335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001758);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001818, EnemyEtis);
				break;
			}
			case 17345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001759);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001819, EnemyEtis);
				break;
			}
			case 17355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001760);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001820, EnemyEtis);
				break;
			}
			case 17365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001761);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001821, EnemyEtis);
				break;
			}
			case 17375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001762);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001822, EnemyEtis);
				break;
			}
			case 17385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001763);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001823, EnemyEtis);
				break;
			}
			case 17395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001764);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001824, EnemyEtis);
				break;
			}
			case 17405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001765);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001825, EnemyEtis);
				break;
			}
			case 17415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001766);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001826, EnemyEtis);
				break;
			}
			case 17425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001767);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001827, EnemyEtis);
				break;
			}
			case 17435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001768);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001828, EnemyEtis);
				break;
			}
			case 17445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001769);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001829, EnemyEtis);
				break;
			}
			case 17455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001770);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001830, EnemyEtis);
				break;
			}
			case 17465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001771);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001831, EnemyEtis);
				break;
			}
			case 17475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001772);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001832, EnemyEtis);
				break;
			}
			case 17485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001773);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001833, EnemyEtis);
				break;
			}
			case 17495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001774);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001834, EnemyEtis);
				break;
			}
			case 17505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001775);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001835, EnemyEtis);
				break;
			}
			case 17515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001776);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001836, EnemyEtis);
				break;
			}
			case 17525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001777);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001837, EnemyEtis);
				break;
			}
			case 17535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001778);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001838, EnemyEtis);
				break;
			}
			case 17545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001779);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001839, EnemyEtis);
				break;
			}
			case 17555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001780);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001840, EnemyEtis);
				break;
			}
			case 17565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001781);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001841, EnemyEtis);
				break;
			}
			case 17575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001782);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001842, EnemyEtis);
				break;
			}
			case 17585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001783);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001843, EnemyEtis);
				break;
			}
			case 17595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001784);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001844, EnemyEtis);
				break;
			}
			case 17605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001785);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001845, EnemyEtis);
				break;
			}
			case 17615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001786);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001846, EnemyEtis);
				break;
			}
			case 17625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001787);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001847, EnemyEtis);
				break;
			}
			case 17635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001788);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001848, EnemyEtis);
				break;
			}
			case 17645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001789);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001849, EnemyEtis);
				break;
			}
			case 17655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001790);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001850, EnemyEtis);
				break;
			}
			case 17665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001791);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001851, EnemyEtis);
				break;
			}
			case 17675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001792);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001852, EnemyEtis);
				break;
			}
			case 17685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001793);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001853, EnemyEtis);
				break;
			}
			case 17695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001794);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001854, EnemyEtis);
				break;
			}
			case 17705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001795);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001855, EnemyEtis);
				break;
			}
			case 17715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001796);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001856, EnemyEtis);
				break;
			}
			case 17725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001797);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001857, EnemyEtis);
				break;
			}
			case 17735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001798);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001858, EnemyEtis);
				break;
			}
			case 17745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001799);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001859, EnemyEtis);
				break;
			}
			case 17755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001800);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001860, EnemyEtis);
				break;
			}
			case 17765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001801);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001861, EnemyEtis);
				break;
			}
			case 17775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001802);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001862, EnemyEtis);
				break;
			}
			case 17785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001803);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001863, EnemyEtis);
				break;
			}
			case 17795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001804);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001864, EnemyEtis);
				break;
			}
			case 17805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001805);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001865, EnemyEtis);
				break;
			}
			case 17815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001806);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001866, EnemyEtis);
				break;
			}
			case 17825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001807);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001867, EnemyEtis);
				break;
			}
			case 17835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001808);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001868, EnemyEtis);
				break;
			}
			case 17845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001809);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001869, EnemyEtis);
				break;
			}
			case 17855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001810);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001870, EnemyEtis);
				break;
			}
			case 17865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001811);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001871, EnemyEtis);
				break;
			}
			case 17875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001812);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001872, EnemyEtis);
				break;
			}
			case 17885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001813);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001873, EnemyEtis);
				break;
			}
			case 17895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001814);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001874, EnemyEtis);
				break;
			}
			case 17900: {
				requestActor(10003234, EnemyDrastea);
				break;
			}
			case 17905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001815);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001875, EnemyEtis);
				break;
			}
			case 17915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001816);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001876, EnemyEtis);
				break;
			}
			case 17925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001817);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001877, EnemyEtis);
				break;
			}
			case 17935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001818);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001878, EnemyEtis);
				break;
			}
			case 17945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001819);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001879, EnemyEtis);
				break;
			}
			case 17955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001820);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001880, EnemyEtis);
				break;
			}
			case 17965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001821);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001881, EnemyEtis);
				break;
			}
			case 17975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001822);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001882, EnemyEtis);
				break;
			}
			case 17985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001823);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001883, EnemyEtis);
				break;
			}
			case 17995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001824);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001884, EnemyEtis);
				break;
			}
			case 18005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001825);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001885, EnemyEtis);
				break;
			}
			case 18015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001826);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001886, EnemyEtis);
				break;
			}
			case 18025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001827);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001887, EnemyEtis);
				break;
			}
			case 18035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001828);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001888, EnemyEtis);
				break;
			}
			case 18045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001829);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001889, EnemyEtis);
				break;
			}
			case 18055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001830);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001890, EnemyEtis);
				break;
			}
			case 18065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001831);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001891, EnemyEtis);
				break;
			}
			case 18075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001832);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001892, EnemyEtis);
				break;
			}
			case 18085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001833);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001893, EnemyEtis);
				break;
			}
			case 18095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001834);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001894, EnemyEtis);
				break;
			}
			case 18105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001835);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001895, EnemyEtis);
				break;
			}
			case 18115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001836);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001896, EnemyEtis);
				break;
			}
			case 18125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001837);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001897, EnemyEtis);
				break;
			}
			case 18135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001838);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001898, EnemyEtis);
				break;
			}
			case 18145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001839);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001899, EnemyEtis);
				break;
			}
			case 18155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001840);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001900, EnemyEtis);
				break;
			}
			case 18165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001841);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001901, EnemyEtis);
				break;
			}
			case 18175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001842);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001902, EnemyEtis);
				break;
			}
			case 18185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001843);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001903, EnemyEtis);
				break;
			}
			case 18195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001844);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001904, EnemyEtis);
				break;
			}
			case 18205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001845);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001905, EnemyEtis);
				break;
			}
			case 18215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001846);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001906, EnemyEtis);
				break;
			}
			case 18225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001847);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001907, EnemyEtis);
				break;
			}
			case 18235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001848);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001908, EnemyEtis);
				break;
			}
			case 18245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001849);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001909, EnemyEtis);
				break;
			}
			case 18255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001850);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001910, EnemyEtis);
				break;
			}
			case 18265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001851);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001911, EnemyEtis);
				break;
			}
			case 18275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001852);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001912, EnemyEtis);
				break;
			}
			case 18285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001853);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001913, EnemyEtis);
				break;
			}
			case 18295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001854);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001914, EnemyEtis);
				break;
			}
			case 18305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001855);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001915, EnemyEtis);
				break;
			}
			case 18315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001856);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001916, EnemyEtis);
				break;
			}
			case 18325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001857);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001917, EnemyEtis);
				break;
			}
			case 18335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001858);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001918, EnemyEtis);
				break;
			}
			case 18345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001859);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001919, EnemyEtis);
				break;
			}
			case 18355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001860);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001920, EnemyEtis);
				break;
			}
			case 18365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001861);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001921, EnemyEtis);
				break;
			}
			case 18375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001862);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001922, EnemyEtis);
				break;
			}
			case 18385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001863);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001923, EnemyEtis);
				break;
			}
			case 18395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001864);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001924, EnemyEtis);
				break;
			}
			case 18405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001865);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001925, EnemyEtis);
				break;
			}
			case 18415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001866);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001926, EnemyEtis);
				break;
			}
			case 18425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001867);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001927, EnemyEtis);
				break;
			}
			case 18435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001868);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001928, EnemyEtis);
				break;
			}
			case 18445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001869);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001929, EnemyEtis);
				break;
			}
			case 18455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001870);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001930, EnemyEtis);
				break;
			}
			case 18465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001871);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001931, EnemyEtis);
				break;
			}
			case 18475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001872);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001932, EnemyEtis);
				break;
			}
			case 18485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001873);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001933, EnemyEtis);
				break;
			}
			case 18495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001874);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001934, EnemyEtis);
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003234);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 18505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001875);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001935, EnemyEtis);
				break;
			}
			case 18515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001876);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001936, EnemyEtis);
				break;
			}
			case 18525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001877);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001937, EnemyEtis);
				break;
			}
			case 18535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001878);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001938, EnemyEtis);
				break;
			}
			case 18545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001879);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001939, EnemyEtis);
				break;
			}
			case 18555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001880);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001940, EnemyEtis);
				break;
			}
			case 18565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001881);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001941, EnemyEtis);
				break;
			}
			case 18575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001882);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001942, EnemyEtis);
				break;
			}
			case 18585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001883);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001943, EnemyEtis);
				break;
			}
			case 18595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001884);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001944, EnemyEtis);
				break;
			}
			case 18605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001885);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001945, EnemyEtis);
				break;
			}
			case 18615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001886);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001946, EnemyEtis);
				break;
			}
			case 18625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001887);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001947, EnemyEtis);
				break;
			}
			case 18635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001888);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001948, EnemyEtis);
				break;
			}
			case 18645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001889);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001949, EnemyEtis);
				break;
			}
			case 18655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001890);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001950, EnemyEtis);
				break;
			}
			case 18665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001891);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001951, EnemyEtis);
				break;
			}
			case 18675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001892);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001952, EnemyEtis);
				break;
			}
			case 18685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001893);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001953, EnemyEtis);
				break;
			}
			case 18695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001894);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001954, EnemyEtis);
				break;
			}
			case 18705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001895);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001955, EnemyEtis);
				break;
			}
			case 18715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001896);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001956, EnemyEtis);
				break;
			}
			case 18725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001897);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001957, EnemyEtis);
				break;
			}
			case 18735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001898);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001958, EnemyEtis);
				break;
			}
			case 18745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001899);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001959, EnemyEtis);
				break;
			}
			case 18755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001900);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001960, EnemyEtis);
				break;
			}
			case 18765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001901);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001961, EnemyEtis);
				break;
			}
			case 18775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001902);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001962, EnemyEtis);
				break;
			}
			case 18785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001903);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001963, EnemyEtis);
				break;
			}
			case 18795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001904);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001964, EnemyEtis);
				break;
			}
			case 18805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001905);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001965, EnemyEtis);
				break;
			}
			case 18815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001906);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001966, EnemyEtis);
				break;
			}
			case 18825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001907);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001967, EnemyEtis);
				break;
			}
			case 18835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001908);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001968, EnemyEtis);
				break;
			}
			case 18845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001909);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001969, EnemyEtis);
				break;
			}
			case 18855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001910);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001970, EnemyEtis);
				break;
			}
			case 18865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001911);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001971, EnemyEtis);
				break;
			}
			case 18875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001912);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001972, EnemyEtis);
				break;
			}
			case 18885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001913);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001973, EnemyEtis);
				break;
			}
			case 18895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001914);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001974, EnemyEtis);
				break;
			}
			case 18905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001915);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001975, EnemyEtis);
				break;
			}
			case 18915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001916);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001976, EnemyEtis);
				break;
			}
			case 18925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001917);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001977, EnemyEtis);
				break;
			}
			case 18935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001918);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001978, EnemyEtis);
				break;
			}
			case 18945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001919);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001979, EnemyEtis);
				break;
			}
			case 18955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001920);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001980, EnemyEtis);
				break;
			}
			case 18965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001921);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001981, EnemyEtis);
				break;
			}
			case 18975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001922);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001982, EnemyEtis);
				break;
			}
			case 18985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001923);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001983, EnemyEtis);
				break;
			}
			case 18995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001924);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001984, EnemyEtis);
				break;
			}
			case 19005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001925);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001985, EnemyEtis);
				break;
			}
			case 19015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001926);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001986, EnemyEtis);
				break;
			}
			case 19025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001927);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001987, EnemyEtis);
				break;
			}
			case 19035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001928);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001988, EnemyEtis);
				break;
			}
			case 19045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001929);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001989, EnemyEtis);
				break;
			}
			case 19055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001930);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001990, EnemyEtis);
				break;
			}
			case 19065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001931);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001991, EnemyEtis);
				break;
			}
			case 19075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001932);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001992, EnemyEtis);
				break;
			}
			case 19085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001933);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001993, EnemyEtis);
				break;
			}
			case 19095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001934);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001994, EnemyEtis);
				break;
			}
			case 19105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001935);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001995, EnemyEtis);
				break;
			}
			case 19115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001936);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001996, EnemyEtis);
				break;
			}
			case 19125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001937);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001997, EnemyEtis);
				break;
			}
			case 19135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001938);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001998, EnemyEtis);
				break;
			}
			case 19145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001939);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10001999, EnemyEtis);
				break;
			}
			case 19155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001940);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002000, EnemyEtis);
				break;
			}
			case 19165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001941);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002001, EnemyEtis);
				break;
			}
			case 19175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001942);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002002, EnemyEtis);
				break;
			}
			case 19185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001943);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002003, EnemyEtis);
				break;
			}
			case 19195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001944);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002004, EnemyEtis);
				break;
			}
			case 19205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001945);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002005, EnemyEtis);
				break;
			}
			case 19215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001946);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002006, EnemyEtis);
				break;
			}
			case 19225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001947);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002007, EnemyEtis);
				break;
			}
			case 19235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001948);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002008, EnemyEtis);
				break;
			}
			case 19245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001949);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002009, EnemyEtis);
				break;
			}
			case 19255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001950);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002010, EnemyEtis);
				break;
			}
			case 19265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001951);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002011, EnemyEtis);
				break;
			}
			case 19275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001952);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002012, EnemyEtis);
				break;
			}
			case 19285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001953);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002013, EnemyEtis);
				break;
			}
			case 19295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001954);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002014, EnemyEtis);
				break;
			}
			case 19305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001955);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002015, EnemyEtis);
				break;
			}
			case 19315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001956);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002016, EnemyEtis);
				break;
			}
			case 19325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001957);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002017, EnemyEtis);
				break;
			}
			case 19335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001958);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002018, EnemyEtis);
				break;
			}
			case 19345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001959);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002019, EnemyEtis);
				break;
			}
			case 19355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001960);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002020, EnemyEtis);
				break;
			}
			case 19365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001961);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002021, EnemyEtis);
				break;
			}
			case 19375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001962);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002022, EnemyEtis);
				break;
			}
			case 19385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001963);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002023, EnemyEtis);
				break;
			}
			case 19395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001964);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002024, EnemyEtis);
				break;
			}
			case 19400: {
				requestActor(10003256, VarietyRatislavia001);
				break;
			}
			case 19405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001965);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002025, EnemyEtis);
				break;
			}
			case 19415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001966);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002026, EnemyEtis);
				break;
			}
			case 19425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001967);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002027, EnemyEtis);
				break;
			}
			case 19435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001968);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002028, EnemyEtis);
				break;
			}
			case 19445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001969);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002029, EnemyEtis);
				break;
			}
			case 19455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001970);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002030, EnemyEtis);
				break;
			}
			case 19465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001971);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002031, EnemyEtis);
				break;
			}
			case 19475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001972);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002032, EnemyEtis);
				break;
			}
			case 19485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001973);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002033, EnemyEtis);
				break;
			}
			case 19495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001974);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002034, EnemyEtis);
				break;
			}
			case 19505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001975);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002035, EnemyEtis);
				break;
			}
			case 19515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001976);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002036, EnemyEtis);
				break;
			}
			case 19525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001977);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002037, EnemyEtis);
				break;
			}
			case 19535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001978);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002038, EnemyEtis);
				break;
			}
			case 19545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001979);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002039, EnemyEtis);
				break;
			}
			case 19555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001980);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002040, EnemyEtis);
				break;
			}
			case 19565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001981);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002041, EnemyEtis);
				break;
			}
			case 19575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001982);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002042, EnemyEtis);
				break;
			}
			case 19585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001983);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002043, EnemyEtis);
				break;
			}
			case 19595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001984);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002044, EnemyEtis);
				break;
			}
			case 19605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001985);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002045, EnemyEtis);
				break;
			}
			case 19615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001986);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002046, EnemyEtis);
				break;
			}
			case 19625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001987);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002047, EnemyEtis);
				break;
			}
			case 19635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001988);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002048, EnemyEtis);
				break;
			}
			case 19645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001989);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002049, EnemyEtis);
				break;
			}
			case 19655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001990);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002050, EnemyEtis);
				break;
			}
			case 19665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001991);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002051, EnemyEtis);
				break;
			}
			case 19675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001992);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002052, EnemyEtis);
				break;
			}
			case 19685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001993);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002053, EnemyEtis);
				break;
			}
			case 19695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001994);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002054, EnemyEtis);
				break;
			}
			case 19700: {
				requestActor(10000023, EnemyErmione);
				break;
			}
			case 19705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001995);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002055, EnemyEtis);
				break;
			}
			case 19715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001996);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002056, EnemyEtis);
				break;
			}
			case 19725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001997);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002057, EnemyEtis);
				break;
			}
			case 19735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001998);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002058, EnemyEtis);
				break;
			}
			case 19745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10001999);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002059, EnemyEtis);
				break;
			}
			case 19755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002000);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002060, EnemyEtis);
				break;
			}
			case 19765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002001);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002061, EnemyEtis);
				break;
			}
			case 19775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002002);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002062, EnemyEtis);
				break;
			}
			case 19785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002003);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002063, EnemyEtis);
				break;
			}
			case 19795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002004);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002064, EnemyEtis);
				break;
			}
			case 19805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002005);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002065, EnemyEtis);
				break;
			}
			case 19815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002006);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002066, EnemyEtis);
				break;
			}
			case 19825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002007);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002067, EnemyEtis);
				break;
			}
			case 19835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002008);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002068, EnemyEtis);
				break;
			}
			case 19845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002009);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002069, EnemyEtis);
				break;
			}
			case 19855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002010);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002070, EnemyEtis);
				break;
			}
			case 19865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002011);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002071, EnemyEtis);
				break;
			}
			case 19875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002012);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002072, EnemyEtis);
				break;
			}
			case 19885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002013);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002073, EnemyEtis);
				break;
			}
			case 19895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002014);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002074, EnemyEtis);
				break;
			}
			case 19900: {
				requestActor(10003235, EnemyDrastea);
				break;
			}
			case 19905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002015);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002075, EnemyEtis);
				break;
			}
			case 19915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002016);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002076, EnemyEtis);
				break;
			}
			case 19925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002017);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002077, EnemyEtis);
				break;
			}
			case 19935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002018);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002078, EnemyEtis);
				break;
			}
			case 19945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002019);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002079, EnemyEtis);
				break;
			}
			case 19955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002020);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002080, EnemyEtis);
				break;
			}
			case 19965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002021);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002081, EnemyEtis);
				break;
			}
			case 19975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002022);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002082, EnemyEtis);
				break;
			}
			case 19985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002023);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002083, EnemyEtis);
				break;
			}
			case 19995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002024);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002084, EnemyEtis);
				break;
			}
			case 20000: {
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(10003256);
				getSceneChief()->appendGroupChild(pRatislavia);
				break;
			}
			case 20005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002025);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002085, EnemyEtis);
				break;
			}
			case 20015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002026);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002086, EnemyEtis);
				break;
			}
			case 20025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002027);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002087, EnemyEtis);
				break;
			}
			case 20035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002028);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002088, EnemyEtis);
				break;
			}
			case 20045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002029);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002089, EnemyEtis);
				break;
			}
			case 20055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002030);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002090, EnemyEtis);
				break;
			}
			case 20065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002031);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002091, EnemyEtis);
				break;
			}
			case 20075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002032);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002092, EnemyEtis);
				break;
			}
			case 20085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002033);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002093, EnemyEtis);
				break;
			}
			case 20095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002034);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002094, EnemyEtis);
				break;
			}
			case 20105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002035);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002095, EnemyEtis);
				break;
			}
			case 20115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002036);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002096, EnemyEtis);
				break;
			}
			case 20125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002037);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002097, EnemyEtis);
				break;
			}
			case 20135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002038);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002098, EnemyEtis);
				break;
			}
			case 20145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002039);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002099, EnemyEtis);
				break;
			}
			case 20155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002040);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002100, EnemyEtis);
				break;
			}
			case 20165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002041);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002101, EnemyEtis);
				break;
			}
			case 20175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002042);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002102, EnemyEtis);
				break;
			}
			case 20185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002043);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002103, EnemyEtis);
				break;
			}
			case 20195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002044);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002104, EnemyEtis);
				break;
			}
			case 20205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002045);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002105, EnemyEtis);
				break;
			}
			case 20215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002046);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002106, EnemyEtis);
				break;
			}
			case 20225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002047);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002107, EnemyEtis);
				break;
			}
			case 20235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002048);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002108, EnemyEtis);
				break;
			}
			case 20245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002049);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002109, EnemyEtis);
				break;
			}
			case 20255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002050);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002110, EnemyEtis);
				break;
			}
			case 20265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002051);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002111, EnemyEtis);
				break;
			}
			case 20275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002052);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002112, EnemyEtis);
				break;
			}
			case 20285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002053);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002113, EnemyEtis);
				break;
			}
			case 20295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002054);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002114, EnemyEtis);
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000023);
				getSceneChief()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002055);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002115, EnemyEtis);
				break;
			}
			case 20315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002056);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002116, EnemyEtis);
				break;
			}
			case 20325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002057);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002117, EnemyEtis);
				break;
			}
			case 20335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002058);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002118, EnemyEtis);
				break;
			}
			case 20345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002059);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002119, EnemyEtis);
				break;
			}
			case 20355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002060);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002120, EnemyEtis);
				break;
			}
			case 20365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002061);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002121, EnemyEtis);
				break;
			}
			case 20375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002062);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002122, EnemyEtis);
				break;
			}
			case 20385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002063);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002123, EnemyEtis);
				break;
			}
			case 20395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002064);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002124, EnemyEtis);
				break;
			}
			case 20405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002065);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002125, EnemyEtis);
				break;
			}
			case 20415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002066);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002126, EnemyEtis);
				break;
			}
			case 20425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002067);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002127, EnemyEtis);
				break;
			}
			case 20435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002068);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002128, EnemyEtis);
				break;
			}
			case 20445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002069);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002129, EnemyEtis);
				break;
			}
			case 20455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002070);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002130, EnemyEtis);
				break;
			}
			case 20465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002071);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002131, EnemyEtis);
				break;
			}
			case 20475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002072);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002132, EnemyEtis);
				break;
			}
			case 20485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002073);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002133, EnemyEtis);
				break;
			}
			case 20495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002074);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002134, EnemyEtis);
				break;
			}
			case 20500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003235);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 20505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002075);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002135, EnemyEtis);
				break;
			}
			case 20515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002076);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002136, EnemyEtis);
				break;
			}
			case 20525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002077);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002137, EnemyEtis);
				break;
			}
			case 20535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002078);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002138, EnemyEtis);
				break;
			}
			case 20545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002079);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002139, EnemyEtis);
				break;
			}
			case 20555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002080);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002140, EnemyEtis);
				break;
			}
			case 20565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002081);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002141, EnemyEtis);
				break;
			}
			case 20575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002082);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002142, EnemyEtis);
				break;
			}
			case 20585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002083);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002143, EnemyEtis);
				break;
			}
			case 20595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002084);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002144, EnemyEtis);
				break;
			}
			case 20605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002085);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002145, EnemyEtis);
				break;
			}
			case 20615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002086);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002146, EnemyEtis);
				break;
			}
			case 20625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002087);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002147, EnemyEtis);
				break;
			}
			case 20635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002088);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002148, EnemyEtis);
				break;
			}
			case 20645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002089);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002149, EnemyEtis);
				break;
			}
			case 20655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002090);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002150, EnemyEtis);
				break;
			}
			case 20665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002091);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002151, EnemyEtis);
				break;
			}
			case 20675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002092);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002152, EnemyEtis);
				break;
			}
			case 20685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002093);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002153, EnemyEtis);
				break;
			}
			case 20695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002094);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002154, EnemyEtis);
				break;
			}
			case 20705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002095);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002155, EnemyEtis);
				break;
			}
			case 20715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002096);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002156, EnemyEtis);
				break;
			}
			case 20725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002097);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002157, EnemyEtis);
				break;
			}
			case 20735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002098);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002158, EnemyEtis);
				break;
			}
			case 20745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002099);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002159, EnemyEtis);
				break;
			}
			case 20755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002100);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002160, EnemyEtis);
				break;
			}
			case 20765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002101);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002161, EnemyEtis);
				break;
			}
			case 20775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002102);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002162, EnemyEtis);
				break;
			}
			case 20785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002103);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002163, EnemyEtis);
				break;
			}
			case 20795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002104);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002164, EnemyEtis);
				break;
			}
			case 20805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002105);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002165, EnemyEtis);
				break;
			}
			case 20815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002106);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002166, EnemyEtis);
				break;
			}
			case 20825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002107);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002167, EnemyEtis);
				break;
			}
			case 20835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002108);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002168, EnemyEtis);
				break;
			}
			case 20845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002109);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002169, EnemyEtis);
				break;
			}
			case 20855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002110);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002170, EnemyEtis);
				break;
			}
			case 20865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002111);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002171, EnemyEtis);
				break;
			}
			case 20875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002112);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002172, EnemyEtis);
				break;
			}
			case 20885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002113);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002173, EnemyEtis);
				break;
			}
			case 20895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002114);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002174, EnemyEtis);
				break;
			}
			case 20905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002115);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002175, EnemyEtis);
				break;
			}
			case 20915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002116);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002176, EnemyEtis);
				break;
			}
			case 20925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002117);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002177, EnemyEtis);
				break;
			}
			case 20935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002118);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002178, EnemyEtis);
				break;
			}
			case 20945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002119);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002179, EnemyEtis);
				break;
			}
			case 20955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002120);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002180, EnemyEtis);
				break;
			}
			case 20965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002121);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002181, EnemyEtis);
				break;
			}
			case 20975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002122);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002182, EnemyEtis);
				break;
			}
			case 20985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002123);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002183, EnemyEtis);
				break;
			}
			case 20995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002124);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002184, EnemyEtis);
				break;
			}
			case 21005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002125);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002185, EnemyEtis);
				break;
			}
			case 21015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002126);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002186, EnemyEtis);
				break;
			}
			case 21025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002127);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002187, EnemyEtis);
				break;
			}
			case 21035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002128);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002188, EnemyEtis);
				break;
			}
			case 21045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002129);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002189, EnemyEtis);
				break;
			}
			case 21055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002130);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002190, EnemyEtis);
				break;
			}
			case 21065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002131);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002191, EnemyEtis);
				break;
			}
			case 21075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002132);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002192, EnemyEtis);
				break;
			}
			case 21085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002133);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002193, EnemyEtis);
				break;
			}
			case 21095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002134);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002194, EnemyEtis);
				break;
			}
			case 21105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002135);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002195, EnemyEtis);
				break;
			}
			case 21115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002136);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002196, EnemyEtis);
				break;
			}
			case 21125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002137);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002197, EnemyEtis);
				break;
			}
			case 21135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002138);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002198, EnemyEtis);
				break;
			}
			case 21145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002139);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002199, EnemyEtis);
				break;
			}
			case 21155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002140);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002200, EnemyEtis);
				break;
			}
			case 21165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002141);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002201, EnemyEtis);
				break;
			}
			case 21175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002142);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002202, EnemyEtis);
				break;
			}
			case 21185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002143);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002203, EnemyEtis);
				break;
			}
			case 21195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002144);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002204, EnemyEtis);
				break;
			}
			case 21205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002145);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002205, EnemyEtis);
				break;
			}
			case 21215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002146);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002206, EnemyEtis);
				break;
			}
			case 21225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002147);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002207, EnemyEtis);
				break;
			}
			case 21235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002148);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002208, EnemyEtis);
				break;
			}
			case 21245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002149);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002209, EnemyEtis);
				break;
			}
			case 21255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002150);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002210, EnemyEtis);
				break;
			}
			case 21265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002151);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002211, EnemyEtis);
				break;
			}
			case 21275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002152);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002212, EnemyEtis);
				break;
			}
			case 21285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002153);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002213, EnemyEtis);
				break;
			}
			case 21295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002154);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002214, EnemyEtis);
				break;
			}
			case 21305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002155);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002215, EnemyEtis);
				break;
			}
			case 21315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002156);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002216, EnemyEtis);
				break;
			}
			case 21325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002157);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002217, EnemyEtis);
				break;
			}
			case 21335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002158);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002218, EnemyEtis);
				break;
			}
			case 21345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002159);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002219, EnemyEtis);
				break;
			}
			case 21355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002160);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002220, EnemyEtis);
				break;
			}
			case 21365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002161);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002221, EnemyEtis);
				break;
			}
			case 21375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002162);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002222, EnemyEtis);
				break;
			}
			case 21385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002163);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002223, EnemyEtis);
				break;
			}
			case 21395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002164);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002224, EnemyEtis);
				break;
			}
			case 21405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002165);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002225, EnemyEtis);
				break;
			}
			case 21415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002166);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002226, EnemyEtis);
				break;
			}
			case 21425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002167);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002227, EnemyEtis);
				break;
			}
			case 21435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002168);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002228, EnemyEtis);
				break;
			}
			case 21445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002169);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002229, EnemyEtis);
				break;
			}
			case 21455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002170);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002230, EnemyEtis);
				break;
			}
			case 21465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002171);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002231, EnemyEtis);
				break;
			}
			case 21475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002172);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002232, EnemyEtis);
				break;
			}
			case 21485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002173);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002233, EnemyEtis);
				break;
			}
			case 21495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002174);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002234, EnemyEtis);
				break;
			}
			case 21505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002175);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002235, EnemyEtis);
				break;
			}
			case 21515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002176);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002236, EnemyEtis);
				break;
			}
			case 21525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002177);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002237, EnemyEtis);
				break;
			}
			case 21535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002178);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002238, EnemyEtis);
				break;
			}
			case 21545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002179);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002239, EnemyEtis);
				break;
			}
			case 21555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002180);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002240, EnemyEtis);
				break;
			}
			case 21565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002181);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002241, EnemyEtis);
				break;
			}
			case 21575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002182);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002242, EnemyEtis);
				break;
			}
			case 21585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002183);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002243, EnemyEtis);
				break;
			}
			case 21595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002184);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002244, EnemyEtis);
				break;
			}
			case 21605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002185);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002245, EnemyEtis);
				break;
			}
			case 21615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002186);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002246, EnemyEtis);
				break;
			}
			case 21625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002187);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002247, EnemyEtis);
				break;
			}
			case 21635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002188);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002248, EnemyEtis);
				break;
			}
			case 21645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002189);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002249, EnemyEtis);
				break;
			}
			case 21655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002190);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002250, EnemyEtis);
				break;
			}
			case 21665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002191);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002251, EnemyEtis);
				break;
			}
			case 21675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002192);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002252, EnemyEtis);
				break;
			}
			case 21685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002193);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002253, EnemyEtis);
				break;
			}
			case 21695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002194);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002254, EnemyEtis);
				break;
			}
			case 21705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002195);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002255, EnemyEtis);
				break;
			}
			case 21715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002196);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002256, EnemyEtis);
				break;
			}
			case 21725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002197);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002257, EnemyEtis);
				break;
			}
			case 21735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002198);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002258, EnemyEtis);
				break;
			}
			case 21745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002199);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002259, EnemyEtis);
				break;
			}
			case 21755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002200);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002260, EnemyEtis);
				break;
			}
			case 21765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002201);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002261, EnemyEtis);
				break;
			}
			case 21775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002202);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002262, EnemyEtis);
				break;
			}
			case 21785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002203);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002263, EnemyEtis);
				break;
			}
			case 21795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002204);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002264, EnemyEtis);
				break;
			}
			case 21805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002205);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002265, EnemyEtis);
				break;
			}
			case 21815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002206);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002266, EnemyEtis);
				break;
			}
			case 21825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002207);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002267, EnemyEtis);
				break;
			}
			case 21835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002208);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002268, EnemyEtis);
				break;
			}
			case 21845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002209);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002269, EnemyEtis);
				break;
			}
			case 21855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002210);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002270, EnemyEtis);
				break;
			}
			case 21865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002211);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002271, EnemyEtis);
				break;
			}
			case 21875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002212);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002272, EnemyEtis);
				break;
			}
			case 21885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002213);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002273, EnemyEtis);
				break;
			}
			case 21895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002214);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002274, EnemyEtis);
				break;
			}
			case 21900: {
				requestActor(10003236, EnemyDrastea);
				break;
			}
			case 21905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002215);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002275, EnemyEtis);
				break;
			}
			case 21915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002216);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002276, EnemyEtis);
				break;
			}
			case 21925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002217);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002277, EnemyEtis);
				break;
			}
			case 21935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002218);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002278, EnemyEtis);
				break;
			}
			case 21945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002219);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002279, EnemyEtis);
				break;
			}
			case 21955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002220);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002280, EnemyEtis);
				break;
			}
			case 21965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002221);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002281, EnemyEtis);
				break;
			}
			case 21975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002222);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002282, EnemyEtis);
				break;
			}
			case 21985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002223);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002283, EnemyEtis);
				break;
			}
			case 21995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002224);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002284, EnemyEtis);
				break;
			}
			case 22005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002225);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002285, EnemyEtis);
				break;
			}
			case 22015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002226);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002286, EnemyEtis);
				break;
			}
			case 22025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002227);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002287, EnemyEtis);
				break;
			}
			case 22035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002228);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002288, EnemyEtis);
				break;
			}
			case 22045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002229);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002289, EnemyEtis);
				break;
			}
			case 22055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002230);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002290, EnemyEtis);
				break;
			}
			case 22065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002231);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002291, EnemyEtis);
				break;
			}
			case 22075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002232);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002292, EnemyEtis);
				break;
			}
			case 22085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002233);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002293, EnemyEtis);
				break;
			}
			case 22095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002234);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002294, EnemyEtis);
				break;
			}
			case 22105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002235);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002295, EnemyEtis);
				break;
			}
			case 22115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002236);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002296, EnemyEtis);
				break;
			}
			case 22125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002237);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002297, EnemyEtis);
				break;
			}
			case 22135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002238);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002298, EnemyEtis);
				break;
			}
			case 22145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002239);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002299, EnemyEtis);
				break;
			}
			case 22155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002240);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002300, EnemyEtis);
				break;
			}
			case 22165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002241);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002301, EnemyEtis);
				break;
			}
			case 22175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002242);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002302, EnemyEtis);
				break;
			}
			case 22185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002243);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002303, EnemyEtis);
				break;
			}
			case 22195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002244);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002304, EnemyEtis);
				break;
			}
			case 22205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002245);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002305, EnemyEtis);
				break;
			}
			case 22215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002246);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002306, EnemyEtis);
				break;
			}
			case 22225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002247);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002307, EnemyEtis);
				break;
			}
			case 22235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002248);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002308, EnemyEtis);
				break;
			}
			case 22245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002249);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002309, EnemyEtis);
				break;
			}
			case 22255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002250);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002310, EnemyEtis);
				break;
			}
			case 22265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002251);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002311, EnemyEtis);
				break;
			}
			case 22275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002252);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002312, EnemyEtis);
				break;
			}
			case 22285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002253);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002313, EnemyEtis);
				break;
			}
			case 22295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002254);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002314, EnemyEtis);
				break;
			}
			case 22305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002255);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002315, EnemyEtis);
				break;
			}
			case 22315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002256);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002316, EnemyEtis);
				break;
			}
			case 22325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002257);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002317, EnemyEtis);
				break;
			}
			case 22335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002258);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002318, EnemyEtis);
				break;
			}
			case 22345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002259);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002319, EnemyEtis);
				break;
			}
			case 22355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002260);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002320, EnemyEtis);
				break;
			}
			case 22365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002261);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002321, EnemyEtis);
				break;
			}
			case 22375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002262);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002322, EnemyEtis);
				break;
			}
			case 22385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002263);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002323, EnemyEtis);
				break;
			}
			case 22395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002264);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002324, EnemyEtis);
				break;
			}
			case 22405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002265);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002325, EnemyEtis);
				break;
			}
			case 22415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002266);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002326, EnemyEtis);
				break;
			}
			case 22425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002267);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002327, EnemyEtis);
				break;
			}
			case 22435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002268);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002328, EnemyEtis);
				break;
			}
			case 22445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002269);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002329, EnemyEtis);
				break;
			}
			case 22455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002270);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002330, EnemyEtis);
				break;
			}
			case 22465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002271);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002331, EnemyEtis);
				break;
			}
			case 22475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002272);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002332, EnemyEtis);
				break;
			}
			case 22485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002273);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002333, EnemyEtis);
				break;
			}
			case 22495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002274);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002334, EnemyEtis);
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003236);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 22505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002275);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002335, EnemyEtis);
				break;
			}
			case 22515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002276);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002336, EnemyEtis);
				break;
			}
			case 22525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002277);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002337, EnemyEtis);
				break;
			}
			case 22535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002278);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002338, EnemyEtis);
				break;
			}
			case 22545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002279);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002339, EnemyEtis);
				break;
			}
			case 22555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002280);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002340, EnemyEtis);
				break;
			}
			case 22565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002281);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002341, EnemyEtis);
				break;
			}
			case 22575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002282);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002342, EnemyEtis);
				break;
			}
			case 22585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002283);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002343, EnemyEtis);
				break;
			}
			case 22595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002284);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002344, EnemyEtis);
				break;
			}
			case 22605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002285);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002345, EnemyEtis);
				break;
			}
			case 22615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002286);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002346, EnemyEtis);
				break;
			}
			case 22625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002287);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002347, EnemyEtis);
				break;
			}
			case 22635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002288);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002348, EnemyEtis);
				break;
			}
			case 22645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002289);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002349, EnemyEtis);
				break;
			}
			case 22655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002290);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002350, EnemyEtis);
				break;
			}
			case 22665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002291);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002351, EnemyEtis);
				break;
			}
			case 22675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002292);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002352, EnemyEtis);
				break;
			}
			case 22685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002293);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002353, EnemyEtis);
				break;
			}
			case 22695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002294);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002354, EnemyEtis);
				break;
			}
			case 22705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002295);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002355, EnemyEtis);
				break;
			}
			case 22715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002296);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002356, EnemyEtis);
				break;
			}
			case 22725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002297);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002357, EnemyEtis);
				break;
			}
			case 22735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002298);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002358, EnemyEtis);
				break;
			}
			case 22745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002299);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002359, EnemyEtis);
				break;
			}
			case 22755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002300);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002360, EnemyEtis);
				break;
			}
			case 22765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002301);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002361, EnemyEtis);
				break;
			}
			case 22775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002302);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002362, EnemyEtis);
				break;
			}
			case 22785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002303);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002363, EnemyEtis);
				break;
			}
			case 22795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002304);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002364, EnemyEtis);
				break;
			}
			case 22805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002305);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002365, EnemyEtis);
				break;
			}
			case 22815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002306);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002366, EnemyEtis);
				break;
			}
			case 22825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002307);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002367, EnemyEtis);
				break;
			}
			case 22835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002308);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002368, EnemyEtis);
				break;
			}
			case 22845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002309);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002369, EnemyEtis);
				break;
			}
			case 22855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002310);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002370, EnemyEtis);
				break;
			}
			case 22865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002311);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002371, EnemyEtis);
				break;
			}
			case 22875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002312);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002372, EnemyEtis);
				break;
			}
			case 22885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002313);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002373, EnemyEtis);
				break;
			}
			case 22895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002314);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002374, EnemyEtis);
				break;
			}
			case 22905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002315);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002375, EnemyEtis);
				break;
			}
			case 22915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002316);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002376, EnemyEtis);
				break;
			}
			case 22925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002317);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002377, EnemyEtis);
				break;
			}
			case 22935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002318);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002378, EnemyEtis);
				break;
			}
			case 22945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002319);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002379, EnemyEtis);
				break;
			}
			case 22955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002320);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002380, EnemyEtis);
				break;
			}
			case 22965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002321);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002381, EnemyEtis);
				break;
			}
			case 22975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002322);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002382, EnemyEtis);
				break;
			}
			case 22985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002323);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002383, EnemyEtis);
				break;
			}
			case 22995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002324);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002384, EnemyEtis);
				break;
			}
			case 23005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002325);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002385, EnemyEtis);
				break;
			}
			case 23015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002326);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002386, EnemyEtis);
				break;
			}
			case 23025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002327);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002387, EnemyEtis);
				break;
			}
			case 23035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002328);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002388, EnemyEtis);
				break;
			}
			case 23045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002329);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002389, EnemyEtis);
				break;
			}
			case 23055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002330);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002390, EnemyEtis);
				break;
			}
			case 23065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002331);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002391, EnemyEtis);
				break;
			}
			case 23075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002332);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002392, EnemyEtis);
				break;
			}
			case 23085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002333);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002393, EnemyEtis);
				break;
			}
			case 23095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002334);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002394, EnemyEtis);
				break;
			}
			case 23105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002335);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002395, EnemyEtis);
				break;
			}
			case 23115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002336);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002396, EnemyEtis);
				break;
			}
			case 23125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002337);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002397, EnemyEtis);
				break;
			}
			case 23135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002338);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002398, EnemyEtis);
				break;
			}
			case 23145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002339);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002399, EnemyEtis);
				break;
			}
			case 23155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002340);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002400, EnemyEtis);
				break;
			}
			case 23165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002341);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002401, EnemyEtis);
				break;
			}
			case 23175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002342);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002402, EnemyEtis);
				break;
			}
			case 23185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002343);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002403, EnemyEtis);
				break;
			}
			case 23195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002344);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002404, EnemyEtis);
				break;
			}
			case 23205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002345);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002405, EnemyEtis);
				break;
			}
			case 23215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002346);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002406, EnemyEtis);
				break;
			}
			case 23225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002347);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002407, EnemyEtis);
				break;
			}
			case 23235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002348);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002408, EnemyEtis);
				break;
			}
			case 23245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002349);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002409, EnemyEtis);
				break;
			}
			case 23255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002350);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002410, EnemyEtis);
				break;
			}
			case 23265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002351);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002411, EnemyEtis);
				break;
			}
			case 23275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002352);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002412, EnemyEtis);
				break;
			}
			case 23285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002353);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002413, EnemyEtis);
				break;
			}
			case 23295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002354);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002414, EnemyEtis);
				break;
			}
			case 23305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002355);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002415, EnemyEtis);
				break;
			}
			case 23315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002356);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002416, EnemyEtis);
				break;
			}
			case 23325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002357);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002417, EnemyEtis);
				break;
			}
			case 23335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002358);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002418, EnemyEtis);
				break;
			}
			case 23345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002359);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002419, EnemyEtis);
				break;
			}
			case 23355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002360);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002420, EnemyEtis);
				break;
			}
			case 23365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002361);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002421, EnemyEtis);
				break;
			}
			case 23375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002362);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002422, EnemyEtis);
				break;
			}
			case 23385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002363);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002423, EnemyEtis);
				break;
			}
			case 23395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002364);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002424, EnemyEtis);
				break;
			}
			case 23405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002365);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002425, EnemyEtis);
				break;
			}
			case 23415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002366);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002426, EnemyEtis);
				break;
			}
			case 23425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002367);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002427, EnemyEtis);
				break;
			}
			case 23435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002368);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002428, EnemyEtis);
				break;
			}
			case 23445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002369);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002429, EnemyEtis);
				break;
			}
			case 23455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002370);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002430, EnemyEtis);
				break;
			}
			case 23465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002371);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002431, EnemyEtis);
				break;
			}
			case 23475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002372);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002432, EnemyEtis);
				break;
			}
			case 23485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002373);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002433, EnemyEtis);
				break;
			}
			case 23495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002374);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002434, EnemyEtis);
				break;
			}
			case 23505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002375);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002435, EnemyEtis);
				break;
			}
			case 23515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002376);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002436, EnemyEtis);
				break;
			}
			case 23525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002377);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002437, EnemyEtis);
				break;
			}
			case 23535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002378);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002438, EnemyEtis);
				break;
			}
			case 23545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002379);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002439, EnemyEtis);
				break;
			}
			case 23555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002380);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002440, EnemyEtis);
				break;
			}
			case 23565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002381);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002441, EnemyEtis);
				break;
			}
			case 23575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002382);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002442, EnemyEtis);
				break;
			}
			case 23585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002383);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002443, EnemyEtis);
				break;
			}
			case 23595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002384);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002444, EnemyEtis);
				break;
			}
			case 23605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002385);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002445, EnemyEtis);
				break;
			}
			case 23615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002386);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002446, EnemyEtis);
				break;
			}
			case 23625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002387);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002447, EnemyEtis);
				break;
			}
			case 23635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002388);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002448, EnemyEtis);
				break;
			}
			case 23645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002389);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002449, EnemyEtis);
				break;
			}
			case 23655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002390);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002450, EnemyEtis);
				break;
			}
			case 23665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002391);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002451, EnemyEtis);
				break;
			}
			case 23675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002392);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002452, EnemyEtis);
				break;
			}
			case 23685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002393);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002453, EnemyEtis);
				break;
			}
			case 23695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002394);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002454, EnemyEtis);
				break;
			}
			case 23705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002395);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002455, EnemyEtis);
				break;
			}
			case 23715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002396);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002456, EnemyEtis);
				break;
			}
			case 23725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002397);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002457, EnemyEtis);
				break;
			}
			case 23735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002398);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002458, EnemyEtis);
				break;
			}
			case 23745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002399);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002459, EnemyEtis);
				break;
			}
			case 23755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002400);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002460, EnemyEtis);
				break;
			}
			case 23765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002401);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002461, EnemyEtis);
				break;
			}
			case 23775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002402);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002462, EnemyEtis);
				break;
			}
			case 23785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002403);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002463, EnemyEtis);
				break;
			}
			case 23795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002404);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002464, EnemyEtis);
				break;
			}
			case 23805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002405);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002465, EnemyEtis);
				break;
			}
			case 23815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002406);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002466, EnemyEtis);
				break;
			}
			case 23825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002407);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002467, EnemyEtis);
				break;
			}
			case 23835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002408);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002468, EnemyEtis);
				break;
			}
			case 23845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002409);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002469, EnemyEtis);
				break;
			}
			case 23855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002410);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002470, EnemyEtis);
				break;
			}
			case 23865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002411);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002471, EnemyEtis);
				break;
			}
			case 23875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002412);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002472, EnemyEtis);
				break;
			}
			case 23885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002413);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002473, EnemyEtis);
				break;
			}
			case 23895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002414);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002474, EnemyEtis);
				break;
			}
			case 23900: {
				requestActor(10003237, EnemyDrastea);
				break;
			}
			case 23905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002415);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002475, EnemyEtis);
				break;
			}
			case 23915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002416);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002476, EnemyEtis);
				break;
			}
			case 23925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002417);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002477, EnemyEtis);
				break;
			}
			case 23935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002418);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002478, EnemyEtis);
				break;
			}
			case 23945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002419);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002479, EnemyEtis);
				break;
			}
			case 23955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002420);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002480, EnemyEtis);
				break;
			}
			case 23965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002421);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002481, EnemyEtis);
				break;
			}
			case 23975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002422);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002482, EnemyEtis);
				break;
			}
			case 23985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002423);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002483, EnemyEtis);
				break;
			}
			case 23995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002424);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002484, EnemyEtis);
				break;
			}
			case 24005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002425);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002485, EnemyEtis);
				break;
			}
			case 24015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002426);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002486, EnemyEtis);
				break;
			}
			case 24025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002427);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002487, EnemyEtis);
				break;
			}
			case 24035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002428);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002488, EnemyEtis);
				break;
			}
			case 24045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002429);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002489, EnemyEtis);
				break;
			}
			case 24055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002430);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002490, EnemyEtis);
				break;
			}
			case 24065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002431);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002491, EnemyEtis);
				break;
			}
			case 24075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002432);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002492, EnemyEtis);
				break;
			}
			case 24085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002433);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002493, EnemyEtis);
				break;
			}
			case 24095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002434);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002494, EnemyEtis);
				break;
			}
			case 24105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002435);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002495, EnemyEtis);
				break;
			}
			case 24115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002436);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002496, EnemyEtis);
				break;
			}
			case 24125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002437);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002497, EnemyEtis);
				break;
			}
			case 24135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002438);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002498, EnemyEtis);
				break;
			}
			case 24145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002439);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002499, EnemyEtis);
				break;
			}
			case 24155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002440);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002500, EnemyEtis);
				break;
			}
			case 24165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002441);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002501, EnemyEtis);
				break;
			}
			case 24175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002442);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002502, EnemyEtis);
				break;
			}
			case 24185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002443);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002503, EnemyEtis);
				break;
			}
			case 24195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002444);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002504, EnemyEtis);
				break;
			}
			case 24205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002445);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002505, EnemyEtis);
				break;
			}
			case 24215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002446);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002506, EnemyEtis);
				break;
			}
			case 24225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002447);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002507, EnemyEtis);
				break;
			}
			case 24235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002448);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002508, EnemyEtis);
				break;
			}
			case 24245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002449);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002509, EnemyEtis);
				break;
			}
			case 24255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002450);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002510, EnemyEtis);
				break;
			}
			case 24265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002451);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002511, EnemyEtis);
				break;
			}
			case 24275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002452);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002512, EnemyEtis);
				break;
			}
			case 24285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002453);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002513, EnemyEtis);
				break;
			}
			case 24295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002454);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002514, EnemyEtis);
				break;
			}
			case 24305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002455);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002515, EnemyEtis);
				break;
			}
			case 24315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002456);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002516, EnemyEtis);
				break;
			}
			case 24325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002457);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002517, EnemyEtis);
				break;
			}
			case 24335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002458);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002518, EnemyEtis);
				break;
			}
			case 24345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002459);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002519, EnemyEtis);
				break;
			}
			case 24355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002460);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002520, EnemyEtis);
				break;
			}
			case 24365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002461);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002521, EnemyEtis);
				break;
			}
			case 24375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002462);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002522, EnemyEtis);
				break;
			}
			case 24385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002463);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002523, EnemyEtis);
				break;
			}
			case 24395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002464);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002524, EnemyEtis);
				break;
			}
			case 24405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002465);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002525, EnemyEtis);
				break;
			}
			case 24415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002466);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002526, EnemyEtis);
				break;
			}
			case 24425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002467);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002527, EnemyEtis);
				break;
			}
			case 24435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002468);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002528, EnemyEtis);
				break;
			}
			case 24445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002469);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002529, EnemyEtis);
				break;
			}
			case 24455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002470);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002530, EnemyEtis);
				break;
			}
			case 24465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002471);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002531, EnemyEtis);
				break;
			}
			case 24475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002472);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002532, EnemyEtis);
				break;
			}
			case 24485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002473);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002533, EnemyEtis);
				break;
			}
			case 24495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002474);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002534, EnemyEtis);
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003237);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 24505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002475);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002535, EnemyEtis);
				break;
			}
			case 24515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002476);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002536, EnemyEtis);
				break;
			}
			case 24525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002477);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002537, EnemyEtis);
				break;
			}
			case 24535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002478);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002538, EnemyEtis);
				break;
			}
			case 24545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002479);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002539, EnemyEtis);
				break;
			}
			case 24555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002480);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002540, EnemyEtis);
				break;
			}
			case 24565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002481);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002541, EnemyEtis);
				break;
			}
			case 24575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002482);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002542, EnemyEtis);
				break;
			}
			case 24585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002483);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002543, EnemyEtis);
				break;
			}
			case 24595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002484);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002544, EnemyEtis);
				break;
			}
			case 24605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002485);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002545, EnemyEtis);
				break;
			}
			case 24615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002486);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002546, EnemyEtis);
				break;
			}
			case 24625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002487);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002547, EnemyEtis);
				break;
			}
			case 24635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002488);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002548, EnemyEtis);
				break;
			}
			case 24645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002489);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002549, EnemyEtis);
				break;
			}
			case 24655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002490);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002550, EnemyEtis);
				break;
			}
			case 24665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002491);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002551, EnemyEtis);
				break;
			}
			case 24675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002492);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002552, EnemyEtis);
				break;
			}
			case 24685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002493);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002553, EnemyEtis);
				break;
			}
			case 24695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002494);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002554, EnemyEtis);
				break;
			}
			case 24705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002495);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002555, EnemyEtis);
				break;
			}
			case 24715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002496);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002556, EnemyEtis);
				break;
			}
			case 24725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002497);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002557, EnemyEtis);
				break;
			}
			case 24735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002498);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002558, EnemyEtis);
				break;
			}
			case 24745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002499);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002559, EnemyEtis);
				break;
			}
			case 24755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002500);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002560, EnemyEtis);
				break;
			}
			case 24765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002501);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002561, EnemyEtis);
				break;
			}
			case 24775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002502);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002562, EnemyEtis);
				break;
			}
			case 24785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002503);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002563, EnemyEtis);
				break;
			}
			case 24795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002504);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002564, EnemyEtis);
				break;
			}
			case 24805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002505);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002565, EnemyEtis);
				break;
			}
			case 24815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002506);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002566, EnemyEtis);
				break;
			}
			case 24825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002507);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002567, EnemyEtis);
				break;
			}
			case 24835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002508);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002568, EnemyEtis);
				break;
			}
			case 24845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002509);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002569, EnemyEtis);
				break;
			}
			case 24855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002510);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002570, EnemyEtis);
				break;
			}
			case 24865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002511);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002571, EnemyEtis);
				break;
			}
			case 24875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002512);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002572, EnemyEtis);
				break;
			}
			case 24885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002513);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002573, EnemyEtis);
				break;
			}
			case 24895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002514);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002574, EnemyEtis);
				break;
			}
			case 24905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002515);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002575, EnemyEtis);
				break;
			}
			case 24915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002516);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002576, EnemyEtis);
				break;
			}
			case 24925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002517);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002577, EnemyEtis);
				break;
			}
			case 24935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002518);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002578, EnemyEtis);
				break;
			}
			case 24945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002519);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002579, EnemyEtis);
				break;
			}
			case 24955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002520);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002580, EnemyEtis);
				break;
			}
			case 24965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002521);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002581, EnemyEtis);
				break;
			}
			case 24975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002522);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002582, EnemyEtis);
				break;
			}
			case 24985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002523);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002583, EnemyEtis);
				break;
			}
			case 24995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002524);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002584, EnemyEtis);
				break;
			}
			case 25005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002525);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002585, EnemyEtis);
				break;
			}
			case 25015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002526);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002586, EnemyEtis);
				break;
			}
			case 25025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002527);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002587, EnemyEtis);
				break;
			}
			case 25035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002528);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002588, EnemyEtis);
				break;
			}
			case 25045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002529);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002589, EnemyEtis);
				break;
			}
			case 25055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002530);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002590, EnemyEtis);
				break;
			}
			case 25065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002531);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002591, EnemyEtis);
				break;
			}
			case 25075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002532);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002592, EnemyEtis);
				break;
			}
			case 25085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002533);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002593, EnemyEtis);
				break;
			}
			case 25095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002534);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002594, EnemyEtis);
				break;
			}
			case 25105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002535);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002595, EnemyEtis);
				break;
			}
			case 25115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002536);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002596, EnemyEtis);
				break;
			}
			case 25125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002537);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002597, EnemyEtis);
				break;
			}
			case 25135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002538);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002598, EnemyEtis);
				break;
			}
			case 25145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002539);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002599, EnemyEtis);
				break;
			}
			case 25155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002540);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002600, EnemyEtis);
				break;
			}
			case 25165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002541);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002601, EnemyEtis);
				break;
			}
			case 25175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002542);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002602, EnemyEtis);
				break;
			}
			case 25185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002543);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002603, EnemyEtis);
				break;
			}
			case 25195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002544);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002604, EnemyEtis);
				break;
			}
			case 25205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002545);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002605, EnemyEtis);
				break;
			}
			case 25215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002546);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002606, EnemyEtis);
				break;
			}
			case 25225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002547);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002607, EnemyEtis);
				break;
			}
			case 25235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002548);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002608, EnemyEtis);
				break;
			}
			case 25245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002549);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002609, EnemyEtis);
				break;
			}
			case 25255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002550);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002610, EnemyEtis);
				break;
			}
			case 25265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002551);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002611, EnemyEtis);
				break;
			}
			case 25275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002552);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002612, EnemyEtis);
				break;
			}
			case 25285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002553);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002613, EnemyEtis);
				break;
			}
			case 25295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002554);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002614, EnemyEtis);
				break;
			}
			case 25305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002555);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002615, EnemyEtis);
				break;
			}
			case 25315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002556);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002616, EnemyEtis);
				break;
			}
			case 25325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002557);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002617, EnemyEtis);
				break;
			}
			case 25335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002558);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002618, EnemyEtis);
				break;
			}
			case 25345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002559);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002619, EnemyEtis);
				break;
			}
			case 25355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002560);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002620, EnemyEtis);
				break;
			}
			case 25365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002561);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002621, EnemyEtis);
				break;
			}
			case 25375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002562);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002622, EnemyEtis);
				break;
			}
			case 25385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002563);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002623, EnemyEtis);
				break;
			}
			case 25395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002564);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002624, EnemyEtis);
				break;
			}
			case 25405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002565);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002625, EnemyEtis);
				break;
			}
			case 25415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002566);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002626, EnemyEtis);
				break;
			}
			case 25425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002567);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002627, EnemyEtis);
				break;
			}
			case 25435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002568);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002628, EnemyEtis);
				break;
			}
			case 25445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002569);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002629, EnemyEtis);
				break;
			}
			case 25455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002570);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002630, EnemyEtis);
				break;
			}
			case 25465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002571);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002631, EnemyEtis);
				break;
			}
			case 25475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002572);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002632, EnemyEtis);
				break;
			}
			case 25485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002573);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002633, EnemyEtis);
				break;
			}
			case 25495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002574);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002634, EnemyEtis);
				break;
			}
			case 25505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002575);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002635, EnemyEtis);
				break;
			}
			case 25515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002576);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002636, EnemyEtis);
				break;
			}
			case 25525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002577);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002637, EnemyEtis);
				break;
			}
			case 25535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002578);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002638, EnemyEtis);
				break;
			}
			case 25545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002579);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002639, EnemyEtis);
				break;
			}
			case 25555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002580);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002640, EnemyEtis);
				break;
			}
			case 25565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002581);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002641, EnemyEtis);
				break;
			}
			case 25575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002582);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002642, EnemyEtis);
				break;
			}
			case 25585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002583);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002643, EnemyEtis);
				break;
			}
			case 25595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002584);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002644, EnemyEtis);
				break;
			}
			case 25605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002585);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002645, EnemyEtis);
				break;
			}
			case 25615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002586);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002646, EnemyEtis);
				break;
			}
			case 25625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002587);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002647, EnemyEtis);
				break;
			}
			case 25635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002588);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002648, EnemyEtis);
				break;
			}
			case 25645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002589);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002649, EnemyEtis);
				break;
			}
			case 25655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002590);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002650, EnemyEtis);
				break;
			}
			case 25665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002591);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002651, EnemyEtis);
				break;
			}
			case 25675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002592);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002652, EnemyEtis);
				break;
			}
			case 25685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002593);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002653, EnemyEtis);
				break;
			}
			case 25695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002594);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002654, EnemyEtis);
				break;
			}
			case 25705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002595);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002655, EnemyEtis);
				break;
			}
			case 25715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002596);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002656, EnemyEtis);
				break;
			}
			case 25725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002597);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002657, EnemyEtis);
				break;
			}
			case 25735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002598);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002658, EnemyEtis);
				break;
			}
			case 25745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002599);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002659, EnemyEtis);
				break;
			}
			case 25755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002600);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002660, EnemyEtis);
				break;
			}
			case 25765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002601);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002661, EnemyEtis);
				break;
			}
			case 25775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002602);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002662, EnemyEtis);
				break;
			}
			case 25785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002603);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002663, EnemyEtis);
				break;
			}
			case 25795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002604);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002664, EnemyEtis);
				break;
			}
			case 25805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002605);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002665, EnemyEtis);
				break;
			}
			case 25815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002606);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002666, EnemyEtis);
				break;
			}
			case 25825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002607);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002667, EnemyEtis);
				break;
			}
			case 25835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002608);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002668, EnemyEtis);
				break;
			}
			case 25845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002609);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002669, EnemyEtis);
				break;
			}
			case 25855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002610);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002670, EnemyEtis);
				break;
			}
			case 25865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002611);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002671, EnemyEtis);
				break;
			}
			case 25875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002612);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002672, EnemyEtis);
				break;
			}
			case 25885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002613);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002673, EnemyEtis);
				break;
			}
			case 25895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002614);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002674, EnemyEtis);
				break;
			}
			case 25900: {
				requestActor(10003238, EnemyDrastea);
				break;
			}
			case 25905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002615);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002675, EnemyEtis);
				break;
			}
			case 25915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002616);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002676, EnemyEtis);
				break;
			}
			case 25925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002617);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002677, EnemyEtis);
				break;
			}
			case 25935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002618);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002678, EnemyEtis);
				break;
			}
			case 25945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002619);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002679, EnemyEtis);
				break;
			}
			case 25955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002620);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002680, EnemyEtis);
				break;
			}
			case 25965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002621);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002681, EnemyEtis);
				break;
			}
			case 25975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002622);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002682, EnemyEtis);
				break;
			}
			case 25985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002623);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002683, EnemyEtis);
				break;
			}
			case 25995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002624);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002684, EnemyEtis);
				break;
			}
			case 26005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002625);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002685, EnemyEtis);
				break;
			}
			case 26015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002626);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002686, EnemyEtis);
				break;
			}
			case 26025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002627);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002687, EnemyEtis);
				break;
			}
			case 26035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002628);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002688, EnemyEtis);
				break;
			}
			case 26045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002629);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002689, EnemyEtis);
				break;
			}
			case 26055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002630);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002690, EnemyEtis);
				break;
			}
			case 26065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002631);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002691, EnemyEtis);
				break;
			}
			case 26075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002632);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002692, EnemyEtis);
				break;
			}
			case 26085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002633);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002693, EnemyEtis);
				break;
			}
			case 26095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002634);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002694, EnemyEtis);
				break;
			}
			case 26105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002635);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002695, EnemyEtis);
				break;
			}
			case 26115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002636);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002696, EnemyEtis);
				break;
			}
			case 26125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002637);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002697, EnemyEtis);
				break;
			}
			case 26135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002638);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002698, EnemyEtis);
				break;
			}
			case 26145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002639);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002699, EnemyEtis);
				break;
			}
			case 26155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002640);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002700, EnemyEtis);
				break;
			}
			case 26165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002641);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002701, EnemyEtis);
				break;
			}
			case 26175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002642);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002702, EnemyEtis);
				break;
			}
			case 26185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002643);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002703, EnemyEtis);
				break;
			}
			case 26195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002644);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002704, EnemyEtis);
				break;
			}
			case 26205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002645);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002705, EnemyEtis);
				break;
			}
			case 26215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002646);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002706, EnemyEtis);
				break;
			}
			case 26225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002647);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002707, EnemyEtis);
				break;
			}
			case 26235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002648);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002708, EnemyEtis);
				break;
			}
			case 26245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002649);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002709, EnemyEtis);
				break;
			}
			case 26255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002650);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002710, EnemyEtis);
				break;
			}
			case 26265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002651);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002711, EnemyEtis);
				break;
			}
			case 26275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002652);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002712, EnemyEtis);
				break;
			}
			case 26285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002653);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002713, EnemyEtis);
				break;
			}
			case 26295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002654);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002714, EnemyEtis);
				break;
			}
			case 26305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002655);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002715, EnemyEtis);
				break;
			}
			case 26315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002656);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002716, EnemyEtis);
				break;
			}
			case 26325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002657);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002717, EnemyEtis);
				break;
			}
			case 26335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002658);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002718, EnemyEtis);
				break;
			}
			case 26345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002659);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002719, EnemyEtis);
				break;
			}
			case 26355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002660);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002720, EnemyEtis);
				break;
			}
			case 26365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002661);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002721, EnemyEtis);
				break;
			}
			case 26375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002662);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002722, EnemyEtis);
				break;
			}
			case 26385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002663);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002723, EnemyEtis);
				break;
			}
			case 26395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002664);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002724, EnemyEtis);
				break;
			}
			case 26405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002665);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002725, EnemyEtis);
				break;
			}
			case 26415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002666);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002726, EnemyEtis);
				break;
			}
			case 26425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002667);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002727, EnemyEtis);
				break;
			}
			case 26435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002668);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002728, EnemyEtis);
				break;
			}
			case 26445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002669);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002729, EnemyEtis);
				break;
			}
			case 26455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002670);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002730, EnemyEtis);
				break;
			}
			case 26465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002671);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002731, EnemyEtis);
				break;
			}
			case 26475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002672);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002732, EnemyEtis);
				break;
			}
			case 26485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002673);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002733, EnemyEtis);
				break;
			}
			case 26495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002674);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002734, EnemyEtis);
				break;
			}
			case 26500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003238);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 26505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002675);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002735, EnemyEtis);
				break;
			}
			case 26515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002676);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002736, EnemyEtis);
				break;
			}
			case 26525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002677);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002737, EnemyEtis);
				break;
			}
			case 26535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002678);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002738, EnemyEtis);
				break;
			}
			case 26545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002679);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002739, EnemyEtis);
				break;
			}
			case 26555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002680);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002740, EnemyEtis);
				break;
			}
			case 26565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002681);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002741, EnemyEtis);
				break;
			}
			case 26575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002682);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002742, EnemyEtis);
				break;
			}
			case 26585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002683);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002743, EnemyEtis);
				break;
			}
			case 26595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002684);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002744, EnemyEtis);
				break;
			}
			case 26605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002685);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002745, EnemyEtis);
				break;
			}
			case 26615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002686);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002746, EnemyEtis);
				break;
			}
			case 26625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002687);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002747, EnemyEtis);
				break;
			}
			case 26635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002688);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002748, EnemyEtis);
				break;
			}
			case 26645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002689);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002749, EnemyEtis);
				break;
			}
			case 26655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002690);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002750, EnemyEtis);
				break;
			}
			case 26665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002691);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002751, EnemyEtis);
				break;
			}
			case 26675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002692);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002752, EnemyEtis);
				break;
			}
			case 26685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002693);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002753, EnemyEtis);
				break;
			}
			case 26695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002694);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002754, EnemyEtis);
				break;
			}
			case 26705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002695);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002755, EnemyEtis);
				break;
			}
			case 26715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002696);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002756, EnemyEtis);
				break;
			}
			case 26725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002697);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002757, EnemyEtis);
				break;
			}
			case 26735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002698);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002758, EnemyEtis);
				break;
			}
			case 26745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002699);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002759, EnemyEtis);
				break;
			}
			case 26755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002700);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002760, EnemyEtis);
				break;
			}
			case 26765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002701);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002761, EnemyEtis);
				break;
			}
			case 26775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002702);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002762, EnemyEtis);
				break;
			}
			case 26785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002703);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002763, EnemyEtis);
				break;
			}
			case 26795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002704);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002764, EnemyEtis);
				break;
			}
			case 26805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002705);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002765, EnemyEtis);
				break;
			}
			case 26815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002706);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002766, EnemyEtis);
				break;
			}
			case 26825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002707);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002767, EnemyEtis);
				break;
			}
			case 26835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002708);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002768, EnemyEtis);
				break;
			}
			case 26845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002709);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002769, EnemyEtis);
				break;
			}
			case 26855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002710);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002770, EnemyEtis);
				break;
			}
			case 26865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002711);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002771, EnemyEtis);
				break;
			}
			case 26875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002712);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002772, EnemyEtis);
				break;
			}
			case 26885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002713);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002773, EnemyEtis);
				break;
			}
			case 26895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002714);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002774, EnemyEtis);
				break;
			}
			case 26905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002715);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002775, EnemyEtis);
				break;
			}
			case 26915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002716);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002776, EnemyEtis);
				break;
			}
			case 26925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002717);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002777, EnemyEtis);
				break;
			}
			case 26935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002718);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002778, EnemyEtis);
				break;
			}
			case 26945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002719);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002779, EnemyEtis);
				break;
			}
			case 26955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002720);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002780, EnemyEtis);
				break;
			}
			case 26965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002721);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002781, EnemyEtis);
				break;
			}
			case 26975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002722);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002782, EnemyEtis);
				break;
			}
			case 26985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002723);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002783, EnemyEtis);
				break;
			}
			case 26995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002724);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002784, EnemyEtis);
				break;
			}
			case 27005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002725);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002785, EnemyEtis);
				break;
			}
			case 27015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002726);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002786, EnemyEtis);
				break;
			}
			case 27025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002727);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002787, EnemyEtis);
				break;
			}
			case 27035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002728);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002788, EnemyEtis);
				break;
			}
			case 27045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002729);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002789, EnemyEtis);
				break;
			}
			case 27055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002730);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002790, EnemyEtis);
				break;
			}
			case 27065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002731);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002791, EnemyEtis);
				break;
			}
			case 27075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002732);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002792, EnemyEtis);
				break;
			}
			case 27085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002733);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002793, EnemyEtis);
				break;
			}
			case 27095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002734);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002794, EnemyEtis);
				break;
			}
			case 27105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002735);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002795, EnemyEtis);
				break;
			}
			case 27115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002736);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002796, EnemyEtis);
				break;
			}
			case 27125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002737);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002797, EnemyEtis);
				break;
			}
			case 27135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002738);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002798, EnemyEtis);
				break;
			}
			case 27145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002739);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002799, EnemyEtis);
				break;
			}
			case 27155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002740);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002800, EnemyEtis);
				break;
			}
			case 27165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002741);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002801, EnemyEtis);
				break;
			}
			case 27175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002742);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002802, EnemyEtis);
				break;
			}
			case 27185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002743);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002803, EnemyEtis);
				break;
			}
			case 27195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002744);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002804, EnemyEtis);
				break;
			}
			case 27205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002745);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002805, EnemyEtis);
				break;
			}
			case 27215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002746);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002806, EnemyEtis);
				break;
			}
			case 27225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002747);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002807, EnemyEtis);
				break;
			}
			case 27235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002748);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002808, EnemyEtis);
				break;
			}
			case 27245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002749);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002809, EnemyEtis);
				break;
			}
			case 27255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002750);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002810, EnemyEtis);
				break;
			}
			case 27265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002751);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002811, EnemyEtis);
				break;
			}
			case 27275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002752);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002812, EnemyEtis);
				break;
			}
			case 27285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002753);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002813, EnemyEtis);
				break;
			}
			case 27295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002754);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002814, EnemyEtis);
				break;
			}
			case 27305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002755);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002815, EnemyEtis);
				break;
			}
			case 27315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002756);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002816, EnemyEtis);
				break;
			}
			case 27325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002757);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002817, EnemyEtis);
				break;
			}
			case 27335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002758);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002818, EnemyEtis);
				break;
			}
			case 27345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002759);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002819, EnemyEtis);
				break;
			}
			case 27355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002760);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002820, EnemyEtis);
				break;
			}
			case 27365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002761);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002821, EnemyEtis);
				break;
			}
			case 27375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002762);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002822, EnemyEtis);
				break;
			}
			case 27385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002763);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002823, EnemyEtis);
				break;
			}
			case 27395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002764);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002824, EnemyEtis);
				break;
			}
			case 27405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002765);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002825, EnemyEtis);
				break;
			}
			case 27415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002766);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002826, EnemyEtis);
				break;
			}
			case 27425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002767);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002827, EnemyEtis);
				break;
			}
			case 27435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002768);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002828, EnemyEtis);
				break;
			}
			case 27445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002769);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002829, EnemyEtis);
				break;
			}
			case 27455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002770);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002830, EnemyEtis);
				break;
			}
			case 27465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002771);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002831, EnemyEtis);
				break;
			}
			case 27475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002772);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002832, EnemyEtis);
				break;
			}
			case 27485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002773);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002833, EnemyEtis);
				break;
			}
			case 27495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002774);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002834, EnemyEtis);
				break;
			}
			case 27505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002775);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002835, EnemyEtis);
				break;
			}
			case 27515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002776);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002836, EnemyEtis);
				break;
			}
			case 27525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002777);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002837, EnemyEtis);
				break;
			}
			case 27535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002778);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002838, EnemyEtis);
				break;
			}
			case 27545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002779);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002839, EnemyEtis);
				break;
			}
			case 27555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002780);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002840, EnemyEtis);
				break;
			}
			case 27565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002781);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002841, EnemyEtis);
				break;
			}
			case 27575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002782);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002842, EnemyEtis);
				break;
			}
			case 27585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002783);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002843, EnemyEtis);
				break;
			}
			case 27595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002784);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002844, EnemyEtis);
				break;
			}
			case 27605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002785);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002845, EnemyEtis);
				break;
			}
			case 27615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002786);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002846, EnemyEtis);
				break;
			}
			case 27625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002787);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002847, EnemyEtis);
				break;
			}
			case 27635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002788);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002848, EnemyEtis);
				break;
			}
			case 27645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002789);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002849, EnemyEtis);
				break;
			}
			case 27655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002790);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002850, EnemyEtis);
				break;
			}
			case 27665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002791);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002851, EnemyEtis);
				break;
			}
			case 27675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002792);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002852, EnemyEtis);
				break;
			}
			case 27685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002793);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002853, EnemyEtis);
				break;
			}
			case 27695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002794);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002854, EnemyEtis);
				break;
			}
			case 27705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002795);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002855, EnemyEtis);
				break;
			}
			case 27715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002796);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002856, EnemyEtis);
				break;
			}
			case 27725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002797);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002857, EnemyEtis);
				break;
			}
			case 27735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002798);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002858, EnemyEtis);
				break;
			}
			case 27745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002799);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002859, EnemyEtis);
				break;
			}
			case 27755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002800);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002860, EnemyEtis);
				break;
			}
			case 27765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002801);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002861, EnemyEtis);
				break;
			}
			case 27775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002802);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002862, EnemyEtis);
				break;
			}
			case 27785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002803);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002863, EnemyEtis);
				break;
			}
			case 27795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002804);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002864, EnemyEtis);
				break;
			}
			case 27805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002805);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002865, EnemyEtis);
				break;
			}
			case 27815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002806);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002866, EnemyEtis);
				break;
			}
			case 27825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002807);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002867, EnemyEtis);
				break;
			}
			case 27835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002808);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002868, EnemyEtis);
				break;
			}
			case 27845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002809);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002869, EnemyEtis);
				break;
			}
			case 27855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002810);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002870, EnemyEtis);
				break;
			}
			case 27865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002811);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002871, EnemyEtis);
				break;
			}
			case 27875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002812);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002872, EnemyEtis);
				break;
			}
			case 27885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002813);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002873, EnemyEtis);
				break;
			}
			case 27895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002814);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002874, EnemyEtis);
				break;
			}
			case 27900: {
				requestActor(10003239, EnemyDrastea);
				break;
			}
			case 27905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002815);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002875, EnemyEtis);
				break;
			}
			case 27915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002816);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002876, EnemyEtis);
				break;
			}
			case 27925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002817);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002877, EnemyEtis);
				break;
			}
			case 27935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002818);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002878, EnemyEtis);
				break;
			}
			case 27945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002819);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002879, EnemyEtis);
				break;
			}
			case 27955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002820);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002880, EnemyEtis);
				break;
			}
			case 27965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002821);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002881, EnemyEtis);
				break;
			}
			case 27975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002822);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002882, EnemyEtis);
				break;
			}
			case 27985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002823);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002883, EnemyEtis);
				break;
			}
			case 27995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002824);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002884, EnemyEtis);
				break;
			}
			case 28005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002825);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002885, EnemyEtis);
				break;
			}
			case 28015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002826);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002886, EnemyEtis);
				break;
			}
			case 28025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002827);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002887, EnemyEtis);
				break;
			}
			case 28035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002828);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002888, EnemyEtis);
				break;
			}
			case 28045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002829);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002889, EnemyEtis);
				break;
			}
			case 28055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002830);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002890, EnemyEtis);
				break;
			}
			case 28065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002831);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002891, EnemyEtis);
				break;
			}
			case 28075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002832);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002892, EnemyEtis);
				break;
			}
			case 28085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002833);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002893, EnemyEtis);
				break;
			}
			case 28095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002834);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002894, EnemyEtis);
				break;
			}
			case 28105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002835);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002895, EnemyEtis);
				break;
			}
			case 28115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002836);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002896, EnemyEtis);
				break;
			}
			case 28125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002837);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002897, EnemyEtis);
				break;
			}
			case 28135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002838);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002898, EnemyEtis);
				break;
			}
			case 28145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002839);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002899, EnemyEtis);
				break;
			}
			case 28155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002840);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002900, EnemyEtis);
				break;
			}
			case 28165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002841);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002901, EnemyEtis);
				break;
			}
			case 28175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002842);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002902, EnemyEtis);
				break;
			}
			case 28185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002843);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002903, EnemyEtis);
				break;
			}
			case 28195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002844);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002904, EnemyEtis);
				break;
			}
			case 28205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002845);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002905, EnemyEtis);
				break;
			}
			case 28215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002846);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002906, EnemyEtis);
				break;
			}
			case 28225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002847);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002907, EnemyEtis);
				break;
			}
			case 28235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002848);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002908, EnemyEtis);
				break;
			}
			case 28245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002849);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002909, EnemyEtis);
				break;
			}
			case 28255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002850);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002910, EnemyEtis);
				break;
			}
			case 28265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002851);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002911, EnemyEtis);
				break;
			}
			case 28275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002852);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002912, EnemyEtis);
				break;
			}
			case 28285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002853);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002913, EnemyEtis);
				break;
			}
			case 28295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002854);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002914, EnemyEtis);
				break;
			}
			case 28305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002855);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002915, EnemyEtis);
				break;
			}
			case 28315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002856);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002916, EnemyEtis);
				break;
			}
			case 28325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002857);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002917, EnemyEtis);
				break;
			}
			case 28335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002858);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002918, EnemyEtis);
				break;
			}
			case 28345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002859);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002919, EnemyEtis);
				break;
			}
			case 28355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002860);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002920, EnemyEtis);
				break;
			}
			case 28365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002861);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002921, EnemyEtis);
				break;
			}
			case 28375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002862);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002922, EnemyEtis);
				break;
			}
			case 28385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002863);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002923, EnemyEtis);
				break;
			}
			case 28395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002864);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002924, EnemyEtis);
				break;
			}
			case 28405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002865);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002925, EnemyEtis);
				break;
			}
			case 28415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002866);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002926, EnemyEtis);
				break;
			}
			case 28425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002867);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002927, EnemyEtis);
				break;
			}
			case 28435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002868);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002928, EnemyEtis);
				break;
			}
			case 28445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002869);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002929, EnemyEtis);
				break;
			}
			case 28455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002870);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002930, EnemyEtis);
				break;
			}
			case 28465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002871);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002931, EnemyEtis);
				break;
			}
			case 28475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002872);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002932, EnemyEtis);
				break;
			}
			case 28485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002873);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002933, EnemyEtis);
				break;
			}
			case 28495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002874);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002934, EnemyEtis);
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003239);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 28505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002875);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002935, EnemyEtis);
				break;
			}
			case 28515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002876);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002936, EnemyEtis);
				break;
			}
			case 28525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002877);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002937, EnemyEtis);
				break;
			}
			case 28535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002878);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002938, EnemyEtis);
				break;
			}
			case 28545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002879);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002939, EnemyEtis);
				break;
			}
			case 28555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002880);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002940, EnemyEtis);
				break;
			}
			case 28565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002881);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002941, EnemyEtis);
				break;
			}
			case 28575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002882);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002942, EnemyEtis);
				break;
			}
			case 28585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002883);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002943, EnemyEtis);
				break;
			}
			case 28595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002884);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002944, EnemyEtis);
				break;
			}
			case 28605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002885);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002945, EnemyEtis);
				break;
			}
			case 28615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002886);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002946, EnemyEtis);
				break;
			}
			case 28625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002887);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002947, EnemyEtis);
				break;
			}
			case 28635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002888);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002948, EnemyEtis);
				break;
			}
			case 28645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002889);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002949, EnemyEtis);
				break;
			}
			case 28655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002890);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002950, EnemyEtis);
				break;
			}
			case 28665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002891);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002951, EnemyEtis);
				break;
			}
			case 28675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002892);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002952, EnemyEtis);
				break;
			}
			case 28685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002893);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002953, EnemyEtis);
				break;
			}
			case 28695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002894);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002954, EnemyEtis);
				break;
			}
			case 28705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002895);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002955, EnemyEtis);
				break;
			}
			case 28715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002896);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002956, EnemyEtis);
				break;
			}
			case 28725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002897);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002957, EnemyEtis);
				break;
			}
			case 28735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002898);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002958, EnemyEtis);
				break;
			}
			case 28745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002899);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002959, EnemyEtis);
				break;
			}
			case 28755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002900);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002960, EnemyEtis);
				break;
			}
			case 28765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002901);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002961, EnemyEtis);
				break;
			}
			case 28775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002902);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002962, EnemyEtis);
				break;
			}
			case 28785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002903);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002963, EnemyEtis);
				break;
			}
			case 28795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002904);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002964, EnemyEtis);
				break;
			}
			case 28805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002905);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002965, EnemyEtis);
				break;
			}
			case 28815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002906);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002966, EnemyEtis);
				break;
			}
			case 28825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002907);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002967, EnemyEtis);
				break;
			}
			case 28835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002908);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002968, EnemyEtis);
				break;
			}
			case 28845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002909);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002969, EnemyEtis);
				break;
			}
			case 28855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002910);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002970, EnemyEtis);
				break;
			}
			case 28865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002911);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002971, EnemyEtis);
				break;
			}
			case 28875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002912);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002972, EnemyEtis);
				break;
			}
			case 28885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002913);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002973, EnemyEtis);
				break;
			}
			case 28895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002914);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002974, EnemyEtis);
				break;
			}
			case 28905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002915);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002975, EnemyEtis);
				break;
			}
			case 28915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002916);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002976, EnemyEtis);
				break;
			}
			case 28925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002917);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002977, EnemyEtis);
				break;
			}
			case 28935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002918);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002978, EnemyEtis);
				break;
			}
			case 28945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002919);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002979, EnemyEtis);
				break;
			}
			case 28955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002920);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002980, EnemyEtis);
				break;
			}
			case 28965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002921);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002981, EnemyEtis);
				break;
			}
			case 28975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002922);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002982, EnemyEtis);
				break;
			}
			case 28985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002923);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002983, EnemyEtis);
				break;
			}
			case 28995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002924);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002984, EnemyEtis);
				break;
			}
			case 29005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002925);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002985, EnemyEtis);
				break;
			}
			case 29015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002926);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002986, EnemyEtis);
				break;
			}
			case 29025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002927);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002987, EnemyEtis);
				break;
			}
			case 29035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002928);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002988, EnemyEtis);
				break;
			}
			case 29045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002929);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002989, EnemyEtis);
				break;
			}
			case 29055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002930);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002990, EnemyEtis);
				break;
			}
			case 29065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002931);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002991, EnemyEtis);
				break;
			}
			case 29075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002932);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002992, EnemyEtis);
				break;
			}
			case 29085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002933);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002993, EnemyEtis);
				break;
			}
			case 29095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002934);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002994, EnemyEtis);
				break;
			}
			case 29105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002935);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002995, EnemyEtis);
				break;
			}
			case 29115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002936);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002996, EnemyEtis);
				break;
			}
			case 29125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002937);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002997, EnemyEtis);
				break;
			}
			case 29135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002938);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002998, EnemyEtis);
				break;
			}
			case 29145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002939);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10002999, EnemyEtis);
				break;
			}
			case 29155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002940);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003000, EnemyEtis);
				break;
			}
			case 29165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002941);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003001, EnemyEtis);
				break;
			}
			case 29175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002942);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003002, EnemyEtis);
				break;
			}
			case 29185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002943);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003003, EnemyEtis);
				break;
			}
			case 29195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002944);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003004, EnemyEtis);
				break;
			}
			case 29205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002945);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003005, EnemyEtis);
				break;
			}
			case 29215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002946);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003006, EnemyEtis);
				break;
			}
			case 29225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002947);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003007, EnemyEtis);
				break;
			}
			case 29235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002948);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003008, EnemyEtis);
				break;
			}
			case 29245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002949);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003009, EnemyEtis);
				break;
			}
			case 29255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002950);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003010, EnemyEtis);
				break;
			}
			case 29265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002951);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003011, EnemyEtis);
				break;
			}
			case 29275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002952);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003012, EnemyEtis);
				break;
			}
			case 29285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002953);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003013, EnemyEtis);
				break;
			}
			case 29295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002954);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003014, EnemyEtis);
				break;
			}
			case 29305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002955);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003015, EnemyEtis);
				break;
			}
			case 29315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002956);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003016, EnemyEtis);
				break;
			}
			case 29325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002957);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003017, EnemyEtis);
				break;
			}
			case 29335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002958);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003018, EnemyEtis);
				break;
			}
			case 29345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002959);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003019, EnemyEtis);
				break;
			}
			case 29355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002960);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003020, EnemyEtis);
				break;
			}
			case 29365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002961);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003021, EnemyEtis);
				break;
			}
			case 29375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002962);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003022, EnemyEtis);
				break;
			}
			case 29385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002963);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003023, EnemyEtis);
				break;
			}
			case 29395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002964);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003024, EnemyEtis);
				break;
			}
			case 29405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002965);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003025, EnemyEtis);
				break;
			}
			case 29415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002966);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003026, EnemyEtis);
				break;
			}
			case 29425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002967);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003027, EnemyEtis);
				break;
			}
			case 29435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002968);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003028, EnemyEtis);
				break;
			}
			case 29445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002969);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003029, EnemyEtis);
				break;
			}
			case 29455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002970);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003030, EnemyEtis);
				break;
			}
			case 29465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002971);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003031, EnemyEtis);
				break;
			}
			case 29475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002972);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003032, EnemyEtis);
				break;
			}
			case 29485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002973);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003033, EnemyEtis);
				break;
			}
			case 29495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002974);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003034, EnemyEtis);
				break;
			}
			case 29505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002975);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003035, EnemyEtis);
				break;
			}
			case 29515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002976);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003036, EnemyEtis);
				break;
			}
			case 29525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002977);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003037, EnemyEtis);
				break;
			}
			case 29535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002978);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003038, EnemyEtis);
				break;
			}
			case 29545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002979);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003039, EnemyEtis);
				break;
			}
			case 29555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002980);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003040, EnemyEtis);
				break;
			}
			case 29565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002981);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003041, EnemyEtis);
				break;
			}
			case 29575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002982);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003042, EnemyEtis);
				break;
			}
			case 29585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002983);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003043, EnemyEtis);
				break;
			}
			case 29595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002984);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003044, EnemyEtis);
				break;
			}
			case 29605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002985);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003045, EnemyEtis);
				break;
			}
			case 29615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002986);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003046, EnemyEtis);
				break;
			}
			case 29625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002987);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003047, EnemyEtis);
				break;
			}
			case 29635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002988);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003048, EnemyEtis);
				break;
			}
			case 29645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002989);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003049, EnemyEtis);
				break;
			}
			case 29655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002990);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003050, EnemyEtis);
				break;
			}
			case 29665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002991);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003051, EnemyEtis);
				break;
			}
			case 29675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002992);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003052, EnemyEtis);
				break;
			}
			case 29685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002993);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003053, EnemyEtis);
				break;
			}
			case 29695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002994);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003054, EnemyEtis);
				break;
			}
			case 29705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002995);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003055, EnemyEtis);
				break;
			}
			case 29715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002996);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003056, EnemyEtis);
				break;
			}
			case 29725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002997);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003057, EnemyEtis);
				break;
			}
			case 29735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002998);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003058, EnemyEtis);
				break;
			}
			case 29745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10002999);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003059, EnemyEtis);
				break;
			}
			case 29755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003000);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003060, EnemyEtis);
				break;
			}
			case 29765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003001);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003061, EnemyEtis);
				break;
			}
			case 29775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003002);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003062, EnemyEtis);
				break;
			}
			case 29785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003003);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003063, EnemyEtis);
				break;
			}
			case 29795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003004);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003064, EnemyEtis);
				break;
			}
			case 29805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003005);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003065, EnemyEtis);
				break;
			}
			case 29815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003006);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003066, EnemyEtis);
				break;
			}
			case 29825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003007);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003067, EnemyEtis);
				break;
			}
			case 29835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003008);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003068, EnemyEtis);
				break;
			}
			case 29845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003009);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003069, EnemyEtis);
				break;
			}
			case 29855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003010);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003070, EnemyEtis);
				break;
			}
			case 29865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003011);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003071, EnemyEtis);
				break;
			}
			case 29875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003012);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003072, EnemyEtis);
				break;
			}
			case 29885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003013);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003073, EnemyEtis);
				break;
			}
			case 29895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003014);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003074, EnemyEtis);
				break;
			}
			case 29900: {
				requestActor(10003240, EnemyDrastea);
				break;
			}
			case 29905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003015);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003075, EnemyEtis);
				break;
			}
			case 29915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003016);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003076, EnemyEtis);
				break;
			}
			case 29925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003017);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003077, EnemyEtis);
				break;
			}
			case 29935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003018);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003078, EnemyEtis);
				break;
			}
			case 29945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003019);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003079, EnemyEtis);
				break;
			}
			case 29955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003020);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003080, EnemyEtis);
				break;
			}
			case 29965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003021);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003081, EnemyEtis);
				break;
			}
			case 29975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003022);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003082, EnemyEtis);
				break;
			}
			case 29985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003023);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003083, EnemyEtis);
				break;
			}
			case 29995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003024);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003084, EnemyEtis);
				break;
			}
			case 30005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003025);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003085, EnemyEtis);
				break;
			}
			case 30015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003026);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003086, EnemyEtis);
				break;
			}
			case 30025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003027);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003087, EnemyEtis);
				break;
			}
			case 30035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003028);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003088, EnemyEtis);
				break;
			}
			case 30045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003029);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003089, EnemyEtis);
				break;
			}
			case 30055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003030);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003090, EnemyEtis);
				break;
			}
			case 30065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003031);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003091, EnemyEtis);
				break;
			}
			case 30075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003032);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003092, EnemyEtis);
				break;
			}
			case 30085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003033);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003093, EnemyEtis);
				break;
			}
			case 30095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003034);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003094, EnemyEtis);
				break;
			}
			case 30105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003035);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003095, EnemyEtis);
				break;
			}
			case 30115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003036);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003096, EnemyEtis);
				break;
			}
			case 30125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003037);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003097, EnemyEtis);
				break;
			}
			case 30135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003038);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003098, EnemyEtis);
				break;
			}
			case 30145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003039);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003099, EnemyEtis);
				break;
			}
			case 30155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003040);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003100, EnemyEtis);
				break;
			}
			case 30165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003041);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003101, EnemyEtis);
				break;
			}
			case 30175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003042);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003102, EnemyEtis);
				break;
			}
			case 30185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003043);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003103, EnemyEtis);
				break;
			}
			case 30195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003044);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003104, EnemyEtis);
				break;
			}
			case 30205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003045);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003105, EnemyEtis);
				break;
			}
			case 30215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003046);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003106, EnemyEtis);
				break;
			}
			case 30225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003047);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003107, EnemyEtis);
				break;
			}
			case 30235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003048);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003108, EnemyEtis);
				break;
			}
			case 30245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003049);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003109, EnemyEtis);
				break;
			}
			case 30255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003050);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003110, EnemyEtis);
				break;
			}
			case 30265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003051);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003111, EnemyEtis);
				break;
			}
			case 30275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003052);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003112, EnemyEtis);
				break;
			}
			case 30285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003053);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003113, EnemyEtis);
				break;
			}
			case 30295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003054);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003114, EnemyEtis);
				break;
			}
			case 30305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003055);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003115, EnemyEtis);
				break;
			}
			case 30315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003056);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003116, EnemyEtis);
				break;
			}
			case 30325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003057);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003117, EnemyEtis);
				break;
			}
			case 30335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003058);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003118, EnemyEtis);
				break;
			}
			case 30345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003059);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003119, EnemyEtis);
				break;
			}
			case 30355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003060);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003120, EnemyEtis);
				break;
			}
			case 30365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003061);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003121, EnemyEtis);
				break;
			}
			case 30375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003062);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003122, EnemyEtis);
				break;
			}
			case 30385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003063);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003123, EnemyEtis);
				break;
			}
			case 30395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003064);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003124, EnemyEtis);
				break;
			}
			case 30405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003065);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003125, EnemyEtis);
				break;
			}
			case 30415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003066);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003126, EnemyEtis);
				break;
			}
			case 30425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003067);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003127, EnemyEtis);
				break;
			}
			case 30435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003068);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003128, EnemyEtis);
				break;
			}
			case 30445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003069);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003129, EnemyEtis);
				break;
			}
			case 30455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003070);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003130, EnemyEtis);
				break;
			}
			case 30465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003071);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003131, EnemyEtis);
				break;
			}
			case 30475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003072);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003132, EnemyEtis);
				break;
			}
			case 30485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003073);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003133, EnemyEtis);
				break;
			}
			case 30495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003074);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003134, EnemyEtis);
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003240);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 30505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003075);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003135, EnemyEtis);
				break;
			}
			case 30515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003076);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003136, EnemyEtis);
				break;
			}
			case 30525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003077);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003137, EnemyEtis);
				break;
			}
			case 30535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003078);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003138, EnemyEtis);
				break;
			}
			case 30545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003079);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003139, EnemyEtis);
				break;
			}
			case 30555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003080);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003140, EnemyEtis);
				break;
			}
			case 30565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003081);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003141, EnemyEtis);
				break;
			}
			case 30575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003082);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003142, EnemyEtis);
				break;
			}
			case 30585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003083);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003143, EnemyEtis);
				break;
			}
			case 30595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003084);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003144, EnemyEtis);
				break;
			}
			case 30605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003085);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003145, EnemyEtis);
				break;
			}
			case 30615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003086);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003146, EnemyEtis);
				break;
			}
			case 30625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003087);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003147, EnemyEtis);
				break;
			}
			case 30635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003088);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003148, EnemyEtis);
				break;
			}
			case 30645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003089);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003149, EnemyEtis);
				break;
			}
			case 30655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003090);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003150, EnemyEtis);
				break;
			}
			case 30665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003091);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003151, EnemyEtis);
				break;
			}
			case 30675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003092);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003152, EnemyEtis);
				break;
			}
			case 30685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003093);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003153, EnemyEtis);
				break;
			}
			case 30695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003094);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003154, EnemyEtis);
				break;
			}
			case 30705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003095);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003155, EnemyEtis);
				break;
			}
			case 30715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003096);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003156, EnemyEtis);
				break;
			}
			case 30725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003097);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003157, EnemyEtis);
				break;
			}
			case 30735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003098);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003158, EnemyEtis);
				break;
			}
			case 30745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003099);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003159, EnemyEtis);
				break;
			}
			case 30755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003100);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003160, EnemyEtis);
				break;
			}
			case 30765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003101);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003161, EnemyEtis);
				break;
			}
			case 30775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003102);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003162, EnemyEtis);
				break;
			}
			case 30785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003103);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003163, EnemyEtis);
				break;
			}
			case 30795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003104);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003164, EnemyEtis);
				break;
			}
			case 30805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003105);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003165, EnemyEtis);
				break;
			}
			case 30815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003106);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003166, EnemyEtis);
				break;
			}
			case 30825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003107);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003167, EnemyEtis);
				break;
			}
			case 30835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003108);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003168, EnemyEtis);
				break;
			}
			case 30845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003109);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003169, EnemyEtis);
				break;
			}
			case 30855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003110);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003170, EnemyEtis);
				break;
			}
			case 30865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003111);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003171, EnemyEtis);
				break;
			}
			case 30875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003112);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003172, EnemyEtis);
				break;
			}
			case 30885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003113);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003173, EnemyEtis);
				break;
			}
			case 30895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003114);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003174, EnemyEtis);
				break;
			}
			case 30905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003115);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003175, EnemyEtis);
				break;
			}
			case 30915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003116);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003176, EnemyEtis);
				break;
			}
			case 30925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003117);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003177, EnemyEtis);
				break;
			}
			case 30935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003118);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003178, EnemyEtis);
				break;
			}
			case 30945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003119);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003179, EnemyEtis);
				break;
			}
			case 30955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003120);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003180, EnemyEtis);
				break;
			}
			case 30965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003121);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003181, EnemyEtis);
				break;
			}
			case 30975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003122);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003182, EnemyEtis);
				break;
			}
			case 30985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003123);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003183, EnemyEtis);
				break;
			}
			case 30995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003124);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003184, EnemyEtis);
				break;
			}
			case 31005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003125);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003185, EnemyEtis);
				break;
			}
			case 31015: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003126);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003186, EnemyEtis);
				break;
			}
			case 31025: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003127);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003187, EnemyEtis);
				break;
			}
			case 31035: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003128);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003188, EnemyEtis);
				break;
			}
			case 31045: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003129);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003189, EnemyEtis);
				break;
			}
			case 31055: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003130);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003190, EnemyEtis);
				break;
			}
			case 31065: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003131);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003191, EnemyEtis);
				break;
			}
			case 31075: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003132);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003192, EnemyEtis);
				break;
			}
			case 31085: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003133);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003193, EnemyEtis);
				break;
			}
			case 31095: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003134);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003194, EnemyEtis);
				break;
			}
			case 31100: {
				requestScene(10000003, StageDebugPartClimax);
				break;
			}
			case 31105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003135);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003195, EnemyEtis);
				break;
			}
			case 31115: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003136);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003196, EnemyEtis);
				break;
			}
			case 31125: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003137);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003197, EnemyEtis);
				break;
			}
			case 31135: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003138);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003198, EnemyEtis);
				break;
			}
			case 31145: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003139);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003199, EnemyEtis);
				break;
			}
			case 31155: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003140);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003200, EnemyEtis);
				break;
			}
			case 31165: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003141);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003201, EnemyEtis);
				break;
			}
			case 31175: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003142);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003202, EnemyEtis);
				break;
			}
			case 31185: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003143);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003203, EnemyEtis);
				break;
			}
			case 31195: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003144);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003204, EnemyEtis);
				break;
			}
			case 31205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003145);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003205, EnemyEtis);
				break;
			}
			case 31215: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003146);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003206, EnemyEtis);
				break;
			}
			case 31225: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003147);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003207, EnemyEtis);
				break;
			}
			case 31235: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003148);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003208, EnemyEtis);
				break;
			}
			case 31245: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003149);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003209, EnemyEtis);
				break;
			}
			case 31255: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003150);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003210, EnemyEtis);
				break;
			}
			case 31265: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003151);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003211, EnemyEtis);
				break;
			}
			case 31275: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003152);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003212, EnemyEtis);
				break;
			}
			case 31285: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003153);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003213, EnemyEtis);
				break;
			}
			case 31295: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003154);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003214, EnemyEtis);
				break;
			}
			case 31305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003155);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003215, EnemyEtis);
				break;
			}
			case 31315: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003156);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003216, EnemyEtis);
				break;
			}
			case 31325: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003157);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003217, EnemyEtis);
				break;
			}
			case 31335: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003158);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003218, EnemyEtis);
				break;
			}
			case 31345: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003159);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003219, EnemyEtis);
				break;
			}
			case 31355: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003160);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003220, EnemyEtis);
				break;
			}
			case 31365: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003161);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003221, EnemyEtis);
				break;
			}
			case 31375: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003162);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003222, EnemyEtis);
				break;
			}
			case 31385: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003163);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003223, EnemyEtis);
				break;
			}
			case 31395: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003164);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(10003224, EnemyEtis);
				break;
			}
			case 31405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003165);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31415: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003166);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31425: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003167);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31435: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003168);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31445: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003169);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31455: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003170);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31465: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003171);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31475: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003172);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31485: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003173);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31495: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003174);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003175);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31515: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003176);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31525: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003177);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31535: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003178);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31545: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003179);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31555: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003180);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31565: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003181);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31575: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003182);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31585: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003183);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31595: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003184);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003185);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31615: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003186);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31625: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003187);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31635: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003188);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31645: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003189);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31655: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003190);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31665: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003191);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31675: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003192);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31685: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003193);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31695: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003194);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003195);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31715: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003196);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31725: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003197);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31735: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003198);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31745: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003199);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31755: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003200);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31765: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003201);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31775: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003202);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31785: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003203);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31795: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003204);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003205);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31815: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003206);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31825: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003207);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31835: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003208);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31845: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003209);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31855: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003210);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31865: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003211);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31875: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003212);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31885: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003213);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31895: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003214);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31900: {
				requestActor(10003241, EnemyDrastea);
				break;
			}
			case 31905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003215);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31915: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003216);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31925: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003217);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31935: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003218);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31945: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003219);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31955: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003220);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31965: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003221);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31975: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003222);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31985: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003223);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 31995: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10003224);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 32000: {
				appendChild(receiveScene(10000003));
				break;
			}
			case 32500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003241);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 33900: {
				requestActor(10003242, EnemyDrastea);
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003242);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 35900: {
				requestActor(10003243, EnemyDrastea);
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003243);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 37900: {
				requestActor(10003244, EnemyDrastea);
				break;
			}
			case 38500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003244);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 39700: {
				requestActor(10000024, EnemyErmione);
				break;
			}
			case 39900: {
				requestActor(10003245, EnemyDrastea);
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000024);
				getSceneChief()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003245);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 41900: {
				requestActor(10003246, EnemyDrastea);
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003246);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 43900: {
				requestActor(10003247, EnemyDrastea);
				break;
			}
			case 44500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003247);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 45900: {
				requestActor(10003248, EnemyDrastea);
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003248);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 47900: {
				requestActor(10003249, EnemyDrastea);
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003249);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 49900: {
				requestActor(10003250, EnemyDrastea);
				break;
			}
			case 50500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003250);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 51900: {
				requestActor(10003251, EnemyDrastea);
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003251);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 53900: {
				requestActor(10003252, EnemyDrastea);
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003252);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 55900: {
				requestActor(10003253, EnemyDrastea);
				break;
			}
			case 56500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003253);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 57900: {
				requestActor(10003254, EnemyDrastea);
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10003254);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 3290-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_FAINAL: {
            if (pPhase->hasJustChanged()) {
                //STGDBGClimax_終焉の処理
                _TRACE_("STGDBGClimax_終焉のStageDebugPartController::PHASE_FAINALきた");
            }

            if (pPhase->hasArrivedFrameAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void StageDebugPartController::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_STAGEDEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_event_val == EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
        pPhase->change(PHASE_FAINAL); //フェーズをStageDebugPartController::PHASE_FAINALに切り替える
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
