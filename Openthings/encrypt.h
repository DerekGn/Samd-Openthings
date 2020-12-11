#ifndef ENCRYPT_H_
#define ENCRYPT_H_

/**
 * \brief Function to randomise the seed
 * 
 * \param noise The noise
 * 
 * \return void
 */
void randomise_seed(uint16_t noise);

/**
 * \brief Function to generate the pip to be sent in an encrypted transmitted message, based on the current seed and encryption id, the encryption id
 * 
 * \param[in] encryptionid The encryption id to use for pip generation.
 * 
 * \return uint16_t The generated pip
 */
uint16_t generate_pip(uint8_t encryptionid);

/**
 * \brief Function to update the seed to match the pip received in the message.
 * 
 * \param[in] encryptionid The encryption id to use for pip generation.
 * \param pip The pip from the message
 * 
 * \return void
 */
void seed(uint8_t encryptionid, uint16_t pip);

/**
 * \brief Function to encrypt or decrypt the next byte of data in the stream.
 * 
 * \param[in] data The data byte to encrypt.
 * 
 * \return uint8_t The encrypted value.
 */
uint8_t encrypt_decrypt(uint8_t data);

#endif /* ENCRYPT_H_ */