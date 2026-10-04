// class Solution {
// public:
//     double myPow(double x, int n) {
//         if (x == 0.) 
//             return 0.;
//         if (n == INT_MIN)
//             return myPow(x, n+1)/x;
//         if (n < 0)
//             return myPow(1./x, -n);
//         // n >= 0
//         double result=1.;
//         double xPow2 = x;
//         while (n > 0) {
//             if (n%2 == 1) {
//                 result *= xPow2;
//             }
//             n /= 2;
//             xPow2 *= xPow2;
//         }
//         return result;
//     }
// };
// Above initial solution passed 306 out of 309 tests. It failed on 307:
// x=-0.9999999968539456 n=-1669585506 output=191.06373 expected=191.06370
// This is result of numerical accumulated error. Frankly I am not sure which result is better,
// expected or output.

class Solution {
public:
    double myPow(double x, int n) {
        long long N=n;
        if (x == 0.) 
            return 0.;
        bool negative = (N<0);
        if (N<0) {N *= -1;}
        double result=1.;
        while (N > 0) {
            if (N%2 == 1) {result *= x;}
            N /= 2;
            x *= x;
        }
        if (negative) {result = 1./result;}
        return result;
    }
};