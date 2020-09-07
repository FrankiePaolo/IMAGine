/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);

/* methods for lists */
struct utils * depth(struct symbol * e);
struct utils * get(struct symbol * e,struct utils * v);
void push(struct symbol * e,struct utils * v);
void pop(struct symbol * e);