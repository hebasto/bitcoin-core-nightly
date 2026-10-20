// Boost-free reconstruction of boost/multi_index/detail/bucket_array.hpp (Boost 1.92):
//   bucket_array(al, end_, size) : size_index_(size_index(size)), spc(al, sizes[size_index_] + 1) { clear(end_); }
//   auto_space(al, n) : n_(n), data_(n_ ? allocate(n_) : pointer(0)) {}
//   clear(): for (x = begin(), y = end(); x != y; ++x) x->prior() = pointer(0);
// with end() = buckets() + size() and size() = sizes[size_index_].
#include <cstddef>

struct node { node* prior; };

extern const std::size_t sizes[];      // a table of primes in Boost

struct auto_space {
    std::size_t n_;
    node* data_;
    explicit auto_space(std::size_t n) : n_(n), data_(n_ ? static_cast<node*>(::operator new(n_ * sizeof(node))) : nullptr) {}
    ~auto_space() { ::operator delete(data_); }
};

struct bucket_array {
    std::size_t size_index_;
    auto_space spc;

    explicit bucket_array(std::size_t idx) : size_index_(idx), spc(sizes[size_index_] + 1) { clear(); }

    std::size_t size() const { return sizes[size_index_]; }
    node* begin() const { return spc.data_; }
    node* end() const { return spc.data_ + size(); }

    void clear() {
        for (node* x = begin(), *y = end(); x != y; ++x) x->prior = nullptr;
    }
};

bucket_array* make(std::size_t idx) { return new bucket_array(idx); }
