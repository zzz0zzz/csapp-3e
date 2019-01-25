 /* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(x&~y) & ~(~x&y));
}



/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1 << 31);
}



/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int is_tmax_or_minus_one = !((x^(x+1))+1);
  int is_minus_one = !(x+1);
  
  return is_tmax_or_minus_one & !is_minus_one;
}



/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask = 0xAA + (0xAA << 8) + (0xAA << 16) + (0xAA << 24);

  return !((x & mask) ^ mask);
}



/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */

int negate(int x) {
  return ~x + 1;
}



/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int is_x_between_0x30_and_0x3F = !((x >> 4) ^ 3);
  int is_x_plus_6_between_0x30_and_0x3F = !(((x+6) >> 4) ^ 3);
  
  return is_x_between_0x30_and_0x3F & is_x_plus_6_between_0x30_and_0x3F;
}



/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int is_x_non_zero = ~(!!x) + 1;

  return (is_x_non_zero & y) | (~is_x_non_zero & z);
}



/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

int isLessOrEqual(int x, int y) {
  int x_equals_tmin = !(x ^ (1 << 31));
  int x_inverse = ~x + 1;
  int sum = y + x_inverse;
  int y_is_non_negative = (y >> 31) + 1;
  int x_inverse_is_non_negative = (x_inverse >> 31) + 1;
  int sum_is_non_negative = (sum >> 31) + 1;
  int overflow_occured = (!(y_is_non_negative ^ x_inverse_is_non_negative)) &
                         (y_is_non_negative ^ sum_is_non_negative);

  return x_equals_tmin |
        (overflow_occured & y_is_non_negative) |
        ((!overflow_occured) & sum_is_non_negative);
}



/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int minus_x = ~x + 1;
  int x_msb = (x >> 31) & 1;
  int minus_x_msb = (minus_x >> 31) & 1;
  int x_is_not_zero = x_msb | minus_x_msb;

  return ~x_is_not_zero & 1;
}



/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int mask = x >> 31;
  int current_shift;
  int result = 1;

  current_shift = (!!((x >> 15) ^ mask)) << 4;
  x >>= current_shift;
  result += current_shift;
    
  current_shift = (!!((x >> 7) ^ mask)) << 3;
  x >>= current_shift;
  result += current_shift;    
    
  current_shift = (!!((x >> 3) ^ mask)) << 2;
  x >>= current_shift;
  result += current_shift;
        
  current_shift = (!!((x >> 1) ^ mask)) << 1;
  x >>= current_shift;
  result += current_shift;    
    
  current_shift = (!!((x >> 0) ^ mask)) << 0;
  x >>= current_shift;
  result += current_shift;    

  return result;
}



/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign = uf & (1 << 31);
  unsigned exponent = (uf >> 23) & 0xff;
  unsigned fraction = uf & 0x7fffff;

  if (exponent == 255) return uf;  // NaN or infinity
  if (exponent > 0) { // normalized
    exponent = exponent + 1;
    if (exponent == 255) fraction = 0;

    return sign + (exponent << 23) + fraction;
  }

  // denormalized - exponent equals zero
  return sign + (exponent << 23) + (fraction << 1);
}



/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = (uf >> 31) & 1;
  int exponent = (uf >> 23) & 0xff;
  int fraction = uf & 0x7fffff;
  int bias = 127;
  int real_exponent = exponent - bias;
  int tmin = 1 << 31;
  int fraction_length = 23;
  int result;
  
  if (real_exponent > 31) return 0x80000000;
  if (real_exponent == 31) {
    if (fraction == 0 && sign == 1)
      return tmin;
    else
      return 0x80000000;
  }
  if (real_exponent < 0) return 0;

  result = fraction + (1 << fraction_length);
  
  if (real_exponent > fraction_length) result <<= (real_exponent - fraction_length);
  if (real_exponent < fraction_length) result >>= (fraction_length - real_exponent);

  if (sign == 1) result *= (-1);
  
  return result;
}



/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int bias = 127;
  int fraction_length = 23;
  unsigned infinity = 0xFF << fraction_length;
  int result;
  
  if (x > 127) {
    result = infinity;
  } else if (x > -127) {
    result = (x + bias) << fraction_length;
  } else if (x == -127) { ///denormalized, only an approximation
    result = (1 << 23) - 1;
  } else if (x > -151) { // denormalized, exact
    result = 1 << (x + 150);
  } else result = 0;

  return result;
}




/*
 *   Some more functions
 */



/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}



/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */

int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xff;
}



/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */

int logicalShift(int x, int n) {
  int n_equals_zero = ~(!n + ~0);
  int y = ((x >> 1) & ~(1 << 31)) >> (n + ~0);

  return (n_equals_zero & x) | (~n_equals_zero & y);
}



/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */

int bitCount(int x) {
  int mask = 1 + (1 << 8) + (1 << 16) + (1 << 24);
  int sums = ((x >> 0) & mask) +
             ((x >> 1) & mask) +
             ((x >> 2) & mask) +
             ((x >> 3) & mask) +
             ((x >> 4) & mask) +
             ((x >> 5) & mask) +
             ((x >> 6) & mask) +
             ((x >> 7) & mask);

  return ((sums >> 0)  & 0xff) +
         ((sums >> 8)  & 0xff) +
         ((sums >> 16) & 0xff) +
         ((sums >> 24) & 0xff);
}



/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int minus_1 = ~0;
    int n_equals_32 = !(n ^ 32);
    int x_equals_zero_or_minus_one;

    x = x >> (n + minus_1);
    x_equals_zero_or_minus_one = !((x + 1)^(!x));

    return n_equals_32 | x_equals_zero_or_minus_one;
}



/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int divpwr2(int x, int n) {
  int is_x_negative = x >> 31;

  x = x + (is_x_negative & ((1 << n) + ~0));
    
  return x >> n;
}



/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */

int isPositive(int x) {
  int x_is_negative = (x >> 31) & 1;
  int x_does_not_equal_zero = !!x;

  return (!x_is_negative) & x_does_not_equal_zero;
}



/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int result = 0;
    int current_shift;

    current_shift = (!!(x >> 16)) << 4;
    x >>= current_shift;
    result += current_shift;
    
    current_shift = (!!(x >> 8)) << 3;
    x >>= current_shift;
    result += current_shift;    
    
    current_shift = (!!(x >> 4)) << 2;
    x >>= current_shift;
    result += current_shift;
        
    current_shift = (!!(x >> 2)) << 1;
    x >>= current_shift;
    result += current_shift;    
    
    current_shift = (!!(x >> 1)) << 0;
    x >>= current_shift;
    result += current_shift;    

    return result;
}



/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned exponent = (uf >> 23) & 0xff;
    unsigned fraction = uf & 0x7fffff; 
    unsigned uf_is_nan = (exponent == 0xff && fraction != 0);

    if (uf_is_nan) return uf;
    return uf ^ (1 << 31);
}



/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

unsigned float_i2f(int x) {
  unsigned sign = x & (1 << 31);
  unsigned i;
  unsigned exponent;
  unsigned exponent_bias = 127;
  unsigned fraction;
  unsigned remainder;

  if (!x) return 0;

  if (sign) x = ~x + 1;
  i = 0;
  while (!((x << i) & (1 << 31))) ++i;
  exponent = 31 - i;
  x = x << i;
  fraction = (x >> 8) & 0x7fffff;
  remainder = x & 0xff;

  if (remainder > 128 || (remainder == 128 && fraction % 2))
    fraction = fraction + 1;

  return sign + ((exponent + exponent_bias) << 23) + fraction;
}
