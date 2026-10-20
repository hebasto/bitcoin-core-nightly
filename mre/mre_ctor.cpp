// Candidate built from what survived cvise on txmempool.cpp: a class holding a
// multi_index_container with two hashed indexes whose hashers are seeded by an
// opaque call, a const member initialised from an opaque call, and a
// std::function-taking call with a <=> lambda in the constructor body.
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/tag.hpp>
#include <array>
#include <compare>
#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <mutex>

struct Hash256 { std::array<unsigned char, 32> data{}; bool operator==(const Hash256&) const = default; auto operator<=>(const Hash256&) const = default; };

uint64_t GetRand64();

struct SaltedHasher {
    const uint64_t k0, k1;
    SaltedHasher() : k0{GetRand64()}, k1{GetRand64()} {}
    size_t operator()(const Hash256& h) const { uint64_t v; std::memcpy(&v, h.data.data(), 8); return v ^ k0 ^ k1; }
};

struct Ref { Hash256 id; };
struct Entry : Ref { std::array<unsigned char, 200> payload{}; int64_t time{0}; };

struct entry_txid { typedef Hash256 result_type; const Hash256& operator()(const Entry& e) const { return e.id; } };
struct entry_wtxid { typedef Hash256 result_type; const Hash256& operator()(const Entry& e) const { return e.id; } };
struct CompareByTime { bool operator()(const Entry& a, const Entry& b) const { return a.time < b.time; } };
struct entry_time {};
struct index_by_wtxid {};

struct Graph { virtual ~Graph() = default; };
std::unique_ptr<Graph> MakeGraph(int64_t, int64_t, int64_t, std::function<std::strong_ordering(const Ref&, const Ref&)>);

struct Options { int64_t cluster_count{64}; int64_t cluster_size_vbytes{101000}; };
struct Error { int code{0}; };
Options&& Flatten(Options&& opts, Error& error);

class Pool {
public:
    using indexed_set = boost::multi_index::multi_index_container<
        Entry,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_unique<entry_txid, SaltedHasher>,
            boost::multi_index::hashed_unique<boost::multi_index::tag<index_by_wtxid>, entry_wtxid, SaltedHasher>,
            boost::multi_index::ordered_non_unique<boost::multi_index::tag<entry_time>, boost::multi_index::identity<Entry>, CompareByTime>
        >
    >;

    mutable std::recursive_mutex cs;
    std::unique_ptr<Graph> m_graph;
    indexed_set mapTx;
    const Options m_opts;

    Pool(Options opts, Error& error);
};

Pool::Pool(Options opts, Error& error)
    : m_opts{Flatten(std::move(opts), error)}
{
    m_graph = MakeGraph(m_opts.cluster_count, m_opts.cluster_size_vbytes * 4, 75'000,
                        [&](const Ref& a, const Ref& b) noexcept { return a.id <=> b.id; });
}
