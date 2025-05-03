#ifndef BIG_UINT_MULTIPLICATION_HELPER
#define BIG_UINT_MULTIPLICATION_HELPER

// TODO: stop using this. I think I can do the multiplications better
void uint64_multiplication_result_high_and_low(const unsigned long long a, const unsigned long long b, unsigned long long *high, unsigned long long *low);
void uint64_sum_with_overflow_flag(const unsigned long long a, const unsigned long long b, unsigned long long *result, unsigned long long *overflow_flag);
void add_component_to_limb(unsigned long long a_limb, unsigned long long b_limb, unsigned long long *carry_high, unsigned long long *carry_low, unsigned long long *result_limb);

#endif