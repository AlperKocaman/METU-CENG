module Hw2 where

data ASTResult = ASTError String | ASTJust (String, String, Int) deriving (Show, Read)
data ASTDatum = ASTSimpleDatum String | ASTLetDatum String deriving (Show, Read)
data AST = EmptyAST | ASTNode ASTDatum AST AST deriving (Show, Read)

isNumber :: String -> Bool
eagerEvaluation :: AST -> ASTResult
normalEvaluation :: AST -> ASTResult
-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT isNumber, eagerEvaluation and normalEvaluation FUNCTIONS ACCORDING TO GIVEN SIGNATURES -- 

isNumber "" = False
isNumber str@(x:xs)
    | x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '-' = isNumber2 xs 
    | x == '5' || x == '6' || x == '7' || x == '8' || x == '9'             = isNumber2 xs 
    | otherwise = False

isNumber2 :: String -> Bool 
isNumber2 "" = True
isNumber2 str@(x:xs)
    | x == '0' || x == '1' || x == '2' || x == '3' || x == '4' = isNumber2 xs 
    | x == '5' || x == '6' || x == '7' || x == '8' || x == '9' = isNumber2 xs
    | otherwise = False
-----------------------------------------------------------------------------------------------------------

eagerEvaluation ast = if error1 (replace1 ast) then ASTError (print_error1 (replace1 ast)) else ASTJust ((eval (replace ast)), (eval2(replace ast)) , (counter (replace ast)))

error1 :: AST -> Bool
error1 (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum x1) EmptyAST EmptyAST) EmptyAST )
    | (isNumber x1) == False = True
    | otherwise = False

error1 (ASTNode (ASTSimpleDatum "str") (ASTNode (ASTSimpleDatum x1) EmptyAST EmptyAST) EmptyAST ) = False

error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x1 == "str" || x2 == "str" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x2 == "str" = True
    | eval2(right1) == "str" = True
    | otherwise = (error1( ASTNode (ASTLetDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | x1 == "str" = True
    | eval2(right2) == "str" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTLetDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x1 == "str" || x2 == "str" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x2 == "str" = True
    | eval2(right1) == "str" = True
    | otherwise = (error1( ASTNode (ASTLetDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | x1 == "str" = True
    | eval2(right2) == "str" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTLetDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "negate") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) EmptyAST )
    | x1 == "str" = True
    | otherwise = error1( ASTNode (ASTSimpleDatum x1) left1 right1 )

error1 (ASTNode (ASTSimpleDatum "negate") ( ASTNode (ASTLetDatum x1) left1 right1 ) EmptyAST ) 
    | eval2(right1) == "str" = True
    | otherwise =  error1( ASTNode (ASTLetDatum x1) left1 right1 ) 

error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x1 == "num" || x2 == "num" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | x2 == "num" = True
    | eval2(right1) == "num" = True
    | otherwise = (error1( ASTNode (ASTLetDatum x1) left1 right1 ) || error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | x1 == "num" = True
    | eval2(right2) == "num" = True
    | otherwise = (error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) || error1( ASTNode (ASTLetDatum x2) left2 right2 ) )

error1 (ASTNode (ASTSimpleDatum "len") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) EmptyAST )
    | x1 == "num" = True
    | otherwise = error1( ASTNode (ASTSimpleDatum x1) left1 right1 )

error1 (ASTNode (ASTSimpleDatum "len") ( ASTNode (ASTLetDatum x1) left1 right1 ) EmptyAST )
    | eval2(right1) == "num" = True
    | otherwise =  error1( ASTNode (ASTLetDatum x1) left1 right1 )

error1 (ASTNode (ASTLetDatum x) left1 right1) = error1 right1

error1 (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) = False
-----------------------------------------------------------------------------------------------------------------------------------

print_error1 :: AST -> String
print_error1 (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum x1) EmptyAST EmptyAST) EmptyAST )
    | (isNumber x1) == False = "the value " ++ "'"++ x1 ++ "'"++ " is not a number!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "str") (ASTNode (ASTSimpleDatum x1) EmptyAST EmptyAST) EmptyAST ) = ""

print_error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) ) 
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | x1 == "str" && x2 == "str" = "plus operation is not defined between str and str!"
    | x1 == "str"                = "plus operation is not defined between str and num!" 
    | x2 == "str"                = "plus operation is not defined between num and str!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) ) 
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | x1 == "str" && x2 == "str" = "times operation is not defined between str and str!"
    | x1 == "str"                = "times operation is not defined between str and num!" 
    | x2 == "str"                = "times operation is not defined between num and str!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "negate") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) EmptyAST ) 
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | x1 == "str"                = "negate operation is not defined on str!" 
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) ) 
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | x1 == "num" && x2 == "num" = "cat operation is not defined between num and num!"
    | x1 == "num"                = "cat operation is not defined between num and str!" 
    | x2 == "num"                = "cat operation is not defined between str and num!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "len") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) EmptyAST ) 
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | x1 == "num"                = "len operation is not defined on num!" 
    | otherwise = ""

print_error1 (ASTNode (ASTLetDatum x) left1 right1) 
    | print_error1 right1 /= "" = print_error1 right1
    | otherwise = ""

------------

print_error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | ((x2 == "str") && ((eval2(right1)) == "str" )) = "plus operation is not defined between str and str!"
    | x2 == "str" = "plus operation is not defined between num and str!"
    | ((eval2(right1)) == "str" ) = "plus operation is not defined between str and num!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "plus") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTLetDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTLetDatum x2) left2 right2 )
    | ((x1 == "str") && ((eval2(right2)) == "str" )) = "plus operation is not defined between str and str!"
    | x1 == "str" = "plus operation is not defined between str and num!"
    | ((eval2(right2)) == "str" ) = "plus operation is not defined between num and str!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | ((x2 == "str") && ((eval2(right1)) == "str" )) = "times operation is not defined between str and str!"
    | x2 == "str" = "times operation is not defined between num and str!"
    | ((eval2(right1)) == "str" ) = "times operation is not defined between str and num!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "times") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTLetDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTLetDatum x2) left2 right2 )
    | ((x1 == "str") && ((eval2(right2)) == "str" )) = "times operation is not defined between str and str!"
    | x1 == "str" = "times operation is not defined between str and num!"
    | ((eval2(right2)) == "str" ) = "times operation is not defined between num and str!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "negate") ( ASTNode (ASTLetDatum x1) left1 right1 ) EmptyAST )
    | print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) 
    | ((eval2(right1)) == "str" )                = "len operation is not defined on str!" 
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTLetDatum x1) left1 right1 ) ( ASTNode (ASTSimpleDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x2) left2 right2 )
    | ((x2 == "num") && ((eval2(right1)) == "num" )) = "cat operation is not defined between num and num!"
    | x2 == "num" = "cat operation is not defined between str and num!"
    | ((eval2(right1)) == "num" ) = "cat operation is not defined between num and str!" 
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "cat") ( ASTNode (ASTSimpleDatum x1) left1 right1 ) ( ASTNode (ASTLetDatum x2) left2 right2 ) )
    | print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTSimpleDatum x1) left1 right1 ) 
    | print_error1( ASTNode (ASTLetDatum x2) left2 right2 ) /= "" = print_error1( ASTNode (ASTLetDatum x2) left2 right2 )
    | ((x1 == "num") && ((eval2(right2)) == "num" )) = "cat operation is not defined between num and num!"
    | x1 == "num" = "cat operation is not defined between num and str!"
    | ((eval2(right2)) == "num" ) = "cat operation is not defined between str and num!"
    | otherwise = ""

print_error1 (ASTNode (ASTSimpleDatum "len") ( ASTNode (ASTLetDatum x1) left1 right1 ) EmptyAST )
    | print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) /= "" = print_error1( ASTNode (ASTLetDatum x1) left1 right1 ) 
    | ((eval2(right1)) == "num" )                = "len operation is not defined on num!" 
    | otherwise = ""


-------------    

print_error1 (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) = ""

-------------------------------------------------------------------------------------------------

replace :: AST -> AST
replace (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) = (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST)
replace (ASTNode (ASTSimpleDatum x) first EmptyAST) = (ASTNode (ASTSimpleDatum x) (replace first) EmptyAST)
replace (ASTNode (ASTSimpleDatum x) first second) = (ASTNode (ASTSimpleDatum x) (replace first) (replace second) )
replace (ASTNode (ASTLetDatum    x) first second) = (ASTNode (ASTLetDatum    x) (replace first) (replace2((eval (replace first)), second, x)) )

replace2:: (String, AST, String) -> AST
replace2 (result , (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) , var )
    | ((var == x) && (isNumber result == True)) = (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum result) EmptyAST EmptyAST) EmptyAST)
    | var == x                                  = (ASTNode (ASTSimpleDatum "str") (ASTNode (ASTSimpleDatum result) EmptyAST EmptyAST) EmptyAST)
    | otherwise                                 = (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST)

replace2 (result , (ASTNode (ASTSimpleDatum x) first EmptyAST) , var) = (ASTNode (ASTSimpleDatum x) (replace2 (result, first, var)) EmptyAST)    
replace2 (result , (ASTNode (ASTSimpleDatum x) first second) , var) = (ASTNode (ASTSimpleDatum x) (replace2 (result, first, var)) (replace2 (result, second, var)))
replace2 (result , (ASTNode (ASTLetDatum x) first second) , var)
    | x == var = (ASTNode (ASTLetDatum x) (replace first) (replace2 ((eval (replace(first))), second, x)) )
    | x /= var = (ASTNode (ASTLetDatum x) (replace2(result, first, var )) (replace2 ( (eval( replace2 ( result, first , var ) ) ) , ( replace2 ( result, second , var ) ) , x )) )

eval :: AST -> String
eval EmptyAST = ""
eval (ASTNode (ASTSimpleDatum x) first second)
    | x == "plus"    = show((read (eval(first))::Integer) + (read (eval(second))::Integer)) 
    | x == "times"   = show((read (eval(first))::Integer) * (read (eval(second))::Integer)) 
    | x == "negate"  = show((read (eval(first))::Integer) * (-1))
    | x == "cat"     = eval(first) ++ eval(second)
    | x == "len"     = show(length(eval(first)))
    | x == "num"     = eval(first)
    | x == "str"     = eval(first)
    | otherwise      = x 

eval (ASTNode (ASTLetDatum x) first second) = eval(second) 

counter :: AST -> Int
counter EmptyAST = 0
counter (ASTNode (ASTSimpleDatum x) first second)
    | x == "plus"    = counter(first) + counter(second) + 1 
    | x == "times"   = counter(first) + counter(second) + 1
    | x == "negate"  = counter(first) + 1
    | x == "cat"     = counter(first) + counter(second) + 1
    | x == "len"     = counter(first) + 1
    | x == "num"     = 0
    | x == "str"     = 0
    | otherwise      = 0 

counter (ASTNode (ASTLetDatum x) first second) = counter(first) + counter(second)

normalEvaluation ast = if error1 (replace1 ast) then ASTError (print_error1 (replace1 ast)) else ASTJust ((eval (replace1 ast)), (eval2(replace1 ast)) , (counter1 (replace1 ast)))

replace1 :: AST -> AST
replace1 (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) = (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST)
replace1 (ASTNode (ASTSimpleDatum x) first EmptyAST) = (ASTNode (ASTSimpleDatum x) (replace1 first) EmptyAST)
replace1 (ASTNode (ASTSimpleDatum x) first second) = (ASTNode (ASTSimpleDatum x) (replace1 first) (replace1 second) )
replace1 (ASTNode (ASTLetDatum    x) first second) = (ASTNode (ASTLetDatum    x) (replace1 first) (replace3((replace1 first), second, x)) )

replace3:: (AST, AST, String) -> AST
replace3 (left , (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST ), var)
    | var == x = left
    | otherwise = (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST )

replace3 (left , (ASTNode (ASTSimpleDatum x) first EmptyAST ), var) = (ASTNode (ASTSimpleDatum x) (replace3 (left, first, var)) EmptyAST)
replace3 (left , (ASTNode (ASTSimpleDatum x) first second ), var) =   (ASTNode (ASTSimpleDatum x) (replace3 (left, first, var)) (replace3 (left, second, var)))
replace3 (left , (ASTNode (ASTLetDatum x) first second) , var)
    | x == var = (ASTNode (ASTLetDatum x) (replace1 first) (replace3 ((replace1(first)), second, x)) )
    | x /= var = (ASTNode (ASTLetDatum x) (replace3(left, first, var )) (replace3 ( ( replace3 ( left, first , var ) ) , ( replace3 ( left, second , var ) ) , x )) )    

counter1 :: AST -> Int
counter1 EmptyAST = 0
counter1 (ASTNode (ASTSimpleDatum x) first second)
    | x == "plus"    = counter1(first) + counter1(second) + 1 
    | x == "times"   = counter1(first) + counter1(second) + 1
    | x == "negate"  = counter1(first) + 1
    | x == "cat"     = counter1(first) + counter1(second) + 1
    | x == "len"     = counter1(first) + 1
    | x == "num"     = 0
    | x == "str"     = 0
    | otherwise      = 0 

counter1 (ASTNode (ASTLetDatum x) first second) = counter1(second)

eval2 :: AST -> String
eval2 EmptyAST = ""
eval2 (ASTNode (ASTSimpleDatum x)  first second)
    | x == "plus"    = "num" 
    | x == "times"   = "num" 
    | x == "negate"  = "num" 
    | x == "cat"     = "str"
    | x == "len"     = "num" 
    | x == "num"     = "num" 
    | x == "str"     = "str"  
    | otherwise = if isNumber x then "num" else "str"

eval2 (ASTNode (ASTLetDatum x) first second) = eval2(second)

