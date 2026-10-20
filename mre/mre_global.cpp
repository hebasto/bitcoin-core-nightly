// Boost-based: container with a hashed and an ordered index, constructed as a global.
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

struct Entry { int id; };

boost::multi_index::multi_index_container<
    Entry,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<boost::multi_index::member<Entry, int, &Entry::id>>,
        boost::multi_index::ordered_non_unique<boost::multi_index::identity<Entry>>
    >
> g_set;
