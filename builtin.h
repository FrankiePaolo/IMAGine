# include <vips/vips.h>

/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);

/* methods for images */
void getWidth(struct symref * v);
void add(struct symref * l,struct symref * r,struct ast * p);   //Sums 2 images
void subtract_img(struct symref * l,struct symref * r);         //Subtracts 2 images
void invert(struct ast * l,struct symref * v);                  //Inverts the image
void average(struct symref * v);
void openImg(char * path);

/* methods for lists */
struct utils * depth(struct symbol * e);
void get(struct symbol * e,struct utils * v);
void push(struct symbol * e,struct utils * v);
void pop(struct symbol * e);