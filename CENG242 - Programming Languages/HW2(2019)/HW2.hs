module HW2 (
    parse, -- reexport for easy terminal use
    foldAndPropagateConstants,
    assignCommonSubexprs,
    reducePoly
) where

import Expression
import Parser

-- Do not change the module definition and imports above! Feel free
-- to modify the parser, but please remember that it is just a helper
-- module and is not related to your grade. You should only submit
-- this file. Feel free to import other modules, especially Data.List!

------------------------------Fold and Propagate Constants--------------------------------------------------------------------------------------
foldAndPropagateConstants :: [(String, ExprV)] -> [(String, ExprV)]
foldAndPropagateConstants [] = []
foldAndPropagateConstants lst = foldAndPropagateConstantsCaller lst lst

foldAndPropagateConstantsCaller :: [(String, ExprV)] -> [(String, ExprV)] -> [(String, ExprV)]
foldAndPropagateConstantsCaller [] lst = []
foldAndPropagateConstantsCaller (x:xs) lst = foldAndPropagateConstantsHelper (replacePreviousVariables x lst) 
                                ++ (foldAndPropagateConstantsCaller xs (lst ++ foldAndPropagateConstantsHelper (replacePreviousVariables x lst)))

replacePreviousVariables :: (String, ExprV) -> [(String, ExprV)] -> (String, ExprV)
replacePreviousVariables (str, exp) lst = (str, replacePreviousVariablesHelper exp lst)

replacePreviousVariablesHelper :: ExprV -> [(String, ExprV)] -> ExprV
replacePreviousVariablesHelper (Leaf (Constant a)) lst = (Leaf (Constant a))
replacePreviousVariablesHelper (Leaf (Variable a)) lst = checkForPreviousVariables a lst
replacePreviousVariablesHelper (UnaryOperation Minus left) lst 
                    = (UnaryOperation Minus (replacePreviousVariablesHelper left lst))
replacePreviousVariablesHelper (BinaryOperation operation left right) lst 
                    = (BinaryOperation operation (replacePreviousVariablesHelper left lst) 
                        (replacePreviousVariablesHelper right lst))

checkForPreviousVariables :: String -> [(String, ExprV)] -> ExprV
checkForPreviousVariables var1 [] = (Leaf (Variable var1))
checkForPreviousVariables var1 ((var2,expr):xs) 
                    = if((var1 == var2) && (isConstantLeaf(expressionCalculator expr 1)))
                    then (expressionCalculator expr 1)
                    else checkForPreviousVariables var1 xs 

isConstantLeaf :: ExprV -> Bool
isConstantLeaf (Leaf (Constant a)) = True
isConstantLeaf otherwise = False

foldAndPropagateConstantsHelper :: (String, ExprV) -> [(String, ExprV)]
foldAndPropagateConstantsHelper (str, expr) = [(str, expressionCalculator expr 1)]

expressionCalculator :: ExprV -> Int -> ExprV
expressionCalculator (Leaf value) num = (Leaf value)
expressionCalculator (UnaryOperation Minus (Leaf (Constant a))) num = (Leaf (Constant (-1*a)))
expressionCalculator (UnaryOperation Minus expr) num  
    | num == 0 = UnaryOperation Minus (expressionCalculator expr num) -- delete expression calc 
    | otherwise = expressionCalculator(UnaryOperation Minus (expressionCalculator expr num)) (num-1)
expressionCalculator (BinaryOperation Plus (Leaf (Constant a)) (Leaf (Constant b))) num
                     = (Leaf (Constant (a+b)))
expressionCalculator (BinaryOperation Times (Leaf (Constant a)) (Leaf (Constant b))) num
                     = (Leaf (Constant (a*b)))
expressionCalculator (BinaryOperation operation left right) num 
    | num == 0 = (BinaryOperation operation left right)
    | otherwise = expressionCalculator(BinaryOperation operation 
        (expressionCalculator(left) (num-1) ) (expressionCalculator(right) (num-1))) (num-1)

------------------------------------Assign Common Subexpressions------------------------------------------------------------------------
assignCommonSubexprs :: ExprV -> ([(String, ExprV)], ExprV)
assignCommonSubexprs expr = ( (answerHandler (changeCommonsCaller3 expr) 0), returnLastElement (changeCommonsCaller3 expr))

answerHandler :: [ExprV] -> Int -> [(String, ExprV)]
answerHandler [] num = []
answerHandler (x:[]) num = []
answerHandler (x:xs) num = [("$" ++ show num, x)] ++ answerHandler xs (num+1)

returnLastElement :: [ExprV] -> ExprV
returnLastElement (x:[]) = x 
returnLastElement (x:xs) = returnLastElement xs 

changeCommonsCaller3 :: ExprV -> [ExprV]
changeCommonsCaller3 expr = changeCommonsCaller2 [expr] 
                            (length (putDuplicatesToList (takeExpressionsToList expr) (takeExpressionsToList expr) []) +1 )  
                            False 

changeCommonsCaller2 :: [ExprV] -> Int -> Bool -> [ExprV]
changeCommonsCaller2 lst 0 bool = lst
changeCommonsCaller2 lst num True = changeCommonsCaller2 (changeCommons lst lst 0) (num-1) True 
changeCommonsCaller2 (x:xs) num False = changeCommonsCaller2 (changeCommonsCaller x) (num-1) True

changeCommonsCaller :: ExprV -> [ExprV]
changeCommonsCaller expr = changeCommons (putDuplicatesToList (takeExpressionsToList expr) (takeExpressionsToList expr) []) 
                ( (putDuplicatesToList (takeExpressionsToList expr) (takeExpressionsToList expr) []) ++ [expr]) 0   


-- inject main expression at the end
changeCommons :: [ExprV] -> [ExprV] -> Int ->[ExprV]
changeCommons [] resultLst num = resultLst
changeCommons (x:xs) resultLst num = changeCommons xs (changeCommonsHelper x resultLst num num) (num+1)

changeCommonsHelper :: ExprV -> [ExprV] -> Int -> Int ->[ExprV]
changeCommonsHelper expr [] varNameNum passNum = []
changeCommonsHelper expr (x:xs) varNameNum passNum 
    | passNum >= 0 = [x] ++ changeCommonsHelper expr xs varNameNum (passNum-1)
    | otherwise = changeCommonsHelper2 expr x varNameNum ++ changeCommonsHelper expr xs varNameNum passNum  

changeCommonsHelper2 :: ExprV -> ExprV -> Int -> [ExprV]
changeCommonsHelper2 expr expr2 varNameNum = [changeCommonsHelper3 expr expr2 varNameNum]

changeCommonsHelper3 :: ExprV -> ExprV -> Int -> ExprV
changeCommonsHelper3 expr (Leaf value) varNameNum = (Leaf value)
changeCommonsHelper3 expr (UnaryOperation Minus expr2) varNameNum 
    | expr == (UnaryOperation Minus expr2) = (Leaf (Variable ("$" ++ show varNameNum)))
    | otherwise = (UnaryOperation Minus (changeCommonsHelper3 expr expr2 varNameNum))
changeCommonsHelper3 expr (BinaryOperation operation expr1 expr2) varNameNum
    | expr == (BinaryOperation operation expr1 expr2) = (Leaf (Variable ("$" ++ show varNameNum)))
    | otherwise = (BinaryOperation operation (changeCommonsHelper3 expr expr1 varNameNum) 
    	(changeCommonsHelper3 expr expr2 varNameNum))

takeExpressionsToList :: ExprV -> [ExprV]
takeExpressionsToList (Leaf value) = []
takeExpressionsToList (UnaryOperation Minus expr) = takeExpressionsToList expr ++ [(UnaryOperation Minus expr)] 
takeExpressionsToList (BinaryOperation operation expr1 expr2) = takeExpressionsToList expr1 ++ takeExpressionsToList expr2 
                                                              ++ [(BinaryOperation operation expr1 expr2)]

-- In given parameters, last element should be deleted
putDuplicatesToList :: [ExprV] -> [ExprV] -> [ExprV] -> [ExprV]
putDuplicatesToList [] lst resultLst = resultLst
putDuplicatesToList lst [] resultLst = resultLst
putDuplicatesToList (x1:xs1) (x2:xs2) resultLst = putDuplicatesToList xs1 xs2 (checkInSecondList x1 xs2 resultLst)

checkInSecondList :: ExprV -> [ExprV] -> [ExprV] -> [ExprV]
checkInSecondList expr [] resultLst = resultLst
checkInSecondList expr (x:xs) resultLst 
	| expr == x = checkInResultList expr resultLst resultLst
    | otherwise = checkInSecondList expr xs resultLst

checkInResultList :: ExprV -> [ExprV] -> [ExprV] -> [ExprV]
checkInResultList expr [] resultLst = resultLst ++ [expr]
checkInResultList expr (x:xs) resultLst
    | expr == x = resultLst
    | otherwise = checkInResultList expr xs resultLst


------------------------------------Reduce Polynomial-----------------------------------------------------------------------------------

reducePoly :: ExprV -> ExprV
reducePoly expr = reducePoly3 (reducePoly2 expr)

reducePoly3 :: ExprV -> ExprV
reducePoly3 (Leaf value) = (Leaf value)
reducePoly3 (UnaryOperation Minus (Leaf (Constant a))) = (Leaf (Constant (a*(-1))))
reducePoly3 (UnaryOperation Minus (Leaf (Variable a))) = (UnaryOperation Minus (Leaf (Variable a)))
reducePoly3 (UnaryOperation Minus expr) = (UnaryOperation Minus (reducePoly3 expr)) 
reducePoly3 (BinaryOperation operation left right) = (BinaryOperation operation (reducePoly3 left) (reducePoly3 right))

reducePoly2 :: ExprV -> ExprV
reducePoly2 expr = parse (takeLastPlusOperator (listToExpression (calculateConstants expr) (findVariableName expr) 0))


takeLastPlusOperator :: String -> String
takeLastPlusOperator str
    | (length str) > 0 = take ((length str) -1) str 
    | otherwise = str  

calculateConstants :: ExprV -> [Int]
calculateConstants (Leaf (Constant value)) = [value]
calculateConstants (Leaf (Variable var)) = [0,1]
calculateConstants (UnaryOperation Minus expr) = map (*(-1)) (calculateConstants expr)
calculateConstants (BinaryOperation Plus left right) = addTwoList (calculateConstants left) (calculateConstants right)
calculateConstants (BinaryOperation Times left right) = multiplyTwoList (calculateConstants left) (calculateConstants right) 0

addTwoList :: [Int] -> [Int] -> [Int]
addTwoList [] [] = []
addTwoList (x1:xs1) [] = [x1] ++ addTwoList xs1 []
addTwoList [] (x2:xs2) = [x2] ++ addTwoList [] xs2
addTwoList (x1:xs1) (x2:xs2) = [x1+x2] ++ addTwoList xs1 xs2 

multiplyTwoList :: [Int] -> [Int] -> Int -> [Int]
multiplyTwoList (x1:xs1) [] num = []
multiplyTwoList [] (x2:xs2) num = []
multiplyTwoList (x1:[]) (x2:xs2) num = generateZerosList num ++  map (*(x1)) (x2:xs2)
multiplyTwoList (x1:xs1) (x2:xs2) num = addTwoList (multiplyTwoList [x1] (x2:xs2) num ) (multiplyTwoList xs1 (x2:xs2) (num+1) )

generateZerosList :: Int -> [Int]
generateZerosList 0 = []
generateZerosList num = [0] ++ generateZerosList (num-1) 

findVariableName :: ExprV -> String
findVariableName (Leaf (Constant value)) = ""
findVariableName (Leaf (Variable var)) = var 
findVariableName (UnaryOperation Minus expr) = findVariableName expr
findVariableName (BinaryOperation operation left right) = if (findVariableName left) == ""
                                                          then (findVariableName right)
                                                          else (findVariableName left)

listToExpression :: [Int] -> String -> Int -> String
listToExpression [] str num = ""
listToExpression (x:xs) str num
    | x == 0 = listToExpression xs str (num+1)
    | x == 1 && num /= 0 = (getVariablesSecondForm str num) ++ "+" ++ listToExpression xs str (num+1)
    | x == -1 && num /= 0 = "-" ++ (getVariablesSecondForm str num) ++ "+" ++ listToExpression xs str (num+1)
    | otherwise = show x ++ (getVariables str num) ++ "+" ++ listToExpression xs str (num+1)

getVariables :: String -> Int -> String
getVariables str 0 = ""
getVariables str num = "*" ++ str ++ getVariables str (num-1) 

getVariablesSecondForm :: String -> Int -> String
getVariablesSecondForm str 0 = ""
getVariablesSecondForm str num = str ++ getVariables str (num-1) 

-- an extra dummy variable, so as to not crash the GUI
notImpl :: ExprV
notImpl = Leaf $ Variable "Not Implemented"

