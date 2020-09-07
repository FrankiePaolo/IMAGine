/* methods for images */
struct utils * getWidth(struct symref * v);
struct utils * getHeight(struct symref * v);
struct utils * getBands(struct symref * v);
struct utils * toColorSpace(struct symref * l,struct ast * v,struct ast * s);
struct utils * crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height);
struct utils * smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height);
struct utils * add(struct symref * l,struct symref * r,struct ast * p);                   //Sums 2 images
struct utils * subtract_img(struct symref * l,struct symref * r,struct ast * p);          //Subtracts 2 images
struct utils * invert(struct symref * l,struct ast * v);                                  //Inverts the image
struct utils * average(struct symref * v);
void openImg(char * path);
struct utils * rotate(struct symref * l,struct ast * v,struct ast * s);
struct utils * histeq(struct symref * l,struct ast * v);
struct utils * norm(struct symref * l,struct ast * v);
struct utils * gaussianBlur(struct symref * l,struct ast * v,struct ast * s);
struct utils * canny(struct symref * l,struct ast * v);
struct utils * sobel(struct symref * l,struct ast * v);