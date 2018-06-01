#include <iostream>
#include <gtest/gtest.h>

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

int main(int _argc, char **_argv)
{
  ::testing::InitGoogleTest(&_argc, _argv);
  const int result = RUN_ALL_TESTS();
  std::getchar();
  return result;
}