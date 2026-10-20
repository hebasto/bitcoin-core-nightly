// Like mre_txmempool.cpp, but with a large element type (CTxMemPoolEntry is a few hundred bytes).
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/tag.hpp>
#include <array>
#include <cstdint>
#include <cstring>
#include <memory>

struct Hash256 { std::array<unsigned char, 32> data{}; bool operator==(const Hash256&) const = default; };

struct Entry {
    std::shared_ptr<const int> tx;
    Hash256 txid;
    Hash256 wtxid;
    int64_t fee{0};
    std::array<unsigned char, 200> padding{};
    int64_t time{0};
    bool operator<(const Entry& o) const { return time < o.time; }
};

struct SaltedHasher {
    uint64_t k0{1}, k1{2};
    size_t operator()(const Hash256& h) const { uint64_t v; std::memcpy(&v, h.data.data(), 8); return v ^ k0 ^ k1; }
};

struct entry_txid { using result_type = Hash256; const Hash256& operator()(const Entry& e) const { return e.txid; } };
struct entry_wtxid { using result_type = Hash256; const Hash256& operator()(const Entry& e) const { return e.wtxid; } };
struct index_by_wtxid {};
struct entry_time {};

using Set = boost::multi_index_container<
    Entry,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<entry_txid, SaltedHasher>,
        boost::multi_index::hashed_unique<boost::multi_index::tag<index_by_wtxid>, entry_wtxid, SaltedHasher>,
        boost::multi_index::ordered_non_unique<boost::multi_index::tag<entry_time>, boost::multi_index::identity<Entry>, std::less<Entry>>
    >
>;

struct Pool {
    Set set;
    int opts;
    Pool(int o) : opts{o} {}
};

std::unique_ptr<Pool> make_pool(int o) { return std::make_unique<Pool>(o); }
