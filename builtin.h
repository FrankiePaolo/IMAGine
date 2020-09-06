# include <vips/vips.h>

/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);

/* methods for images */
struct utils * getWidth(struct symref * v);
void getHeight(struct symref * v);
void getBands(struct symref * v);
void toColorSpace(struct symref * l,struct ast * v,struct ast * s);
void crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height);
void smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height);
void add(struct symref * l,struct symref * r,struct ast * p);                   //Sums 2 images
void subtract_img(struct symref * l,struct symref * r,struct ast * p);          //Subtracts 2 images
void invert(struct symref * l,struct ast * v);                                  //Inverts the image
void average(struct symref * v);
void openImg(char * path);
void getBands(struct symref * v);
void crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height);
void smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height);
void toColorSpace(struct symref * l,struct ast * v,struct ast * s);
void rotate(struct symref * l,struct ast * v,struct ast * s);


/* methods for lists */
struct utils * depth(struct symbol * e);
void get(struct symbol * e,struct utils * v);
void push(struct symbol * e,struct utils * v);
void pop(struct symbol * e);