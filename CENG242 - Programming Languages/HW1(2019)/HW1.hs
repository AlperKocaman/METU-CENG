module HW1 (
    form,
    constGrid,
    flatten,
    access,
    slice,
    vcat,
    hcat,
    without,
    matches2d
) where

-- do not modify the module declaration above!
-- this will ensure that you cannot load (compile)
-- the module without implementing all of the functions.

-- If you have functions you do not want to implement,
-- leave them as undefined or make them have another
-- default value. If you fully remove any of their definitions,
-- that will be a compilation error during evaluation,
-- and you will be eligible for (yay!) a 5 point deduction
-- (that's bad for your grade). Runtime errors in your code 
-- (rather than compilation errors) are acceptable and will simply
-- result in you getting zero from the specific test case causing
-- an error.

-------------------------
-- Fellowship of the Grid (25, 5, 5, 5 points)
form :: [a] -> (Int, Int) -> [[a]] 
form a (0, col) = []
form (x:xs) (row, col) = [formHelper (x:xs) (0, col)] ++ form (drop (col-1) xs) (row-1, col)

formHelper :: [a] -> (Int, Int) -> [a]
formHelper [] (row, col) = []
formHelper (x:xs) (0, 0) = []
formHelper (x:xs) (0, col) = [x] ++ formHelper xs (0, col-1)

constGrid :: a -> (Int, Int) -> [[a]]
constGrid a (0, col) = []
constGrid a (row, col) = [constGridHelper a (0, col)] ++ constGrid a (row-1, col)  

constGridHelper :: a -> (Int, Int) -> [a]
constGridHelper a (0,0) = []
constGridHelper a (0, col) = [a] ++ constGridHelper a (0, col-1)

flatten :: [[a]] -> [a]
flatten [] = []
flatten (x:xs) = x ++ flatten xs  

access :: [[a]] -> (Int, Int) -> a
access a (row, col) = ((a !! row) !! col)
----------------------------
-- The Two Signatures (10, 5, 5, 10 points)
slice :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
slice  a (i1, i2) (j1, j2) = if i1+1 <= i2 
                                then [sliceHelper (a!!i1) (0, 0) (j1, j2)] ++ slice a (i1+1, i2) (j1, j2)
                                else [] 

sliceHelper :: [a] -> (Int, Int) -> (Int, Int) -> [a]
sliceHelper a (0, 0) (j1, j2) = if j1+1 <= j2 
                                    then [a!!j1] ++ sliceHelper a (0, 0) (j1+1, j2)
                                    else []    

vcat :: [[a]] -> [[a]] -> [[a]]
vcat a b = a ++ b

hcat :: [[a]] -> [[a]] -> [[a]]
hcat [] [] = []
hcat (x1:xs1) [] = [x1] ++ hcat [] xs1
hcat [] (x2:xs2) = [x2] ++ hcat [] xs2 
hcat (x1:xs1) (x2:xs2) = [x1 ++ x2] ++ hcat xs1 xs2

without :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
without  a (i1, i2) (j1, j2) = withoutRow a (i1,i2) (j1,j2) (0, 0)  

withoutRow :: [[a]] -> (Int, Int) -> (Int, Int) -> (Int, Int) -> [[a]]
withoutRow a (i1, i2) (j1, j2) (row, col)
    | row >= length a = []
    | row >= i2 = [(withoutColumn (a !! row) (j1, j2) (0, 0))] ++ withoutRow a (i1, i2) (j1, j2) (row+1, col)
    | row >= i1 = withoutRow a (i1, i2) (j1, j2) (row+1, col)
    | row < i1 = [(withoutColumn (a !! row) (j1, j2) (0, 0))] ++ withoutRow a (i1, i2) (j1, j2) (row+1, col)    

withoutColumn :: [a] -> (Int, Int) -> (Int, Int) -> [a]
withoutColumn a (j1, j2) (row, col)
    | col >= length a = []
    | col >= j2 = [a !! col] ++ withoutColumn a (j1, j2) (row, col+1)
    | col >= j1 = withoutColumn a (j1, j2) (row, col+1)
    | col < j1 = [a !! col] ++ withoutColumn a (j1, j2) (row, col+1)

----------------------------
-- Return of the Non-trivial (30 points, 15 subject to runtime constraints)
matches2d :: Eq a => [[a]] -> [[a]] -> [(Int, Int)]
matches2d (x1:xs1) (x2:xs2) = if length (x1:xs1) < length (x2:xs2)
                                then []
                                else matches2dHelper (x1:xs1) (x2:xs2) (-1)

matches2dHelper :: Eq a => [[a]] -> [[a]] -> Int ->[(Int, Int)]
matches2dHelper (x1:xs1) [] row = []
matches2dHelper [] (x2:xs2) row = []
matches2dHelper (x1:xs1) (x2:xs2) row = matches2dHelper2 xs1 xs2 (matches1d x1 x2 0) (row+1)
                                        ++ matches2dHelper xs1 (x2:xs2) (row+1)

matches2dHelper2 :: Eq a => [[a]] -> [[a]] -> [Int] -> Int-> [(Int, Int)]
matches2dHelper2 [] [] (x3:xs3) row = [(row,x3)] ++ matches2dHelper4 xs3 row
matches2dHelper2 list1 list2 [] row = []
matches2dHelper2 [] list2 list3 row = []
matches2dHelper2 list1 [] (x3:xs3) row = [(row,x3)] ++ matches2dHelper2 list1 [] xs3 row
matches2dHelper2 (x1:xs1) (x2:xs2) (x3:xs3) row =  if (matches2dHelper3 (x1:xs1) (x2:xs2) x3)
                                                        then [(row,x3)] ++ (matches2dHelper2 (x1:xs1) (x2:xs2) xs3 row)
                                                        else matches2dHelper2 (x1:xs1) (x2:xs2) xs3 row

matches2dHelper3 :: Eq a => [[a]] -> [[a]] -> Int -> Bool
matches2dHelper3 [] [] x3 = True
matches2dHelper3 (x1:xs1) [] x3 = True
matches2dHelper3 [] (x2:xs2) x3 = False
matches2dHelper3 (x1:xs1) (x2:xs2) x3 = if (checkEqual x1 x2 x3)  
                                            then matches2dHelper3 xs1 xs2 x3
                                            else False

matches2dHelper4 :: [Int] -> Int-> [(Int, Int)]
matches2dHelper4 [] row = []
matches2dHelper4 (x3:xs3) row = [(row,x3)] ++ matches2dHelper4 xs3 row

matches1d :: Eq a => [a] -> [a] -> Int -> [Int]
matches1d [] [] col = [col]
matches1d (x1:xs1) [] col = [col]
matches1d [] (x2:xs2) col = []
matches1d (x1:xs1) (x2:xs2) col
    | x1 == x2 = matches1dHelper xs1 xs2 col ++ matches1d xs1 (x2:xs2) (col+1)
    | x1 /= x2 = matches1d xs1 (x2:xs2) (col+1)

matches1dHelper :: Eq a => [a] -> [a] -> Int -> [Int] 
matches1dHelper [] [] col = [col]
matches1dHelper (x1:xs1) [] col = [col]
matches1dHelper [] (x2:xs2) col = []
matches1dHelper (x1:xs1) (x2:xs2) col
    | x1 == x2 = matches1dHelper xs1 xs2 col
    | otherwise = [] 

checkEqual :: Eq a => [a] -> [a] -> Int -> Bool
checkEqual (x1:xs1) [] num = True
checkEqual [] [] num = True
checkEqual [] (x2:xs2) num = False
checkEqual (x1:xs1) (x2:xs2) 0 
    | x1 == x2 = checkEqual xs1 xs2 0
    | x1 /= x2 = False
checkEqual (x1:xs1) (x2:xs2) num = checkEqual xs1 (x2:xs2) (num-1)
----------------------------
-- What is undefined? Just a value that will cause an error
-- when evaluated, from the GHC implementation:
-- undefined = error "Prelude.undefined"
-- But it allows your module to be compiled
-- since the function definitions will exist.
