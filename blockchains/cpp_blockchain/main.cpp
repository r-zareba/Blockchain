#include <iostream>
//#include <utility>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <map>

//#include "Block.h"

#include "cryptography.h"
#include "Transactions.h"
#include "UtxoSet.h"



#include <ctime>


class TestClass {
public:
    TestClass(int x, int y) : x(x), y(y) {};
//    TestClass() = default;

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

    void setX(int x_) {
        x = x_;
    }

private:
    int x;
    int y;
    void someFunc(int x) {
        this->x += x;
    }

};


int main() {


    // Simulation of transactions

    UtxoSet utxoSet;



    auto [minerPrivateKey, minerPublicKey] = cryptography::generateKeys();

    auto [privateKey2, publiKey2] = cryptography::generateKeys();
    auto [privateKey3, publiKey3] = cryptography::generateKeys();

    std::string minerAddress = cryptography::generateAddress(minerPublicKey);
    std::string address2 = cryptography::generateAddress(publiKey2);
    std::string address3 = cryptography::generateAddress(publiKey3);

    Transaction coinBaseTransaction = Transaction::generateCoinBase(100, minerAddress);
    std::string coinbaseHashStr = cryptography::sha256HashToStr(coinBaseTransaction.getHash());

//    transactions[coinbaseHashStr] = coinBaseTransaction;

    // Every transaction represents a state change in UTXO !
//    std::cout << utxoSet.getSize();
    utxoSet.update(coinBaseTransaction);
//    std::cout << '\n' << utxoSet.getSize();
//    std::cout << "..." << utxoSet.getTotal();



//     Miner Creates Output to user2 - sends 50 satoshis
    Output output{50, address2};

    Sha256Hash prevHash = coinBaseTransaction.getHash();
    Input input{prevHash, 0};
    Transaction transaction{{input}, {output}, 0, 0};
    transaction.sign(minerPrivateKey);


//     Check if miner is able to spend that output
    bool isSpendable = transaction.verify(0, utxoSet);
    std::cout << "Is spendable: " << isSpendable;

    if (isSpendable)
        utxoSet.update(transaction);

    std::cout << '\n' << utxoSet.getSize();
    std::cout << "..." << utxoSet.getTotal();
    std::cout << '\n';



    std::string s = "scott_10";
    int pos = s.find_first_of('_');
    std::string firstname = s.substr(0, pos);
    int x = std::stoi(s.substr(pos+1));

//    int id = std::stoi(lastname);
    std::cout << '\n' << firstname;
    std::cout << '\n' << x;

    Sha256Hash a = cryptography::sha256(125, "asd");
    std::string aString = cryptography::sha256HashToStr(a);

    std::cout << aString << '\n';

    Sha256Hash b = cryptography::hashStrToSha256(aString);

    std::cout << '\n';
    std::cout << "Is Equal: " << (a == b);








//    for (size_t i=0; i<size; ++i)
//        std::cout << std::setfill('0') << std::hex << au.value[i];


//    Sha256Hash b = cryptography::sha256(125, "asd");
//
//    std::string s1 = cryptography::sha256HashToStr(a);
//    Sha256Hash h1{s1.c_str()};
//

    return 0;
}