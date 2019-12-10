/** FioTreasury header file
 *  Description: FioTreasury smart contract controls block producer and tpid payments.
 *  @author Adam Androulidakis
 *  @modifedby
 *  @file fio.treasury.cpp
 *  @copyright Dapix
 */

#include <fio.common/fio.common.hpp>
#include <fio.common/fioerror.hpp>
#include <eosiolib/time.hpp>
#include <fio.address/fio.address.hpp>
#include <fio.tpid/fio.tpid.hpp>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

namespace fioio {
    using namespace eosio;

    // @abi table clockstate i64
    struct [[eosio::table]] treasurystate {
        uint64_t lasttpidpayout;
        uint64_t payschedtimer;
        uint64_t rewardspaid;
        uint64_t bpreservetokensminted;
        uint64_t fdtnreservetokensminted;

        // Set the primary key to a constant value to store only one row
        uint64_t primary_key() const { return lasttpidpayout; }

        EOSLIB_SERIALIZE(treasurystate, (lasttpidpayout)(payschedtimer)(rewardspaid)
          (bpreservetokensminted)(fdtnreservetokensminted)
        )
    };

    typedef eosio::multi_index<"clockstate"_n, treasurystate> rewards_table;

    //@abi table bppaysched
    struct [[eosio::table]] bppaysched {

        name owner;
        uint64_t abpayshare = 0;
        uint64_t sbpayshare = 0;
        double votes;

        uint64_t primary_key() const { return owner.value; }

        EOSLIB_SERIALIZE( bppaysched, (owner)(abpayshare)(sbpayshare)(votes)
        )
    };

    typedef eosio::multi_index<"voteshares"_n, bppaysched> voteshares_table;
}