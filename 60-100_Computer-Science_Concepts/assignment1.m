|| Program 1 - Returns age
p1 = "24 years old"
|| Program 2 - Returns name
p2 = "Zach Shaver"
|| Program 3 - Doubles one number
p3 n = n * 2
|| Program 4 - Finds biggest of two numbers
p4 n m = n, if n > m
p4 n m = m, if m >= n   
|| Program 5 - Takes a list of numbers, returns them doubled
p5 list_doubled = map (*2) list_doubled
|| Program 6 - Takes a list, returns first number
p6 first_list = first_list!0
|| Program 7 - Takes a list, returns product of all numbers in list
p7 product_list = foldr (*) 1 product_list
|| Program 8 - Takes a number, returns its factorial
p8 0 = 1
p8 1 = 1
p8 n = p8 (n-1) * n
|| Program 9 - Takes two lists of numbers, returns numbers that are common to both lists
p9 list1 list2 = list1 -- (list1 -- list2)
|| Program 10 - Takes a list, returns it in reverse order
p10 revlist = foldr postfix [] revlist
|| Program 11 - Takes a number, returns True if the number is even, False if odd
p11 0 = True
p11 1 = False
p11 n = p11 (n-1)
|| Program 12 - Takes a list of pairs of numbers and returns the sum of all the numbers that appear first in the pair
p12 n m o = map (+)!0 
