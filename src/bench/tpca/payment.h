#pragma once

#include "coordinator.h"
#include "bench/tpca/workload.h"

namespace janus {

class TpcaPaymentChopper: public TxData {

 public:

  TpcaPaymentChopper() {}

  virtual void Init(TxRequest &req);

  virtual bool HandleOutput(int pi,
                            int res,
                            map<int32_t, Value> &output) override {
    return false;
  }

  virtual bool IsReadOnly() { return false; }

  virtual void Reset() override;

  virtual ~TpcaPaymentChopper() { }

};

} // namespace janus
