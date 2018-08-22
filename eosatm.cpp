#include "eosatm.hpp"

void eosatm::config(int8_t timezone, uint64_t daily_limit)
{
    
}

void eosatm::handle_transfer(account_name from, account_name to, extended_asset quantity, string memo)
{
    if (from != _self)
        return;
}