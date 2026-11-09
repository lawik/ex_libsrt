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
  // The NIFs run in whichever process calls them, so they may run concurrently
  // on the same state. This mutex guards server/client against being destroyed
  // by stop_* while another NIF is using them.
  std::mutex instance_mutex;
  std::unique_ptr<Server> server;
  std::unique_ptr<Client> client;
} State;

#include "_generated/srt_nif.h"
