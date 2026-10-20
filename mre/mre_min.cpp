#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

struct Entry { int id; };

using Set = boost::multi_index_container<
    Entry,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<boost::multi_index::member<Entry, int, &Entry::id>>
    >
>;

Set* make_set() { return new Set(); }
