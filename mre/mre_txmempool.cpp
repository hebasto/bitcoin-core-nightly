// Mirrors CTxMemPool::indexed_transaction_set from Bitcoin Core (src/txmempool.h).
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/tag.hpp>
#include <array>
#include <cstdint>
#include <cstring>

struct Hash256 { std::array<unsigned char, 32> data{}; bool operator==(const Hash256&) const = default; };

struct Entry {
    Hash256 txid;
    Hash256 wtxid;
    int64_t fee{0};
};

struct SaltedHasher {
    uint64_t k0{1}, k1{2};
    size_t operator()(const Hash256& h) const { uint64_t v; std::memcpy(&v, h.data.data(), 8); return v ^ k0 ^ k1; }
};

struct index_by_txid {};
struct index_by_wtxid {};
struct index_by_fee {};

using Set = boost::multi_index_container<
    Entry,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<boost::multi_index::tag<index_by_txid>,  boost::multi_index::member<Entry, Hash256, &Entry::txid>,  SaltedHasher>,
        boost::multi_index::hashed_unique<boost::multi_index::tag<index_by_wtxid>, boost::multi_index::member<Entry, Hash256, &Entry::wtxid>, SaltedHasher>,
        boost::multi_index::ordered_non_unique<boost::multi_index::tag<index_by_fee>, boost::multi_index::member<Entry, int64_t, &Entry::fee>>
    >
>;

struct Pool {
    Set set;
    Pool() : set{} {}
};

Pool* make_pool() { return new Pool(); }
