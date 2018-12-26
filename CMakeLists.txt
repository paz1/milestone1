cmake_minimum_required(VERSION 3.12)
project(milestone1)

##set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
add_executable(milestone1 main.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h PrintCommand.cpp PrintCommand.h LoopCommand.cpp LoopCommand.h Reader.cpp Reader.h IfCommand.cpp IfCommand.h CommandExpression.cpp CommandExpression.h Expression.h DefineVarCommand.cpp DefineVarCommand.h SymbolTable.cpp SymbolTable.h BinaryExpression.cpp BinaryExpression.h Minus.cpp Minus.h Mult.cpp Mult.h Number.cpp Number.h Plus.cpp Plus.h Div.cpp Div.h SleepCommand.cpp SleepCommand.h Setter.cpp Setter.h ConditionParser.cpp ConditionParser.h ExpressionCreator.cpp ExpressionCreator.h)