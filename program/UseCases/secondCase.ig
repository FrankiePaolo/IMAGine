def getBlur(a){
	blur=1;
	if(width(a)>100 && height(a)>288)then{
		blur=3;
		print("Blur di dimensioni: " + blur);
		blur;
	}else{
		print("Blur di dimensioni: " + blur);
		blur;
	}
}
def pageLine(a){
	print("---------"*a);
}

img lena="../program/Images/lena.tif";
img pencils="../program/Images/pencils.jpg";

out1="../program/Images/Case2/blurredLena.tif";
out2="../program/Images/Case2/blurredPencils.jpg";

list imgLi={lena,pencils};
list outLi={out1,out2};

index=1;
while(index<=length(imgLi))do{
	img tempIm=get(imgLi,index);
	showImage(gaussianBlur(tempIm,get(outLi,index),getBlur(tempIm)));
	pageLine(6);
	index=index+1;
}
