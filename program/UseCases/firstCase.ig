def getDim(a){
	// Finds the dimensions of the area to crop
	wi=width(a);
	hi=height(a);
	if(wi>200 && hi>200)then{
		100;
	}else{
		wi*hi;
	}
}
def pageLine(a){
	print("---------"*a);
}

img lena="../program/Images/lena.tif";
img pencils="../program/Images/pencils.jpg";

convert(lena,"../program/Images/lena.jpg");
pageLine(1);

list outLi={};
i=1;
while(i<9)do{
	push(outLi,"../program/Images/Case1/outImg"+i+".jpg");
	i=i+1;
}

list imgLi={lena,pencils};
push(imgLi, extractBand(get(imgLi, 1), "../program/Images/Case1/band"+1+".jpg", 0));
remove(imgLi, 1);
push(imgLi, extractBand(get(imgLi, 1), "../program/Images/Case1/band"+2+".jpg", 0));
remove(imgLi, 1);
pageLine(3);

list imgOut={};
counterLi=1;
counter=1;
foreach(tempLi:imgLi){
		push(imgOut, sobel(tempLi,get(outLi,counterLi)));
		push(imgOut, canny(tempLi,get(outLi,counterLi+1)));
    smartCrop(get(imgOut, counter), get(outLi,counterLi+2), getDim(tempLi), getDim(tempLi));
    smartCrop(get(imgOut, counter+1), get(outLi,counterLi+3), getDim(tempLi), getDim(tempLi));
		counter=counter+1;
		counterLi=counterLi+4;
}

foreach(elaborate:imgOut){
		showImage(elaborate);
}
