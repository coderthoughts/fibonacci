#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>

extern "C" {
    void init()  {
    }

    struct compute {
       uint64_t iterations;
    };

    struct PACKED(result) {
		result() {};
		result(eosio::name id, uint64_t value):id(id), value(value) {};
        eosio::name id;
        uint64_t value;
    };

    using Results = eosio::table<N(fibonacci), N(fibonacci), N(results), result, uint64_t>;

	uint64_t fibonacci(uint64_t iterations) {
		uint64_t first = 0;
		uint64_t second = 1;

		if (iterations == 0)
			return 0;

		eosio::print("1 ");
		for (uint64_t i=1; i < iterations; i++) {
			uint64_t res = first + second;
			first = second;
			second = res;
			eosio::print(res, " ");
		}
		return second;
	}

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action ) {
		if (action == N(compute)) {
			auto message = eosio::current_message<compute>();
			eosio::print("Calling fibonacci\n");
			uint64_t num = fibonacci(message.iterations);

			result res(eosio::name(code), num);
			Results::store(res, res.id);
			eosio::print("Stored result in database\n");
		}
    }
} // extern "C"
