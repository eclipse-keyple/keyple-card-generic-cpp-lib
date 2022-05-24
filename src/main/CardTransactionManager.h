/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <string>
#include <vector>

namespace keyple {
namespace card {
namespace generic {

/**
 * Provides basic methods to prepare and process APDU exchange with a card.
 */
class CardTransactionManager {
public:
    /**
     * 
     */
    virtual ~CardTransactionManager() = default;

    /**
     * Prepares an APDU to be transmitted the next time processApdusToByteArrays()} is
     * invoked.
     *
     * @param apduCommand A not empty hexadecimal string containing a raw APDU command.
     * @return This instance.
     * @since 2.0.0
     */
    virtual CardTransactionManager& prepareApdu(const std::string& apduCommand) = 0;

    /**
     * Prepares an APDU to be transmitted the next time processApdusToByteArrays() is
     * invoked.
     *
     * @param apduCommand A not empty const uint8_t arrays containing raw APDU commands.
     * @return This instance.
     * @since 2.0.0
     */
    virtual CardTransactionManager& prepareApdu(const std::vector<uint8_t>& apduCommand) = 0;

    /**
     * Prepares an APDU to be transmitted the next time processApdusToByteArrays() is
     * invoked.
     *
     * @param cla The class const uint8_t.
     * @param ins The instruction const uint8_t.
     * @param p1 The P1 parameter.
     * @param p2 The P2 parameter.
     * @param dataIn The APDU data, null if there is no data.
     * @param le The expected output length, 0 if the output length is unspecified, null if no
     *        output data is expected.
     * @return This instance.
     * @since 2.0.0
     */
    virtual CardTransactionManager& prepareApdu(const uint8_t cla, 
                                                const uint8_t ins, 
                                                const uint8_t p1, 
                                                const uint8_t p2, 
                                                const std::vector<uint8_t>& dataIn, 
                                                const uint8_t le) = 0;

    /**
     * Prepares an APDU to be transmitted the next time processApdusToByteArrays() is
     * invoked.
     *
     * @param cla The class const uint8_t.
     * @param ins The instruction const uint8_t.
     * @param p1 The P1 parameter.
     * @param p2 The P2 parameter.
     * @param dataIn The APDU data, null if there is no data.
     * 
     * @return This instance.
     * @since 2.0.0
     */
    virtual CardTransactionManager& prepareApdu(const uint8_t cla, 
                                                const uint8_t ins, 
                                                const uint8_t p1, 
                                                const uint8_t p2, 
                                                const std::vector<uint8_t>& dataIn) = 0;

    /**
     * Requests the closing of the physical channel after the next transmission of APDUs.
     *
     * @return This instance.
     * @since 2.0.0
     */
    virtual CardTransactionManager& prepareReleaseChannel() = 0;

    /**
     * Transmits all prepared APDUs, closes the physical channel if required, and returns a list of
     * responses to the APDUs in the form of list of of const uint8_t arrays.
     *
     * <p>If the prepared APDU list is empty an empty list is returned.
     *
     * <p>The prepared APDU list is cleared after this method has been invoked.
     *
     * @return A not null reference.
     * @throw TransactionException If the communication with the card or the reader has failed.
     */
    virtual const std::vector<std::vector<uint8_t>> processApdusToByteArrays() = 0;

    /**
     * Transmits all prepared APDUs, closes the physical channel if required, and returns a list of
     * responses to the APDUs in the form of list of hexadecimal strings.
     *
     * <p>If the prepared APDU list is empty an empty list is returned.
     *
     * <p>The prepared APDU list is cleared after this method has been invoked.
     *
     * @return A not null reference.
     * @throw TransactionException If the communication with the card or the reader has failed.
     */
    virtual const std::vector<std::string> processApdusToHexStrings() = 0;
};

}
}
}
