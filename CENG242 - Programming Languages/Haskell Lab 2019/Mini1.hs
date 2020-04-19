module Mini1 (
    gridMap,
    gridMapIf,
    evalExpr,
    getVars,
    evalDeriv,
    parse -- reexported to allow use
    ) where

import Expression
import Parser

-- Do not modify the module declaration and imports above!
-- Also do not change the function signatures and do not
-- remove the dummy implementations of the functions if
-- you want your code to compile.

-- Feel free to import anything else here

import Data.List

-- gridMap (20 points), map function over grid elements
gridMap :: (a -> b) -> [[a]] -> [[b]]
gridMap function [] = []
gridMap function (x:xs) = gridMapHelper function x ++ gridMap function xs

gridMapHelper :: (a -> b) -> [a] -> [[b]]
gridMapHelper function lst = [(map function lst)]

-- gridMapIf (20 points), map functions over grid elements 
-- that satisfy the predicate provided as the first arg.
gridMapIf :: (a -> Bool) -> (a -> a) -> [[a]] -> [[a]]
gridMapIf predicate function [] = []
gridMapIf predicate function (x:xs) = [gridMapIfHelper predicate function x] ++ gridMapIf predicate function xs

gridMapIfHelper :: (a -> Bool) -> (a -> a) -> [a] -> [a]
gridMapIfHelper predicate function [] = []
gridMapIfHelper predicate function (x:xs) 
    | map predicate [x] == [True] = map function [x] ++ gridMapIfHelper predicate function xs
    | otherwise = [x] ++ gridMapIfHelper predicate function xs 

-- evalExpr (20 points), evaluate the expression by
-- substituting (var, value) pairs given in the first arg.
evalExpr :: [(String, Int)] -> ExprV -> Int
evalExpr lst (Leaf (Constant value)) = value
evalExpr lst (Leaf (Variable var))  = evalExprHelper lst var 
evalExpr lst (UnaryOperation Minus expr) = (-1) * (evalExpr lst expr)
evalExpr lst (BinaryOperation Plus left right) = (evalExpr lst left) + (evalExpr lst right)
evalExpr lst (BinaryOperation Times left right) = (evalExpr lst left) * (evalExpr lst right)

evalExprHelper :: [(String, Int)] -> String ->Int
evalExprHelper ((str, value):xs) var 
    | str == var = value
    | otherwise = evalExprHelper xs var 

-- getVars (20 points), return the variables contained
-- in the expression in a list (ordered, no duplicates)
getVars :: ExprV -> [String]
getVars expr = eliminateDuplicates (sort (getVarsHelper expr []) )

eliminateDuplicates :: [String] -> [String]
eliminateDuplicates [] = []
eliminateDuplicates (x:[]) = [x]
eliminateDuplicates (x:y:[])
    | x == y = [y]
    | otherwise = [x] ++ [y]
eliminateDuplicates (x:y:xs)
    | x == y = eliminateDuplicates (y:xs)
    | otherwise = [x] ++ eliminateDuplicates (y:xs)

getVarsHelper :: ExprV -> [String] -> [String]
getVarsHelper (Leaf (Constant value)) lst = lst
getVarsHelper (Leaf (Variable var)) lst = lst ++ [var]
getVarsHelper (UnaryOperation Minus expr) lst = getVarsHelper expr lst
getVarsHelper (BinaryOperation operation left right) lst = (getVarsHelper left lst) ++ (getVarsHelper right lst)


-- evalDeriv (20 points), evaluate the first derivative
-- with respect to the variable given in the second
-- arg. using (var, value) pairs given in the first arg.
evalDeriv :: [(String, Int)] -> String -> ExprV -> Int
evalDeriv lst derivVar (Leaf (Constant value)) = 0
evalDeriv lst derivVar (Leaf (Variable var)) = if var == derivVar 
                                               then 1
                                               else 0
evalDeriv lst derivVar (UnaryOperation Minus expr) = (-1) * (evalDeriv lst derivVar expr)
evalDeriv lst derivVar (BinaryOperation Plus left right) = (evalDeriv lst derivVar left) + (evalDeriv lst derivVar right)
evalDeriv lst derivVar (BinaryOperation Times left right)
                                        = (evalDeriv lst derivVar left)*(evalExpr lst right)  
                                        + (evalDeriv lst derivVar right)*(evalExpr lst left)

-- Looks like that's all! 