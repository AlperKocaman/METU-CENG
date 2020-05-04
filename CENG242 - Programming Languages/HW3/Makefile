LDFLAGS=-std=c++11

transaction: ; g++ $(LDFLAGS) transaction_test.cpp Transaction.cpp -o Test -ggdb3
account: ; g++ $(LDFLAGS) account_test.cpp Transaction.cpp Account.cpp -o Test -g
bank: ; g++ $(LDFLAGS) bank_test.cpp Transaction.cpp Account.cpp Bank.cpp -o Test
run: ;./Test
valgrind: ; valgrind --leak-check=full --show-leak-kinds=all ./Test
clean: ; rm -rf Test
