|| Individual Assignment 2 - 60-100

|| Completed by Zach Shaver - 104425444



p1 = [(1,2),(2,3)]

p2 = p1 -- [(1,2)]

p3 = map (^3)  

p4 = foldr (+) 0

p5 n m = n, if n > 0;
      
       = m, otherwise

p6 list1 list2 = list1, if [x | x <- list1 ] > [x | x <- list2 ]
	       
	       = list2, otherwise 

p7 0 = True

p7 1 = False

p7 n = True, if p7 (n-3)
     
     = False, otherwise

p8 [] n     = False 

p8 (x:xs) n = True, if x = n
	    
	    = p8 xs n, otherwise

p9 = p4 . p3

p10 list4 list5 = [(x, y) | x <- list4; y <- list5; x > y]
