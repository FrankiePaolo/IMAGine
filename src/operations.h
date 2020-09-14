/* arithmetic operations */
    void sum(struct utils * v, struct utils * l, struct utils * r);
    void subtract(struct utils * v, struct utils * l, struct utils * r);
    void multiply(struct utils * v, struct utils * l, struct utils * r);
    struct utils * divide(struct utils * l, struct utils * r);

/* comparisons */
    void biggerThan(struct utils * v, struct utils * l, struct utils * r);
    void smallerThan(struct utils * v, struct utils * l, struct utils * r);
    void unequal(struct utils * v, struct utils * l, struct utils * r);
    void equal(struct utils * v, struct utils * l, struct utils * r);
    void biggerOrEqual(struct utils * v, struct utils * l, struct utils * r);
    void smallerOrEqual(struct utils * v, struct utils * l, struct utils * r);
    void absoluteValue(struct utils * v, struct utils * l);