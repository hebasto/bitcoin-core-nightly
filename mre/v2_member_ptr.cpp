// V2: like V1, but the loop runs over spc.data_ (as in Boost) instead of a global pointer.
struct node { node* prior; };
node* allocate();
long bucket_count;

struct auto_space {
    long n_;
    node* data_;
    explicit auto_space(long n) : n_(n), data_(n_ ? allocate() : nullptr) {}
};

struct bucket_array {
    auto_space spc;
    bucket_array() : spc(bucket_count + 1) {
        for (node* x = spc.data_, *y = spc.data_ + bucket_count; x != y; ++x) x->prior = nullptr;
    }
};

bucket_array* make() { return new bucket_array(); }
