#include "../config.h"
#include "../multi_value.h"
#include "../rcc/dep_graph.h"
#include "../rcc/graph_marshaler.h"
#include "exec.h"
#include "sched.h"

namespace rococo {

int OCCExecutor::StartLaunch(const SimpleCommand& cmd,
                             rrr::i32 *res,
                             map<int32_t, Value> &output,
                             rrr::DeferredReply *defer) {
  this->execute(cmd, res, output);
  defer->reply();

  return 0;
}


int OCCExecutor::Prepare() {
  verify(Config::config_s->cc_mode_ == MODE_OCC);
  auto txn = (mdb::TxnOCC *)mdb_txn();
  verify(txn != NULL);

  if (txn->commit_prepare())
    return SUCCESS;
  else
    return REJECT;
}


int OCCExecutor::commit() {
  verify(mdb_txn_ != NULL);
  verify(mdb_txn_ == sched_->RemoveMTxn(cmd_id_));
  ((mdb::TxnOCC *) mdb_txn_)->commit_confirm();
  delete mdb_txn_;
  mdb_txn_ = nullptr;
  return SUCCESS;
}


} // namespace rococo