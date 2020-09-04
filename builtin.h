# include <vips/vips.h>

/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);

/* methods for images */
void getWidth(struct symref * v);
void invert(struct symref * v);
void average(struct symref * v);
void openImg(char * path);

/* methods for lists */
struct utils * depth(struct symbol * e);
void get(struct symbol * e,struct utils * v);
void push(struct symbol * e,struct utils * v);
void pop(struct symbol * e);