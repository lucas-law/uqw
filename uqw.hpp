#ifndef _UNQLITE_WRAPPER_H_
#define _UNQLITE_WRAPPER_H_

#include "unqlite.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <cassert>

namespace uqw {

class unqlite_wrapper
{
public:
    unqlite_wrapper(const char *db_file)
        : p_db_persist_(nullptr)
        , p_db_mem_(nullptr)
    {
        int rc = unqlite_open(&p_db_persist_, db_file, UNQLITE_OPEN_CREATE);
        assert(rc == UNQLITE_OK && p_db_persist_ != nullptr);
        rc = unqlite_open(&p_db_mem_, ":mem:", UNQLITE_OPEN_CREATE);
        assert(rc == UNQLITE_OK && p_db_mem_ != nullptr);
    }

    ~unqlite_wrapper()
    {
        unqlite_close(p_db_persist_);
        unqlite_close(p_db_mem_);
    }

public:
    std::vector<unsigned char> get(const std::string &key, bool persistance)
    {
        int rc = UNQLITE_OK;
        unqlite_int64 n_bytes;
        unqlite *target = persistance ? p_db_persist_ : p_db_mem_;
        do {
            rc = unqlite_kv_fetch(target, key.c_str(), key.size(), nullptr, &n_bytes);
            if (rc != UNQLITE_OK) break;

            std::vector<unsigned char> value(n_bytes);
            rc = unqlite_kv_fetch(target, key.c_str(), key.size(), value.data(), &n_bytes);
            if (rc != UNQLITE_OK) break;

            return value;
        } while (0);

        return std::vector<unsigned char>();
    }

    bool put(const std::string &key, const std::vector<unsigned char> &value, bool persistance)
    {
        int rc = UNQLITE_OK;
        unqlite *target = persistance ? p_db_persist_ : p_db_mem_;
        rc = unqlite_kv_store(target, key.c_str(), key.length(), value.data(), value.size());
        return rc == UNQLITE_OK;
    }

private:
    unqlite *p_db_persist_;
    unqlite *p_db_mem_;
};

}
#endif
