# include <vips/vips.h>

/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);
void getWidth(struct symref * v);
void invert(struct symref * v);
void average(struct symref * v);