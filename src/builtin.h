/* call built in functions */
    struct utils * callbuiltin(struct fncall * f);

/* built-in functions */
    void print_B(struct utils * v);

/* methods for lists */
    struct utils * length(struct symref * e);
    struct utils * get(struct symref * e,struct utils * v);
    void push(struct symref * e,struct utils * v);
    void list_remove(struct symref * e, struct utils * s);
    void pop(struct symref * e);
    void insert(struct symref * e, struct utils * v, struct utils * s);