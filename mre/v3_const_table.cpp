// V3: like V1, but the count comes from a const table with a variable index (as in Boost:
// bucket_array_base<true>::sizes[size_index_]).
#include <cstddef>
struct node { node* prior; };
node* allocate();
extern const std::size_t sizes[];
std::size_t size_index_;
node* buckets;

struct auto_space {
    std::size_t n_;
    node* data_;
    explicit auto_space(std::size_t n) : n_(n), data_(n_ ? allocate() : nullptr) {}
};

struct bucket_array {
    auto_space spc;
    bucket_array() : spc(sizes[size_index_] + 1) {
        for (node* x = buckets, *y = buckets + sizes[size_index_]; x != y; ++x) x->prior = nullptr;
    }
};

bucket_array* make() { return new bucket_array(); }
