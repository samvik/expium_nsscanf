
#include <catch2/catch_test_macros.hpp>

#include <cstring>
#include <iostream>
#include <nsscanf.h>

TEST_CASE("Parsing of simple unsigned", "[unsigned]")
{
  unsigned value1;
  int n = expium_nsscanf("42", "%u", &value1);
  REQUIRE(n == 1);
  REQUIRE(value1 == 42);
}

TEST_CASE("Parsing of two unsigned", "[unsigned]")
{
  unsigned value1, value2;
  int n = expium_nsscanf("Hello_42@1337!", "Hello_%u@%u!", &value1, &value2);
  REQUIRE(n == 2);
  REQUIRE(value1 == 42);
  REQUIRE(value2 == 1337);
}

TEST_CASE("Escape sequence", "[unsigned]")
{
  unsigned value1;
  int n = expium_nsscanf("Hello_%42%!", "Hello_\\%%u\\%!", &value1);
  REQUIRE(n == 1);
  REQUIRE(value1 == 42);
}

TEST_CASE("Parsing of simple unsigned", "[signed]")
{
  int value1;
  int n = expium_nsscanf("-42", "%d", &value1);
  REQUIRE(n == 1);
  REQUIRE(value1 == -42);
}

TEST_CASE("Parsing of string", "[string]")
{
  char str[128];
  int n = expium_nsscanf("Hello World", "Hello %s", str);
  REQUIRE(n == 1);
  REQUIRE(strcmp(str, "World") == 0);
}

TEST_CASE("Parsing of all types", "[string, signed, unsigned]")
{
  char str[128];
  unsigned value1;
  int value2;
  int n = expium_nsscanf("Hello World 42, -1337!", "Hello %s %u, %d!", str,
                         &value1, &value2);
  REQUIRE(n == 3);
  REQUIRE(value1 == 42);
  REQUIRE(value2 == -1337);
  REQUIRE(strcmp(str, "World") == 0);
}

TEST_CASE("Non matching caracther should faile gracefully",
          "[string, unsigned]")
{
  char str[128];
  unsigned value1;
  int n = expium_nsscanf("HeLLo World 42!", "Hello %s %u!", str, &value1);
  REQUIRE(n == 0);
}