struct CTxMemPoolEntry {};
struct SaltedWtxidHasher {
  SaltedWtxidHasher();
};
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
struct mempoolentry_wtxid {
  typedef int result_type;
};
struct CTxMemPool {
  using indexed_transaction_set = boost::multi_index_container<
      CTxMemPoolEntry,
      boost::multi_index::indexed_by<
          boost::multi_index::hashed_unique< mempoolentry_wtxid,
                                             SaltedWtxidHasher >,
          boost::multi_index::ordered_non_unique<
              boost::multi_index::identity< CTxMemPoolEntry > > > >;
  indexed_transaction_set mapTx;
  CTxMemPool();
};
CTxMemPool::CTxMemPool() {}
