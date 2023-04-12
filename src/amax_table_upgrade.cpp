#include <amax_table_upgrade.hpp>

void amax_table_upgrade::create(uint64_t id, name fullname, uint64_t age, string sex, string work) {
    check(age >= 6 && age < 100, "invalid age");

    auto p = person_tbl.find(id);
    check(p == person_tbl.end(), "person is exists");

    person_tbl.emplace(_self, [&](auto& row) {
        row.id       = id;
        row.fullname = fullname;
        row.age      = age;
        row.sex      = sex;
        row.work     = work;
    });
}

void amax_table_upgrade::update(uint64_t id, name fullname, uint64_t age, string sex, string work) {
    check(age >= 6 && age < 100, "invalid age");

    auto iter = person_tbl.find(id);
    check(iter != person_tbl.end(), "person is not exists");

    person_tbl.modify(iter, _self, [&](auto& row) {
        row.fullname = fullname;
        row.age      = age;
        row.sex      = sex;
        row.work     = work;
    });
}

void amax_table_upgrade::remove(uint64_t id) {
    auto iter = person_tbl.find(id);
    check(iter != person_tbl.end(), "person is not exists");

    person_tbl.erase(iter);
}