// V4: like V3, with the table defined in the translation unit (so its values are visible).
#include <cstddef>
struct node { node* prior; };
node* allocate();
static const std::size_t sizes[] = {53ul, 97ul, 193ul, 389ul, 769ul, 1543ul, 3079ul, 6151ul};
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
