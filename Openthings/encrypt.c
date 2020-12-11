#include <stdint.h>
#include <stddef.h>

/* Static variable maintaining the value of the linear shift random number
 * generator for the next transmission or reception. */
static uint16_t random;

void randomise_seed( uint16_t noise )
{
    random = random ^ noise;
    if ( random == 0 ) {
        random = 1; /* the seed must not be zero */
    }
}

uint8_t encrypt_decrypt( uint8_t data )
{
    size_t i;
    for ( i = 0; i < 5; ++i ) {
        random = ( random & 1 ) ? ( ( random >> 1 ) ^ 62965U )
                                : ( random >> 1 );
    }
    return ( uint8_t )( random ^ data ^ 90U );
}

uint16_t generate_pip( uint8_t encryptionid )
{
    return ( random ^ ( ( (uint16_t)encryptionid ) << 8 ) );
}

void seed( uint8_t encryptionid, uint16_t pip )
{
    random = ( ( ( (uint16_t)encryptionid ) << 8 ) ^ pip );
}
