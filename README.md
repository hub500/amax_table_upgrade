--- amax_table_upgrade Project ---

- How to Build -

  - cd to 'build' directory
  - run the command 'cmake ..'
  - run the command 'make'

- After build -

  - The built smart contract is under the 'amax_table_upgrade' directory in the 'build' directory
  - You can then do a 'set contract' action with 'amcli' and point in to the './build/amax_table_upgrade' directory

- Additions to CMake should be done to the CMakeLists.txt in the './src' directory and not in the top level CMakeLists.txt

* create tblupgrade account & deploy contract

```
amcli create account amax tblupgrade AM6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV AM6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

executed transaction: 918229b15af81e52df1fd35363c0db3179d3820882619f653e75f377b3e568f3  200 bytes  6373 us
#          amax <= amax::newaccount             {"creator":"amax","name":"tblupgrade","owner":{"threshold":1,"keys":[{"key":"AM6MRyAjQq8ud7hVNYcfnVP...


amcli set contract tblupgrade ./amax_table_upgrade -p tblupgrade

Reading WASM from /root/workspace/amax_table_upgrade/build/amax_table_upgrade/amax_table_upgrade.wasm...
Publishing contract...
executed transaction: 5f7e7a388eb8994b65ae0bfd4298576edd0bd18b757e481c8975e77beebf4444  3240 bytes  12597 us
#          amax <= amax::setcode                {"account":"tblupgrade","vmtype":0,"vmversion":0,"code":"0061736d01000000017d1460000060027f7f0060047...
#          amax <= amax::setabi                 {"account":"tblupgrade","abi":"0d616d61783a3a6162692f312e3100040663726561746500030269640675696e74363...
```

* call contract create row data

```
amcli push action tblupgrade create '[1,"one",20]' -p hello

executed transaction: 75565485120c3cd743781a344a6a54d07fec22093bfed93d35ec5f6b6854f356  120 bytes  8775 us
#    tblupgrade <= tblupgrade::create           {"id":1,"fullname":"one","age":20}


amcli get table tblupgrade tblupgrade persons

{
  "rows": [{
      "id": 1,
      "fullname": "one",
      "age": 20
    }
  ],
  "more": false,
  "next_key": ""
}
```

* call contract update data

```
amcli push action tblupgrade update '[1,"oneone",22]' -p hello

executed transaction: c1d4ede18c84aeeb6ec038f6c1ab967b1cc95946f0a9f4b665c00ae2e0ce2681  120 bytes  5359 us
#    tblupgrade <= tblupgrade::update           {"id":1,"fullname":"oneone","age":22}


amcli get table tblupgrade tblupgrade persons

{
  "rows": [{
      "id": 1,
      "fullname": "oneone",
      "age": 22
    }
  ],
  "more": false,
  "next_key": ""
}
```

* call contract create data & remove data

```
amcli push action tblupgrade create '[2,"two",18]' -p hello

executed transaction: 3a8a4fbe5cc790800272c01400090158a1dce9884342636f3585fa9c47bb098b  120 bytes  2697 us
#    tblupgrade <= tblupgrade::create           {"id":2,"fullname":"two","age":18}


amcli get table tblupgrade tblupgrade persons
{
  "rows": [{
      "id": 1,
      "fullname": "oneone",
      "age": 22
    },{
      "id": 2,
      "fullname": "two",
      "age": 18
    }
  ],
  "more": false,
  "next_key": ""
}


amcli push action tblupgrade remove '[2]' -p hello

executed transaction: 19be9342e114b1a6fee9a14acb6ea9be5048606ea58b1da05c1a8a2edeac6cd8  104 bytes  3073 us
#    tblupgrade <= tblupgrade::remove           {"id":2}


amcli get table tblupgrade tblupgrade persons
{
  "rows": [{
      "id": 1,
      "fullname": "oneone",
      "age": 22
    }
  ],
  "more": false,
  "next_key": ""
}
```
