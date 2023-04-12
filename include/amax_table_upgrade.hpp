#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract]] amax_table_upgrade : public contract {
public:
    using contract::contract;

    amax_table_upgrade(name receiver, name code, datastream<const char*> ds)
        : contract(receiver, code, ds), person_tbl(receiver, receiver.value) {}

    [[eosio::action]] void create(uint64_t id, name fullname, uint64_t age, string sex, string work);

    [[eosio::action]] void update(uint64_t id, name fullname, uint64_t age, string sex, string work);

    [[eosio::action]] void remove(uint64_t id);

    using create_action = action_wrapper<"create"_n, &amax_table_upgrade::create>;
    using update_action = action_wrapper<"update"_n, &amax_table_upgrade::update>;
    using remove_action = action_wrapper<"remove"_n, &amax_table_upgrade::remove>;

private:
    struct [[eosio::table]] person {
        uint64_t id;
        name     fullname;
        uint64_t age;
        // add field
        string sex;
        string work;

        uint64_t primary_key() const { return id; }
        uint64_t get_age() const { return age; }
    };

    /// upgrade start
    // EOSLIB_SERIALIZE(person, (id)(fullname)(age));
    EOSLIB_SERIALIZE(person, (id)(fullname)(age)(sex)(work));

    // template <typename DataStream>
    // friend DataStream& operator<<(DataStream& ds, const person& t) {
    //     return ds << t.id << t.fullname << t.age << t.sex << t.work;
    // }

    // template <typename DataStream>
    // friend DataStream& operator>>(DataStream& ds, person& t) {
    //     return ds >> t.id << t.fullname << t.age;
    // }
    /// upgrade end

    // clang-format off
    typedef eosio::multi_index<"persons"_n, person,
        indexed_by<"byage"_n, const_mem_fun<person, uint64_t, &person::get_age>>
    > person_idx;
    // clang-format on

    person_idx person_tbl;
};
