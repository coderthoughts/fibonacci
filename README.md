To use this contract:

Send some data to it to compute:
./eosc push message david1 compute '{"ival":16}' --scope david1

The result of the computation (33 in this case) will be stored in a table:
$ ./eosc get table  david1 david1 results
{
  "rows": [{
      "id": "david1",
      "value": 33
    }
  ],
  "more": false
}

