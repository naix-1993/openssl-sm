#include <stdio.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>

int main()
{
    int ret;
    ECDSA_SIG *sig;
    EC_KEY *eckey;

    eckey = EC_KEY_new_by_curve_name(NID_secp192k1);

    if(eckey == NULL)
    {
        printf("Create eckey failed.\n");
    }

    if(!EC_KEY_generate_key(eckey))
    {
        printf("Generate key failed.\n");
    }

    char digest[] = "51ea611e3d9a74b3cacbdcee8ed455dd002d54eb";

    sig = ECDSA_do_sign(digest, 20, eckey);
    if(sig == NULL)
    {
        printf("Compute ECDSA signature failed.\n");
    }

    ret = ECDSA_do_verify(digest, 20, sig, eckey);

    if(ret == -1)
    {
        printf("Verify failed.\n");
    } 
    else if(ret == 0) 
    {
        printf("Incorrect signature.\n");
    }
    else
    {
        printf("Correct signature.\n");
    }

    return 0;
}

