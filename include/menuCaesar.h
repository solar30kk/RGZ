#pragma once 

void menuCaesar();

namespace MenuCaesar {

    enum Type {
        EncryptionFile = 1,
        DecryptionFile = 2,
        EncryptionText = 3,
        DecryptionText = 4,
        CAESAR_EXIT = 0,
    };
}