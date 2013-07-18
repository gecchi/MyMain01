window.onload = function(){
	//var matchObj= new RegExp("cv");
	var cvObj;
	var is_hit = false;
	for(x = 0; x < 3; x++){
		selectObj = document.getElementsByTagName("canvas");
		for(i=0; i < selectObj.length; i++){
			//if(selectObj[i].id.match(matchObj)){
				cvObj = selectObj[i];
				is_hit = true;
				break;
			//}
		}
		if (is_hit) {
			break;
		}
	}
	var r = 1.0;
    var ctx = cvObj.getContext('2d');
    ctx.clearRect(0, 0, cvObj.width, cvObj.height);
    ctx.translate(cvObj.width-(cvObj.width*r), 0);
    ctx.scale(r, r);
}