#pragma once 

void menuAtbash();

namespace MenuAtbash {

    enum Type {
        EncryptionFile = 1,
        DecryptionFile = 2,
        EncryptionText = 3,
        DecryptionText = 4,
        ATBASH_EXIT = 0,
    };
}