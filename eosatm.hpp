#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>

#include <string>

using namespace std;
using namespace eosio;

struct transfer_args
{
    account_name from;
    account_name to;
    asset quantity;
    string memo;
};

class eosatm : public contract
{
  public:
    using contract::contract;

    const extended_symbol LIMITING_TOKEN = extended_symbol(S(4, EOS), N(eosio.token));

    /// @abi table config
    struct config_info
    {
        int8_t timezone;
        uint64_t daily_limit;
    };

    typedef singleton<N(config), config_info> tbl_config;

    /// @abi action
    void config(int8_t timezone, uint64_t daily_limit);

    void handle_transfer(account_name from, account_name to, extended_asset quantity, string memo);
};

extern "C"
{
    void apply(uint64_t receiver, uint64_t code, uint64_t action)
    {
        auto self = receiver;
        eosatm thiscontract(self);
        if (code == self)
        {
            switch (action)
            {
                EOSIO_API(eosatm, (config))
            }
        }
        else if (action == N(transfer))
        {
            auto transfer_data = unpack_action_data<transfer_args>();
            thiscontract.handle_transfer(transfer_data.from, transfer_data.to, extended_asset(transfer_data.quantity, code), transfer_data.memo);
        }
    }
}
