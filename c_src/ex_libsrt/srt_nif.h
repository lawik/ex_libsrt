#pragma once

#include "client/client.h"
#include "server/server.h"
#include <memory>
#include <mutex>
#include <unifex/unifex.h>
#include <unordered_map>

typedef struct SRTState {
  UnifexPid owner;
  UnifexEnv* env;
  std::unordered_map<int, UnifexPid> conn_receivers;
  std::mutex conn_receivers_mutex;
  // env is shared by every callback thread; unifex_send is not thread-safe on it
  std::mutex send_mutex;
  std::unique_ptr<Server> server;
  std::unique_ptr<Client> client;
} State;

#include "_generated/srt_nif.h"
