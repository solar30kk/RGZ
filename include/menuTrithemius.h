#pragma once 

void menuTrithemius();

namespace MenuTrithemius {

    enum Type {
        EncryptionFile = 1,
        DecryptionFile = 2,
        EncryptionText = 3,
        DecryptionText = 4,
        TRITHEMIUS_EXIT = 0,
    };
}