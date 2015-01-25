# numericV1.0
Numerical Analysis Project

I learned numerical analysis algorithms in 2014 spring. The class used matlab to implement those algorithms. I came up the idea to make a numerical analysis software package in C++ as a project to practice.

v1.0 is capable of 
1. approximating function via polynominal interpolation 
2. solving nonlinear equation via iteration methods 
3. solving matrix inverse and linear equations

Example:

1. Lagrange and newton methods to interpolate y = x - sin(x)

LagrangeInterpolation
f(x) = 

-0.158529 *  ( x + 0.8 )  ( x + 0.4 )  ( x - 0.2 ) 
------------------------------------------------------------ + 
 ( -1 + 0.8 )  ( -1 + 0.4 )  ( -1 - 0.2 ) 

-0.0826439 *  ( x + 1 )  ( x + 0.4 )  ( x - 0.2 ) 
------------------------------------------------------------ + 
 ( -0.8 + 1 )  ( -0.8 + 0.4 )  ( -0.8 - 0.2 ) 

-0.0105817 *  ( x + 1 )  ( x + 0.8 )  ( x - 0.2 ) 
------------------------------------------------------------ + 
 ( -0.4 + 1 )  ( -0.4 + 0.8 )  ( -0.4 - 0.2 ) 

0.00133067 *  ( x + 1 )  ( x + 0.8 )  ( x + 0.4 ) 
------------------------------------------------------------ + 
 ( 0.2 + 1 )  ( 0.2 + 0.8 )  ( 0.2 + 0.4 ) 


NewtonInterpolation
f(x) = 

-0.158529 *  + 

0.379426 *  ( x + 1 )  + 

-0.332117 *  ( x + 1 )  ( x + 0.8 )  + 

0.143179 *  ( x + 1 )  ( x + 0.8 )  ( x + 0.4 ) 

2. Secant Method to solve y = x^3 - x - 1  

Secant Method solving y = x^3 - x - 1
///////////////////////
Ignorance : 0.0001
Precision : 0.0001
Interval  : [ -10 ,  11 ] (Interval only means where it begins iterating)
Segment   : 10
Iteration : 100
[  -10, -7.9 ]
x = 1.32473
[ -7.9, -5.8 ]
x = N/A
[ -5.8, -3.7 ]
x = N/A
[ -3.7, -1.6 ]
x = N/A
[ -1.6,  0.5 ]
x = N/A
[  0.5,  2.6 ]
x = N/A
[  2.6,  4.7 ]
x = 1.32472
[  4.7,  6.8 ]
x = 1.32472
[  6.8,  8.9 ]
x = 1.32472
[  8.9,   11 ]
x = N/A

3. Gauss elimination method to factorize LU  Matrix 

vandermonde matrix with vec5(3 4 5 6 7)
        1           3           9          27          81   
        1           4          16          64         256   
        1           5          25         125         625   
        1           6          36         216        1296   
        1           7          49         343        2401   

van's lower triangle matrix
        1           0           0           0           0   
        1           1           0           0           0   
        1         0.5           1           0           0   
        1        0.75          -2           1           0   
        1        0.25   -0.428571    0.372913           1   

van's upper triangle matrix
        1           3           9          27          81   
        0           4          40         316        2320   
        0           0           7          31          55   
        0           0           0         -77       -1086   
        0           0           0           0     23.5547   

4. Gauss-Jordan method's to solve matrix inverse 

m =

        1           3           9          27          81   
        1           7          49         343        2401   
        1           6          36         216        1296   
        1           5          25         125         625   
        1           4          16          64         256   

inv(m) = 

       35          15         -70         126        -105   
 -26.5833      -14.25     64.8333      -112.5        88.5   
  7.45833     4.95833    -21.8333       36.25    -26.8333   
-0.916667       -0.75     3.16667          -5         3.5   
0.0416667   0.0416667   -0.166667        0.25   -0.166667   

m * inv(m) =

        1           0           0           0           0   
        0           1           0           0           0   
        0           0           1           0           0   
        0           0           0           1           0   
        0           0           0           0           1   


