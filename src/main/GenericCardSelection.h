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

/* Calypsonet Terminal Reader */
#include "CardSelection.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::reader::selection::spi;

/**
 * Card specific {@link CardSelection} providing means to filter cards, select applications.
 *
 * @since 2.0.0
 */
class GenericCardSelection : public CardSelection {
public:
    /**
     * Navigation options through the different applications contained in the card according to the
     * ISO7816-4 standard.
     *
     * @since 2.0.0
     */
    enum class FileOccurrence {
        /**
         * First occurrence.
         *
         * @since 2.0.0
         */
        FIRST,

        /**
         * Last occurrence.
         *
         * @since 2.0.0
         */
        LAST,

        /**
         * Next occurrence.
         *
         * @since 2.0.0
         */
        NEXT,

        /**
         * Previous occurrence.
         *
         * @since 2.0.0
         */
        PREVIOUS
    };

    /**
     * Types of templates available in return for the Select Application command, according to the
     * ISO7816-4 standard.
     *
     * @since 2.0.0
     */
    enum class FileControlInformation {
        /**
         * File control information.
         *
         * @since 2.0.0
         */
        FCI,

        /**
         * File control parameters.
         *
         * @since 2.0.0
         */
        FCP,

        /**
         * File management data.
         *
         * @since 2.0.0
         */
        FMD,
        
        /**
         * No response expected.
         *
         * @since 2.0.0
         */
        NO_RESPONSE
    };

    /**
     * Requests a protocol-based filtering by defining an expected card.
     *
     * <p>If the card protocol is set, only cards using that protocol will match the card selector.
     *
     * @param cardProtocol A not empty String.
     * @return The current instance.
     * @throw IllegalArgumentException If the argument is null or empty.
     * @since 2.0.0
     */
    virtual GenericCardSelection& filterByCardProtocol(const std::string& cardProtocol) = 0;

    /**
     * Requests a power-on data-based filtering by defining a regular expression that will be
     * applied to the card's power-on data.
     *
     * <p>If it is set, only the cards whose power-on data is recognized by the provided regular
     * expression will match the card selector.
     *
     * @param powerOnDataRegex A valid regular expression
     * @return The current instance.
     * @throw IllegalArgumentException If the provided regular expression is null, empty or invalid.
     * @since 2.0.0
     */
    virtual GenericCardSelection& filterByPowerOnData(const std::string& powerOnDataRegex) = 0;

    /**
     * Requests a DF Name-based filtering by defining in a byte array the AID that will be included
     * in the standard SELECT APPLICATION command sent to the card during the selection process.
     *
     * <p>The provided AID can be a right truncated image of the target DF Name
     * (see ISO 7816-4 4.2).
     *
     * @param aid A byte array containing 5 to 16 bytes.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided array is null or out of range.
     * @since 2.0.0
     */
    virtual GenericCardSelection& filterByDfName(const std::vector<uint8_t>& aid) = 0;

    /**
     * Requests a DF Name-based filtering by defining in a hexadecimal string the AID that will be
     * included in the standard SELECT APPLICATION command sent to the card during the selection
     * process.
     *
     * <p>The provided AID can be a right truncated image of the target DF Name 
     * (see ISO 7816-4 4.2).
     *
     * @param aid A hexadecimal string representation of 5 to 16 bytes.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided AID is null, invalid or out of range.
     * @since 2.0.0
     */
    virtual GenericCardSelection& filterByDfName(const std::string& aid) = 0;

    /**
     * Sets the file occurrence mode (see ISO7816-4).
     *
     * <p>The default value is {@link GenericCardSelection.FileOccurrence#FIRST}.
     *
     * @param fileOccurrence The {@link GenericCardSelection.FileOccurrence}.
     * @return The current instance.
     * @throw IllegalArgumentException If fileOccurrence is null.
     * @since 2.0.0
     */
    virtual GenericCardSelection& setFileOccurrence(const FileOccurrence fileOccurrence) = 0;

    /**
     * Sets the file control mode (see ISO7816-4).
     *
     * <p>The default value is {@link GenericCardSelection.FileControlInformation#FCI}.
     *
     * @param fileControlInformation The {@link GenericCardSelection.FileControlInformation}.
     * @return The current instance.
     * @throw IllegalArgumentException If fileControlInformation is null.
     * @since 2.0.0
     */
    virtual GenericCardSelection& setFileControlInformation(
        const FileControlInformation fileControlInformation) = 0;

    /**
     * Adds a status word to the list of those that should be considered successful for the Select
     * Application APDU.
     *
     * <p>Note: initially, the list contains the standard successful status word {@code 9000h}.
     *
     * @param statusWord A positive int &le; {@code FFFFh}.
     * @return The current instance.
     * @since 2.0.0
     */
    virtual GenericCardSelection& addSuccessfulStatusWord(const int statusWord) = 0;
};

}
}
}
