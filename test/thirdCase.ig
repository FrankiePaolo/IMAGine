img im="./../test/Images/pencils.jpg";

wi=width(im);
he=height(im);
ba=bands(im);
mi=min(im);
ma=max(im);
avg=average(im);

print("Image 'im' details:");
print("Width: " + wi + " Height: " + he + " Bands: " + ba + " Min: " + mi + " Max: " + ma + " Avg: " + avg);
print("--------------------");

list outNames=
{"inverted","hsv","equalized","normalised",
"canny","sobel","sharpen","converted","added",
"subtracted","rotated","flipped","gaussianBlu",
"smartCrop","zoomed","cropped"};

i=1;
while(i<=length(outNames))do{
	insert(outNames, "../test/Images/Result/Case3/"+get(outNames, i)+".jpg", i+1);
	remove(outNames, i);
	i=i+1;
}
print("---------");



img inverted=invert(im,get(outNames,1));
img differentColor=convertColorSpace(im,get(outNames,2),"hsv");
img equalized=histEq(im,get(outNames,3));
img normalised=normalise(im,get(outNames,4));
img cannyImg=canny(im,get(outNames,5));
img sobelImg=sobel(im,get(outNames,6));
img sharpened=sharpen(im,get(outNames,7));
img converted=convert(im,get(outNames,8));
img added=add(im,equalized,get(outNames,9));
img subtracted=subtract(im,sobelImg,get(outNames,10));
img rotated=rotate(im,get(outNames,11),45.7);
img flipped=flip(im,get(outNames,12),"hor");
img gaussianBlurred=gaussianBlur(im,get(outNames,13),1);
img smartCropped=smartCrop(im,get(outNames,14),200,200);
img zommed=zoom(im,get(outNames,15),5,5);
img cropped=crop(im,get(outNames,16),50,50,50,50);
