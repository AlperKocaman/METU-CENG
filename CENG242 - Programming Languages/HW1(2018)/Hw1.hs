module Hw1 where

type Mapping = [(String, String, String)]
data AST = EmptyAST | ASTNode String AST AST deriving (Show, Read)

writeExpression :: (AST, Mapping) -> String
evaluateAST :: (AST, Mapping) -> (AST, String)
-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT writeExpression and evaluateAST FUNCTION ACCORDING TO GIVEN SIGNATURES --

writeExpression ( ast , mapping ) = mapping_helper2 mapping ++ ast_helper ast

mapping_helper2 :: Mapping ->String
mapping_helper2 [] = "" 
mapping_helper2 mapping = "Let " ++ mapping_helper mapping ++ " in "

mapping_helper :: Mapping -> String
mapping_helper  []  = ""
mapping_helper [(x1 , x2 , x3)] 
    | x2 == "num" = x1 ++ "="++ x3
    | x2 == "str" = x1 ++ "=\"" ++ x3 ++ "\""

mapping_helper (x : xs)   = mapping_helper [x] ++ ";" ++ mapping_helper xs
 
ast_helper :: AST -> String 
ast_helper EmptyAST = []
ast_helper ast = ast_helper2 ast

ast_helper2 :: AST -> String
ast_helper2 EmptyAST = ""
ast_helper2 (ASTNode x first second) 
    | x == "plus"    = "("++ ast_helper2 first ++"+"++ ast_helper2 second++")" 
    | x == "times"   = "("++ast_helper2 first ++"*"++ ast_helper2 second++")"
    | x == "negate"  = "("++"-"++ ast_helper2 first ++ ast_helper2 second++")"
    | x == "cat"     = "("++ast_helper2 first ++"++"++ ast_helper2 second++")"
    | x == "len"     = "("++"length "++ast_helper2 first ++ ast_helper2 second++")"
    | x == "num"     = ast_helper2 first ++ ast_helper2 second
    | x == "str"     = "\""++ast_helper2 first ++ "\"" ++ ast_helper2 second
    | otherwise      = ast_helper2 first ++x++ ast_helper2 second

evaluateAST ( ast , mapping ) = (ast_1 (ast , mapping)  , eval2 (ast , mapping))

ast_1 :: (AST , Mapping ) -> AST
ast_1 (ast , [])  = ast
ast_1 ( EmptyAST , mapping ) = EmptyAST
ast_1 ((ASTNode x left right) , (xf:xs) ) = ast_1( (ast_1_helper((ASTNode x left right) , [xf])) , xs ) 

ast_1_helper :: (AST , Mapping ) -> AST
ast_1_helper (EmptyAST , [(x1 , x2 , x3)]) = EmptyAST 
ast_1_helper ((ASTNode x left right) , [(x1 , x2 , x3)])
    | x == x1   = ASTNode x2 (ASTNode x3 EmptyAST EmptyAST) (ast_1_helper(right , [(x1 , x2 , x3)]))
    | otherwise = ASTNode x (ast_1_helper(left , [(x1 , x2 , x3)])) (ast_1_helper(right , [(x1 , x2 , x3)])) 

eval2:: (AST , Mapping ) -> String
eval2 (ast , mapping) = eval( ast_1(ast , mapping) )

eval :: AST -> String 
eval EmptyAST = ""
eval (ASTNode x first second)
    | x == "plus"    = show((read (eval(first))::Integer) + (read (eval(second))::Integer)) 
    | x == "times"   = show((read (eval(first))::Integer) * (read (eval(second))::Integer)) 
    | x == "negate"  = show((read (eval(first))::Integer) * (-1))
    | x == "cat"     = eval(first) ++ eval(second)
    | x == "len"     = show(length(eval(first)))
    | x == "num"     = eval(first)
    | x == "str"     = eval(first)
    | otherwise      = x
 