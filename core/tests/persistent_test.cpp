//
// Created by Dmitry Khrykin on 27.07.2020.
//

#include <vector>
#include <unordered_map>
#include <algorithm>

#include <catch2/catch.hpp>

#include "persistent.h"
#include "notifier.h"

TEST_CASE("Persistent Storage", "[persistent]") {
    std::unordered_map<std::string, std::vector<uint8_t>> storage_mock;

    stg::persistent_storage::backend::set_setter([&](const std::string &key,
                                                     const void *data,
                                                     size_t size) {
        storage_mock[key] = std::vector<uint8_t>((const uint8_t *) data,
                                                 (const uint8_t *) data + size);
    });

    stg::persistent_storage::backend::set_getter([&](const std::string &key,
                                                     const auto &result) {
        result(storage_mock[key].data());
    });

    stg::persistent_storage::test();

    SECTION("non-existent key") {
        REQUIRE(stg::persistent_storage::get<std::string>("some") == nullptr);
    }

    SECTION("POD") {
        {
            uint32_t i = 48;
            stg::persistent_storage::set("uint32_t", i);
        }

        REQUIRE(*stg::persistent_storage::get<uint32_t>("uint32_t") == 48);
    }

    SECTION("std::string") {
        {
            std::string test_string = "test std::string";
            stg::persistent_storage::set("std::string", test_string);
            stg::persistent_storage::set("const char *", "test const char *");
        }

        REQUIRE(*stg::persistent_storage::get<std::string>("std::string") == "test std::string");
        REQUIRE(*stg::persistent_storage::get<std::string>("const char *") == "test const char *");
    }

    SECTION("std::vector<std::string>") {
        {
            std::vector<std::string> test_strings = {"Test 1", "Тест 2"};
            stg::persistent_storage::set("std::vector", test_strings);
        }

        std::vector<std::string> expected_strings = {"Test 1", "Тест 2"};
        REQUIRE(*stg::persistent_storage::get<std::vector<std::string>>("std::vector") == expected_strings);
    }

    SECTION("stg::notifier::dictionary") {
        {
            stg::notifier::dictionary test_map = {
                    {"A", {"Test 1", "Тест 2"}},
                    {"B", {"Test 3", "Тест 4"}}
            };

            stg::persistent_storage::set("std::unordered_map", test_map);
        }

        stg::notifier::dictionary expected_map = {
                {"A", {"Test 1", "Тест 2"}},
                {"B", {"Test 3", "Тест 4"}}
        };

        REQUIRE(*stg::persistent_storage::get<stg::notifier::dictionary>("std::unordered_map") == expected_map);
    }
}
