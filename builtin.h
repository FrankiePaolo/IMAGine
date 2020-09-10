/* call built in functions */
struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
void print_B(struct utils * v);

/* methods for lists */
struct utils * length(struct symbol * e);
struct utils * get(struct symbol * e,struct utils * v);
void push(struct symbol * e,struct utils * v);
void pop(struct symbol * e);
void insert(struct symbol * e, struct utils * v, struct utils * s);
void list_remove(struct symbol * e, struct utils * s);