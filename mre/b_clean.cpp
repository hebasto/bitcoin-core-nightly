// Cleaned-up form of the reduced reproducer.
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <cstddef>

struct Entry {};

struct Hasher {
    Hasher();                                   // defined in another translation unit
    std::size_t operator()(int) const;
};

struct Key {
    typedef int result_type;
    int operator()(const Entry&) const;
};

struct Pool {
    boost::multi_index_container<
        Entry,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_unique<Key, Hasher>,
            boost::multi_index::ordered_non_unique<boost::multi_index::identity<Entry>>>>
        set;
    Pool();
};

Pool::Pool() {}
