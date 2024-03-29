// Working methods 

img im="/home/frank/Desktop/Img/image.jpg";
out="/home/frank/Desktop/Img/inverted.jpg";
out2="/home/frank/Desktop/Img/hsv.jpg";
out3="/home/frank/Desktop/Img/equalized.jpg";
out4="/home/frank/Desktop/Img/normalised.jpg";
out5="/home/frank/Desktop/Img/canny.jpg";
out6="/home/frank/Desktop/Img/sobel.jpg";
out7="/home/frank/Desktop/Img/sharpen.jpg";
out8="/home/frank/Desktop/Img/converted.tif";
out9="/home/frank/Desktop/Img/added.jpg";
out10="/home/frank/Desktop/Img/subtracted.jpg";
out11="/home/frank/Desktop/Img/rotated.jpg";
out12="/home/frank/Desktop/Img/flipped.jpg";
out13="/home/frank/Desktop/Img/gaussianBlurred.jpg";
out14="/home/frank/Desktop/Img/smartCropped.jpg";
out15="/home/frank/Desktop/Img/zommed.jpg";
out16="/home/frank/Desktop/Img/cropped.jpg";

img inverted=invert(im,out);
img differentColor=convertColorSpace(im,out2,"hsv");
img equalized=histEq(im,out3);
img normalised=normalise(im,out4);
img cannyImg=canny(im,out5);
img sobelImg=sobel(im,out6);
img sharpened=sharpen(im,out7);
img converted=convert(im,out8);
img added=add(im,equalized,out9);
img subtracted=subtract(im,sobelImg,out10);
img rotated=rotate(im,out11,45.7);
img flipped=flip(im,out12,"hor");
img gaussianBlurred=gaussianBlur(im,out13,1);
img smartCropped=smartCrop(im,out14,200,200);
img zommed=zoom(im,out15,5,5);
img cropped=crop(im,out16,50,50,50,50);

wi=width(im);
he=height(im);
ba=bands(im);
mi=min(im);
ma=max(im);
avg=average(im);

//showImage(im);
// -------------------------------------------



