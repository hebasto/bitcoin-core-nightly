// V1: readable rendering of the cvise result: start pointer and bucket count are globals,
// the count is a signed long, allocation is an opaque call.
struct node { node* prior; };
node* allocate();
long bucket_count;      // Boost: sizes[size_index_]
node* buckets;          // Boost: spc.data()

struct auto_space {
    long n_;
    node* data_;
    explicit auto_space(long n) : n_(n), data_(n_ ? allocate() : nullptr) {}
};

struct bucket_array {
    auto_space spc;
    bucket_array() : spc(bucket_count + 1) {
        for (node* x = buckets, *y = buckets + bucket_count; x != y; ++x) x->prior = nullptr;
    }
};

bucket_array* make() { return new bucket_array(); }
