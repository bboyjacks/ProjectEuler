#include <iostream>
#include <gtest/gtest.h>
#include "Grid.h"
#include <fstream>
#include <sstream>

typedef unsigned int ui;

// Problem 1 : Multiples of 3 and 5
int MultiplesOfThreeAndFive(const unsigned int _limit)
{
  unsigned int total = 0;

  // Add up all numbers divisible by three
  for (unsigned i = 3; i < _limit; i += 3)
  {
    total += i;
  }

  // Add up all numbers divisible by 5 but not divisible by three
  for (unsigned i = 5; i < _limit; i += 5)
  {
    if (i % 3 != 0)
      total += i;
  }
  return total;
}

TEST(ProjectEuler, multiples_of_3_and_5)
{
  ASSERT_EQ(23, MultiplesOfThreeAndFive(10));
  ASSERT_EQ(2318, MultiplesOfThreeAndFive(100));

  std::cout << MultiplesOfThreeAndFive(1000) << std::endl;
}

// Problem 2 : Even Fibonacci Numbers
int EvenFibonacciNumbers(const unsigned int _limit)
{
  unsigned int cur_num = 0;
  unsigned int prev_num_1 = 1;
  unsigned int prev_num_2 = 2;
  unsigned int total = prev_num_2;

  if (_limit < prev_num_2)
    return -1;

  while (true)
  {
    cur_num = prev_num_1 + prev_num_2;
    if (cur_num > _limit)
      break;
    if (cur_num % 2 == 0)
      total += cur_num;
    prev_num_1 = prev_num_2;
    prev_num_2 = cur_num;
  }
  return total;
}

TEST(ProjectEuler, even_fibonacci_numbers)
{
  ASSERT_EQ(44, EvenFibonacciNumbers(90));
  std::cout << EvenFibonacciNumbers(4000000) << std::endl;
}

// Problem 3 : Largest Prime Factor
int IsPrime(const long long int _num)
{
  long long count = 1;
  long long result = 1;
  while (count <= std::sqrt(_num))
  {
    if (_num % count == 0 && count != 1)
    {
      result = count;
      break;
    }
    count++;
  }
  return result;
}

void GetLargestPrimeFactors(const long long _num, std::vector<long long>& _result)
{
  const long long result = IsPrime(_num);

  if (result == 1)
  {
    _result.push_back(_num);
  }
  else
  {
    _result.push_back(result);
    const long long reduced_num = static_cast<long long>(_num / result);
    GetLargestPrimeFactors(reduced_num, _result);
  }
}

TEST(ProjectEuler, largest_prime_factor)
{
  std::vector<long long> result;
  GetLargestPrimeFactors(600851475143, result);

  for (int prime : result)
    std::cout << prime << std::endl;
}

// Problem 4 : Largest Palindrome Product
bool IsNumPalindrome(const int _num)
{
  int normal_num = _num;
  int reverse_num = 0;
  while (normal_num != 0)
  {
    reverse_num = (reverse_num * 10) + (normal_num % 10);
    normal_num /= 10;
  }

  return reverse_num == _num;
}

int FindLargestPalindromProduct()
{
  unsigned int winner = 0;
  for (unsigned int i = 999; i >= 100; i--)
  {
    for (unsigned int j = 999; j >= 100; j--)
    {
      const unsigned int num = i * j;
      const bool is_palindrome = IsNumPalindrome(num);
      if (is_palindrome)
      {
        if (winner < num)
          winner = num;
      }
    }
  }
  return winner;
}

TEST(ProjectEuler, largest_palindrom_product)
{
  std::cout << FindLargestPalindromProduct() << std::endl;
}

// Problem 5 : Smallest Multiple
ui SmallestMultiple(const ui _start, const ui _end)
{
  std::vector<ui> prime_factors;
  for (ui i = _start; i < _end; i++)
  {
    if (i == 1)
    {
      prime_factors.push_back(i);
    }
    else
    {
      ui cur_num = i;
      for (ui& prime_num : prime_factors)
      {
        if (cur_num % prime_num == 0)
          cur_num /= prime_num;
      }
      prime_factors.push_back(cur_num);
    }
  }

  ui total = 1;
  for (ui& prime_num : prime_factors)
    total *= prime_num;
  return total;
}

TEST(ProjectEuler, smallest_multiple)
{
  ASSERT_EQ(232792560, SmallestMultiple(1, 20));
}

// Problem 6 : Sum Square Difference
ui SumOfSquaredDifference(const ui _limit)
{
  ui total = 0;
  for (ui i = 1; i <= _limit; i++)
  {
    for (ui j = 1; j <= _limit; j++)
    {
      if (i != j)
        total += (i * j);
    }
  }

  return total;
}

TEST(ProjectEuler, sum_of_squared_difference)
{
  std::cout << SumOfSquaredDifference(100) << std::endl;
}

// Problem 7 : 10001st prime
ui FindNthPrime(const ui _nth)
{
  std::vector<ui> primes = { 2,3,5,7,11,13 };
  ui cur_num = primes.back();
  ui cur_prime_index = 6;

  bool prime_not_found{ true };
  while (true)
  {
    while (prime_not_found)
    {
      cur_num += 2;
      bool cur_num_prime{ true };
      for (ui& prime : primes)
      {
        if (cur_num % prime == 0)
        {
          cur_num_prime = false;
          break;
        }
      }

      if (cur_num_prime)
      {
        prime_not_found = false;
        cur_prime_index++;
      }
    }

    if (cur_prime_index == _nth)
    {
      break;
    }
    else
    {
      primes.push_back(cur_num);
      prime_not_found = true;
    }
  }

  return cur_num;
}

TEST(ProjectEuler, problem_7_10001_prime)
{
  EXPECT_EQ(17, FindNthPrime(7));
  EXPECT_EQ(19, FindNthPrime(8));
  EXPECT_EQ(23, FindNthPrime(9));

  std::cout << FindNthPrime(10001) << std::endl;
}

// Problem 9 : Special Pythagorean Triplet
ui FindSpecialPythagoreanTriplet(const ui _limit)
{
  ui answer = 0;
  for (ui a = 0; a < _limit; a++)
  {
    for (ui b = 0; b < _limit; b++)
    {
      const ui c = _limit - a - b;
      if (a * a + b * b == c * c && a < b && b < c)
      {
        answer = a * b * c;
        break;
      }
    }
  }
  return answer;
}

TEST(ProjectEuler, special_pythagorean_triple)
{
  std::cout << FindSpecialPythagoreanTriplet(1000) << std::endl;
}

// Problem 10 : Summation of Primes
bool IsNumPrime(const ui _num)
{
  ui cur_num = 3;
  bool cur_num_prime = true;
  while (cur_num <= std::sqrt(_num))
  {
    if (_num % cur_num == 0 || _num % 2 == 0)
    {
      cur_num_prime = false;
      break;
    }
    cur_num += 2;
  }
  return cur_num_prime;
}

long long SumOfPrimesBelow(const ui _limit)
{
  long long total = 28;
  ui cur_num = 13;
  while (true)
  {
    if (cur_num > _limit)
      break;

    if (IsNumPrime(cur_num))
    {
      total += cur_num;
    }
    cur_num += 2;
  }

  return total;
}

TEST(ProjectEuler, sum_of_prime_below)
{
  ASSERT_TRUE(IsNumPrime(11));
  ASSERT_FALSE(IsNumPrime(12));
  ASSERT_TRUE(IsNumPrime(13));
  ASSERT_FALSE(IsNumPrime(25));

  EXPECT_EQ(100, SumOfPrimesBelow(25));
  EXPECT_EQ(129, SumOfPrimesBelow(30));
  EXPECT_EQ(277050, SumOfPrimesBelow(2000));
  EXPECT_EQ(1709600813, SumOfPrimesBelow(200000));
  std::cout << SumOfPrimesBelow(2000000) << std::endl;
}

// Problem 11 : Largest product in a grid
void CompareMax(int& _max, const int _a, const int _b, const int _c, const int _d)
{

  const int product = _a * _b * _c * _d;
  if (_max < product)
  {
    _max = product;
  }
}

TEST(ProjectEuler, largest_product_in_a_grid)
{
  Grid grid;
  grid.LoadGrid("Grid.txt");

  int max_product = 0;

  for (ui j = 3; j <= 16; j++)
  {
    for (ui i = 3; i <= 16; i++)
    {
      // Four values to the right
      const int a_r = grid.GetValue(i, j);
      const int b_r = grid.GetValue(i + 1, j);
      const int c_r = grid.GetValue(i + 2, j);
      const int d_r = grid.GetValue(i + 3, j);

      CompareMax(max_product, a_r, b_r, c_r, d_r);

      // Four values right-down diagonal
      const int a_r_d = grid.GetValue(i, j);
      const int b_r_d = grid.GetValue(i + 1, j + 1);
      const int c_r_d = grid.GetValue(i + 2, j + 2);
      const int d_r_d = grid.GetValue(i + 3, j + 3);

      CompareMax(max_product, a_r_d, b_r_d, c_r_d, d_r_d);

      // Four values down
      const int a_d = grid.GetValue(i, j);
      const int b_d = grid.GetValue(i, j + 1);
      const int c_d = grid.GetValue(i, j + 2);
      const int d_d = grid.GetValue(i, j + 3);

      CompareMax(max_product, a_d, b_d, c_d, d_d);

      // Four values left-down diagonal
      const int a_l_d = grid.GetValue(i, j);
      const int b_l_d = grid.GetValue(i - 1, j + 1);
      const int c_l_d = grid.GetValue(i - 2, j + 2);
      const int d_l_d = grid.GetValue(i - 3, j + 3);

      CompareMax(max_product, a_l_d, b_l_d, c_l_d, d_l_d);

      // Four values left
      const int a_l = grid.GetValue(i, j);
      const int b_l = grid.GetValue(i - 1, j);
      const int c_l = grid.GetValue(i - 2, j);
      const int d_l = grid.GetValue(i - 3, j);

      CompareMax(max_product, a_l, b_l, c_l, d_l);

      // Four values left-up diagonal
      const int a_l_u = grid.GetValue(i, j);
      const int b_l_u = grid.GetValue(i - 1, j - 1);
      const int c_l_u = grid.GetValue(i - 2, j - 2);
      const int d_l_u = grid.GetValue(i - 3, j - 3);

      CompareMax(max_product, a_l_u, b_l_u, c_l_u, d_l_u);

      // Four values up
      const int a_u = grid.GetValue(i, j);
      const int b_u = grid.GetValue(i, j - 1);
      const int c_u = grid.GetValue(i, j - 2);
      const int d_u = grid.GetValue(i, j - 3);

      CompareMax(max_product, a_u, b_u, c_u, d_u);
    }
  }

  std::cout << "Max product: " << max_product << std::endl;
}

// Problem 12 : Highly Divisible Triangular Number
ui HighlyDivisibleTriangularNumber(const ui _threshold)
{
  ui total_divisors = 2;
  bool found_num = false;
  ui answer = 0;
  ui starting_num = 3;
  ui cur_index = 2;

  while (!found_num)
  {
    cur_index++;
    starting_num += cur_index;

    for (ui i = 2; i <= std::sqrt(starting_num); i++)
    {
      if (starting_num % i == 0)
        total_divisors += 2;

      if (total_divisors >= _threshold)
      {
        answer = starting_num;
        found_num = true;
        break;
      }
    }

    if (!found_num)
      total_divisors = 2;
  }

  return answer;
}

TEST(ProjectEuler, highly_divisible_triangle_number)
{
  std::cout << HighlyDivisibleTriangularNumber(500) << std::endl;
}

// Problem 13 : Large Sum
long long LargeSum(const std::string& _file)
{
  long long total = 0;
  std::fstream file(_file);
  std::string str;
  while (std::getline(file, str))
  {
    long long cur_num = 0;
    for (ui i = 0; i < 10; i++)
    {
      const long long integer = str[i] - '0';
      cur_num = (cur_num * 10) + (integer);
    }

    total += cur_num;
  }
  return total;
}

TEST(ProjectEuler, large_sum)
{
  std::cout << LargeSum("LargeSum.txt") << std::endl;
}

// Problem 14 : Longest Collatz Sequence
ui CollatzNum(ui _num)
{
  ui count = 0;
  while (_num != 1)
  {
    count++;
    if (_num % 2 == 0)
    {
      _num /= 2;
    }
    else
    {
      _num = (3 * _num) + 1;
    }
  }
  return count;
}

ui FindMaxCollatzNum(const ui _limit) 
{
  ui max_collatz = 0;
  ui num_for_max_collatz = 0;
  for (ui i = 2; i < _limit; i++)
  {
    const ui cur_collatz_num = CollatzNum(i);
    if (max_collatz < cur_collatz_num)
    {
      max_collatz = cur_collatz_num;
      num_for_max_collatz = i;
    }
  }
  return num_for_max_collatz;
}

TEST(ProjectEuler, collatz_num)
{
  std::cout << FindMaxCollatzNum(1000000) << std::endl;
}

ui FindLatticePath(const ui _width)
{
  for (ui j = 0; j <= _width; j++)
  {
    for (ui i = 0; i <= _width; i++)
    {

    }
  }
  return 0;
}

int main(int _argc, char **_argv)
{
  ::testing::InitGoogleTest(&_argc, _argv);
  const int result = RUN_ALL_TESTS();
  std::getchar();
  return result;
} 